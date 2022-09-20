/************************************************************************
This code is a mix of DIY MPU-6050 Joystick https://www.instructables.com/DIY-MPU-6050-USB-Joystick/ Pin_Joystick, code written by Pin Chung
and joystick_simple, code written by gdsports https://github.com/gdsports/xac_joystick_tinyusb/blob/main/examples/joystick_simple/joystick_simple.ino
MIT License
Copyright (c) 2022 makergo@apf.asso.fr
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*************************************************************************/

#include "xac_joystick_tinyusb.h"
#include <MPU6050_tockn.h>
#include <Wire.h>
TUJoystick Joystick;
MPU6050 mpu6050(Wire);


#define ResetPin 3

int lastButtonState=0;
int currentButtonState;

float zeroX=0;
float zeroY=0;
float zeroZ=0;

//upper and lower limit on the angle of the MPU6050 board range.
int upperLimit = 20;
int lowerLimit = -20;

void setup()
{
  Joystick.begin();

  // wait until device mounted
  while( !USBDevice.mounted() ) delay(1);

  pinMode(ResetPin, INPUT_PULLUP);
   
 Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(false);
}

void ResetMPU6050(float x, float y, float z){
  //Center the Joystick at current position
  zeroX=x;
  zeroY=y;
  zeroZ=z;
 
}

void loop()
{  
   mpu6050.update();
   float x=mpu6050.getAngleX();
   float y=mpu6050.getAngleY();
   float z=mpu6050.getAngleZ();
   
   if (!digitalRead(ResetPin)) {
    ResetMPU6050(x,y,z); }

  x-=zeroX;
  y-=zeroY;
  z-=zeroZ;
  
   if (x>upperLimit) x=upperLimit;
   else if (x<lowerLimit) x=lowerLimit;
   if (y>upperLimit) y=upperLimit;
   else if (y<lowerLimit) y=lowerLimit;
   if (z>upperLimit) z=upperLimit;
   else if (z<lowerLimit) z=lowerLimit;

  // Move x/y Axis to a random position
  Joystick.xAxis(map(y, lowerLimit,upperLimit, 0,255));
  Joystick.yAxis(map(x, lowerLimit,upperLimit, 0,255));
  

  // Functions above only set the values.
  // This writes the report to the host.
   Joystick.loop();}
