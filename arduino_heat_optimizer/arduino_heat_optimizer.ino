#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20, 16, 2); 
									
const int sensorPin = A0;   
const int motorPin = 6;     
float temp;
int motorSpeed = 150;
float tempChange = 0;

void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(motorPin, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("Serial connection started");
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  
  float voltage = sensorValue * 5.0 / 1023; 
  temp = (voltage - 0.5) * 100 + tempChange;
  // Change temperature according to the motor speed
  if(motorSpeed >= 150)
    tempChange += 0.5;
  else
    tempChange -= 0.5;
  
  
  // Print temperature on the first line
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print(" C");
  // Print motor speed on the second line
  lcd.setCursor(0, 1);
  lcd.print("Motor Speed: ");
  lcd.print(motorSpeed);
 
  delay(2000);
  
  lcd.clear();
 
  // Control the motor based on temperature
  if (temp > 60) {
    motorSpeed -= 10;
    if (motorSpeed < 100) motorSpeed = 100;
    analogWrite(motorPin, motorSpeed);
    //Serial.println("Temperature higher than 60 so motor will be slowed down");
    //Serial.print("Current motorSpeed: ");
    //Serial.println(motorSpeed);
    //Serial.println("********************");


  }else if ((15 < temp) && (temp < 40)){
    motorSpeed += 10;
    if (motorSpeed > 200 ) motorSpeed = 200;
    analogWrite(motorPin, motorSpeed);
    //Serial.println("Temperature is below 40 so motor will be speed up");
    //Serial.print("Current motorSpeed: ");
    //Serial.println(motorSpeed);
    //Serial.println("********************");
    
  } else if (temp < 5) {
    digitalWrite(motorPin, LOW);
    //Serial.println("Temperature is below 5 so motor will be stop");
  }
}
