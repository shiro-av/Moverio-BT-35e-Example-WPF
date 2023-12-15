//*********************************************************
//
// Copyright(C) Seiko Epson Corporation 2019. All rights reserved.
//
//*********************************************************

using System;
using System.Collections.Generic;
using System.Management;
using System.Timers;

namespace SampleBrightnessControl.Watchers
{
    internal class MoverioWatcher
    {
        private readonly Dictionary<string, MoverioType> SupportMoverios = new Dictionary<string, MoverioType>()
        {
            { "VID_0483&PID_5750", MoverioType.BT35E },
            { "VID_04B8&PID_0C0C", MoverioType.BT30C }
        };

        public event EventHandler<MoverioInfo> Add;
        public event EventHandler<MoverioInfo> Remove;

        private Timer timer;
        private readonly List<MoverioInfo> connectedMoverioInfos = new List<MoverioInfo>();

        public void Start()
        {
            if (timer != null)
            {
                return;
            }

            timer = new Timer(500);
            timer.Elapsed += (sender, e) =>
            {
                var removeMoverioInfos = new List<MoverioInfo>(connectedMoverioInfos);

                foreach (var info in GetMoverioInfos())
                {
                    if (connectedMoverioInfos.Contains(info))
                    {
                        removeMoverioInfos.Remove(info);
                    }
                    else
                    {
                        connectedMoverioInfos.Add(info);
                        OnAdd(info);
                    }
                }

                foreach (var info in removeMoverioInfos)
                {
                    connectedMoverioInfos.Remove(info);
                    OnRemove(info);
                }
            };
            timer.Start();
        }

        public void Stop()
        {
            if (timer == null)
            {
                return;
            }

            timer.Stop();
            timer.Dispose();
        }

        private List<MoverioInfo> GetMoverioInfos()
        {
            var infos = new List<MoverioInfo>();

            using (ManagementClass managementClass = new ManagementClass("Win32_SerialPort"))
            {
                foreach (var management in managementClass.GetInstances())
                {
                    var id = management.GetPropertyValue("PNPDeviceID") as string;
                    foreach (var key in SupportMoverios.Keys)
                    {
                        if (id.Contains(key))
                        {
                            infos.Add(new MoverioInfo(SupportMoverios[key], management.GetPropertyValue("DeviceID") as string));
                        }
                    }
                }
            }

            return infos;
        }

        protected virtual void OnAdd(MoverioInfo e)
        {
            Add?.Invoke(this, e);
        }

        protected virtual void OnRemove(MoverioInfo e)
        {
            Remove?.Invoke(this, e);
        }
    }
}
