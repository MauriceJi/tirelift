#include <LiquidCrystal_I2C.h>
#include <Wire.h>

const int pingPin = 5; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 18; // Echo Pin of Ultrasonic Sensor

// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;

unsigned long previousMillis = 0UL;
unsigned long interval = 500UL;

// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

void setup(){
  // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();

  Serial.begin (115200);
}

void loop(){
   long duration, inches, cm;

   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);

   duration = pulseIn(echoPin, HIGH);
   cm = microsecondsToCentimeters(duration);
   String cmPrint = String(cm);

  // set cursor to first column, first row
  lcd.setCursor(0, 0);
  // print message
  lcd.print("Position: " + cmPrint + " cm");
 
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > interval)
  {
	/* The Arduino executes this code once every second
 	*  (interval = 1000 (ms) = 1 second).
 	*/
 	previousMillis = currentMillis;
  }

  lcd.clear();
}

long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}




/////////////////////
#include <LiquidCrystal_I2C.h>

//Ultra-Sonic Sensor
#define trigPin 5
#define echoPin 18

//Height Button Save
#define buttonPin 17

//
#define golocationPin 16

//Relay Pins(Up)
#define upRelay 4

//Relay Pins(Down)
#define downRelay 2

//Yes and No Buttons
#define YES 12
#define NO 13

//define sound speed in cm/uS
#define SOUND_SPEED 0.034



long duration;
int distanceCm;
int saveddistanceCM;

LiquidCrystal_I2C lcd(0x27, 20, 4); // I2C address 0x27, 20 column and 4 rows

void IRAM_ATTR saveDistance(){
  saveddistanceCM = distanceCm;
}

void IRAM_ATTR moveActuator(){
  if(digitalRead(YES) == LOW){
    while(saveddistanceCM > distanceCm && saveddistanceCM != distanceCm){ //turn on first group of relays
      digitalWrite(upRelay, HIGH);
    }
    digitalWrite(upRelay, LOW);
    while(saveddistanceCM < distanceCm && saveddistanceCM != distanceCm){ //turn on second group of relays
      digitalWrite(downRelay, HIGH);
    }
   digitalWrite(downRelay, LOW);
    while(saveddistanceCM = distanceCm){
      digitalWrite(downRelay, LOW);
      digitalWrite(upRelay, LOW);
    }
  }else if(digitalRead(NO) == LOW){

  }
}

void IRAM_ATTR reset(){
  while(saveddistanceCM < distanceCm && saveddistanceCM != distanceCm){ //turn on second group of relays
      digitalWrite(downRelay, HIGH);
    }
   digitalWrite(downRelay, LOW);
}

void setup() {
  lcd.init(); // initialize the lcd
  lcd.backlight();
  
  Serial.begin(115200); // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(upRelay, OUTPUT);
  pinMode(downRelay, OUTPUT);
  
  pinMode(buttonPin, INPUT_PULLUP);//Pull up button
  attachInterrupt(digitalPinToInterrupt(buttonPin), saveDistance, CHANGE);//Save distance interrupt

  pinMode(golocationPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(golocationPin), moveActuator, CHANGE);//Save distance interrupt
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;

  String distanceCmPrint = String(distanceCm);
  String saveddistanceCmPrint = String(saveddistanceCM);
  
  // Prints the distance in the LCD
  lcd.setCursor(0, 0);            // move cursor the first row
  lcd.print("Distance: " + distanceCmPrint);          // print message at the first row
  lcd.setCursor(0, 1);            // move cursor to the second row
  lcd.print("Saved Distance: " + saveddistanceCmPrint); // print message at the second row



 delay(500);
 lcd.clear();
}



