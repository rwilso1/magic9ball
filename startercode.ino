// Written by:
// Last Edited: Rashad Wilson
// TEC 284 Magic 8 Ball

//Arduino references can be found at: https://www.arduino.cc/reference/en/

//Necessary library files for the OLED and Accelerometer. Do not edit or delete!

#include <Arduino.h>
#include <U8x8lib.h>
#include "LIS3DHTR.h"

#ifdef SOFTWAREWIRE
    #include <SoftwareWire.h>
    SoftwareWire myWire(3, 2);
    LIS3DHTR<SoftwareWire> LIS; //Software I2C
    #define WIRE myWire
#else
    #include <Wire.h>
    LIS3DHTR<TwoWire> LIS; //Hardware I2C
    #define WIRE Wire
#endif

//Define a structure that holds your variables
struct Message {
  const char* text;
  const char* mood;
};

//Assign your 8 Ball answers and info into an array
Message messages[] = {
  {"For Sure", "Positive"},
  {"Yes", "Positive"},
  {"Definitely!", "Positive"},
  {"Maybe", "Neutral"},
  {"Not Sure...", "Neutral"},
  {"Ask Later", "Neutral"},
  {"I'm Tired", "Neutral"},
  {"No Way!", "Negative"},
  {"No", "Negative"},
  {"Nope", "Negative"}
};

const int messageCount = sizeof(messages) / sizeof(messages[0]);

U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE); //do not delete

//----------Messages----------------//
//Don't change the content here, but use this to create variables/array/data structure)

/*Message#    Message         Mood
  1           For Sure        Positive
  2           Yes             Positive
  3           Definitely!     Positive
  4           Maybe           Neutral
  5           Not Sure...     Neutral
  6           Ask Later       Neutral
  7           I'm Tired       Neutral
  8           No Way!         Negative
  9           No              Negative
  10          Nope            Negative
*/

void setup() {

  LIS.begin(WIRE, 0x19); //I2C init -- do not delete

  //debug below
  Serial.begin(9600);                                     
  u8x8.begin();
}

void loop() {
  static bool messageDisplayed = false;

  u8x8.setFont(u8x8_font_chroma48medium8_r); //do not edit or delete

  if (LIS.getAccelerationZ() > 2) {   //If the Grove board is shaken
    if (!messageDisplayed) {
      int index = random(messageCount);
      const char* msg = messages[index].text;

      u8x8.clear();
      u8x8.drawString(0, 2, "Magic 8 Ball:");
      u8x8.drawString(0, 4, msg);
      messageDisplayed = true;
      delay(3000);
    }
  }

  if (LIS.getAccelerationZ() >= 0.95 && LIS.getAccelerationZ() <= 1.05) {
    if (messageDisplayed) {
      u8x8.clear();
      messageDisplayed = false;
    }
  }
}
