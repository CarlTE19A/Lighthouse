 #include "RotEncoder.h"
#include "SerialInput.h"
#include "i2CDisplay.h"

void setup()  //Setup the Arduino to work correctly and display initial values
{
	Serial.begin(9600);
	pinMode(lightPin, OUTPUT);	//Sets up the pin for the led
  SetupRot(6, 7, 13);
  SetupDisplay();
  analogWrite(lightPin, 255);
  MenuDisplay();
}

void loop() //What to do every time the program updates (As fast as it can)
{
  RotToLightOS();
	SerialToLightOS();
  UpdateTime();
  characters[activeCharacter].Update();
}
void RotToLightOS() //Takes the input from the rotational encoder and does changes in the lightOS
{
  int x = CheckRot();
  if(x == -1)
  {
    MenuChangeOption(-1);
  }
  if(x == 1)
  {
    MenuChangeOption(1);
  }
  if(CheckRotButton() == true)
  {
    MenuActivateOption();
  }
}
void SerialToLightOS()  //Takes input from the serial connection to affect the OS
{
  int serialValue = SerialInput();
  if(serialValue != -1)
  {
    timeOffset = 0;
    activeCharacter = serialValue;  //Remove when Serial is improved
    //Do more stuff here
    Serial.println(activeCharacter);
  } 
}

float UpdateTime()	//To calculate when what should happen a few diffrent time stamps are necesasy
{
	unsigned long realMillis = millis();
	timeOffset += realMillis - prevFrame;
	frameTime = realMillis - prevFrame;
	prevFrame = realMillis;
  return frameTime;
}


//När en loop är klar blir timeOffset 0 igen
//När en ny LightCharacter vals blir timeOffset 0 igen

//Ifall timeOffset är ett värde så ska lampan vara ett visst ljus
//Basiclly så ska det finnas en curve där var timeOffset än är ska det finnas en ljusnivå den ska vara
//När loopen når slutet på yttre loopen(ifall den inte är 0 isåfall den innre) så blir timeOffset 0 igen och den börjar om

//ALLT MÅSTE VARA EXTREMT SNABBT OM KNAPPEN SKA FUNKA
//INTE UPPDATERA NÅGOT I ONÖDAN
