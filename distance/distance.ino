#include <NewPing.h>
#include <Servo.h>

#define TRIGGER_PIN  6  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     5  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

#define BUZZER_PIN     12
#define SERVO_PIN     11

#define BUZZER_ALERT 15
#define SERVO_ANGLE 175

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
Servo myservo;

void setup() {
  Serial.begin(57600); // Open serial monitor at 115200 baud to see ping results.
  pinMode(BUZZER_PIN, OUTPUT);
  myservo.attach(SERVO_PIN);
}

int mini = MAX_DISTANCE;
int maxi = 0;

unsigned int prev = -1;
void loop() {
  delay(300);
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  unsigned int dist = uS / US_ROUNDTRIP_CM;
  
  if (prev == dist || dist == 0) return;
  
  mini = min(mini, dist);
  maxi = max(maxi, dist);
  
  float ratio  = 1 - ((float) (dist - mini))/ (maxi - mini);
  myservo.write(ratio * SERVO_ANGLE);
  
  digitalWrite(BUZZER_PIN, dist != 0 && dist < BUZZER_ALERT ? HIGH: LOW);
  Serial.print(mini);
  Serial.print(" < ");
  Serial.print(dist);
  Serial.print(" < ");
  Serial.print(maxi);
  Serial.println("");
  
  prev = dist;
}
