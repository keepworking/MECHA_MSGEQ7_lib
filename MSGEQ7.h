// MSGEQ7.h
// Library for controlling MSGEQ7 Audio Spectrum Analyzer Chip (https://www.sparkfun.com/products/10468)
// Credit to J Skoba (http://nuewire.com/info-archive/msgeq7-by-j-skoba/) for the original implementation
// retouch by Yevgeny
// thanks to J Skoba , justinb26! 


#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include <thePins_arduino.h>
#endif

class MSGEQ7
{
	public:
		MSGEQ7();
		void init(int left, int right, int strobePin, int resetPin);
		void init();
		void poll();

		int getLValue(int index);
		int getRValue(int index);

	private:
		int L_pin; // read left value
		int R_pin; // read right value
		int strobePin; // strobe is attached to digital pin 2
		int resetPin; // reset is attached to digital pin 3

		int spectrumLValues[7]; 
		int spectrumRValues[7];
};
