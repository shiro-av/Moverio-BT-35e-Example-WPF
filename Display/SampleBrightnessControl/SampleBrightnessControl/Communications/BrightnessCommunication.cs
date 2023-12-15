//*********************************************************
//
// Copyright(C) Seiko Epson Corporation 2019. All rights reserved.
//
//*********************************************************

namespace SampleBrightnessControl.Communications
{
    internal class BrightnessCommunication : SerialCommunication
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
    }
}
