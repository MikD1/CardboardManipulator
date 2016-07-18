/*
* Pins:
* MISO -> 12
* MOSI -> 11
* SCK  -> 13
* CE   -> 8
* CSN  -> 7
* верх - 1;
* право - 2;
* вниз - 3;
* лево - 4;
* второй вправо - 5
* второй влево - 6
* кнопка - 7
* вторая кнопка - 8
* на месте - 0;
* A-base B-main C-sub
*/

#include <RadioSimple.h>
#include <SPI.h>
#include<Servo.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

byte ClawState = 0;
byte LedState = 0;

int MotorAStep = 2;
int MotorAPin = 3;
int MotorBStep = 4;
int MotorBPin = 5;
int MotorCStep = 6;
int MotorCPin = 9;
int ClawPin = 10;
int ledPin = A0;
int repeatStep = 1;

Radio radio("robo5", 2, 1);
Servo claw;
Adafruit_NeoPixel led = Adafruit_NeoPixel(78, ledPin, NEO_BRG + NEO_KHZ800);

void setup()
{
  pinMode(MotorAPin, OUTPUT);
  pinMode(MotorAStep, OUTPUT);
  pinMode(MotorBStep, OUTPUT);
  pinMode(MotorBPin, OUTPUT);
  pinMode(MotorCPin, OUTPUT);
  pinMode(MotorCStep, OUTPUT);
  pinMode(ClawPin, OUTPUT);
  claw.attach(ClawPin);
  led.begin();
  led.show();
}

void loop()
{
  if (radio.available())
  {
    byte state = radio.receiveValue();
    switch (state)
    {
      case 1: //Sub
        MakeStepC(HIGH);
        break;
      case 2: //Main
        MakeStepB(LOW);
        MakeStepC(LOW);
        break;
      case 3: //Sub
        MakeStepC(LOW);

        break;
      case 4: //Main
        MakeStepB(HIGH);
        MakeStepC(HIGH);
        break;
      case 5: //Left base
        MakeStepA(LOW);
        break;
      case 6: //Right base
        MakeStepA(HIGH);
        break;
      case 7:
        if (ClawState = 0)
        {
          OpenClaw();
        }
        else
        {
          CloseClaw();
        }
        break;
      case 8:
        switch (LedState)
        {
          case 0:
            LedState = 1;
            colorWipe(led.Color(0, 0, 255)); //green
            led.show();
            break;
          case 1:
            LedState = 2;
            colorWipe(led.Color(255, 0, 0));
            led.show();
            break;
          case 2:
            LedState = 3;
            colorWipe(led.Color(0, 255, 0)); //purple
            led.show();
            break;
          case 3:
            LedState = 4;
            colorWipe(led.Color(255, 255, 255)); //blue-white
            led.show();
            break;
          case 4:
            LedState = 0;
            colorWipe(led.Color(0, 0, 0));
            led.show();
            break;
        }
    }
  }
}

void MakeStepA(int direction)
{
  for (int i = 0; i <= repeatStep; i++)
  {
    digitalWrite(MotorAStep, direction);
    digitalWrite(MotorAPin, HIGH);
    delayMicroseconds(100);
    digitalWrite(MotorAPin, LOW);
    delayMicroseconds(100);
  }
}
void MakeStepB(int direction)
{
  for (int i = 0; i <= repeatStep; i++)
  {
    digitalWrite(MotorBStep, direction);
    digitalWrite(MotorBPin, HIGH);
    delayMicroseconds(100);
    digitalWrite(MotorBPin, LOW);
    delayMicroseconds(100);
  }
}
void MakeStepC(int direction)
{
  for (int i = 0; i <= repeatStep; i++)
  {
    digitalWrite(MotorCStep, direction);
    digitalWrite(MotorCPin, HIGH);
    delayMicroseconds(100);
    digitalWrite(MotorCPin, LOW);
    delayMicroseconds(100);
  }
}
void OpenClaw()
{
  claw.write(177);
  ClawState = 1;
}
void CloseClaw()
{
  claw.write(130);
  ClawState = 0;
}
void colorWipe(int c)
{
  for (int i = 0; i < led.numPixels(); i++)
  {
    led.setPixelColor(i, c);
    led.show();
  }
}
