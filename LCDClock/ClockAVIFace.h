#ifndef _CLOCKAVIFACE_H_
#define _CLOCKAVIFACE_H_

#include <Time.h>
#include <LiquidCrystal.h>
#include <Wire.h>

#include "Arduino.h"
#include "ClockDefs.h"

class ClockAVIFace
{
private:
	LiquidCrystal *_lcd;
	bool _backlight;

	static void IntToClockDigits(char *dest, int value);
	static void JoinStrings(char *dest, const char *strings[], int count);
	static const char *GetMeridiem();
	static void FillSpaces(char *buffer, int length);

	void BeginLCD();

public:
	ClockAVIFace(LiquidCrystal *lcd);
	~ClockAVIFace();
	void SetLCDLineText(const char *text, int line);
	void DisplayTime();
	void DisplayDateLine();
	void DisplayTimeLine();
	void ToggleBacklight();
	void SetBacklight(bool state);
	void DisplayMessage(char* message);
};

#endif
