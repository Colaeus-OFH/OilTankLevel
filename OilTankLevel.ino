//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
/* Arduino example sketch to control a JSN-SR04T ultrasonic distance sensor with Arduino. No library needed. More info: https://www.makerguides.com */

// Define Trig and Echo pin:
#define trigPin 2
#define echoPin 3

// Define variables:
int duration;
long distance;
float speedofsound;
int temp;
float prcntFull;

void setup()
{
  // Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // temp in Celcius
  temp = 8;

  // speed m/s
  speedofsound = 331.3+(0.606*temp);
  
  // Begin Serial communication at a baudrate of 9600:
  Serial.begin(9600);
  
  lcd.init();                      // initialize the lcd 

  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("Oil Tank Level");
  lcd.setCursor(2,1);
  lcd.print("Checking...");
  delay(1000);
}


void loop()
{
  // Clear the trigPin by setting it LOW:
  digitalWrite(trigPin, LOW);
  
  delayMicroseconds(5);

  // Trigger the sensor by setting the trigPin high for 10 microseconds:
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echoPin. pulseIn() returns the duration (length of the pulse) in microseconds:
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance - Note .0001 is math answer, extra 1 added to make .00011 and correct distance for temp
  distance = duration*(speedofsound*.00011)/2.0;
  
  // Print the distance on the Serial Monitor (Ctrl+Shift+M):
  lcd.clear();                      // initialize the lcd 

  // Print a message to the LCD.

  prcntFull = (116.0-distance)/116.0*100.0;
  lcd.setCursor(0,0);
  lcd.print("Dist    Perc");
  lcd.setCursor(0,1);
  lcd.print(round(distance));
  lcd.print(" cm  ");
  lcd.print(round(prcntFull));
  lcd.print("%");
  
  // Don't need the display updating multiple times/second, so let's slow things down
  delay(1000);
}
