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
    public partial class AmbientLightControl : UserControl, ISensor
    {
        private readonly int keepRecords = 200;
        private readonly LightSensor lightSensor;

        public ChartValues<float> ValuesBrightness { get; } = new ChartValues<float>();

        public AmbientLightControl()
        {
            InitializeComponent();

            lightSensor = new LightSensor(LightSensorCallback);

            DataContext = this;
        }

        public void Active()
        {
            ClearValues();

            lightSensor.Initialize();
        }

        public void Inactive()
        {
            lightSensor.Uninitialize();
        }

        private void LightSensorCallback(float f, int n, ulong timestamp)
        {
            Dispatcher.BeginInvoke(DispatcherPriority.Normal, (Action)(() =>
            {
                Brightness.Text = f.ToString();

                AddValues(ValuesBrightness, f);
            }));
        }

        private void AddValues(ChartValues<float> values, float value)
        {
            values.Add(value);
            if (values.Count > keepRecords)
            {
                values.RemoveAt(0);
            }
        }

        private void ClearValues()
        {
            ValuesBrightness.Clear();

            Brightness.Text = string.Empty;
        }
    }
}
