//*********************************************************
//
// Copyright(C) Seiko Epson Corporation 2019. All rights reserved.
//
//*********************************************************

using LiveCharts;
using SensorLibrary;
using System;
using System.Windows.Controls;
using System.Windows.Threading;

namespace SampleSensorDataChart.Sensors
{
    public partial class LinearAccelerometerControl : UserControl, ISensor
    {
        private readonly int keepRecords = 200;
        private readonly LinearAccelerometerSensor linearAccelerometer;

        public ChartValues<double> ValuesX { get; } = new ChartValues<double>();
        public ChartValues<double> ValuesY { get; } = new ChartValues<double>();
        public ChartValues<double> ValuesZ { get; } = new ChartValues<double>();

        public LinearAccelerometerControl()
        {
            InitializeComponent();

            linearAccelerometer = new LinearAccelerometerSensor(LinearAccelerometerCallback);

            DataContext = this;
        }

        public void Active()
        {
            ClearValues();

            linearAccelerometer.Initialize();
        }

        public void Inactive()
        {
            linearAccelerometer.Uninitialize();
        }

        private void LinearAccelerometerCallback(double x, double y, double z, ulong timestamp)
        {
            Dispatcher.BeginInvoke(DispatcherPriority.Normal, (Action)(() =>
            {
                AxisX.Text = x.ToString();
                AxisY.Text = y.ToString();
                AxisZ.Text = z.ToString();

                AddValues(ValuesX, x);
                AddValues(ValuesY, y);
                AddValues(ValuesZ, z);
            }));
        }

        private void AddValues(ChartValues<double> values, double value)
        {
            values.Add(value);
            if (values.Count > keepRecords)
            {
                values.RemoveAt(0);
            }
        }

        private void ClearValues()
        {
            ValuesX.Clear();
            ValuesY.Clear();
            ValuesZ.Clear();

            AxisX.Text = string.Empty;
            AxisY.Text = string.Empty;
            AxisZ.Text = string.Empty;
        }
    }
}
