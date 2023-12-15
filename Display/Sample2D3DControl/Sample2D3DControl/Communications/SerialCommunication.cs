//*********************************************************
//
// Copyright(C) Seiko Epson Corporation 2019. All rights reserved.
//
//*********************************************************

using System;
using System.IO.Ports;

namespace Sample2D3DControl.Communications
{
    internal abstract class SerialCommunication
    {
        private readonly int Timeout = 500; // Milliseconds

        private readonly SerialPort serialPort = new SerialPort();
        private readonly object serialPort_lock = new object();

        public bool Open(string portName)
        {
            if (string.IsNullOrEmpty(portName))
            {
                return false;
            }

            if (serialPort.IsOpen)
            {
                Close();
            }

            try
            {
                serialPort.PortName = portName;
                serialPort.BaudRate = 9600;
                serialPort.Parity = Parity.None;
                serialPort.DataBits = 8;
                serialPort.StopBits = StopBits.One;
                serialPort.Handshake = Handshake.None;

                serialPort.ReadTimeout = Timeout;
                serialPort.WriteTimeout = Timeout;

                serialPort.Open();
            }
            catch (Exception e)
            {
                Console.WriteLine("Error : " + e.Message);
                return false;
            }

            return true;
        }

        public void Close()
        {
            serialPort.Close();
        }

        protected string WriteAndRead(string command)
        {
            lock (serialPort_lock)
            {
                var response = string.Empty;

                if (!serialPort.IsOpen)
                {
                    return response;
                }

                try
                {
                    serialPort.WriteLine(command);

                    // Since the written command may be read, it is read again when the written command is read.
                    do
                    {
                        response = serialPort.ReadLine().Trim();

                    } while (response == command);

                    serialPort.DiscardInBuffer();
                }
                catch (Exception e)
                {
                    Console.WriteLine("Error : " + e.Message);
                    serialPort.DiscardInBuffer();
                }

                return response;
            }
        }
    }
}
