/*
  Proj2-M WS 2023/24
  Gyro-box Software
  Author: Niclas Muss
*/

// include the library code

//Ultrasonic library
#include <NewPing.h>

//Gyro libraries
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

//LED constants
#define LEDPIN          11    // Arduino pin tied to theLED.
#define LEDPIN2         9    // Arduino pin tied to the second LED.
#define LEDPIN3         8    // Arduino pin tied to the third LED.
#define LEDPIN4         10    // Arduino pin tied to the fourth LED.
#define FLICKERDURATION 5000  //How many Milliseconds the flicker effect should play for
#define FLICKERINTERVAL 50    //How many Milliseconds each flicker Interval should take

//Ultrasonic constants
#define TRIGGER_PIN     2     // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN        3     // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE    400   // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define DETECTION_DISTANCE 20 //Distance that counts as detection

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
int dist = 0;
int randomValue = 0;

//Gyro setup
MPU6050 accelgyro;
int16_t ax, ay, az;
int16_t gx, gy, gz;

const int LEDPINS[] = {LEDPIN, LEDPIN2, LEDPIN3, LEDPIN4};
const int NUM_LEDS = sizeof(LEDPINS) / sizeof(LEDPINS[0]);

void setup()
{
  pinMode(LEDPIN,OUTPUT); //initialize ledPin switch as an output
  pinMode(LEDPIN2,OUTPUT); //initialize ledPin switch as an output
  Serial.begin(115200);
  Wire.begin();
  accelgyro.initialize();
}

void loop() {

  //If the Box is lifted start flickering
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  //different values based on how the Gyro has been mounted
  if(gz>400 || gz<-200)  //when lifted (gy restingin vaslue was 200
  {
    flicker();
  }
  
  else  //when stationary
  {
    unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
    dist = uS / US_ROUNDTRIP_CM; //convert to cm
    if (dist < DETECTION_DISTANCE && dist != 0){ //Person is detected (this can be done better)
      turnLeds(HIGH);
    }
    else {
      turnLeds(LOW);
    }
  }
  delay (10);
}

void flicker(){
  unsigned long startTime = millis();

  while (millis() - startTime < FLICKERDURATION) {

    for (int i = 0; i < NUM_LEDS; i++) {
      digitalWrite(LEDPINS[i], random(2));
    }
   
    delay(50);
  }
}

void turnLeds(int state){
  for (int i = 0; i < NUM_LEDS; i++) {
      digitalWrite(LEDPINS[i], state);
    }
}
