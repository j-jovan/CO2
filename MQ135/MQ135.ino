//  Povezivanje:
//  MQ135 VCC - 5V Arduino
//  MQ135 GND - GND Arduino
//  MQ135 AO - A0 Arduino  (Na nekim senzorima pise AD, ali to je Analog Out)

#include <Wire.h>

int sensorValue;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  sensorValue = analogRead(0);
  Serial.println(sensorValue, DEC);
  delay(1000);
}
