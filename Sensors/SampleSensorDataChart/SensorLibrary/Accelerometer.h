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

	ref class AccelerometerSensor
	{
	};
}

