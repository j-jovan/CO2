#include <Wire.h>

#include "SparkFun_SCD30_Arduino_Library.h" //Biblioteka: http://librarymanager/All#SparkFun_SCD30
SCD30 airSensor;

void setup()
{
  Serial.begin(115200);
  Serial.println("SCD30");
  Wire.begin();

  if (airSensor.begin() == false)
  {
    Serial.println("SCD30 nije povezan");
    while (1)
      ;
  }

}

void loop()
{
  if (airSensor.dataAvailable())
  {
    Serial.print("co2(ppm):");
    Serial.print(airSensor.getCO2());

    Serial.print(" temp(C):");
    Serial.print(airSensor.getTemperature(), 1);

    Serial.print(" humidity(%):");
    Serial.print(airSensor.getHumidity(), 1);

    Serial.println();
  }
  else
    Serial.println("Cekam podatke");

  delay(500);
}
