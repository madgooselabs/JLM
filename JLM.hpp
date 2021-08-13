#pragma once
#include <Arduino.h>

class JLM
{
	private:
		uint8_t numberOfSamples;			// Self explanatory

		uint8_t pinX;					// Analog pin to read for X axis
		uint16_t centerX;				// Self explanatory
		uint16_t minX;
		uint16_t maxX;
		uint16_t deadzoneX;				// Deadzone from center on X axis
		uint16_t reverseDeadzoneX;			// Deadzone from edge on X axis
		uint16_t* rawX;					// Array of samples, X axis

		uint8_t pinY;					// Analog pin to read for Y axis
		uint16_t centerY;				// Self explanatory
		uint16_t minY;
		uint16_t maxY;
		uint16_t deadzoneY;				// Deadzone from center on Y axis
		uint16_t reverseDeadzoneY;			// Deadzone from edge on Y axis
		uint16_t* rawY;					// Array of samples, Y axis 

		uint8_t pinButton;				// Analog pin to read for button press
	public:
		JLM();
		void begin(uint8_t _samples, uint8_t _pinx, uint16_t _dzx, uint16_t _rdzx, uint8_t _piny, uint16_t _dzy, uint16_t _rdzy, uint8_t _pinBtn);
		void sample();
		uint16_t x;					// Average of samples on X axis
		uint16_t y;					// Average of samples on Y axis
		uint16_t button();				// Button (represented as a boolean because it doesn't give depth anyway)
};
