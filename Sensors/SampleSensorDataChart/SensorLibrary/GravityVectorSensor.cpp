//*********************************************************
//
// Copyright(C) Seiko Epson Corporation 2019. All rights reserved.
//
//*********************************************************

#include "pch.h"
#include "GravityVectorSensor.h"

SensorLibrary::GravityVectorSensor::GravityVectorSensor(GravityVectorSensorDelegate^ delegate)
{
	gchDelegate = GCHandle::Alloc(delegate);
	IntPtr ptr = Marshal::GetFunctionPointerForDelegate(delegate);
	GravityVectorSensorCallback callback = static_cast<GravityVectorSensorCallback>(ptr.ToPointer());
	pGravityVectorSensorManagerEvents = new GravityVectorSensorManagerEvents(callback);
}

SensorLibrary::GravityVectorSensor::~GravityVectorSensor()
{
	pGravityVectorSensorManagerEvents->Uninitialize();
	gchDelegate.Free();
}

void SensorLibrary::GravityVectorSensor::Initialize()
{
	pGravityVectorSensorManagerEvents->Initialize();
}

void SensorLibrary::GravityVectorSensor::Uninitialize()
{
	pGravityVectorSensorManagerEvents->Uninitialize();
}