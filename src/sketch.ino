/**
 * A quick example arduino application to test some functions of the library
 */
#include "lencarta_ultrapro.h"

lencarta_ultrapro strobes(9,10);

byte strobeLeft[2] = {2,4};


void setup()
{
	Serial.begin(57600);
	strobes.begin();

}

void loop()
{
	strobes.flashPower(strobeLeft,30);
	delay(1000);
	strobes.lamp(1,3,LENC_LAMP_POW_ON,40);
	delay(1000);
	strobes.sound(1,3,true);
	delay(1000);
	strobes.slaveMode(1,3,true);
	delay(1000);
	if(strobes.fireFlash(strobeLeft))
		Serial.print("Fired strobe");

	if (strobes.test(1,3)) {
		Serial.print("Strobe exists");
	}

	delay(10000);
}
