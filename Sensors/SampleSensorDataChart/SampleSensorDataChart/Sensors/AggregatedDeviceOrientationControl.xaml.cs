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
    public partial class AggregatedDeviceOrientationControl : UserControl, ISensor
    {
        private readonly int keepRecords = 200;
        private readonly AggregatedDeviceOrientationSensor aggregatedDeviceOrientation;

        public ChartValues<double> ValuesX { get; } = new ChartValues<double>();
        public ChartValues<double> ValuesY { get; } = new ChartValues<double>();
        public ChartValues<double> ValuesZ { get; } = new ChartValues<double>();
        public ChartValues<double> ValuesW { get; } = new ChartValues<double>();

        public AggregatedDeviceOrientationControl()
        {
            InitializeComponent();

            aggregatedDeviceOrientation = new AggregatedDeviceOrientationSensor(AggregatedDeviceOrientationCallback);

            DataContext = this;
        }

        public void Active()
        {
            ClearValues();

            aggregatedDeviceOrientation.Initialize();
        }

        public void Inactive()
        {
            aggregatedDeviceOrientation.Uninitialize();
        }

        private void AggregatedDeviceOrientationCallback(float x, float y, float z, float w, ulong timestamp)
        {
            Dispatcher.BeginInvoke(DispatcherPriority.Normal, (Action)(() =>
            {
                AxisX.Text = x.ToString();
                AxisY.Text = y.ToString();
                AxisZ.Text = z.ToString();
                AxisW.Text = w.ToString();

                AddValues(ValuesX, x);
                AddValues(ValuesY, y);
                AddValues(ValuesZ, z);
                AddValues(ValuesW, w);
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
            ValuesW.Clear();

            AxisX.Text = string.Empty;
            AxisY.Text = string.Empty;
            AxisZ.Text = string.Empty;
            AxisW.Text = string.Empty;
        }
    }
}
