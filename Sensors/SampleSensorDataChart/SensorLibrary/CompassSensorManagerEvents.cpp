//-----------------------------------------------------------------------------
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
// Copyright(C) Seiko Epson Corporation 2019. All rights reserved.
//
// Module:
//        CompassSensorManagerEvents.cpp
//
// Description:
//        Implementation of ISensorManagerEvents
//
// Comments: 
//        This is a standard c++ class, but needs to support IUnknown methods
//        to be properly implemented.  This class overrides 
//        ISensorManagerEvents functions to receive updated information from
//        the Sensors API when it is published.
//
//-----------------------------------------------------------------------------

#include "pch.h"
#include "Resource.h"
#include "CompassSensorManagerEvents.h"
#include "CompassSensorEvents.h"

///////////////////////////////////////////////////////////////////////////////
//
// CompassSensorManagerEvents::CompassSensorManagerEvents
//
// Description of function/method:
//        Constructor.
//
// Parameters:
//        CompassSensorCallback callback: callback for notifying sensor value
//
// Return Values:
//        None
//
///////////////////////////////////////////////////////////////////////////////
CompassSensorManagerEvents::CompassSensorManagerEvents(CompassSensorCallback callback)
{
	m_lRefCount = 1; //ref count initialized to 1
	m_pSensorEvents = new CompassSensorEvents(this, callback);
}

