//Definition File
//As all these need to be used everywhere they are defined here
#include "RotEncoder.h"
#include "SerialInput.h"
#include "i2CDisplay.h"

//Menu varibles (not using classes as that takes slightly more memory)
static int activeChoice = 0;
static int activeMenu = 0;
const char string0[] PROGMEM = "Random";
const char string1[] PROGMEM = "Quick Choose";
const char string2[] PROGMEM = "Settings";

const char string3[] PROGMEM = "Random Type";
const char string4[] PROGMEM = "Random Time";
const char string5[] PROGMEM = "Random Type and Time";
const char stringBack[] PROGMEM = "Tillbaka";

const char string6[] PROGMEM = "Fixed";
const char string7[] PROGMEM = "Flash";
const char string8[] PROGMEM = "Group Flash";
const char string9[] PROGMEM = "Quick";
const char string10[] PROGMEM = "Very Quick";
const char string11[] PROGMEM = "Continous Ultra Quick";
const char string12[] PROGMEM = "Long Flash";
const char string13[] PROGMEM = "Isophase";
const char string14[] PROGMEM = "Occulting";
const char string15[] PROGMEM = "Group Occulting";
const char string16[] PROGMEM = "Interupted Quick";
const char string17[] PROGMEM = "Fixed and Flash";

const char string18[] PROGMEM = "Night Mode";
const char string19[] PROGMEM = "Something else";
const char string20[] PROGMEM = "Oh that is cat";

const char *const title[] PROGMEM = {
  string0, string1, string2, 
  string3, string4, string5, stringBack, 
  string6, string7, string8, string9, string10, string11, string12, string13, string14, string15, string16, string17, stringBack, 
  string18, string19, string20, stringBack 
};

PROGMEM const int type[] = {  //OpenMenu = 0, ActivateFunction = 1, ActivateLight = 2
  0, 0, 0,
  1, 1, 1, 0,
  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0,
  1, 1, 1, 0
};

PROGMEM const int target[] = {
  1, 2, 3,
  0, 1, 2, 0,
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 0,
  3, 4, 5, 0
};
PROGMEM const int menuLength[] = {
  3, 4, 13, 4
};

//Normal Varibles
int activeCharacter = 1; //The LightCharacter is currently running
int lightPin = 9;  //The Pin slot for the Led lamp
float timeOffset;   //Time since last loop started
float frameTime;    //How many millis in the frame
float prevFrame;    //To only add time since last frame on timeOffset

int maxLight = 255; //Used as night mode need to lower this value

float currentLightValue = 0;  //The value that is displayed on the lamp
float lastCurrentLightValue = 0; //Only send new value if value has changed
float fixedLightValue = 0;     //The value that will not be inverted and alike (There should never be a need to invert back and forth)
