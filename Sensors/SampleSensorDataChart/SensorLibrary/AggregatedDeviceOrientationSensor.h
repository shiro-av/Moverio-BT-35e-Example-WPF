//*********************************************************
//
// Copyright(C) Seiko Epson Corporation 2019. All rights reserved.
//
//*********************************************************

#pragma once

#include "AggregatedDeviceOrientationSensorManagerEvents.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace SensorLibrary {
	public delegate void AggregatedDeviceOrientationSensorDelegate(float, float, float, float, UInt64);

	public ref class AggregatedDeviceOrientationSensor
	{
	public:
		AggregatedDeviceOrientationSensor(AggregatedDeviceOrientationSensorDelegate^ delegate);
		~AggregatedDeviceOrientationSensor();

		void Initialize();
		void Uninitialize();

	private:
		GCHandle gchDelegate;

		AggregatedDeviceOrientationSensorManagerEvents* pAggregatedDeviceOrientationSensorManagerEvents;
	};
}
