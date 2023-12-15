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
    public partial class CompassControl : UserControl, ISensor
    {
        private readonly int keepRecords = 200;
        private readonly CompassSensor compass;

        public ChartValues<double> ValuesX { get; } = new ChartValues<double>();
        public ChartValues<double> ValuesY { get; } = new ChartValues<double>();
        public ChartValues<double> ValuesZ { get; } = new ChartValues<double>();

        public CompassControl()
        {
            InitializeComponent();

            compass = new CompassSensor(CompassCallback);

            DataContext = this;
        }

        public void Active()
        {
            ClearValues();

            compass.Initialize();
        }

        public void Inactive()
        {
            compass.Uninitialize();
        }

        private void CompassCallback(double x, double y, double z, ulong timestamp)
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
