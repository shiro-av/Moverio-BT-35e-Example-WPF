//*********************************************************
//
// Copyright(C) Seiko Epson Corporation 2019. All rights reserved.
//
//*********************************************************

#include "pch.h"
#include "LinearAccelerometerSensor.h"

SensorLibrary::LinearAccelerometerSensor::LinearAccelerometerSensor(LinearAccelerometerSensorDelegate^ delegate)
{
	gchDelegate = GCHandle::Alloc(delegate);
	IntPtr ptr = Marshal::GetFunctionPointerForDelegate(delegate);
	LinearAccelerometerSensorCallback callback = static_cast<LinearAccelerometerSensorCallback>(ptr.ToPointer());
	pLinearAccelerometerSensorManagerEvents = new LinearAccelerometerSensorManagerEvents(callback);
}

SensorLibrary::LinearAccelerometerSensor::~LinearAccelerometerSensor()
{
	pLinearAccelerometerSensorManagerEvents->Uninitialize();
	gchDelegate.Free();
}

void SensorLibrary::LinearAccelerometerSensor::Initialize()
{
	pLinearAccelerometerSensorManagerEvents->Initialize();
}

void SensorLibrary::LinearAccelerometerSensor::Uninitialize()
{
	pLinearAccelerometerSensorManagerEvents->Uninitialize();
}