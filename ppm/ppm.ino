#include <Servo.h>
 
Servo myservo;  // create servo object to control a servo
                // a maximum of eight servo objects can be created 

void setup() {
  Serial.begin(57600);
  pinMode(9, INPUT);
  myservo.attach(10);  // attaches the servo on pin 9 to the servo object 
}

int min = 18900;//15536; 
int max = 20059;

void loop() {
  
  int pulse = pulseIn(9, LOW);

  float ratio  = ((float) (pulse - min))/ (max - min);
  ratio = ratio < 0 ? 0 : ratio;
  ratio = ratio > 1 ? 1 : ratio;
  myservo.write(ratio*160);
  Serial.print(min);
  Serial.print(" < ");
  Serial.print(pulse);
  Serial.print(" < ");
  Serial.print(max);
  Serial.print(" => ");
  Serial.print(ratio*100);
  Serial.println("%");
  
  delay(100);
}
