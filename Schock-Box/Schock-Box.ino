// include the library code
#include <NewPing.h>

#define VIBSWPIN        8    // Arduino pin tied to the Vibration Switch.
#define LEDPIN          11   // Arduino pin tied to LED.
#define LEDPIN2         12   // Arduino pin tied to the second LED.
#define TRIGGER_PIN     2    // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN        3    // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE    400  // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define DETECTION_DISTANCE 10
#define FLICKERDURATION 5000 //How many Milliseconds the flicker effect should play for
#define FLICKERINTERVAL 50  //How many Milliseconds each flicker Interval should take

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
int shock = 0; //initialize the variable shock as 0 TODO: could use for error handling
int dist = 0;
int randomValue = 0;

void setup()
{
  pinMode(VIBSWPIN,INPUT); //initialize vibration switch as an input
  pinMode(LEDPIN,OUTPUT); //initialize ledPin switch as an output
  pinMode(LEDPIN2,OUTPUT); //initialize ledPin switch as an output
  Serial.begin(115200);
}

void loop() {

  //Print Ping in the Serial Monitor
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  dist = uS / US_ROUNDTRIP_CM; //convert to cm
  Serial.print("Ping: ");
  Serial.print(dist);
  Serial.println("cm");
  //TODO: Maybe move this part

  //If the Box is shaken start flickering
  shock = digitalRead(VIBSWPIN); //read the value from vibration switch
  Serial.println(shock);
  if(shock == LOW)  //with vibration signal
  {
    flicker();
  }
  
  else  //without vibration signal
  {
    if (dist < DETECTION_DISTANCE){ //Person is detected
      digitalWrite(LEDPIN,HIGH); //turn on the led
      digitalWrite(LEDPIN2,HIGH); //turn on the led
    }
    else {
      digitalWrite(LEDPIN,LOW); //turn off the led
      digitalWrite(LEDPIN2,LOW); //turn off the led
    }
  }
  delay (10);
}

void flicker(){
  //Flicker for the time specified in flickerduration
  unsigned long startTime = millis();
  while (millis() - startTime < FLICKERDURATION) {

    randomValue = random(2);  // Generate a random number (0 or 1)

    if (randomValue == 0) {
      digitalWrite(LEDPIN, LOW);
    } else {
      digitalWrite(LEDPIN, HIGH);
    }

    randomValue = random(2);  // Generate a random number (0 or 1)
    if (randomValue == 0) {
      digitalWrite(LEDPIN2, LOW);
    } else {
      digitalWrite(LEDPIN2, HIGH);
    }

    //TODO: Maybe for-loop this
   
    delay(50);
  }
}
