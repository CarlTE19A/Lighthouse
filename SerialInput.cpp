#include "SerialInput.h"
#include "Arduino.h"
int activeReciveRefrence = 10;

int SerialInput()
{
  if (Serial.available() > 0)
  {
    int recivedMsg = Serial.read();
    if(activeReciveRefrence != 10)  //10 is a line feed so should never be used normally
    {
      if(activeReciveRefrence == 48 && recivedMsg >= 48 && recivedMsg <= 57)  //Starts with 0
      {
        activeReciveRefrence = 10;
        return(recivedMsg - 48);  //To remove from the value sent over Serial to use
      }
      else if(activeReciveRefrence == 49 && recivedMsg >= 48 && recivedMsg <= 50)  //Starts with 1
      {
        activeReciveRefrence = 10;
        return(recivedMsg - 38);  //To remove from the value sent over Serial
      }
      activeReciveRefrence = recivedMsg;
      return(-1);
    }
    if(recivedMsg == 104 || recivedMsg == 72) //is h || H
    {   //A help menu what you can send over Serial
      Serial.println("00 = Fixed");
      Serial.println("01 = Flash");
      Serial.println("02 = Group Flash");
      Serial.println("03 = Quick");
      Serial.println("04 = Very Quick");
      Serial.println("05 = Continous ultra quick");
      Serial.println("06 = Long Flash");
      Serial.println("07 = Isophase");
      Serial.println("08 = Occulting");
      Serial.println("09 = Group Occulting (May not be working correctly)");
      Serial.println("10 = Interupted Quick (May not be working correctly)");
      Serial.println("11 = Fixed and Flash");
      recivedMsg = 10;
    }
    activeReciveRefrence = recivedMsg;
  }
  return(-1);
}
