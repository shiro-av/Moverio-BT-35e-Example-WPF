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
//        AmbientLightAwareSensorEvents.cpp
//
// Description:
//        Implementation of ISensorManagerEvents
//
// Comments: 
//        This is a standard c++ class, but needs to support IUnknown methods
//        to be properly implemented.  This class overrides ISensorEvents 
//        functions to receive updated information from the Sensors API when it
//        is published.
//
//-----------------------------------------------------------------------------

#include "pch.h"
#include "Resource.h"
#include "AmbientLightAwareSensorEvents.h"
#include "AmbientLightAwareSensorManagerEvents.h"

///////////////////////////////////////////////////////////////////////////////
//
// AmbientLightAwareSensorEvents::AmbientLightAwareSensorEvents
//
// Description of function/method:
//        Constructor.
//
// Parameters:
//        AmbientLightAwareSensorManagerEvents* sensorManagerEvents:
//            Parent class for callbacks
//        LightSensorCallback callback: callback for notifying sensor value
//
// Return Values:
//        None
//
///////////////////////////////////////////////////////////////////////////////
AmbientLightAwareSensorEvents::AmbientLightAwareSensorEvents(AmbientLightAwareSensorManagerEvents* sensorManagerEvents, LightSensorCallback callback)
{
	m_lRefCount = 1; //ref count initialized to 1
	m_pSensorManagerEvents = sensorManagerEvents;
	m_Callback = callback;
}

///////////////////////////////////////////////////////////////////////////////
//
// AmbientLightAwareSensorEvents::~AmbientLightAwareSensorEvents
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
AmbientLightAwareSensorEvents::~AmbientLightAwareSensorEvents()
{
}

