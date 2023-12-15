//*********************************************************
//
// Copyright(C) Seiko Epson Corporation 2019. All rights reserved.
//
//*********************************************************

#pragma once

#include "CompassSensorManagerEvents.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace SensorLibrary {
	public delegate void CompassSensorDelegate(double, double, double, UInt64);

	public ref class CompassSensor
	{
	public:
		CompassSensor(CompassSensorDelegate^ delegate);
		~CompassSensor();

		void Initialize();
		void Uninitialize();

	private:
		GCHandle gchDelegate;

		CompassSensorManagerEvents* pCompassSensorManagerEvents;
	};
}

