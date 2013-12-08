

//This include is for using GSM in custom Phone library
#include <GSM.h>
#include "Phone.h"

/*
 * PIN ASSIGNMENT
 */
#define PIN_DI_DIALPLATE_IS_DIALING 10
#define PIN_DI_DIALPLATE_IMPULSES 9
#define PIN_DI_HANG_UP 8
#define PIN_DI_EARTHING_BUTTON 6

/*
 * MISC
 */
#define SIM_CARD_PIN "7851"

Phone phone;

void setup()
{
	Serial.begin(9600);
	phone.init(SIM_CARD_PIN, PIN_DI_DIALPLATE_IS_DIALING, PIN_DI_DIALPLATE_IMPULSES, PIN_DI_HANG_UP, PIN_DI_EARTHING_BUTTON);
}

void loop()
{
	phone.update();
}

