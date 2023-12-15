//*********************************************************
//
// Copyright(C) Seiko Epson Corporation 2019. All rights reserved.
//
//*********************************************************

#include "pch.h"
#include "AccelerometerSensor.h"

SensorLibrary::AccelerometerSensor::AccelerometerSensor(AccelerometerSensorDelegate^ delegate)
{
	gchDelegate = GCHandle::Alloc(delegate);
	IntPtr ptr = Marshal::GetFunctionPointerForDelegate(delegate);
	AccelerometerSensorCallback callback = static_cast<AccelerometerSensorCallback>(ptr.ToPointer());
	pAccelerometerSensorManagerEvents = new AccelerometerSensorManagerEvents(callback);
}

SensorLibrary::AccelerometerSensor::~AccelerometerSensor()
{
	pAccelerometerSensorManagerEvents->Uninitialize();
	gchDelegate.Free();
}

void SensorLibrary::AccelerometerSensor::Initialize()
{
	pAccelerometerSensorManagerEvents->Initialize();
}

void SensorLibrary::AccelerometerSensor::Uninitialize()
{
	pAccelerometerSensorManagerEvents->Uninitialize();
}
