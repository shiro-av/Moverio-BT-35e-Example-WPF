//*********************************************************
//
// Copyright(C) Seiko Epson Corporation 2019. All rights reserved.
//
//*********************************************************

#pragma once

#include "LinearAccelerometerSensorManagerEvents.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace SensorLibrary {
	public delegate void LinearAccelerometerSensorDelegate(double, double, double, UInt64);

	public ref class LinearAccelerometerSensor
	{
	public:
		LinearAccelerometerSensor(LinearAccelerometerSensorDelegate^ delegate);
		~LinearAccelerometerSensor();

		void Initialize();
		void Uninitialize();

	private:
		GCHandle gchDelegate;

		LinearAccelerometerSensorManagerEvents* pLinearAccelerometerSensorManagerEvents;
	};
}

