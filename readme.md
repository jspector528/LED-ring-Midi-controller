
I've got 4 WS2812 24 LED rings. The LEDs have a 5v, gnd, and data wire. I want to be able to control the HSV paramaters via MIDI, similar to a 
DMX light setup using the FastLED library.

The ideal would be to group the rings together through a single MIDI channel. so each ring would be a different midi channel.
The note (C4) would be to on/off, the velocity value to be able to select the color (MIDI allows 0-127, we can just have half the amount of control, so still 0-255),
the modulation to select saturation and the pitch bend to change the levels. That way we can control the HSV values

I found a code that works... kinda, it cycles through the lights like a knob instead of a light switch. and it uses to Adafruit Neopixel Library.
Any assistance would be great
