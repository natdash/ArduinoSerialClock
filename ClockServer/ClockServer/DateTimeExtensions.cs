using System;

namespace ClockServer
{
	public static class DateTimeExtensions
	{
		private static long _timestampOrigin = new DateTime(1970, 1, 1).Ticks;

		public static long ToClockTimestamp(this DateTime dateTime)
		{
			long timestamp = dateTime.ToUniversalTime().Ticks - _timestampOrigin;
			timestamp /= TimeSpan.TicksPerSecond;
			return timestamp;
		}

		public static long TimeZoneOffset(this DateTime dateTime)
		{
			long offset = dateTime.Ticks - dateTime.ToUniversalTime ().Ticks;
			offset /= TimeSpan.TicksPerSecond;
			return offset;
		}
	}
}

