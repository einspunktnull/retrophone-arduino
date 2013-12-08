/*
 *  DialPlate.cpp - Library for use with DialPlates.
 *  Created by Albrecht Nitsche, October 22, 2010.
 *  Released into the public domain.
 */

#include "Arduino.h"
#include "DialPlate.h"

#define IMPULSE_TIME 100

DialPlate::DialPlate()
{
}

void DialPlate::init(int dialPin, int impulsePin)
{
	_dialPin = dialPin;
	_impulsePin = impulsePin;
	_currNum = -1;

	pinMode(_dialPin, INPUT);
	pinMode(_impulsePin, INPUT);
}

int DialPlate::getCurrentNumberIfDialing()
{
	int c = 0;
	while (digitalRead(_dialPin))
	{
		if (!digitalRead(_impulsePin))
		{
			c++;
			delay (IMPULSE_TIME);
		}
	}
	if (c == 0 || c > 10) return -1;
	else if (c == 10) return 0;
	else return c;
}

