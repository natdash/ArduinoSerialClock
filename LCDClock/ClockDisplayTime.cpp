#include "ClockDisplayTime.h"

ClockDisplayTime::ClockDisplayTime(ClockAVIFace *clockAVIFace)
	:
	_clockAVIFace(clockAVIFace)
{

}

ClockDisplayTime::~ClockDisplayTime()
{

}

bool ClockDisplayTime::DoWork()
{
	_clockAVIFace->DisplayTimeLine();
	SetNextWorkTime(500);
	return true;
}

