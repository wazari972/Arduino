int START_MN_LED = 0;
int START_HR_LED = 8;

int NB_MN_LED = 6;
int NB_HR_LED = 4;

int SECOND_LED = 13;

int mn;
int hr;

int ONE_SECOND = 10;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  int i;
  
  for (i = START_MN_LED; i < START_MN_LED + NB_MN_LED; i++) {
      pinMode(i, OUTPUT);   
  }  
  for (i = START_HR_LED; i < START_HR_LED + NB_HR_LED; i++) {
      pinMode(i, OUTPUT);   
  }
  
  hr = 2;
  mn = 11;
}

// the loop routine runs over and over again forever:
void loop() {
  static int second_cpt = 59;
  
  digitalWrite(SECOND_LED, second_cpt % 2 == 0 ? HIGH: LOW);
  second_cpt += 1;
  
  delay(ONE_SECOND);
  
  if (second_cpt < 60) {
    return;
  }
  
  second_cpt = 0;
  
  int i;
  int mask = 1;
  for (i = 0; i < NB_MN_LED; i++) {
    digitalWrite(START_MN_LED + i, mn & mask ? HIGH: LOW);
    mask = mask << 1;
  }
  mask = 1;
  for (i = 0; i < NB_HR_LED; i++) {
    digitalWrite(START_HR_LED + i, hr & mask ? HIGH: LOW);
    mask = mask << 1;
  }
  
  mn += 1;
  mn %= 60;
  if (mn == 0) {
    hr += 1;
    hr %= 12;
  }
}