///////////////////////////////////////////////////////////////////////////////
//
// CompassSensorManagerEvents::~CompassSensorManagerEvents
//
// Description of function/method:
//        Destructor. Clean up stored data.
//
// Parameters:
//        none
//
// Return Values:
//        None
//
///////////////////////////////////////////////////////////////////////////////
CompassSensorManagerEvents::~CompassSensorManagerEvents()
{
	if (NULL != m_pSensorEvents)
	{
		delete m_pSensorEvents;
		m_pSensorEvents = NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// CompassSensorManagerEvents::QueryInterface
//
// Description of function/method:
//        IUnknown method, need to implement to support COM classes that
//        are inherited.
//
// Parameters:
//        REFIID riid:     Input. ID of the interface being requested. Either
//                         IUnknown or one of the two classes we inherit.
//        void** ppObject: Output. Address of pointer variable that receives
//                         the interface pointer requested in riid. Upon 
//                         successful return, *ppvObject contains the requested
//                         interface pointer to the object. If the object does
//                         not support the interface specified in iid,
//                         *ppvObject is set to NULL.
//
// Return Values:
//        S_OK on success, else E_NOINTERFACE
//
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CompassSensorManagerEvents::QueryInterface(REFIID riid, void** ppObject)
{
	HRESULT hr = S_OK;

	*ppObject = NULL;
	if (riid == __uuidof(ISensorManagerEvents))
	{
		*ppObject = reinterpret_cast<ISensorManagerEvents*>(this);
	}
	else if (riid == IID_IUnknown)
	{
		*ppObject = reinterpret_cast<IUnknown*>(this);
	}
	else
	{
		hr = E_NOINTERFACE;
	}

	if (SUCCEEDED(hr))
	{
		(reinterpret_cast<IUnknown*>(*ppObject))->AddRef();
	}

	return hr;
}

///////////////////////////////////////////////////////////////////////////////
//
// CompassSensorManagerEvents::AddRef
//
// Description of function/method:
//        Increments the reference count for an interface on an object.
//
// Parameters:
//        none
//
// Return Values:
//        Returns an integer from 1 to n, the value of the new reference count.
//
///////////////////////////////////////////////////////////////////////////////
ULONG _stdcall CompassSensorManagerEvents::AddRef()
{
	m_lRefCount++;
	return m_lRefCount;
}

///////////////////////////////////////////////////////////////////////////////
//
// CompassSensorManagerEvents::Release
//
// Description of function/method:
//        Decrements the reference count for the calling interface on a object.
//        If the reference count on the object falls to 0, the object is freed
//        from memory.
//
// Parameters:
//        none
//
// Return Values:
//        Returns an integer from 1 to n, the value of the new reference count.
//
///////////////////////////////////////////////////////////////////////////////
ULONG _stdcall CompassSensorManagerEvents::Release()
{
	ULONG lRet = --m_lRefCount;

	if (m_lRefCount == 0)
	{
		delete this;
	}

	return lRet;
}

///////////////////////////////////////////////////////////////////////////////
//
// CompassSensorManagerEvents::Initialize
//
// Description of function/method:
//        Initialize the sensor data.
//
// Parameters:
//        none
//
// Return Values:
//        HRESULT S_OK on success
//
///////////////////////////////////////////////////////////////////////////////
HRESULT CompassSensorManagerEvents::Initialize()
{
	HRESULT hr;

	hr = m_spISensorManager.CoCreateInstance(CLSID_SensorManager);
	if (SUCCEEDED(hr))
	{
		hr = m_spISensorManager->SetEventSink(this);
		if (SUCCEEDED(hr))
		{
			// Find all Compass Sensors
			CComPtr<ISensorCollection> spSensors;
			hr = m_spISensorManager->GetSensorsByType(SENSOR_TYPE_COMPASS_3D, &spSensors);
			if (SUCCEEDED(hr) && NULL != spSensors)
			{
				ULONG ulCount = 0;
				hr = spSensors->GetCount(&ulCount);
				if (SUCCEEDED(hr))
				{
					for (ULONG i = 0; i < ulCount; i++)
					{
						CComPtr<ISensor> spSensor;
						hr = spSensors->GetAt(i, &spSensor);
						if (SUCCEEDED(hr))
						{
							if (SUCCEEDED(IsMoverio(spSensor)))
							{
								hr = AddSensor(spSensor);
								if (SUCCEEDED(hr))
								{
									hr = m_pSensorEvents->GetSensorData(spSensor);
								}
							}
						}
					}
				}
			}
		}
	}

	return hr;
}

///////////////////////////////////////////////////////////////////////////////
//
// CompassSensorManagerEvents::Uninitialize
//
// Description of function/method:
//        Uninitialize the sensor data.
//
// Parameters:
//        none
//
// Return Values:
//        HRESULT S_OK on success
//
///////////////////////////////////////////////////////////////////////////////
HRESULT CompassSensorManagerEvents::Uninitialize()
{
	HRESULT hr = S_OK;

	POSITION pos = m_Sensors.GetStartPosition();
	while (NULL != pos)
	{
		ISensor* pSensor = m_Sensors.GetNextValue(pos);
		RemoveSensor(pSensor);
	}

	if (NULL != m_spISensorManager)
	{
		hr = m_spISensorManager->SetEventSink(NULL);
		if (SUCCEEDED(hr))
		{
			m_spISensorManager.Release();
		}
	}

	return hr;
}

///////////////////////////////////////////////////////////////////////////////
//
// CompassSensorManagerEvents::OnSensorEnter
//
// Description of function/method:
//        Implementation of ISensorManager.OnSensorEnter. Check if the sensor
//        is an Compass Sensor and if so then add the sensor.
//
// Parameters:
//        ISensor* pSensor:  Sensor that has been installed
//        SensorState state: State of the sensor
//
// Return Values:
//        S_OK on success, else an error.
//
///////////////////////////////////////////////////////////////////////////////
HRESULT CompassSensorManagerEvents::OnSensorEnter(__RPC__in_opt ISensor* pSensor, SensorState state)
{
	HRESULT hr = S_OK;

	if (NULL != pSensor)
	{
		SENSOR_TYPE_ID idType = GUID_NULL;
		hr = pSensor->GetType(&idType);
		if (SUCCEEDED(hr))
		{
			if (IsEqualIID(idType, SENSOR_TYPE_COMPASS_3D))
			{
				if (SUCCEEDED(IsMoverio(pSensor)))
				{
					hr = AddSensor(pSensor);
					if (SUCCEEDED(hr))
					{
						if (SENSOR_STATE_READY == state)
						{
							hr = m_pSensorEvents->GetSensorData(pSensor);
						}
					}
				}
			}
		}
	}
	else
	{
		hr = E_POINTER;
	}

	return hr;
}

///////////////////////////////////////////////////////////////////////////////
//
// CompassSensorManagerEvents::AddSensor
//
// Description of function/method:
//        Helper function, sets up event sinking for a sensor and saves the
//        sensor.
//
// Parameters:
//        ISensor *pSensor: Input sensor
//
// Return Values:
//        S_OK on success, else an error
//
///////////////////////////////////////////////////////////////////////////////
HRESULT CompassSensorManagerEvents::AddSensor(ISensor* pSensor)
{
	HRESULT hr = S_OK;

	if (NULL != pSensor)
	{
		hr = pSensor->SetEventSink(m_pSensorEvents);
		if (SUCCEEDED(hr))
		{
			// Get the sensor's ID to be used as a key to store the sensor
			SENSOR_ID idSensor = GUID_NULL;
			hr = pSensor->GetID(&idSensor);
			if (SUCCEEDED(hr))
			{
				// Remove sensors from the map to handle only one sensor
				POSITION pos = m_Sensors.GetStartPosition();
				while (NULL != pos)
				{
					ISensor* pSensor = m_Sensors.GetNextValue(pos);
					RemoveSensor(pSensor);
				}

				// Enter the sensor into the map and take the ownership of its lifetime
				pSensor->AddRef(); // the sensor is released in the destructor
				m_Sensors[idSensor] = pSensor;
			}
		}
	}
	else
	{
		hr = E_POINTER;
	}

	return hr;
}

///////////////////////////////////////////////////////////////////////////////
//
// CompassSensorManagerEvents::RemoveSensor
//
// Description of function/method:
//        Helper function, clears the event sink for the sensor and then
//        releases the sensor.
//
// Parameters:
//        ISensor *pSensor: Input sensor
//
// Return Values:
//        S_OK on success, else an error
//
///////////////////////////////////////////////////////////////////////////////
HRESULT CompassSensorManagerEvents::RemoveSensor(ISensor* pSensor)
{
	HRESULT hr = S_OK;

	// Release the event and ISensor objecets
	if (NULL != pSensor)
	{
		hr = pSensor->SetEventSink(NULL); // This also decreases the ref count of the sink object.

		SENSOR_ID idSensor = GUID_NULL;
		hr = pSensor->GetID(&idSensor);
		if (SUCCEEDED(hr))
		{
			m_Sensors.RemoveKey(idSensor);
		}

		pSensor->Release();
	}
	else
	{
		hr = E_POINTER;
	}

	return hr;
}

///////////////////////////////////////////////////////////////////////////////
//
// CompassSensorManagerEvents::RemoveSensor
//
// Description of function/method:
//        Helper function, clears the event sink for the sensor and then
//        releases the sensor.
//
// Parameters:
//        REFSENSOR_ID sensorID: Input sensor
//
// Return Values:
//        S_OK on success, else an error
//
///////////////////////////////////////////////////////////////////////////////
HRESULT CompassSensorManagerEvents::RemoveSensor(REFSENSOR_ID sensorID)
{
	HRESULT hr = S_OK;

	if (m_Sensors.Lookup(sensorID))
	{
		ISensor* pSensor = m_Sensors[sensorID];
		m_Sensors.RemoveKey(sensorID);
		pSensor->Release();
	}
	else
	{
		hr = HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
	}

	return hr;
}

///////////////////////////////////////////////////////////////////////////////
//
// CompassSensorManagerEvents::IsMoverio
//
// Description of function/method:
//        Helper function, check if the sensor is Moverio
//
// Parameters:
//        REFSENSOR_ID sensorID: Sensor
//
// Return Values:
//        S_OK on success, else an error
//
///////////////////////////////////////////////////////////////////////////////
HRESULT CompassSensorManagerEvents::IsMoverio(ISensor* pSensor)
{
	const BSTR SupportMoverios[] =
	{
		L"VID_0483",	// BT-35E
		L"VID_04B8"		// BT-30C
	};

	HRESULT hr = E_FAIL;
	PROPVARIANT pvDevice;
	PropVariantInit(&pvDevice);
	pSensor->GetProperty(SENSOR_PROPERTY_DEVICE_PATH, &pvDevice);

	for (DWORD dwIndex = 0; dwIndex < ARRAYSIZE(SupportMoverios); dwIndex++)
	{
		if (NULL != wcsstr(pvDevice.bstrVal, SupportMoverios[dwIndex]))
		{
			hr = S_OK;
		}
	}

	PropVariantClear(&pvDevice);
	return hr;
}
