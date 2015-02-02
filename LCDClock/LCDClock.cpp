#include "LCDClock.h"

int lcdPins[] = { 8, 9, 4, 5, 6, 7 };
LCDSerialClock clock(10, lcdPins);

bool valid = true;
const char *time;
const char *song;

void setup()
{
	clock.SetTime(1);
	Serial.begin(19200);
}

void loop()
{
	if (Serial.available())
		clock.ProcessSerial();
	clock.UpdateDisplay();
	clock.CheckSync();
	clock.CheckInput();
}
