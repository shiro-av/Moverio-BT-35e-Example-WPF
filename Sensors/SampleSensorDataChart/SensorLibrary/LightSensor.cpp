//*********************************************************
//
// Copyright(C) Seiko Epson Corporation 2019. All rights reserved.
//
//*********************************************************

#include "pch.h"
#include "LightSensor.h"

SensorLibrary::LightSensor::LightSensor(LightSensorDelegate^ delegate)
{
	gchDelegate = GCHandle::Alloc(delegate);
	IntPtr ptr = Marshal::GetFunctionPointerForDelegate(delegate);
	LightSensorCallback callback = static_cast<LightSensorCallback>(ptr.ToPointer());
	pAmbientLightAwareSensorManagerEvents = new AmbientLightAwareSensorManagerEvents(callback);
}

SensorLibrary::LightSensor::~LightSensor()
{
	pAmbientLightAwareSensorManagerEvents->Uninitialize();
	gchDelegate.Free();
}

void SensorLibrary::LightSensor::Initialize()
{
	pAmbientLightAwareSensorManagerEvents->Initialize();
}

void SensorLibrary::LightSensor::Uninitialize()
{
	pAmbientLightAwareSensorManagerEvents->Uninitialize();
}
