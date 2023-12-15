//*********************************************************
//
// Copyright(C) Seiko Epson Corporation 2019. All rights reserved.
//
//*********************************************************

using MahApps.Metro.Controls;
using Sample2D3DControl.Communications;
using Sample2D3DControl.Watchers;
using System;
using System.Windows;
using System.Windows.Controls;

namespace Sample2D3DControl
{
    public partial class MainWindow : MetroWindow
    {
        private readonly MoverioWatcher moverioWatcher = new MoverioWatcher();
        private readonly DisplayModeCommunication communication = new DisplayModeCommunication();
        private string portName;

        public MainWindow()
        {
            InitializeComponent();
        }

        private void MetroWindow_Loaded(object sender, RoutedEventArgs e)
        {
            moverioWatcher.Add += MoverioWatcher_Add;
            moverioWatcher.Remove += MoverioWatcher_Remove;
            moverioWatcher.Start();
        }

        private void MetroWindow_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            moverioWatcher.Add -= MoverioWatcher_Add;
            moverioWatcher.Remove -= MoverioWatcher_Remove;
            moverioWatcher.Stop();
        }

        private void MoverioWatcher_Add(object sender, MoverioInfo e)
        {
            if (string.IsNullOrEmpty(portName))
            {
                Dispatcher.BeginInvoke((Action)(() => EnableButtons(communication.Open(e.portName))));
                portName = e.portName;
            }
        }

        private void MoverioWatcher_Remove(object sender, MoverioInfo e)
        {
            if (e.portName == portName)
            {
                communication.Close();
                portName = string.Empty;
                Dispatcher.BeginInvoke((Action)(() => EnableButtons(false)));
            }
        }

        private void Get2D3D_Click(object sender, RoutedEventArgs e)
        {
            var mode = communication.GetMode();

            if (string.IsNullOrEmpty(mode))
            {
                Current2D3D.Text = "Error";
            }
            else
            {
                Current2D3D.Text = mode;
            }
        }

        private void Set2D3D_Click(object sender, RoutedEventArgs e)
        {
            EnableButtons(true);

            var button = sender as Button;
            var mode = button.Content as string;
            if (communication.SetMode(mode))
            {
                button.IsEnabled = false;
            }
        }

        private void EnableButtons(bool enable)
        {
            ButtonGet.IsEnabled = enable;
            Button2D.IsEnabled = enable;
            Button3D.IsEnabled = enable;
        }
    }
}
