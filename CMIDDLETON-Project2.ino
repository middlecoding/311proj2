//led1
const int LED_1_PIN = 2;
unsigned long previousTimeLED1Blink = 0;
unsigned long LED1BlinkDelay = 0;
byte LED1State = LOW;

//led2
const int LED_2_PIN = 3;
unsigned long previousTimeLED2Blink = 0;
unsigned long LED2BlinkDelay = 0;
byte LED2State = LOW;

bool LED1Start = false;
bool LED2Start = false;

int serialState = 1;
int currentLED = 0;

int readFix = 0;

//functions to be executed cyclicly
void led1();
void led2();
void userPrompt();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_1_PIN,OUTPUT);
  pinMode(LED_2_PIN,OUTPUT);
  //needs to print this once to start rest of prompts
  Serial.println("What LED (1 or 2)?");
}

void loop() {
  userPrompt();
  led1();
  led2();
}

void userPrompt(){
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0){
    //had to do this to stop serial from executing twice
    readFix++;
    if(readFix%2 == 0){
      readFix = 0;
    }

    //Takes user input for LED
    bool run = false;
    int userInput = Serial.parseInt();
    //checks if input in Serial
    //prevents accidental trigger
    if(serialState == 1 && !run && readFix%2 == 1){
      if(userInput == 1){
        currentLED = 1;
      }
      else if(userInput == 2){
        currentLED = 2;
      }
      serialState = 2;

      Serial.println("What interval (in msec?");
      run = true;
    }

    //checks if input in Serial
    //prevents accidental trigger
    //Takes user input for time delay
    else if(serialState == 2 && !run && readFix %2 == 1){
      if(currentLED == 1){
        LED1Start = true;
        LED1BlinkDelay = userInput;
      }
      else if(currentLED == 2){
        LED2Start = true;
        LED2BlinkDelay = userInput;
      }
      serialState = 1;
      Serial.println("What LED (1 or 2)?");
      run = true;
    }
  }
}

void led1(){
  //current time using millis
  unsigned long timeNow = millis();

  //LED 1
  if(LED1Start && (timeNow - previousTimeLED1Blink > LED1BlinkDelay)){
    previousTimeLED1Blink += LED1BlinkDelay;
    //checks condition of LED, sets accordingly
    if(LED1State == HIGH){
      LED1State = LOW;
    }
    else{
      LED1State = HIGH;
    }
    digitalWrite(LED_1_PIN,LED1State);
  }
}

void led2(){
  //current time using millis
  unsigned long timeNow = millis();

  //LED 2
  if(LED2Start && (timeNow - previousTimeLED2Blink > LED2BlinkDelay)){
    previousTimeLED2Blink += LED2BlinkDelay;
    //checks condition of LED, sets accordingly
    if(LED2State == HIGH){
      LED2State = LOW;
    }
    else{
      LED2State = HIGH;
    }
    digitalWrite(LED_2_PIN,LED2State);
  }
}