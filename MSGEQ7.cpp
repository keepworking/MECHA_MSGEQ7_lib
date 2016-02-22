// MSGEQ7.cpp
// Library for controlling MSGEQ7 Audio Spectrum Analyzer Chip (https://www.sparkfun.com/products/10468)
// Credit to J Skoba (http://nuewire.com/info-archive/msgeq7-by-j-skoba/) for the original implementation
// retouch by Yevgeny
// thanks to J Skoba, justinb26! 

#include "MSGEQ7.h"

MSGEQ7::MSGEQ7() 
{
	MSGEQ7::L_pin = A0;
	MSGEQ7::R_pin = A1;
	MSGEQ7::strobePin = 4;
	MSGEQ7::resetPin = 5;
}

void MSGEQ7::init(int left, int right, int strobePin, int resetPin)
{
	MSGEQ7::L_pin = left;
	MSGEQ7::R_pin = right;
	MSGEQ7::strobePin = strobePin;
	MSGEQ7::resetPin = resetPin;

	pinMode(MSGEQ7::L_pin, INPUT);
	pinMode(MSGEQ7::R_pin, INPUT);
	pinMode(MSGEQ7::strobePin, OUTPUT);
	pinMode(MSGEQ7::resetPin, OUTPUT);
	analogReference(DEFAULT);
}

void MSGEQ7::init()
{
	pinMode(MSGEQ7::L_pin, INPUT);
	pinMode(MSGEQ7::R_pin, INPUT);
	pinMode(MSGEQ7::strobePin, OUTPUT);
	pinMode(MSGEQ7::resetPin, OUTPUT);
	analogReference(DEFAULT);
}

void MSGEQ7::poll()
{
 digitalWrite(MSGEQ7::resetPin, HIGH);
 digitalWrite(MSGEQ7::resetPin, LOW);

 for (int i = 0; i < 7; i++)
 {
   digitalWrite(MSGEQ7::strobePin, LOW);
   delayMicroseconds(30); // to allow the output to settle
   MSGEQ7::spectrumLValues[i] = analogRead(MSGEQ7::L_pin);
   MSGEQ7::spectrumRValues[i] = analogRead(MSGEQ7::R_pin);  
   digitalWrite(MSGEQ7::strobePin, HIGH);
 }

 digitalWrite(MSGEQ7::resetPin, LOW);
 digitalWrite(MSGEQ7::strobePin, HIGH);
 delay(10);
}

int MSGEQ7::getLValue(int index)
{
	return MSGEQ7::spectrumLValues[index];
}

int MSGEQ7::getRValue(int index)
{
	return MSGEQ7::spectrumRValues[index];
}
