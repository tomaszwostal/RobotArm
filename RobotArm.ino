#include <PololuMaestro.h>

#ifdef SERIAL_PORT_HARDWARE_OPEN
#define maestroSerial SERIAL_PORT_HARDWARE_OPEN
#else
#include <SoftwareSerial.h>
SoftwareSerial maestroSerial(10, 11);
#endif

MicroMaestro maestro(maestroSerial);

const int joyX = A1;
const int joyY = A2;
const int joyClaw = A3;
const int swXY = 2;
const int swClaw = 3;

int X;
int Y;
int claw;
int XyButton;
int ClawButton;


void setup()
{
  maestroSerial.begin(9600);
  pinMode(swXY, INPUT_PULLUP);
  pinMode(swClaw, INPUT_PULLUP);
}

void loop()
{
  X = analogRead(joyX);
  X = map(X, 0, 1023, 922*4, 2000*4);

  Y = analogRead(joyY);
  Y = map(Y, 0, 1023, 922*4, 2000*4);

  claw = analogRead(joyClaw);
  claw = map(claw, 0, 1023, 922*4, 2000*4); 

  XyButton = digitalRead (swXY);
  ClawButton = digitalRead (swClaw);
  
  if (XyButton == 0) 
  {
    maestro.setTarget(0, X);
    maestro.setTarget(1, Y);
    delay(100);
  }
  else {
    maestro.setSpeed(0, 10);
    maestro.setAcceleration(0,127);
    maestro.setTarget(0, X);
    delay(100);

    maestro.setSpeed(1, 10);
    maestro.setAcceleration(1,127);
    maestro.setTarget(1, Y);
    delay(100);
  }
  
   if (ClawButton == 0) 
  {
    maestro.setTarget(2, claw);
    delay(100);
  }
  else {
    maestro.setSpeed(2, 10);
    maestro.setAcceleration(2,127);
    maestro.setTarget(2, claw);
    delay(100);
  }
  
}
