//*********************************************************
//
// Copyright(C) Seiko Epson Corporation 2019. All rights reserved.
//
//*********************************************************

#pragma once

#include "AmbientLightAwareSensorManagerEvents.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace SensorLibrary {
	public delegate void LightSensorDelegate(float, int, UInt64);

	public ref class LightSensor
	{
	public:
		LightSensor(LightSensorDelegate^ delegate);
		~LightSensor();

		void Initialize();
		void Uninitialize();

	private:
		GCHandle gchDelegate;

		AmbientLightAwareSensorManagerEvents* pAmbientLightAwareSensorManagerEvents;
	};
}
