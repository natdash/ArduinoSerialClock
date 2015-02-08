using System;
using System.IO;
using System.Threading.Tasks;
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

		public bool Active = false;

		public DateTime LastActivity;

		private Stream _stream;

		public ClockServer (Stream stream)
		{
			_stream = stream;
		}

		public async Task ReadASync()
		{
			byte[] readByte = new byte[1];
			Task<int> task = _stream.ReadAsync (readByte, 0, 1);
			int x = await task;
			if (readByte[0] != 0) {
				LastActivity = DateTime.Now;
				char header = (char)readByte[0];
				Console.Write(header);
				
				switch((MessageType)header)
				{
				case MessageType.RequestTimestamp:
					{
						long timestamp = DateTime.Now.ToClockTimestamp();
						SendTimestamp(timestamp);
						SendLocalTimeZone();
						Active = true;
						//						SendAlarm (DateTime.Now.AddSeconds (10), "Wake up!");
						break;
					}
				}
			}

						return;
		}

		public void SendLocalTimeZone()
		{
			long offset = DateTime.Now.TimeZoneOffset();
			long hours = offset / 3600;
			long minutes = (offset % 3600) / 60;
			long timezone = hours * 100 + minutes;
			SendTimeZone (timezone);
		}

		public void SendAlarm(DateTime time, string message)
		{
			SendMessage (MessageType.SendAlarm, string.Format("{0}|{1}",time.ToClockTimestamp (),message));
		}

		public void SendTimeZone(long timezone)
		{
			SendMessage (MessageType.SendTimezone, string.Format ("{0}", timezone));
		}

		public void SendTimestamp(long timestamp)
		{
			SendMessage (MessageType.SendTimestamp, string.Format ("{0}", timestamp));
		}

		private void SendMessage(MessageType type, string message)
		{
			WriteMessage (string.Format ("{0}{1}\n", (char)type, message));
		}

		private void WriteMessage(string message) 
		{
			byte[] line = System.Text.ASCIIEncoding.Default.GetBytes(message);
			_stream.Write(line, 0, line.Length);
			Console.Write(message);
		}
	}

}

