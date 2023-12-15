//-----------------------------------------------------------------------
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
// Copyright(C) Seiko Epson Corporation 2019. All rights reserved.
//
// Module:
//        AggregatedDeviceOrientationSensorManagerEvents.h
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
//-----------------------------------------------------------------------
#pragma once

#include <SensorsApi.h>
#include <sensors.h>
#include <atlcoll.h>
#pragma comment(lib, "Sensorsapi.lib")

typedef void(_stdcall* AggregatedDeviceOrientationSensorCallback)(float, float, float, float, UINT64);

// Forward declaration.
class AggregatedDeviceOrientationSensorEvents;

class AggregatedDeviceOrientationSensorManagerEvents :
	public ISensorManagerEvents
{
public:
	// These three methods are for IUnknown
	STDMETHOD(QueryInterface)(REFIID riid, void** ppObject);
	ULONG _stdcall AddRef();
	ULONG _stdcall Release();

	// Constructor and destructor
	AggregatedDeviceOrientationSensorManagerEvents(AggregatedDeviceOrientationSensorCallback callback);
	virtual ~AggregatedDeviceOrientationSensorManagerEvents();

	// Initialize and Uninitialize called by parent dialog
	HRESULT Initialize();
	HRESULT Uninitialize();

	// ISensorManagerEvents method override
	STDMETHOD(OnSensorEnter)(__RPC__in_opt ISensor* pSensor, SensorState state);

	// Is a callback from child SensorEvents
	HRESULT RemoveSensor(REFSENSOR_ID sensorID);

private:
	// Member variable to implement IUnknown reference count
	LONG m_lRefCount;

	// Helper functions
	HRESULT AddSensor(ISensor* pSensor);
	HRESULT RemoveSensor(ISensor* pSensor);

	HRESULT IsMoverio(ISensor* pSensor);

	AggregatedDeviceOrientationSensorEvents* m_pSensorEvents; // Sensor Events class used for event sinking
	CComPtr<ISensorManager> m_spISensorManager;      // Global to keep reference for life of class
	CAtlMap<SENSOR_ID, ISensor*> m_Sensors;          // Map to store sensors for life of class
};
