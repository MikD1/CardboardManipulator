/*
* Pins:
* MISO -> 12
* MOSI -> 11
* SCK  -> 13
* CE   -> 8
* CSN  -> 7
*
* верх - 1;
* вправо - 2;
* вниз - 3;
* влево - 4;
* второй влево - 5
* второй вправо - 6
* кнопка - 7
* вторая кнопка - 8
* на месте - 0
*/

#include <RadioSimple.h>
#include <SPI.h>

int X = A0;
int Y = A1;
int Z = 3;
int X1 = A2;
int Z1 = 4;
bool button1State = false;
bool button2State = false;
Radio radio("pult5", 1, 1);

void setup()
{
  Serial.begin(9600);
  pinMode(X, INPUT);
  pinMode(Y, INPUT);
  pinMode(X1, INPUT);
  pinMode(Z, INPUT_PULLUP);
  pinMode(Z1, INPUT_PULLUP);
}

void loop()
{
  byte state = GetJoystickState();
  //Serial.println(state);
  if (state != 0)
  {
    radio.sendValue("robo5", state);
  }
}
byte GetJoystickState()
{
  int valueX = analogRead(X);
  int valueY = analogRead(Y);
  int valueX1 = analogRead(X1); //Sub
  if(!digitalRead(Z)&&!button1State)
  {
    button1State = true;
    return 7;
  }
  if(digitalRead(Z))
  {
    button1State = false;
  }
  if(!digitalRead(Z1)&&!button2State)
  {
    button2State = true;
    return 8;
  }
  if(digitalRead(Z1))
  {
    button2State = false;
  }
  if (valueY < 50)
  {
    return 2;
  }
  if (valueX > 975)
  {
    return 5;
  }
  if (valueY > 975)
  {
    return 4;
  }
  if (valueX < 50)
  {
    return 6;
  }
  if (valueX1 > 975)
  {
    return 1;
  }
  if (valueX1 < 50)
  {
    return 3;
  }
  return 0;
}
