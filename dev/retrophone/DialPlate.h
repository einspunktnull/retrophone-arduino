/*
 *  DialPlate.h - Library for use with DialPlates.
 *  Created by Albrecht Nitsche, October 22, 2010.
 *  Released into the public domain.
 */

#ifndef DialPlate_h
#define DialPlate_h

#include "Arduino.h"


class DialPlate
{
	public:
		DialPlate();
		void init(int dialPin, int impulsePin);
		int getCurrentNumberIfDialing();
	private:
		int _dialPin;
		int _impulsePin;
		int _currNum;
};

#endif 
