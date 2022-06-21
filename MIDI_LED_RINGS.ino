#include <FastLED.h>
// How many leds in your strip?
#define NUM_LEDS 96

#define DATA_PIN 4

// Define the array of leds
CRGB leds[NUM_LEDS];
CHSV ring1(0, 255, 100);
CHSV ring2(0, 255, 100);
CHSV ring3(0, 255, 100);
CHSV ring4(0, 255, 100);
CHSV off(0, 0, 0);

// -----------------------------------------------------------------------------

void handleNoteOn(byte channel, byte pitch, byte velocity)
{

  if ( pitch == 0x24 ||  pitch == 0x26 || pitch == 0x28 || pitch == 0x29)
  {
    update_hue(pitch, velocity); //this function is used to update hue of selected ring
    //pitch send velocity of hue (0 ..127)
  }

  if ( channel == 2 && (pitch == 0x30 ||  pitch == 0x32 || pitch == 0x34 || pitch == 0x35))
  {
    update_val(channel, pitch, velocity);
  }

  if ( pitch == 0x3C ||  pitch == 0x3E || pitch == 0x40 || pitch == 0x41)
  {
    update_sat(pitch, velocity);
  }
  on_off(pitch, 1); //this function is used to turn on or off specific ring

}

void handleNoteOff(byte channel, byte pitch, byte velocity)
{
  on_off(pitch, 0); //this function is used to turn on or off specific ring

}

// -----------------------------------------------------------------------------

void setup()
{
  FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
  // Connect the handleNoteOn function to the library,
  // so it is called upon reception of a NoteOn.
  usbMIDI.setHandleNoteOn(handleNoteOn);  // Put only the name of the function
  Serial.println("code started");
  // Do the same for NoteOffs
  usbMIDI.setHandleNoteOff(handleNoteOff);

}

void loop()
{
  // Call MIDI.read the fastest you can for real-time performance.
  usbMIDI.read();
  delay(2);
}




void update_hue(byte pitch, byte velocity)  // This will update the velocity. Case 0x(midi note)
{
  byte target_ring = pitch;
  switch (target_ring)
  {
    case 0x24:
      ring1.hue = velocity * 2;
      break;
    case 0x26:

      ring2.hue = velocity * 2;
      break;
    case 0x28:

      ring3.hue = velocity * 2;
      break;
    case 0x29:

      ring4.hue = velocity * 2;
      break;
  }
}

void update_sat(byte pitch, byte velocity)  // This will update the saturation. Case 0x(midi note)
{
  byte target_ring = pitch;
  switch (target_ring)
  {
    case 0x3C:
      ring1.sat = velocity * 2;
      break;
    case 0x3E:
      ring2.sat = velocity * 2;
      break;
    case 0x40:
      ring3.sat = velocity * 2;
      break;
    case 0x41:
      ring4.sat = velocity * 2;
      break;
  }
}


void update_val(byte channel,byte pitch, byte velocity) // This will update the levels/brightness. Case 0x(midi note)
{
  byte target_ring = pitch;
  switch (target_ring)
  {
    case 0x30:
      ring1.val = velocity * 2;
      break;
    case 0x32:
      ring2.val = velocity * 2;
      break;
    case 0x34:
      ring3.val = velocity * 2;
      break;
    case 0x35 :
      ring4.val = velocity * 2;
      break;
  }
}


void on_off(byte pitch, byte velocity) // Making the rings with on/off accoring to velocity note
{
  byte target_ring = pitch;
  if (velocity == 1)
  {
    switch (target_ring)
    { 
      case 0x24:
        for (int i = 0; i < 24; i++)
        {
          leds[i] = ring1;
        }
        FastLED.show();
        break;
      case 0x26:
        for (int i = 0; i < 24; i++)
        {
          leds[i + 24] = ring2;
        }
        FastLED.show();
        break;
      case 0x28:
        for (int i = 0; i < 24; i++)
        {
          leds[i + 24 + 24] = ring3;
        }
        FastLED.show();
        break;
      case 0x29:
        for (int i = 0; i < 24; i++)
        {
          leds[i + 24 + 24 + 24] = ring4;
        }
        FastLED.show();
        break;
    }
  }
  else
  {

    switch (target_ring)
    {
      case 0x24:
        for (int i = 0; i < 24; i++)
        {
          leds[i] = off;
        }
        FastLED.show();
        break;
      case 0x26:
        for (int i = 0; i < 24; i++)
        {
          leds[i + 24] = off;
        }
        FastLED.show();
        break;
      case 0x28:

        for (int i = 0; i < 24; i++)
        {
          leds[i + 24 + 24] = off;
        }
        FastLED.show();
        break;
      case 0x29:
        for (int i = 0; i < 24; i++)
        {
          leds[i + 24 + 24 + 24] = off;
        }
        FastLED.show();
        break;
    }
  }

}
