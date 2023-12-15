//*********************************************************
//
// Copyright(C) Seiko Epson Corporation 2019. All rights reserved.
//
//*********************************************************

#pragma once

#include "AccelerometerSensorManagerEvents.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace SensorLibrary {
	public delegate void AccelerometerSensorDelegate(double, double, double, UInt64);

	public ref class AccelerometerSensor
	{
	public:
		AccelerometerSensor(AccelerometerSensorDelegate^ delegate);
		~AccelerometerSensor();

		void Initialize();
		void Uninitialize();

	private:
		GCHandle gchDelegate;

		AccelerometerSensorManagerEvents* pAccelerometerSensorManagerEvents;
	};
}

