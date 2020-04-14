/*
   Wiring for Arduino - SCD30
   5V - VCC
   GND - GND
   SDA - SDA
   SCL - SCL

   Wiring for LCD (Optional)
   5V - VCC
   GND - GND
   SDA - A4
   SCL - A5
*/

#include <Wire.h>
#include <SparkFun_SCD30_Arduino_Library.h> // http://librarymanager/All#SparkFun_SCD30
#include <LiquidCrystal_I2C.h> // https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library

LiquidCrystal_I2C lcd(0x27, 20, 4);
SCD30 airSensor;

void setup()
{
  Serial.begin(115200);
  Serial.println("SCD30");
  Wire.begin();
  lcd.begin();
  lcd.backlight();

  if (airSensor.begin() == false)
  {
    Serial.println("Problem sa programom");
    while (1)
      ;
  }
}

void loop()
{
  if (airSensor.dataAvailable())
  {
    int co2 = airSensor.getCO2();
    int temp = airSensor.getTemperature() ;
    int vlaznost = airSensor.getHumidity();
   
    Serial.print("CO2(ppm): ");
    Serial.print(co2);

    Serial.print(" temp(C): ");
    Serial.print(temp, 1);

    Serial.print(" humidity(%): ");
    Serial.print(vlaznost, 1);

    lcd.setCursor(0, 0);
    lcd.print("CO2 je:");
    lcd.setCursor(0, 1);
    lcd.print(co2);
    
    Serial.println(" ");
    if (co2 > 250 and co2 < 400)
      Serial.println("Normalna koncentracija CO2");
    if (co2 > 400 and co2 < 1000)
      Serial.println("Ocekivana koncentracija u zatvorenom prostoru sa dobrim protokom vazduha");
    if (co2 > 1000 and co2 < 2000)
      Serial.println("Manjak koncentracije, pospanost i los kvalitet vazduha");
    if (co2 > 2000 and co2 < 5000)
      Serial.println("Glavobolja, pospanost, zagadjen vazduh, losa koncentracija, gubitak paznje i ubrzan rad srca");
    if (co2 > 5000)
      Serial.println("How are you reading this? And why?");
    if (co2 > 40000)
      Serial.println("RIP");
  }
 
  else
    //Serial.println("Cekam podatke");
    delay(500);
}
