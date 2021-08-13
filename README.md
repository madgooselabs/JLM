[![License](https://img.shields.io/badge/License-BSD%203--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)

# JLM interface library

Allows one to easily port JLM reading/smoothing code and stack interfaces on top, regardless of the board. So long as said board has an Arduino core anyway.


# How do I shot web

```c
#include <JLM.hpp>

JLM jlm;
char buf[512];

void setup()
{
	jlm.begin(sampleRate, analogPinX, deadzoneX, reverseDeadzoneX, analogPinY, deadzoneY, reverseDeadzoneY, analogPinButton);
}

void loop()
{
	jlm.sample();
	
	// Do whatever with the inputs
}
```

Access the JLM readings through the attributes x, y, and the button() method.

# TODO

* Button
* "Debouncer" for fast reversing
