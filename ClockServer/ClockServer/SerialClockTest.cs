using System;
using System.IO.Ports;
using System.Threading;
using System.Threading.Tasks;
using System.IO;

namespace ClockServer
{
	public class SerialClockTest
	{
		private static SerialPort _serialPort;
		private static ClockServer _server;
		private static bool _alarmSent = false;
		private static Task _task;

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
			_serialPort = new SerialPort("/dev/tty.usbmodemfd121", 19200);

			while (true) 
			{
				if (_serialPort != null)
				{
					if (_serialPort.IsOpen)
						_serialPort.Close();

					try
					{
						_serialPort.Open();
						_server = new ClockServer(_serialPort.BaseStream);
						break;
					}
					catch (IOException exc)
					{
						Console.WriteLine("Error: {0}", exc.Message);
					}
				}
			}
				
			return _server != null;
		}

		private static void Listen()
		{
			while (true) {
				if (_task == null) {
					_task = _server.ReadASync ();
				} else if (_task.IsCompleted) {
					_task = _server.ReadASync ();
				} else {
					if (_server.Active) {
						if (DateTime.Now.Subtract (_server.LastActivity).Seconds >= 5) {
							if (!_alarmSent) {
								_server.SendAlarm (DateTime.Now.AddSeconds (10), "Wake up!");
								_alarmSent = true;
							}
						}
					}
				}
				Thread.Sleep(1); // give the CPU some time back
			}
		}
	}
}

