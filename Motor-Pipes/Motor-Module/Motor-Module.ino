// include the library code
#include "Arduino.h"
//Stepper library
#include <CheapStepper.h>

//I/O constants
#define IN  14
#define OUT 8

//Motor variables
CheapStepper stepper (2, 3, 4, 5);
boolean moveClockwise = true;
int rotation = 0; //on full rotation is 4096 Steps

//I/O variable
int input = LOW;

void setup() {
  Serial.begin(115200); //IMPORTANT: Influences Motor speed
  pinMode(IN,INPUT); //initialize input
  pinMode(OUT,OUTPUT); //initialize output
  digitalWrite(OUT,LOW); //set the initial output to low
  }

void loop() {
  //read the input from the sensor module
  input = digitalRead(IN);
  Serial.println(input);

  if(input == HIGH){
    //rotate the motor by one step
    //rotateMotor();
    stepper.step(moveClockwise);

    digitalWrite(OUT,HIGH);
  }
  else{
    digitalWrite(OUT,LOW);
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