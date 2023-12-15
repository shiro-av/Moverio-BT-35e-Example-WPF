//*********************************************************
//
// Copyright(C) Seiko Epson Corporation 2019. All rights reserved.
//
//*********************************************************

using MahApps.Metro.Controls;
using testControl.Communications;
using testControl.Watchers;
using System;
using System.Windows;
using System.Windows.Controls;

namespace testControl
{
    public partial class MainWindow : MetroWindow
    {
        private readonly MoverioWatcher moverioWatcher = new MoverioWatcher();
        private readonly testCommunication communication = new testCommunication();
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
                Dispatcher.BeginInvoke((Action)(() =>
                {
                    SetMoverioTypeDisplay(e.type);
                    EnableButtons(communication.Open(e.portName));
                }));
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

        private void GetBrightness_Click(object sender, RoutedEventArgs e)
        {
            var brightness = communication.GetBrightness();

            if (string.IsNullOrEmpty(brightness))
            {
                CurrentBrightness.Text = "Error";
            }
            else
            {
                CurrentBrightness.Text = brightness;
            }
        }

        private void SetBrightness_Click(object sender, RoutedEventArgs e)
        {
            EnableButtons(true);

            var button = sender as Button;
            var brightness = button.Content as string;
            if (communication.SetBrightness(brightness))
            {
                button.IsEnabled = false;
            }
        }

        private void SetBrightnessAuto_Click(object sender, RoutedEventArgs e)
        {
            EnableButtons(true);

            if (communication.SetBrightnessAuto())
            {
                var button = sender as Button;
                button.IsEnabled = false;
            }
        }

        private void SetDisplayOff_Click(object sender, RoutedEventArgs e)
        {
            EnableButtons(true);

            if (communication.SetDisplayOff())
            {
                var button = sender as Button;
                button.IsEnabled = false;
            }
        }

        private void SetDisplayOn_Click(object sender, RoutedEventArgs e)
        {
            EnableButtons(true);

            if (communication.SetDisplayOn())
            {
                var button = sender as Button;
                button.IsEnabled = false;
            }
        }

        private void GetState_Click(object sender, RoutedEventArgs e)
        {
            var state = communication.GetState();

            if (string.IsNullOrEmpty(state))
            {
                CurrentState.Text = "Error";
            }
            else
            {
                if (state == "0")
                    CurrentState.Text = "Отключение питания";
                else if (state == "1")
                    CurrentState.Text = "В процессе инициализации системы Moverio";
                else if (state == "2")
                    CurrentState.Text = "Видеовыход с хост-устройства отсутствует";
                else if (state == "3")
                    CurrentState.Text = "Во время отображения изображения";
                else if (state == "4")
                    CurrentState.Text = "Дисплей выключен";
                else if (state == "5")
                    CurrentState.Text = "В процессе восстановления";

            }
        }

        private void Set2D_Click(object sender, RoutedEventArgs e)
        {
            EnableButtons(true);

            if (communication.Set2D())
            {
                var button = sender as Button;
                button.IsEnabled = false;
            }
        }

        private void Set3D_Click(object sender, RoutedEventArgs e)
        {
            EnableButtons(true);

            if (communication.Set3D())
            {
                var button = sender as Button;
                button.IsEnabled = false;
            }
        }

        private void SetMoverioTypeDisplay(MoverioType type)
        {
            ButtonAuto.Visibility = MoverioType.BT35E == type ? Visibility.Visible : Visibility.Collapsed;
        }

        private void EnableButtons(bool enable)
        {
            ButtonGetBrightness.IsEnabled = enable;
            ButtonOff.IsEnabled = enable;
            ButtonGetState.IsEnabled = enable;
            ButtonOn.IsEnabled = enable;
            ButtonSet2D.IsEnabled = enable;
            ButtonSet3D.IsEnabled = enable;
            ButtonLevel0.IsEnabled = enable;
            ButtonLevel1.IsEnabled = enable;
            ButtonLevel2.IsEnabled = enable;
            ButtonLevel3.IsEnabled = enable;
            ButtonLevel4.IsEnabled = enable;
            ButtonLevel5.IsEnabled = enable;
            ButtonLevel6.IsEnabled = enable;
            ButtonLevel7.IsEnabled = enable;
            ButtonLevel8.IsEnabled = enable;
            ButtonLevel9.IsEnabled = enable;
            ButtonLevel10.IsEnabled = enable;
            ButtonLevel11.IsEnabled = enable;
            ButtonLevel12.IsEnabled = enable;
            ButtonLevel13.IsEnabled = enable;
            ButtonLevel14.IsEnabled = enable;
            ButtonLevel15.IsEnabled = enable;
            ButtonLevel16.IsEnabled = enable;
            ButtonLevel17.IsEnabled = enable;
            ButtonLevel18.IsEnabled = enable;
            ButtonLevel19.IsEnabled = enable;
            ButtonLevel20.IsEnabled = enable;
            ButtonAuto.IsEnabled = enable;
        }
    }
}
