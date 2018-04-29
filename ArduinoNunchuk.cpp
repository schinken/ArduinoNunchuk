/*
 * ArduinoNunchuk.cpp - Improved Wii Nunchuk library for Arduino
 *
 * Copyright 2011-2013 Gabriel Bianconi, http://www.gabrielbianconi.com/
 *
 * Project URL: http://www.gabrielbianconi.com/projects/arduinonunchuk/
 *
 * Based on the following resources:
 * 	http://www.windmeadow.com/node/42
 *	http://todbot.com/blog/2008/02/18/wiichuck-wii-nunchuck-adapter-available/
 *	http://wiibrew.org/wiki/Wiimote/Extension_Controllers
 *
 * Modified by Iscle on 29/04/2018
 */


#include <Arduino.h> 
#include <Wire.h> 
#include "ArduinoNunchuk.h"

#define ADDRESS 0x52

void ArduinoNunchuk::begin() {
	Wire.begin();

	ArduinoNunchuk::_sendByte(0x55, 0xF0);
	ArduinoNunchuk::_sendByte(0x00, 0xFB);
}

bool ArduinoNunchuk::update() {
	uint8_t values[6];

	if (Wire.requestFrom(ADDRESS, 6) != 6) {
		return false;
	}

	for (uint8_t i = 0; Wire.available(); i++) {
		values[i] = Wire.read();
	}

	ArduinoNunchuk::analogX = values[0];
	ArduinoNunchuk::analogY = values[1];
	ArduinoNunchuk::accelX = (values[2] << 2) | ((values[5] >> 2) & 3);
	ArduinoNunchuk::accelY = (values[3] << 2) | ((values[5] >> 4) & 3);
	ArduinoNunchuk::accelZ = (values[4] << 2) | ((values[5] >> 6) & 3);
	ArduinoNunchuk::zButton = !((values[5] >> 0) & 1);
	ArduinoNunchuk::cButton = !((values[5] >> 1) & 1);

	return ArduinoNunchuk::_sendByte(0x00, 0x00);
}

bool ArduinoNunchuk::_sendByte(byte data, byte location) {
	Wire.beginTransmission(ADDRESS);

	Wire.write(location);
	Wire.write(data);

	return Wire.endTransmission() == 0;
}