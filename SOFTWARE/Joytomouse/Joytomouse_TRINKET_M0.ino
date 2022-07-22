 #include <Wire.h>
 #include <MPU6050_light.h>
 #include <Mouse.h>
 #include <Keyboard.h>
 
 MPU6050 mpu(Wire);
 unsigned long timer = 0;
 int Xang, Yang, Zang;
 int linderknop = 3; 
 int middenknop = 8;
 int rechterknop = 1;
 void setup() {
  
  pinMode(linderknop, INPUT_PULLUP);
  pinMode(middenknop, INPUT_PULLUP);
  pinMode(rechterknop, INPUT_PULLUP);

 
  Wire.begin();
  byte status = mpu.begin();
  while (status != 0) { } 
  delay(1000);
  mpu.calcOffsets(); 
  Mouse.begin();    
  Keyboard.begin(); 
 }



 void loop() {
 
 mpu.update();
    
 if ((millis() - timer) > 60) { 

  //Reading the MPU data
  Xang=mpu.getAngleX();
  Yang=mpu.getAngleY();
  Zang=mpu.getAngleZ();
  
  int liknopstate = digitalRead(linderknop);
  int miknopstate = digitalRead(middenknop);
  int reknopstate = digitalRead(rechterknop);
  bool vlagli = 0;
  bool vlagmi = 0;
  bool vlagre = 0;
    if ( liknopstate > 0){
    if (vlagli = 1){
    Mouse.release(MOUSE_LEFT);
    vlagli = 0;
    }
    }
  else {
    Mouse.press(MOUSE_LEFT);
    vlagli = 1;
    } 
    
  if ( miknopstate > 0){
    if (vlagmi = 1){
    Mouse.release(MOUSE_MIDDLE);
    vlagmi = 0;
    }
    }
  else {
    Mouse.press(MOUSE_MIDDLE);
    vlagmi = 1;
    } 
   
   if ( reknopstate > 0){
   if (vlagre = 1){
    Mouse.release(MOUSE_RIGHT);
    vlagre = 0;
    }
    }
  else {
    Mouse.press(MOUSE_RIGHT);
    vlagre=1;
    }   
    
    
   if ((Yang > 6) || (Yang < -6) || (Xang > 6) || (Xang < -6)){  
  
     if (Yang > 6){
     Yang = map(Yang, 6, 10, 1, 10);
     }

     else if (Yang < -6) {
     Yang = map(Yang, -10, -6, -10, -1); 
     }
      
     else if (Xang > 6) {  
     Xang = map(Xang, 6, 10, 1, 10); 
     }

     else if (Xang < -6) {
     Xang = map(Xang, -10, -6, -10, -1); 
     }
    
     Mouse.move(Yang, Xang, 0);
   }
  timer = millis();
   }}
