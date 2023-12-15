//*********************************************************
//
// Copyright(C) Seiko Epson Corporation 2019. All rights reserved.
//
//*********************************************************

#include "pch.h"
#include "CompassSensor.h"

SensorLibrary::CompassSensor::CompassSensor(CompassSensorDelegate^ delegate)
{
	gchDelegate = GCHandle::Alloc(delegate);
	IntPtr ptr = Marshal::GetFunctionPointerForDelegate(delegate);
	CompassSensorCallback callback = static_cast<CompassSensorCallback>(ptr.ToPointer());
	pCompassSensorManagerEvents = new CompassSensorManagerEvents(callback);
}

SensorLibrary::CompassSensor::~CompassSensor()
{
	pCompassSensorManagerEvents->Uninitialize();
	gchDelegate.Free();
}

void SensorLibrary::CompassSensor::Initialize()
{
	pCompassSensorManagerEvents->Initialize();
}

void SensorLibrary::CompassSensor::Uninitialize()
{
	pCompassSensorManagerEvents->Uninitialize();
}
