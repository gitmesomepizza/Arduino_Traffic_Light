//=====================================================
// PINS
//====================================================
const int red = 11;
const int yellow = 10;
const int green = 9;
const int button = 2;
//====================================================
// CONSTANTS
//====================================================
const int numModes = 11;
const int secondsGreen = 20;
const int secondsYellow = 4;
const int secondsRed = 20;
const int buttonPollsPerSecond = 20;
const int buttonPollsDelay = 1000/buttonPollsPerSecond;
const int delayAfterButton = 0;
//====================================================
// VARIABLES
//====================================================
int mode = 0;
int buttonState = 0;

// the setup routine runs once when you press reset:
void setup() {
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(button, INPUT);
}

// the loop routine runs over and over again forever:
void loop() 
{
  //lightDance();
  lightModeSelector();
  if(mode < numModes)
  {
    mode++;
  }
  else mode = 0;
  //clearLights();
  delay(delayAfterButton);
}

void lightModeSelector()
{
  if(mode == 0) //standard traffic light
  {
    while(!checkButton())
    {
      digitalWrite(green, HIGH);   // turn the green LED on (HIGH is the voltage level)
      if(pollButtonFor(secondsGreen)) return;
      digitalWrite(green, LOW);    // turn the green LED off by making the voltage LOW
      digitalWrite(yellow, HIGH);
      if(pollButtonFor(secondsYellow)) return;            
      digitalWrite(yellow, LOW); 
      digitalWrite(red,HIGH);
      if(pollButtonFor(secondsRed)) return;
      digitalWrite(red,LOW);
    }
  }
  else if(mode == 1) //flashing green
  {
    while(!checkButton())
    {
      digitalWrite(green,HIGH);
      if(pollButtonFor(1)) return;
      digitalWrite(green,LOW);
      if(pollButtonFor(1)) return;
    }
  }
  else if(mode == 2) //flashing yellow
  {
    while(!checkButton())
    {
      digitalWrite(yellow,HIGH);
      if(pollButtonFor(1)) return;
      digitalWrite(yellow,LOW);
      if(pollButtonFor(1)) return;
    }
  }
  else if(mode == 3) //flashing red
  {
    while(!checkButton())
    {
      digitalWrite(red,HIGH);
      if(pollButtonFor(1)) return;
      digitalWrite(red,LOW);
      if(pollButtonFor(1)) return;
    }
  }
  else if(mode == 4) //solid green
  {
    digitalWrite(green,HIGH);
    while(!checkButton())
    {
      delay(buttonPollsDelay);
    }
  }
  else if(mode == 5) //solid yellow
  {
    digitalWrite(yellow,HIGH);
    while(!checkButton())
    {
      delay(buttonPollsDelay);
    }
  }
  else if(mode == 6) //solid red
  {
    digitalWrite(red,HIGH);
    while(!checkButton())
    {
      delay(buttonPollsDelay);
    }
  }
  else if(mode == 7) //all lights flash
  {
    while(!checkButton())
    {
      setLights();
      if(pollButtonFor(1)) return;
      clearLights();
      if(pollButtonFor(1)) return;
    }
  }
  else if(mode == 8) //all lights on
  {
    setLights();
    while(!checkButton())
    {
      delay(buttonPollsDelay);
    }
  }
  //======================================================
  // PATTERNS
  //======================================================
  else if(mode == 9) //down
  {
    while(!checkButton())
    {
      digitalWrite(red,HIGH);
      if(pollButtonFor(1)) return;
      digitalWrite(red,LOW);
      digitalWrite(yellow,HIGH);
      if(pollButtonFor(1)) return;
      digitalWrite(yellow,LOW);
      digitalWrite(green,HIGH);
      if(pollButtonFor(1)) return;
      digitalWrite(green,LOW);
    }
  }
  else if(mode == 10) //up
  {
    while(!checkButton())
    {
      digitalWrite(green,HIGH);
      if(pollButtonFor(1)) return;
      digitalWrite(green,LOW);
      digitalWrite(yellow,HIGH);
      if(pollButtonFor(1)) return;
      digitalWrite(yellow,LOW);
      digitalWrite(red,HIGH);
      if(pollButtonFor(1)) return;
      digitalWrite(red,LOW);
    }
  }
  else if(mode == 11) //down and up
  {
    while(!checkButton())
    {
      digitalWrite(red,HIGH);
      if(pollButtonFor(1)) return;
      digitalWrite(red,LOW);
      digitalWrite(yellow,HIGH);
      if(pollButtonFor(1)) return;
      digitalWrite(yellow,LOW);
      digitalWrite(green,HIGH);
      if(pollButtonFor(1)) return;
      digitalWrite(green,LOW);
      digitalWrite(yellow,HIGH);
      if(pollButtonFor(1)) return;
      digitalWrite(yellow,LOW);
    }
  }
}

//turns on all lights
void setLights()
{
  digitalWrite(green, HIGH);
  digitalWrite(yellow, HIGH);
  digitalWrite(red, HIGH);
}

//turns off all lights
void clearLights()
{
  digitalWrite(green, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(red, LOW);
}

void lightDance()
{
  setLights();
  delay(200);
  clearLights();
  delay(200);
  setLights();
  delay(200);
  clearLights();
  delay(200);
}

void oldLightDance()
{
  digitalWrite(green, HIGH);
  delay(200);
  digitalWrite(green, LOW);
  digitalWrite(yellow, HIGH);
  delay(200);
  digitalWrite(yellow, LOW);
  digitalWrite(red, HIGH);
  delay(200);
  digitalWrite(red, LOW);
  delay(200);
}

//returns true if button is currently pushed (after button is released)
boolean checkButton()
{
  if(digitalRead(button) == HIGH) 
  {
    clearLights();
    while(digitalRead(button) == HIGH)
    {
      delay(20);
    }
    return true;
  }
  else return false;
}

boolean pollButtonFor(int seconds)
{
  for(int i = 0; i < seconds*buttonPollsPerSecond; i++)
  {
    delay(buttonPollsDelay);
    if(checkButton()) return true;
    else continue;
  }
  return false;
}