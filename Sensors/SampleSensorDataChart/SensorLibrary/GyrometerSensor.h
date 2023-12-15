//*********************************************************
//
// Copyright(C) Seiko Epson Corporation 2019. All rights reserved.
//
//*********************************************************

#pragma once

#include "GyrometerSensorManagerEvents.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace SensorLibrary {
	public delegate void GyrometerSensorDelegate(double, double, double, UInt64);

	public ref class GyrometerSensor
	{
	public:
		GyrometerSensor(GyrometerSensorDelegate^ delegate);
		~GyrometerSensor();

		void Initialize();
		void Uninitialize();

	private:
		GCHandle gchDelegate;

		GyrometerSensorManagerEvents* pGyrometerSensorManagerEvents;
	};
}
