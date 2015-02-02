using System;
using System.IO;
using System.Security.Cryptography;

namespace ClockServer
{
	public class ClockServer
	{
		private enum MessageType
		{
			SendTimestamp = 'T',
			SendAlarm = 'A',
			RequestTimestamp = 'R',
			SendTimezone = 'Z'
		}

		private Stream _stream;

		public ClockServer (Stream stream)
		{
			_stream = stream;
		}

		public void Listen()
		{
			char header = (char)_stream.ReadByte();
			Console.Write(header);

			switch((MessageType)header)
			{
				case MessageType.RequestTimestamp:
					{
						long timestamp = DateTime.Now.ToClockTimestamp();
						SendTimestamp(MessageType.SendTimestamp, timestamp);
						SendTimezone();
						break;
					}
			}
		}

		public void SendTimezone()
		{
			long offset = DateTime.Now.TimeZoneOffset();
			long hours = offset / 3600;
			long minutes = (offset % 3600) / 60;
			long timezone = hours * 100 + minutes;
			SendTimestamp (MessageType.SendTimezone, timezone);
		}

		public void SendAlarm(DateTime time)
		{
			SendTimestamp(MessageType.SendAlarm, time.ToClockTimestamp());
		}

		private void SendTimestamp(MessageType type, long timestamp)
		{
			string message = string.Format("{0}{1}\n", (char)type, timestamp);
			WriteMessage(message);
		}

		private void WriteMessage(string message) 
		{
			byte[] line = System.Text.ASCIIEncoding.Default.GetBytes(message);
			_stream.Write(line, 0, line.Length);
			Console.Write(message);
		}
	}

}

