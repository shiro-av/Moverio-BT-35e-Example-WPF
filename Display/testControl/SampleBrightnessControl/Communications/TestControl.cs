//*********************************************************
//
// Copyright(C) Seiko Epson Corporation 2019. All rights reserved.
//
//*********************************************************

namespace testControl.Communications
{
    internal class testCommunication : SerialCommunication
    {
        private readonly string BrightnessAuto = "50";

        public bool SetBrightness(string brightness)
        {
            return CheckBrightnessLevel(brightness) && "OK" == WriteAndRead("setbright " + brightness);
        }

        public bool SetBrightnessAuto()
        {
            return "OK" == WriteAndRead("setbright " + BrightnessAuto);
        }

        public string GetBrightness()
        {
            var brightness = WriteAndRead("getbright");

            if (!CheckBrightnessLevel(brightness))
            {
                if (brightness == BrightnessAuto)
                {
                    return "Auto";
                }

                return string.Empty;
            }

            return brightness;
        }

        private bool CheckBrightnessLevel(string brightness)
        {
            return int.TryParse(brightness, out var result) && (0 <= result && result <= 20);
        }

        /*private bool CheckSleep(string sleep)
        {
            return int.TryParse(sleep, out var result) && (0 <= result && result <= 1);
        }*/

        public bool SetDisplayOff()
        {
            return "OK" == WriteAndRead("setmute 1");
        }

        public bool SetDisplayOn()
        {
            return "OK" == WriteAndRead("setmute 0");
        }

        public string GetState()
        {
            var state = WriteAndRead("getsystemstat");
            return state;
        }

        /*public bool SetSleepOff()
        {
            return "OK" == WriteAndRead("enableautosleep 0");
        }

        public bool SetSleepOn()
        {
            return "OK" == WriteAndRead("enableautosleep 1");
        }*/

        public bool Set2D()
        {
            return "OK" == WriteAndRead("set2d3d 0");
        }

        public bool Set3D()
        {
            return "OK" == WriteAndRead("set2d3d 1");
        }
    }
}
