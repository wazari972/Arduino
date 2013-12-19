int START_MN_LED = 0;
int START_HR_LED = 8;

int NB_MN_LED = 6;
int NB_HR_LED = 4;

#define BT_MN A2
#define BT_HR A1

// the setup routine runs once when you press reset:
void setup() {                
  pinMode(BT_MN, INPUT);
  pinMode(BT_HR, INPUT);
  
  // initialize the digital pin as an output.
  int i;
  
  for (i = START_MN_LED; i < START_MN_LED + NB_MN_LED; i++) {
      pinMode(i, OUTPUT);   
  }  
  for (i = START_HR_LED; i < START_HR_LED + NB_HR_LED; i++) {
      pinMode(i, OUTPUT);   
  }
}

void loop()  {
  int i;
  int do_hr = digitalRead(BT_HR);
  int do_mn = digitalRead(BT_MN);
    
  for (i = 0; i < NB_MN_LED; i++) {
    digitalWrite(START_MN_LED + i, do_mn ? HIGH: LOW);
  }
  for (i = 0; i < NB_HR_LED; i++) {
    digitalWrite(START_HR_LED + i, do_hr ? HIGH: LOW);
  }
  delay(100);
}
