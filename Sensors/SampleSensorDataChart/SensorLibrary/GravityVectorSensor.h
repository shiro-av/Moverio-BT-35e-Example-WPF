//*********************************************************
//
// Copyright(C) Seiko Epson Corporation 2019. All rights reserved.
//
//*********************************************************

#pragma once

#include "GravityVectorSensorManagerEvents.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace SensorLibrary {
	public delegate void GravityVectorSensorDelegate(double, double, double, UInt64);

	public ref class GravityVectorSensor
	{
	public:
		GravityVectorSensor(GravityVectorSensorDelegate^ delegate);
		~GravityVectorSensor();

		void Initialize();
		void Uninitialize();

	private:
		GCHandle gchDelegate;

		GravityVectorSensorManagerEvents* pGravityVectorSensorManagerEvents;
	};
}
