// include the library code
#include <NewPing.h>
#include <TVout.h>

#define TRIGGER_PIN_1      2   // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_1         3   // Arduino pin tied to echo pin on the ultrasonic sensor.
#define TRIGGER_PIN_2      5   // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_2         6   // Arduino pin tied to echo pin on the ultrasonic sensor.
#define TRIGGER_PIN_3      11  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_3         12  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE       400 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define DETECTION_DISTANCE 100 //Distance that counts as detection

NewPing sonar1(TRIGGER_PIN_1, ECHO_PIN_1, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar2(TRIGGER_PIN_2, ECHO_PIN_2, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar3(TRIGGER_PIN_3, ECHO_PIN_3, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
int dist1 = 0;
int dist2 = 0;
int dist3 = 0;
int lastSensor = 3;
int highSensor = 0;
bool change = false;

TVout TV;

void setup() {
  Serial.begin(9600); // Open serial monitor at 115200 baud to see ping results.
  TV.begin(PAL, 128, 96);
}

void loop() {
  delay(100); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  
  //Print Ping in the Serial Monitor
  unsigned int uS1 = sonar1.ping(); // Send ping, get ping time in microseconds (uS).
  dist1 = uS1 / US_ROUNDTRIP_CM; //convert to cm
  Serial.print("Ping_1: ");
  Serial.print(dist1);
  Serial.print("cm | ");
  
  unsigned int uS2 = sonar2.ping(); // Send ping, get ping time in microseconds (uS).
  dist2 = uS2 / US_ROUNDTRIP_CM; //convert to cm
  Serial.print("Ping_2: ");
  Serial.print(dist2);
  Serial.print("cm | ");

  unsigned int uS3 = sonar3.ping(); // Send ping, get ping time in microseconds (uS).
  dist3 = uS3 / US_ROUNDTRIP_CM; //convert to cm
  Serial.print("Ping_3: ");
  Serial.print(dist3);
  Serial.print("cm | ");

  highSensor = sensorcheck();

  if (highSensor != lastSensor){
    lastSensor = highSensor;
    change = true;
  }

  switch(lastSensor) {
    case 0:
      // no change 
      break;
    case 1: //closest sensor #941100 (ROT)
      TV.clear_screen();
      TV.draw_rect(20, 20, 40, 40, WHITE);
      break;
    case 2: //#7030A0 (VIOLETT)
      TV.clear_screen();
      TV.draw_circle(40, 40, 20, WHITE);
      break;
    case 3: //#005493 (DUNKELBLAU)
      TV.clear_screen();
      TV.draw_column(60, 60, 20, WHITE);
      break;
      case 4: //#8DD4FB (HELLBLAU)
      //TODO
      break;
      case 5: //furthest Sensor #FFFFFF (WEIẞ)
      //TODO
      break;
    default:
      break;
  }
  if (change){
    delay (400);
    change = false;
  }
}

int sensorcheck() {
  if (dist1 < DETECTION_DISTANCE){ //closest sensor
    Serial.println("sensor 1");
    return 1;
  } else if (dist2 < DETECTION_DISTANCE) {
    Serial.println("sensor 2");
    return 2;
  } else if (dist3 < DETECTION_DISTANCE) {
    Serial.println("sensor 3");
    return 3;
  } else { //no sensor detectects anything
    Serial.println("no sensor"); //TODO: Something about this makes the screen flicker
    return 0;
  }
}
