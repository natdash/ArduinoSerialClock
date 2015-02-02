using System;
using System.IO.Ports;
using System.Threading;
using System.IO;

namespace ClockServer
{
	public class SerialClockTest
	{
		private static SerialPort _serialPort;
		private static ClockServer _server;

		public static void Main(string[] args)
		{
			Console.WriteLine("Arduino Serial Clock Test");

			if (InitialiseServer())
			{
				Listen();
			}

			Console.ReadKey();
		}

		private static bool InitialiseServer()
		{
			_serialPort = new SerialPort("/dev/tty.usbmodemfa131", 19200);

			if (_serialPort != null)
			{
				if (_serialPort.IsOpen)
					_serialPort.Close();

				try
				{
					_serialPort.Open();
					_server = new ClockServer(_serialPort.BaseStream);
				}
				catch (IOException exc)
				{
					Console.WriteLine("Error: {0}", exc.Message);
				}
			}

			return _server != null;
		}

		private static void Listen()
		{
			while (true)
			{
				_server.Listen();
				Thread.Sleep(1); // give the CPU some time back
			}
		}
	}
}