///////////////////////////////////////////////////////////////////////////////
//
// AmbientLightAwareSensorEvents::QueryInterface
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
STDMETHODIMP AmbientLightAwareSensorEvents::QueryInterface(REFIID riid, void** ppObject)
{
	HRESULT hr = S_OK;

	*ppObject = NULL;
	if (riid == __uuidof(ISensorEvents))
	{
		*ppObject = reinterpret_cast<ISensorEvents*>(this);
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
// AmbientLightAwareSensorEvents::AddRef
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
ULONG _stdcall AmbientLightAwareSensorEvents::AddRef()
{
	m_lRefCount++;
	return m_lRefCount;
}

///////////////////////////////////////////////////////////////////////////////
//
// AmbientLightAwareSensorEvents::Release
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
ULONG _stdcall AmbientLightAwareSensorEvents::Release()
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
// AmbientLightAwareSensorEvents::OnStateChanged
//
// Description of function/method:
//        Implementation of ISensor.OnStateChanged. Called when permissions of
//        the sensor have changed, such as the sensor being disabled in control
//        panel. If the sensor is not SENSOR_STATE_READY then its lux value
//        should be ignored.
//
// Parameters:
//        ISensor* pSensor:  Sensor that has changed
//        SensorState state: State of the sensor
//
// Return Values:
//        S_OK
//
///////////////////////////////////////////////////////////////////////////////
HRESULT AmbientLightAwareSensorEvents::OnStateChanged(__RPC__in_opt ISensor* pSensor, SensorState state)
{
	HRESULT hr = S_OK;

	if (NULL != pSensor)
	{
		SENSOR_ID idSensor = GUID_NULL;
		hr = pSensor->GetID(&idSensor);
		if (SUCCEEDED(hr))
		{
			if (SENSOR_STATE_READY == state)
			{
				hr = GetSensorData(pSensor);
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
// AmbientLightAwareSensorEvents::OnDataUpdated
//
// Description of function/method:
//        Implementation of ISensor.OnDataUpdated.  Called when the sensor has
//        published new data.  This reads in the lux value from the report.
//
// Parameters:
//        ISensor* pSensor:            Sensor that has updated data.
//        ISensorDataReport *pNewData: New data to be read
//
// Return Values:
//        S_OK on success, else an error
//
///////////////////////////////////////////////////////////////////////////////
HRESULT AmbientLightAwareSensorEvents::OnDataUpdated(__RPC__in_opt ISensor* pSensor, __RPC__in_opt ISensorDataReport* pNewData)
{
	HRESULT hr = S_OK;

	if ((NULL != pSensor) && (NULL != pNewData))
	{
		hr = GetSensorData(pSensor, pNewData);
	}
	else
	{
		hr = E_UNEXPECTED;
	}

	return hr;
}

///////////////////////////////////////////////////////////////////////////////
//
// AmbientLightAwareSensorEvents::OnEvent
//
// Description of function/method:
//        Implementation of ISensor.OnEevent, a generic or custom sensor event.
//        OnDataUpdated is the event this sample uses to get sensor
//        information.
//
// Parameters:
//        ISensor* pSensor:                  Sensor that has the event.
//        GUID& eventID:                     Type of event.
//        IPortableDeviceValues *pEventData: Data to be read.
//
// Return Values:
//        S_OK
//
///////////////////////////////////////////////////////////////////////////////
HRESULT AmbientLightAwareSensorEvents::OnEvent(__RPC__in_opt ISensor* /*pSensor*/, __RPC__in REFGUID /*eventID*/, __RPC__in_opt IPortableDeviceValues* /*pEventData*/)
{
	// Not implemented
	return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////////
//
// AmbientLightAwareSensorEvents::OnLeave
//
// Description of function/method:
//        Implementation of ISensor.OnLeave.  This sensor is being removed, so
//        it needs to be deleted and freed.
//
// Parameters:
//        REFSENSOR_ID sensorID: 
//
// Return Values:
//        S_OK
//
///////////////////////////////////////////////////////////////////////////////
HRESULT AmbientLightAwareSensorEvents::OnLeave(__RPC__in REFSENSOR_ID sensorID)
{
	HRESULT hr = S_OK;

	hr = m_pSensorManagerEvents->RemoveSensor(sensorID); // Callback into parent

	return hr;
}

///////////////////////////////////////////////////////////////////////////////
//
// AmbientLightAwareSensorEvents::GetSensorData
//
// Description of function/method:
//        Helper function, get data from a sensor and updates the lux
//
// Parameters:
//        ISensor* pSensor: Input sensor
//
// Return Values:
//        S_OK on success, else an error
//
///////////////////////////////////////////////////////////////////////////////
HRESULT AmbientLightAwareSensorEvents::GetSensorData(ISensor* pSensor)
{
	HRESULT hr = S_OK;

	if (NULL != pSensor)
	{
		CComPtr<ISensorDataReport> spDataReport;
		hr = pSensor->GetData(&spDataReport);
		if (SUCCEEDED(hr))
		{
			hr = GetSensorData(pSensor, spDataReport);
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
// AmbientLightAwareSensorEvents::GetSensorData
//
// Description of function/method:
//        Helper function, get data from a sensor and updates the lux
//
// Parameters:
//        ISensor *pSensor:               Input sensor
//        ISensorDataReport* pDataReport: The data to be read
//
// Return Values:
//        S_OK on success, else an error
//
///////////////////////////////////////////////////////////////////////////////
HRESULT AmbientLightAwareSensorEvents::GetSensorData(ISensor* pSensor, ISensorDataReport* pDataReport)
{
	HRESULT hr = S_OK;

	if (NULL != pSensor && NULL != pDataReport)
	{
		SENSOR_ID idSensor = GUID_NULL;
		hr = pSensor->GetID(&idSensor);
		if (SUCCEEDED(hr))
		{
			PROPVARIANT pvLux;
			PropVariantInit(&pvLux);
			hr = pDataReport->GetSensorValue(SENSOR_DATA_TYPE_LIGHT_LEVEL_LUX, &pvLux);
			if (SUCCEEDED(hr))
			{
				PROPVARIANT pvTimeStamp;
				PropVariantInit(&pvTimeStamp);
				pDataReport->GetSensorValue(SENSOR_DATA_TYPE_TIMESTAMP, &pvTimeStamp);
				if (SUCCEEDED(hr))
				{
					UINT64 timestamp = ((UINT64)pvTimeStamp.filetime.dwHighDateTime << 32) | pvTimeStamp.filetime.dwLowDateTime;
					m_Callback(pvLux.fltVal, 1, timestamp);
				}
			}
			PropVariantClear(&pvLux);
		}
	}
	else
	{
		hr = E_INVALIDARG;
	}

	return hr;
}
