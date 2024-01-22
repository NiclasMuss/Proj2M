// include the library code
#include "Arduino.h"
//Stepper library
#include <CheapStepper.h>

//I/O constants
#define IN  14

//Motor variables
CheapStepper stepper1 (2, 3, 4, 5);
CheapStepper stepper2 (9, 10, 11, 12);
//CheapStepper stepper3 (15, 16, 17, 18);

boolean moveClockwise = true;
int rotation = 0; //on full rotation is 4096 Steps

//I/O variable
int input = LOW;

void setup() {
  Serial.begin(115200); //IMPORTANT: Influences Motor speed
  pinMode(IN,INPUT); //initialize input
  }

void loop() {
  //read the input from the sensor module
  input = digitalRead(IN);
  //input= HIGH;
  Serial.println(input);

  if(input == HIGH){
    //rotate the motor by one step
    //rotateMotor();
    stepper1.step(moveClockwise);
    stepper2.step(moveClockwise);
    //stepper3.step(moveClockwise);
  }
  else{
  }
}
/*
void rotateMotor(){
  stepper.step(moveClockwise);
  rotation = rotation + 1;
  if(rotation > 4096){ //only rotate 360 degrees than turn (maybe not neccesary)
    moveClockwise = !moveClockwise;
    rotation = 0;
  }
}
*/