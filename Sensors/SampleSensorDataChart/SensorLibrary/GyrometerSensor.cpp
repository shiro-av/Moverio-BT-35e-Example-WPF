//*********************************************************
//
// Copyright(C) Seiko Epson Corporation 2019. All rights reserved.
//
//*********************************************************

#include "pch.h"
#include "GyrometerSensor.h"

SensorLibrary::GyrometerSensor::GyrometerSensor(GyrometerSensorDelegate^ delegate)
{
	gchDelegate = GCHandle::Alloc(delegate);
	IntPtr ptr = Marshal::GetFunctionPointerForDelegate(delegate);
	GyrometerSensorCallback callback = static_cast<GyrometerSensorCallback>(ptr.ToPointer());
	pGyrometerSensorManagerEvents = new GyrometerSensorManagerEvents(callback);
}

SensorLibrary::GyrometerSensor::~GyrometerSensor()
{
	pGyrometerSensorManagerEvents->Uninitialize();
	gchDelegate.Free();
}

void SensorLibrary::GyrometerSensor::Initialize()
{
	pGyrometerSensorManagerEvents->Initialize();
}

void SensorLibrary::GyrometerSensor::Uninitialize()
{
	pGyrometerSensorManagerEvents->Uninitialize();
}

