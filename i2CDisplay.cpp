#include "i2CDisplay.h"
#include "Arduino.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

static LiquidCrystal_I2C lcd(0x27, 16, 2);

void SetupDisplay()
{
  // initialize the LCD
  lcd.begin();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  displayPrintBoth(0, 0, "Startup", "Complete");
}

void displayPrintln(int posX, int posY, String in)
{
  lcd.setCursor(posX,posY);
  lcd.print(in);
}

void displayPrintBoth(int aOffset, int bOffset, String aString, String bString)
{
  Serial.print("a: ");
  Serial.print(aString);
  Serial.print(" | b: ");
  Serial.println(bString);
  
  lcd.clear();
  lcd.setCursor(aOffset, 0);
  lcd.print(aString + "                ");
  lcd.setCursor(bOffset,1);
  lcd.print(bString + "                ");
}
