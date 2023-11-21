#include <SoftwareSerial.h>
#define joyX A0// for fowward and backward
#define joyY A1
#define joyX1 A2
#define joyY1 A3

SoftwareSerial Arduino_SoftSerial(10,11); //Rx,Tx

void setup() {
  
  Serial.begin(115200);
  Arduino_SoftSerial.begin(9600);
  delay(1000);

  Serial.println("Program Started");

}

void loop() {
   int xValue = analogRead(joyX);  
   int yValue = analogRead(joyY);
   int x1Value = analogRead(joyX1);  
   int y1Value = analogRead(joyY1);


//   Serial.print("X Value ");   
//   Serial.print(xValue);  
//   Serial.print("\t");     
//   Serial.print("Y Value " ); 
//   Serial.println(yValue);


   String direc = "XX \n";
 //for bot 
if((xValue >=200 && xValue <= 1000) && (yValue>=200 && yValue<=1000)){
  direc[0]= 'S';
}
 else if(xValue == 0){
  direc[0] = 'L';
 }
 else if(xValue>=1015){
  direc[0]= 'R';
 }
 else if(yValue==0){
  direc[0]= 'F';
 }
else if(yValue >= 1015){
  direc[0]= 'B';
}
//for gripper

if(x1Value >= 1015){
  direc[1]= 'O';
}
 else if(x1Value == 0){
  direc[1] = 'C';
 }



Serial.println(direc);
  
  Arduino_SoftSerial.print(direc);

  delay(500);
}
