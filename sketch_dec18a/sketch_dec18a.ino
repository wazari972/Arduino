#define BT_CHECK_PERIOD 100       // adjust here
#define BT_INHIBIT_COUNT 4        // adjust here

#define ONE_SECOND 1000            // fix here

/******************************************************/

#define NB_SECONDS 60
#define NB_MINUTES 60
#define NB_HOURS 12

#define NB_MN_POS 6 // = ceil(log(NB_MINUTES, 2))
#define NB_HR_POS 4 // = ceil(log(NB_HOURS, 2))

#define LED_SEC 13
int LED_MN[NB_MN_POS] = {0, 1, 2, 3, 4, 5};
int LED_HR[NB_HR_POS] = {8, 9, 10, 11};

#define BT_MN A1
#define BT_HR A2

int seconds;
int minutes;
int hours;

int check_period_counter;
int bt_inhibited_counter;
int first;

// the setup routine runs once when you press reset:
void setup()  {
  int i;
  // declare LED pins to be an output:
  for (i = 0; i < NB_MN_POS; i++) {
    pinMode(LED_MN[i], OUTPUT);
  }
  for (i = 0; i < NB_HR_POS; i++) {
    pinMode(LED_HR[i], OUTPUT);
  }
  pinMode(LED_SEC, OUTPUT);
  
  // declare BUTTON pins to be an input:
  pinMode(BT_MN, INPUT);
  pinMode(BT_HR, INPUT);
  
  hours = 1;
  minutes = 10;
  seconds = 0;
  
  check_period_counter = 0;
  bt_inhibited_counter = 0;
  
  first = 1;
}

// the loop routine runs over and over again forever:
void loop()  {
  int i;
  int mask;
  
  int do_refresh = 0;
  
  if (first) {
     do_refresh = 1;
    first = 0; 
  }
  
  // wait for a little while
  delay(BT_CHECK_PERIOD);
  check_period_counter++;

  if (bt_inhibited_counter) {
    goto refresh;
  }
  
  if (!digitalRead(BT_MN)) {
    minutes++;
    
    do_refresh = 1;
    bt_inhibited_counter = BT_INHIBIT_COUNT;

    check_period_counter = 0;
    seconds = 0;
  }
  
  if (!digitalRead(BT_HR)) {
    hours++;
    
    do_refresh = 1;
    bt_inhibited_counter = BT_INHIBIT_COUNT;

    check_period_counter = 0;
    seconds = 0;
  }

refresh:
  if (BT_CHECK_PERIOD * check_period_counter > ONE_SECOND) {
    check_period_counter = 0;

    seconds = (seconds + 1) % NB_SECONDS;
    digitalWrite(LED_SEC, seconds % 2 ? HIGH : LOW);
    
    if (!seconds) {
      do_refresh = 1;
      
      minutes = (minutes + 1) % NB_MINUTES;
    
      if (!minutes) {
        hours = (hours + 1) % NB_HOURS;
      }
    }
  }

  if (bt_inhibited_counter) {
    bt_inhibited_counter--;
  }
  
  if (!do_refresh) {
    return;
  }

  mask = 1;
  for (i = 0; i < NB_MN_POS; i++) {
    digitalWrite(LED_MN[i], minutes & mask ? HIGH : LOW);
    mask = mask << 1;
  }
  mask = 1;
  for (i = 0; i < NB_HR_POS; i++) {
    digitalWrite(LED_HR[i], hours & mask ? HIGH : LOW);
    mask = mask << 1;
  }  
}

