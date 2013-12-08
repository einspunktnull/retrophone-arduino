#ifndef Phone_h
#define Phone_h

#include "Arduino.h"
#include "DialPlate.h"
#include <GSM.h>

#define IMPULSE_TIME 100
#define NUM_MAX_LENGTH 20

#define STATE_NOT_CONNECTED 0
#define STATE_CONNECTED 1

class Phone
{
	public:
		Phone();
		void init(String simPinnumber, int dialPin, int impulsePin, int hangUpPin, int earthingPin);
		void update();
	private:
		int _state;
		String _dialedNumber;
		char _dialedNumberBuffer[NUM_MAX_LENGTH];
		char _simPinnumber[5];

		GSM _gsm;
		GSMVoiceCall _gsmVoiceCall;

		DialPlate _dialplate;

		int _hangUpPin;
		int _earthingPin;

		void reset();
		void setState(int state);
};

#endif

