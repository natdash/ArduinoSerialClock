#include "ClockAVIFace.h"

ClockAVIFace::ClockAVIFace(LiquidCrystal *lcd)
	:
	_lcd(lcd),
	_backlight(false)
{
	SetBacklight(true);
	BeginLCD();
}

ClockAVIFace::~ClockAVIFace()
{

}

void ClockAVIFace::IntToClockDigits(char *dest, int value)
{
	if (value >= 0 && value < 10)
	{
		dest[0] = '0';
		dest[1] = value + '0';
		dest[2] = '\0';
	}
	else
		itoa(value, dest, 10);
}

void ClockAVIFace::JoinStrings(char *dest, const char *strings[], int count)
{
	dest[0] = '\0';
	for (int i = 0; i < count; i++)
		strcat(dest, strings[i]);
}

const char *ClockAVIFace::GetMeridiem()
{
	return isAM() ? "AM" : "PM";
}

void ClockAVIFace::FillSpaces(char *buffer, int length)
{
	int i = 0;
	while(buffer[i] != '\0')
		i++;
	for(; i < length; i++)
		buffer[i] = ' ';
	buffer[i] = '\0';
}

void ClockAVIFace::DisplayTime()
{
	DisplayDateLine();
	DisplayTimeLine();
}

void ClockAVIFace::DisplayDateLine()
{
	char dayNumber[3];
	IntToClockDigits(dayNumber, day());

	char dayName[4];
	strcpy(dayName, dayShortStr(weekday()));

	char monthName[10];
	strcpy(monthName, monthStr(month()));

	const char *topLineComponents[] = { dayName, " ", dayNumber, " ", monthName };
	char topLine[17];
	JoinStrings(topLine, topLineComponents, 5);
	FillSpaces(topLine, 16);
	SetLCDLineText(topLine, 0);
}

void ClockAVIFace::DisplayTimeLine()
{
	char hours[3];
	char minutes[3];
	char seconds[3];
	char theYear[5];
	IntToClockDigits(hours, hourFormat12());
	IntToClockDigits(minutes, minute());
	IntToClockDigits(seconds, second());
	itoa(year(), theYear, 10);

	const char *bottomLineComponents[] = { hours, ":", minutes, ":", seconds, " ", GetMeridiem(), " ", theYear };
	char bottomLine[17];
	JoinStrings(bottomLine, bottomLineComponents, 9);

	SetLCDLineText(bottomLine, 1);
}

void ClockAVIFace::SetLCDLineText(const char *text, int line)
{
	_lcd->setCursor(0, line);
	_lcd->print(text);
}

void ClockAVIFace::BeginLCD()
{
	_lcd->begin(16, 2);
}

void ClockAVIFace::ToggleBacklight()
{
	_backlight = !_backlight;
	SetBacklight(_backlight);
}

void ClockAVIFace::SetBacklight(bool state)
{
	if (state)
		digitalWrite(BACKLIGHT_PIN,HIGH);
	else
		digitalWrite(BACKLIGHT_PIN,LOW);
}
