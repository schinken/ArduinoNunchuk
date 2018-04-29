/*
 * ArduinoNunchuk.h - Improved Wii Nunchuk library for Arduino
 *
 * Copyright 2011-2013 Gabriel Bianconi, http://www.gabrielbianconi.com/
 *
 * Project URL: http://www.gabrielbianconi.com/projects/arduinonunchuk/
 *
 * Based on the following resources:
 *	http://www.windmeadow.com/node/42
 *	http://todbot.com/blog/2008/02/18/wiichuck-wii-nunchuck-adapter-available/
 *	http://wiibrew.org/wiki/Wiimote/Extension_Controllers
 *
 * Modified by Iscle on 29/04/2018
 */

#ifndef ArduinoNunchuk_H
#define ArduinoNunchuk_H

#include <Arduino.h>

class ArduinoNunchuk {
	public:
		uint8_t analogX;
		uint8_t analogY;
		uint8_t accelX;
		uint8_t accelY;
		uint8_t accelZ;
		bool zButton;
		bool cButton;

		void init();
		bool update(); // Returns true if update() was successful

	private:
		bool _sendByte(byte data, byte location);
};

#endif
