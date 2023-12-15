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
//        AmbientLightAwareSensorEvents.h
//
// Description:
//        Implementation of ISensorEvents
//
// Comments: 
//        This is a standard c++ class, but needs to support IUnknown methods
//        to be properly implemented.  This class overrides ISensorEvents and
//        functions to receive updated information from Sensors API when it
//        is published.
//
//-----------------------------------------------------------------------
#pragma once
#include <SensorsApi.h>

#include <sensors.h>
#include <atlcoll.h>
#pragma comment(lib, "Sensorsapi.lib")

#include "AmbientLightAwareSensorManagerEvents.h"

class AmbientLightAwareSensorEvents :
	public ISensorEvents
{
public:
	// These three methods are for IUnknown
	STDMETHOD(QueryInterface)(REFIID riid, void** ppObject);
	ULONG _stdcall AddRef();
	ULONG _stdcall Release();

	// Constructor and destructor
	AmbientLightAwareSensorEvents(AmbientLightAwareSensorManagerEvents* sensorManagerEvents, LightSensorCallback callback);
	virtual ~AmbientLightAwareSensorEvents();

	// ISensorEvents method overrides
	STDMETHOD(OnStateChanged)(__RPC__in_opt ISensor* pSensor, SensorState state);
	STDMETHOD(OnDataUpdated)(__RPC__in_opt ISensor* pSensor, __RPC__in_opt ISensorDataReport* pNewData);
	STDMETHOD(OnEvent)(__RPC__in_opt ISensor* pSensor, __RPC__in REFGUID eventID, __RPC__in_opt IPortableDeviceValues* pEventData);
	STDMETHOD(OnLeave)(__RPC__in REFSENSOR_ID sensorID);

	// Helper functions, also called by parent SensorManagerEvents class
	HRESULT GetSensorData(ISensor* pSensor);

private:
	// Member variable to implement IUnknown reference count
	LONG m_lRefCount;

	// Helper functions
	HRESULT GetSensorData(ISensor* pSensor, ISensorDataReport* pDataReport);

	AmbientLightAwareSensorManagerEvents* m_pSensorManagerEvents; // Parent class for callbacks
	LightSensorCallback m_Callback;
};

