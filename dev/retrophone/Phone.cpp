#include "Arduino.h"
#include "Phone.h"
#include "DialPlate.h"

Phone::Phone()
{
}

void Phone::init(String simPinnumber, int dialPin, int impulsePin, int hangUpPin, int earthingPin)
{
	Serial.println("Init Phone");

	setState(STATE_NOT_CONNECTED);

	reset();

	simPinnumber.toCharArray(_simPinnumber, 5);

	_dialplate.init(dialPin, impulsePin);

	_hangUpPin = hangUpPin;
	_earthingPin = earthingPin;

	boolean connected = false;

	while (!connected)
	{
		if (_gsm.begin(_simPinnumber) == GSM_READY)
		{
			connected = true;
			_gsmVoiceCall.hangCall();
			setState(STATE_CONNECTED);
		}
		else
		{
			Serial.println("Not connected");
			delay(1000);
		}
	}
	Serial.println("Now connected");

}

void Phone::reset()
{
	_dialedNumber = "";
}

void Phone::setState(int state)
{
	_state = state;

	Serial.print("_state: ");

	if (_state == STATE_NOT_CONNECTED)
	{
		Serial.println("STATE_NOT_CONNECTED");
	}
	else if (_state == STATE_CONNECTED)
	{
		Serial.println("STATE_CONNECTED");
	}
}

void Phone::update()
{

	if (_state == STATE_CONNECTED)
	{

		//delay(1000);

		bool hasHungUp = !digitalRead(_hangUpPin);

		switch (_gsmVoiceCall.getvoiceCallStatus())
		{
			case TALKING:
				Serial.println("TALKING");
				if (hasHungUp)
				{
					_gsmVoiceCall.hangCall();
				}
				break;
			case RECEIVINGCALL:
				Serial.println("RECEIVINGCALL");
				if (!hasHungUp)
				{
					_gsmVoiceCall.answerCall();
				}
				break;
			case CALLING:
				Serial.println("CALLING");
				if (hasHungUp)
				{
					_gsmVoiceCall.hangCall();
				}
				break;
			case IDLE_CALL:
				Serial.println("IDLE CALL");
				if (!hasHungUp)
				{
					int curNum = _dialplate.getCurrentNumberIfDialing();
					if (curNum != -1)
					{
						_dialedNumber += String(curNum);
						Serial.println(_dialedNumber);
					}

					//if earthing button pressed, try to call
					if (digitalRead(_earthingPin))
					{
						Serial.println();
						Serial.print("dialed number : ");
						Serial.println(_dialedNumber);

						if (_dialedNumber.length() < NUM_MAX_LENGTH)
						{
							if (_dialedNumber.indexOf('0') == 0)
							{
								_dialedNumber = "+49" + _dialedNumber.substring(1);
							}
							_dialedNumber.toCharArray(_dialedNumberBuffer, NUM_MAX_LENGTH);

							Serial.print("Number is okay: ");
							Serial.print(_dialedNumberBuffer);

							int voiceCallSuccess = _gsmVoiceCall.voiceCall(_dialedNumberBuffer);

							Serial.print("voiceCallSuccess: ");
							Serial.println(voiceCallSuccess);
						}
						else
						{
							Serial.println("Number is not okay, it is too long");
							reset();
						}
					}
				}
				else
				{
					reset();
				}
				break;
			default:
				Serial.println("DEINE MUTTER");
				break;
		}

	}

}
