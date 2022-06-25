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


void myControlChange(byte channel, byte control, byte value)
{
  if (control == 0x01 ||  control == 0x02 || control == 0x03 || control == 0x04)
  {
    
    update_val(control, value);
    
  }
  if ( control == 0x05 ||  control == 0x06 || control == 0x07 || control == 0x08)
  {
    
    update_hue(control, value);
    //this function is used to update hue of selected ring
    //pitch send velocity of hue (0 ..127)
  }

  
}  
void handleNoteOn(byte channel, byte pitch, byte velocity)
{

//  if ( channel == 3 && (pitch == 0x3C ||  pitch == 0x3E || pitch == 0x40 || pitch == 0x41))
//  {
//    update_sat(channel, pitch, velocity);
   
  delay(1);
  on_off(pitch, 1); //this function is used to turn on or off specific ring
  

}

void handleNoteOff(byte channel, byte pitch, byte velocity)
{
  delay(1);
  on_off(pitch, 0); //this function is used to turn on or off specific ring
  
}




// -----------------------------------------------------------------------------

void setup()
{
  
  FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
  // Connect the handleNoteOn function to the library,
  // so it is called upon reception of a NoteOn.
  usbMIDI.setHandleControlChange(myControlChange);
  usbMIDI.setHandleNoteOn(handleNoteOn);  // Put only the name of the function
  usbMIDI.setHandleNoteOff(handleNoteOff);
  

}

void loop()
{
 
  usbMIDI.read();
  
}




void update_hue(byte control, byte value)  // This will update the velocity. Case 0x(midi note)
{
  byte target_ring = control;
  switch (target_ring)
  {
    case 0x05:
      ring1.hue = value * 2;
      break;
    case 0x06:

      ring2.hue = value * 2;
      break;
    case 0x07:

      ring3.hue = value * 2;
      break;
    case 0x08:

      ring4.hue = value * 2;
      break;
  }
}

//void update_sat(byte channel, byte pitch, byte velocity)  // This will update the saturation. Case 0x(midi note)
//{
//  byte target_ring = pitch;
//  switch (target_ring)
//  {
//    case 0x3C:
//      ring1.sat = velocity * 2;
//      break;
//    case 0x3E:
//      ring2.sat = velocity * 2;
//      break;
//    case 0x40:
//      ring3.sat = velocity * 2;
//      break;
//    case 0x41:
//      ring4.sat = velocity * 2;
//      break;
//  }
//}


void update_val(byte control, byte value) // This will update the levels/brightness. Case 0x(midi note) Also sends channel to val.
{
  byte target_ring = control;
  switch (target_ring)
  {
    case 0x01:
      ring1.val = value * 2;
      break;
    case 0x02:
      ring2.val = value * 2;
      break;
    case 0x03:
      ring3.val = value * 2;
      break;
    case 0x04 :
      ring4.val = value * 2;
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
