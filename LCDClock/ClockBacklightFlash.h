#ifndef _CLOCKBACKLIGHTFLASH_H_
#define _CLOCKBACKLIGHTFLASH_H_

#include <Wire.h>

#include "Arduino.h"
#include "Worker.h"
#include "ClockAVIFace.h"

class ClockBacklightFlash : public Worker
{
private:
	bool _backlight;
	ClockAVIFace* _clockAVIFace;

public:
	ClockBacklightFlash(ClockAVIFace* clockAVIFace, Worker *syncWorker = 0);
	~ClockBacklightFlash();
	bool DoWork();
};

#endif
