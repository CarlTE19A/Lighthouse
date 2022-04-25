//Decleration for Rotational encoder Encoder
#ifndef _ROTENCODER_H    // Put these two lines at the top of your file.
#define _ROTENCODER_H    // (Use a suitable name, usually based on the file name.)//Define Pins for rotation encoder
#include "Arduino.h"

void SetupRot(int pinA, int pinB, int pinButton);
int CheckRot();
bool CheckRotButton();
#endif
