#ifndef _CLOCKDISPLAYTIME_H_
#define _CLOCKDISPLAYTIME_H_

#include <Time.h>

#include "Worker.h"
#include "ClockAVIFace.h"
#include "ClockAlarm.h"

class ClockDisplayTime : public Worker
{
private:
	ClockAVIFace *_clockAVIFace;

public:
	ClockDisplayTime(ClockAVIFace *clockAVIFace);
	~ClockDisplayTime();
	bool DoWork();
};

#endif


