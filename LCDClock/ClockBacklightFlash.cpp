#include "ClockBacklightFlash.h"

ClockBacklightFlash::ClockBacklightFlash(ClockAVIFace *clockAVIFace, Worker *syncWorker)
	:
	_clockAVIFace(clockAVIFace),
	_backlight(false),
	Worker(syncWorker)
{

}

ClockBacklightFlash::~ClockBacklightFlash()
{
	_clockAVIFace->SetBacklight(true);
}

bool ClockBacklightFlash::DoWork()
{
	_clockAVIFace->SetBacklight(_backlight);
	_backlight = !_backlight;

	SetNextWorkTime(!_backlight ? 350 : 50);
	return true;
}
