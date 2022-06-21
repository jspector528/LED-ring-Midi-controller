
I've got 4 WS2812 24 LED rings. The LEDs have a 5v, gnd, and data wire. I want to be able to control the HSV paramaters via MIDI, similar to a 
DMX light setup using the FastLED library.

The newest upload one is designed for Teensy 4.0
C1 D1 E1 F1 - These are on/off, and velocity controls the Hue
C2 D2 E2 F2 - Velocity value controls Brightness
C3 D3 E3 F3 - Velocity value control saturation

Still some kinks that need to be buffed out - like being able to update color while LED is on without having to add new note.
