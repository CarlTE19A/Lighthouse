class LightCharacter
{
	private:
	  int totalTime;
	  int onTime;
	  bool occulting;
	  float rampTime;
	  float rampPerMilli;
	  int minLight;
    int loopTime;
    int loopAmmount;

	public:
	  String characterName;  //The name of this lightCharacter  (For interface)
	  LightCharacter(String characterName, int totalTime, int onTime, float rampTime);
	  LightCharacter(String characterName, int totalTime, int onTime, float rampTime, bool occulting, int minLight);
    LightCharacter(String characterName, int totalTime, int onTime, float rampTime, bool occulting, int loopTime, int loopAmmount);
	  void Update();
    float LoopControl();
};

LightCharacter::LightCharacter(String characterName, int totalTime, int onTime,float rampTime)  //Declare Simple
{
	this->characterName = characterName;
	this->totalTime = totalTime;
	this->onTime = onTime;
	this->rampTime = rampTime;
	occulting = false;
	minLight = 0;
	rampPerMilli = (maxLight-minLight)/rampTime;

  loopTime = totalTime;
  loopAmmount = 1;
}

LightCharacter::LightCharacter(String characterName, int totalTime, int onTime, float rampTime, bool occulting, int minLight)  //Declare with choice of inverted
{
	this->characterName = characterName;
	this->totalTime = totalTime;
	this->onTime = onTime;
	this->minLight = minLight;
	this->rampTime = rampTime; 
	this->occulting = occulting; 
	rampPerMilli = (maxLight-minLight)/rampTime;

  loopTime = totalTime;
  loopAmmount = 1;
}

LightCharacter::LightCharacter(String characterName, int totalTime, int onTime, float rampTime, bool occulting, int loopTime, int loopAmmount) //Declare with choice of grouped
{ //Creates instance with correct values
	this->characterName = characterName;
  this->totalTime = totalTime;
  this->onTime = onTime;
  this->rampTime = rampTime; 
  this->occulting = occulting; 
  rampPerMilli = (maxLight-minLight)/rampTime;

  //Unique for Grouped
	this->loopTime = loopTime; 
	this->loopAmmount = loopAmmount;
}

void LightCharacter::Update() //Change the light every frame to do anything at all
{
  if(timeOffset >= totalTime)
  {
    timeOffset -= totalTime;
  }
  fixedLightValue = LoopControl();
  fixedLightValue = constrain(fixedLightValue, minLight, maxLight);
  currentLightValue = fixedLightValue;
  if(occulting)
  {
    currentLightValue = maxLight - fixedLightValue;
  }
  if(currentLightValue != lastCurrentLightValue)
  {
    analogWrite(lightPin, currentLightValue);
  }
  lastCurrentLightValue = currentLightValue;
}
float LightCharacter::LoopControl() //Return what value the light should have now based on where in the loops it is
{
  float tempLightValue = fixedLightValue;
  for(int i = 0; i < loopAmmount; i++)
  {
    if(timeOffset >= loopTime * i && timeOffset <= loopTime * i + onTime)
    { //If inside the onTime of a loop  
      if(timeOffset <= loopTime * i + rampTime)
      { //Ramp up the light level
        tempLightValue += rampPerMilli * frameTime;
      }
      else if(timeOffset >= loopTime * i + onTime - rampTime)
      { //Ramp up the light level
        tempLightValue -= rampPerMilli * frameTime;
      }
      else
      {
        return 255;
      }
      return tempLightValue;
    }
  }
  tempLightValue = 0; //If not in onTime
  return tempLightValue;
}
LightCharacter characters[] = 
{
  LightCharacter("Fixed",                 1,      1,      0),
  LightCharacter("Flash",                 3000,   800,    100),
  LightCharacter("Group Flash",           8000,   900,    100, false, 2000, 2),
  LightCharacter("Quick",                 1200,   600,    75),
  LightCharacter("Very Quick",            800,    400,    50),
  LightCharacter("Continous ultra quick", 300,    150,    25),
  LightCharacter("Long Flash",            8000,   2500,   150),
  LightCharacter("Isophase",              10000,  5000,   175),
  LightCharacter("Occulting",             6000,   1400,   100, true,  0),
  LightCharacter("Group Occulting",       8000,   1400,   100, true,  3000, 2),
  LightCharacter("Interupted Quick",      12000,  600,    50, false, 1200, 7),
  LightCharacter("Fixed And Flash",       3000,   800,    100, false, 10),
};
