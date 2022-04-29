#include <Wire.h>
#include <Wire.h>
#include <DHT.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

#define sensorPin 7 // A0-i 7-ci pine deyisdik -bu torpag sensoru idi
#define rele 4
#define dhtPin A0
#define lcdLed 2
#define dhtType DHT11
#define soilSensor A1

int value, temp, nem, pos = 90, pos1 = 0, soilValue;

Servo servoWindow, servoWindow2;
LiquidCrystal_I2C screen(0x27, 16, 2);
DHT dht(dhtPin, dhtType);

void setup() {

  // Soil sensor value.

  // Servo
  servoWindow.attach(13);
  servoWindow2.attach(12);

  pinMode(2, OUTPUT);
  screen.init();
  dht.begin();

  Serial.begin(9600);
}

void loop() {
  // Soil sensor.
  soilValue = analogRead(soilSensor);
  servoWindow.write(pos1);
  servoWindow2.write(pos);

  value = analogRead(sensorPin);
  value = map(value, 0, 1023, 100, 0);

  // Nemlik
  screen.clear();
  screen.setCursor(0, 0);
  screen.print("Torpaq nem: ");
  screen.setCursor(11, 0);
  screen.print(value);
  screen.print("%");

  // Temperatur
  temp = dht.readTemperature();
  nem = dht.readHumidity();
  screen.setCursor(0, 1);
  screen.print("temp: ");
  screen.setCursor(6, 1);
  screen.print(temp);
  screen.print("c");
  // digitalWrite(rele, LOW);

  if (value < 60) {
    digitalWrite(rele, HIGH);
    delay(10000);
    digitalWrite(rele, LOW);
    delay(2000);
  } else {
    digitalWrite(rele, LOW);
  }
  if (temp >= 26) {
    pos = 0;
    pos1 = 90;
  } else {
    pos = 90;
    pos1 = 0;
  }
  screen.home();
  screen.backlight();
  digitalWrite(lcdLed, HIGH);
  Serial.print("Temprature ");
  Serial.println(temp);
  Serial.print("Soil sensor value ");
  Serial.println(soilValue);
  delay(1000);
}
