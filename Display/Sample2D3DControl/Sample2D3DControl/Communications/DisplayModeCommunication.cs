//*********************************************************
//
// Copyright(C) Seiko Epson Corporation 2019. All rights reserved.
//
//*********************************************************

namespace Sample2D3DControl.Communications
{
    internal class DisplayModeCommunication : SerialCommunication
    {
        private readonly string Mode2D = "2D";
        private readonly string Mode3D = "3D";

        private readonly string Mode2DValue = "0";
        private readonly string Mode3DValue = "1";

        public bool SetMode(string mode)
        {
            if (mode == Mode2D)
            {
                return "OK" == WriteAndRead("set2d3d " + Mode2DValue);
            }
            else if (mode == Mode3D)
            {
                return "OK" == WriteAndRead("set2d3d " + Mode3DValue);
            }
            else
            {
                return false;
            }
        }

        public string GetMode()
        {
            var mode = WriteAndRead("get2d3d");

            if (mode == Mode2DValue)
            {
                return Mode2D;
            }
            else if (mode == Mode3DValue)
            {
                return Mode3D;
            }
            else
            {
                return string.Empty;
            }
        }
    }
}
