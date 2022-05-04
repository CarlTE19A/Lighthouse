//Menu varibles (not using classes as that takes slightly more memory)
void MenuChangeOption(int changeValue)  //Changes the active choice of option in a menu
{
  activeChoice += changeValue;
  activeChoice = constrain(activeChoice, 0, pgm_read_word_near(&menuLength[activeMenu]) - 1);
  MenuDisplay();
}
int GetRealActiveChoice() //As the activeChoice is relative to the active Menu this get the real index that shoulb be used in the array to get values
{
  int tempActiveChoice = activeChoice;
  for(int i = 0; i < activeMenu; i++)
  {
    tempActiveChoice += pgm_read_word_near(&menuLength[i]);
  }
  //Serial.print("Menu Length: ");
  //Serial.println(pgm_read_word_near(&menuLength[activeMenu]));
  return tempActiveChoice;
}

void MenuActivateOption() //Activate a specific Option to do what its role is
{
  //Serial.println("------------------------------------------");
  int realActiveChoice = GetRealActiveChoice();
  int tempType = pgm_read_word_near(&type[realActiveChoice]);
  int tempTarget = pgm_read_word_near(&target[realActiveChoice]);
  if(tempType == 0) //Active choice type is open Menu
  {
    activeChoice = 0;
    activeMenu = tempTarget;
    MenuDisplay();
    return;
  }
  else if(tempType == 1) //Active choice type is activate Function
  {
    if(tempTarget == 0)//Random Type
    {
      activeCharacter = random(0, 12);
    }
    else if(tempTarget == 1)//Random Time of active Type
    {
      Serial.println("random time");
    }
    else if(tempTarget == 2)//Random Time and Type
    {
      Serial.println("random both");
    }
    else if(tempTarget == 3)//LED Night Mode
    {
     if(maxLight == 255)
     {
      maxLight = 100; 
     }
     else
     {
      maxLight = 255;
     }
    }
    else if(tempTarget == 4)//Display Night Mode
    {
      if(displayBackLight == true)
     {
      displayBackLight = false;
      SetBacklight(false);
     }
     else
     {
      displayBackLight = true;
      SetBacklight(true);
     }
    }
    else if(tempTarget == 5)//Show active character
    {
      Serial.println(activeCharacter);
      displayPrintln(15, 1, String(activeCharacter));
    }
    return;
  }
  else if(tempType == 2) //Active choice type is open Menu
  {
    timeOffset = 0;
    activeCharacter = pgm_read_word_near(&target[realActiveChoice]);
    return;
  }
  Serial.println("Error : No recognized type");
}
void MenuDisplay()  //Show menu content the I2C Display
{
  int realActiveChoice = GetRealActiveChoice();
  if(pgm_read_word_near(&menuLength[activeMenu]) > activeChoice + 1)
  {
    displayPrintBoth(1, 1, (__FlashStringHelper *)pgm_read_word(&title[realActiveChoice]), (__FlashStringHelper *)pgm_read_word(&title[realActiveChoice + 1]));
    displayPrintln(0, 0, ">");
  }
  else
  {
    displayPrintBoth(1, 1, (__FlashStringHelper *)pgm_read_word(&title[realActiveChoice - 1]), (__FlashStringHelper *)pgm_read_word(&title[realActiveChoice]));
    displayPrintln(0, 1, ">");
  }
}
