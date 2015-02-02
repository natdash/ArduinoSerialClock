#ifndef CLOCKDEFS_H
#define CLOCKDEFS_H

const int COMMAND_LENGTH = 11;
const int SET_TIME = 'T';
const int WRITE_TIME = 'R';
const int SET_ALARM = 'A';
const int WRITE_ALARM = 'W';
const int SET_TIMEZONE = 'Z';
const char REQUEST_TIME = 'R';
const int SYNC_PERIOD = 120;

const int BACKLIGHT_PIN = 3;
const int INPUT_PIN = A0;

const int BUTTON_SIGNAL_SELECT = 741;
const int BUTTON_SIGNAL_RIGHT = 0;
const int BUTTON_SIGNAL_UP = 145;
const int BUTTON_SIGNAL_DOWN = 329;
const int BUTTON_SIGNAL_LEFT = 505;
const int BUTTON_SIGNAL_ERROR = 10;

const int BUTTON_NONE = 0;
const int BUTTON_SELECT = 1;
const int BUTTON_RIGHT = 2;
const int BUTTON_UP = 3;
const int BUTTON_DOWN = 4;
const int BUTTON_LEFT = 5;

#endif
