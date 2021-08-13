#include "JLM.hpp"

JLM::JLM()
{
}

void JLM::begin(uint8_t _samples, uint8_t _pinx, uint16_t _dzx, uint16_t _rdzx, uint8_t _piny, uint16_t _dzy, uint16_t _rdzy, uint8_t _pinBtn)
{
	// Set sample "rate"
	if (_samples > 0)
	{
		numberOfSamples = _samples;
	}
	else
	{
		// TODO: Figure a way to make this actually work
		//#pragma message ("WARNING: Number of samples set to a value inferior to 1; defaulting to 1")
		numberOfSamples = 1;
	}

	// Set axes
	pinX = _pinx;
	deadzoneX = _dzx;
	reverseDeadzoneX = _rdzx;
	
	pinY = _piny;
	deadzoneY = _dzy;
	reverseDeadzoneY = _rdzy;

	pinButton = _pinBtn;
	
	// Read initial values and pray for the lever to not be tilted someway already
	centerX = analogRead(pinX);
	centerY = analogRead(pinY);

	// Infer min and max axial values; empirical tests showed a range of +/- 200 so we're using that as a base
	minX = centerX - 200;
	maxX = centerX + 200;
	minY = centerY - 200;
	maxY = centerY + 200;

	// Allocate memory for the sample arrays
	rawX = (uint16_t*)calloc(numberOfSamples, sizeof(uint16_t));
	rawY = (uint16_t*)calloc(numberOfSamples, sizeof(uint16_t));
}

void JLM::sample()
{
	// Run it every cycle
	static uint8_t counter = 0;

	if (counter < numberOfSamples)
	{
		rawX[counter] = analogRead(pinX);
		rawY[counter] = analogRead(pinY);
		counter++;
	}
	else
	{
		x = 0;
		y = 0;

		for (int i = 0; i < numberOfSamples; i++)
		{
			x += rawX[i];
			y += rawY[i];
		}
		x = x / numberOfSamples;
		y = y / numberOfSamples;

		// Deadzone handling
		if ((x >= centerX - deadzoneX) && (x <= centerX + deadzoneX))
			x = centerX;
		if ((y >= centerY - deadzoneY) && (y <= centerY + deadzoneY))
			y = centerY;
		// Reverse deadzone handling
		if (x <= minX + reverseDeadzoneX)
			x = minX;
		else if (x >= maxX - reverseDeadzoneX)
			x = maxX;
		if (y <= minY + reverseDeadzoneY)
			y = minY;
		else if (y >= maxY - reverseDeadzoneY)
			y = maxY;

		x = map(x, minX, maxX, 0, 1023);
		y = map(y, minY, maxY, 1023, 0);	// Y-axis needs reversing

		counter = 0;
	}
}

uint16_t JLM::button()
{
	return analogRead(pinButton);
}
