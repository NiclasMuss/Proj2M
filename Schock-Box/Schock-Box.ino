// include the library code

//Ultrasonic library
#include <NewPing.h>

//Gyro libraries
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

//LED constants
#define LEDPIN          11    // Arduino pin tied to theLED.
#define LEDPIN2         12    // Arduino pin tied to the second LED.
#define LEDPIN3         13    // Arduino pin tied to the third LED.
#define LEDPIN4         14    // Arduino pin tied to the fourth LED.
#define FLICKERDURATION 5000  //How many Milliseconds the flicker effect should play for
#define FLICKERINTERVAL 50    //How many Milliseconds each flicker Interval should take

//Ultrasonic constants
#define TRIGGER_PIN     2     // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN        3     // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE    400   // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define DETECTION_DISTANCE 10 //Distance that counts as detection

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
int dist = 0;
int randomValue = 0;

//Gyro setup
MPU6050 accelgyro;
int16_t ax, ay, az;

const int LEDPINS[] = {LEDPIN, LEDPIN2, LEDPIN3, LEDPIN4};
const int NUM_LEDS = sizeof(LEDPINS) / sizeof(LEDPINS[0]);

void setup()
{
  pinMode(LEDPIN,OUTPUT); //initialize ledPin switch as an output
  pinMode(LEDPIN2,OUTPUT); //initialize ledPin switch as an output
  Serial.begin(115200);
  Wire.begin();
  accelgyro.initialize(); //TODO: Offset
}

void loop() {

  //Print Ping in the Serial Monitor
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  dist = uS / US_ROUNDTRIP_CM; //convert to cm
  Serial.print("Ping: ");
  Serial.print(dist);
  Serial.println("cm");
  //TODO: Maybe move this part

  //If the Box is lifted start flickering
  accelgyro.getAcceleration(&ax, &ay, &az); //get Accelearation value
  Serial.println(az);
  if(az>23000)  //when lifted
  {
    flicker();
  }
  
  else  //when stationary
  {
    if (dist < DETECTION_DISTANCE){ //Person is detected (this can be done better)
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

void turnLedsold(int state){
  digitalWrite(LEDPIN,state); //turn on the led
  digitalWrite(LEDPIN2,state); //turn on the led
  digitalWrite(LEDPIN3,state); //turn on the led
  digitalWrite(LEDPIN4,state); //turn on the led
}

void flickerold(){
  //Flicker for the time specified in flickerduration
  unsigned long startTime = millis();
  while (millis() - startTime < FLICKERDURATION) {

    randomValue = random(2);  // Generate a random number (0 or 1)
    if (randomValue == 0) {   // Turn the LED on or off based on the random number
      digitalWrite(LEDPIN, LOW);
    } else {
      digitalWrite(LEDPIN, HIGH);
    }

    randomValue = random(2);  // Generate a random number (0 or 1)
    if (randomValue == 0) {   // Turn the LED on or off based on the random number
      digitalWrite(LEDPIN2, LOW);
    } else {
      digitalWrite(LEDPIN2, HIGH);
    }

    randomValue = random(2);  // Generate a random number (0 or 1)
    if (randomValue == 0) {   // Turn the LED on or off based on the random number
      digitalWrite(LEDPIN3, LOW);
    } else {
      digitalWrite(LEDPIN3, HIGH);
    }

    randomValue = random(2);  // Generate a random number (0 or 1)
    if (randomValue == 0) {   // Turn the LED on or off based on the random number
      digitalWrite(LEDPIN4, LOW);
    } else {
      digitalWrite(LEDPIN4, HIGH);
    }
   
    delay(50);
  }
}