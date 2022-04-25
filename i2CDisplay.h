//Decleration for Rotational encoder Encoder
#ifndef _I2CDISPLAY_H    // Put these two lines at the top of your file.
#define _I2CDISPLAY_H    // (Use a suitable name, usually based on the file name.)//Define Pins for rotation encoder
#include "Arduino.h"

void SetupDisplay();
void displayPrintln(int posX, int posY, String in);
void displayPrintBoth(int aOffset, int bOffset, String aString, String bString);
#endif
