#include <Servo.h>
 
Servo myservo;  // create servo object to control a servo
                // a maximum of eight servo objects can be created 

void setup() {
  //Serial.begin(57600);
  pinMode(A5, INPUT);
  myservo.attach(10);  // attaches the servo on pin 9 to the servo object 
}

int min = 0;//15536; 
int max = 1024;

void loop() {
  
  int pulse = analogRead(A5);    // read the input pin
  Serial.println(pulse);             // debug value

  float ratio  = 1 - ((float) (pulse - min))/ (max - min);
  ratio = ratio < 0 ? 0 : ratio;
  ratio = ratio > 1 ? 1 : ratio;
  myservo.write(ratio*175);
  /*
  Serial.print(min);
  Serial.print(" < ");
  Serial.print(pulse);
  Serial.print(" < ");
  Serial.print(max);
  Serial.print(" => ");
  Serial.print(ratio*100);
  Serial.println("%");
  */
  delay(10);
}
