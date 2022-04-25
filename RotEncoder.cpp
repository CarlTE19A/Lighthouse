#include "RotEncoder.h"
#include "Arduino.h"
int rotAPin;
int rotBPin;
int rotButton;

int lastA;
int lastB;
int rotatingTowards; //A = -1 B = 1

int lastButton;

void SetupRot(int pinA, int pinB, int pinButton)
{
  rotAPin = pinA;
  rotBPin = pinB;
  rotButton = pinButton;
  //Define Pins here and not on declaration as by spliting it to .h and .cpp its a library so should not be defined at decleration
	pinMode(rotAPin, INPUT);
	pinMode(rotBPin, INPUT);
  pinMode(rotButton, INPUT);
}

int CheckRot() {
	int a = digitalRead(rotAPin);
	int b = digitalRead(rotBPin);
  int answer = 0;
	if((a!= lastA || b != lastB)) //There is any change at all
	{
    	if(a == 0 && b == 0)  //Actully send rotate signal only if rotation was not only started but also continued
    	{
    		if(rotatingTowards == -1)
        {
				    answer = -1;
        }
        if(rotatingTowards == 1)
        {
        	answer = 1;
        }
    	}
    	else if(a == 0 && !(lastA == 0 || lastB == 0))  //Began Rotating towards A / Left
    	{
    		rotatingTowards = -1;
    	}
    	else if(b == 0 && !(lastA == 0 || lastB == 0))  //Began Rotating towards B / Right
    	{
    		rotatingTowards = 1;
    	}
    	if(a == 1 && b == 1)
    	{
    		rotatingTowards = 0;
    	}
	}
  lastA = a;
  lastB = b;
  return(answer);
}
bool CheckRotButton() //Checks if the button function of the rotational encoder works
{
  int button = digitalRead(rotButton);
  if(button == LOW && lastButton == HIGH)
  {
    lastButton = button;
    return(true);
  }
  lastButton = button;
  return(false);
}
