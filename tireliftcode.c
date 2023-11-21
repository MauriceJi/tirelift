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
