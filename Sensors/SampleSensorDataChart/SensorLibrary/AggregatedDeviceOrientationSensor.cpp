//*********************************************************
//
// Copyright(C) Seiko Epson Corporation 2019. All rights reserved.
//
//*********************************************************

#include "pch.h"
#include "AggregatedDeviceOrientationSensor.h"

SensorLibrary::AggregatedDeviceOrientationSensor::AggregatedDeviceOrientationSensor(AggregatedDeviceOrientationSensorDelegate^ delegate)
{
	gchDelegate = GCHandle::Alloc(delegate);
	IntPtr ptr = Marshal::GetFunctionPointerForDelegate(delegate);
	AggregatedDeviceOrientationSensorCallback callback = static_cast<AggregatedDeviceOrientationSensorCallback>(ptr.ToPointer());
	pAggregatedDeviceOrientationSensorManagerEvents = new AggregatedDeviceOrientationSensorManagerEvents(callback);
}

SensorLibrary::AggregatedDeviceOrientationSensor::~AggregatedDeviceOrientationSensor()
{
	pAggregatedDeviceOrientationSensorManagerEvents->Uninitialize();
	gchDelegate.Free();
}

void SensorLibrary::AggregatedDeviceOrientationSensor::Initialize()
{
	pAggregatedDeviceOrientationSensorManagerEvents->Initialize();
}

void SensorLibrary::AggregatedDeviceOrientationSensor::Uninitialize()
{
	pAggregatedDeviceOrientationSensorManagerEvents->Uninitialize();
}
