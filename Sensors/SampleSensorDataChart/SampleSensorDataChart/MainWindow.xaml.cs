//*********************************************************
//
// Copyright(C) Seiko Epson Corporation 2019. All rights reserved.
//
//*********************************************************

using MahApps.Metro.Controls;
using SampleSensorDataChart.Sensors;
using System.Windows;
using System.Windows.Controls;

namespace SampleSensorDataChart
{
    public partial class MainWindow : MetroWindow
    {
        private ISensor currentSensor;

        public MainWindow()
        {
            InitializeComponent();
        }

        private void MetroWindow_Loaded(object sender, RoutedEventArgs e)
        {
            SensorChanges();
        }

        private void TabControl_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            SensorChanges();
        }

        private void SensorChanges()
        {
            var tabItem = sensorsTab.SelectedItem as TabItem;
            foreach (var obj in tabItem.GetChildObjects())
            {
                if (!(obj is ISensor sensor))
                {
                    continue;
                }

                currentSensor?.Inactive();
                sensor.Active();

                currentSensor = sensor;
            }
        }
    }
}
