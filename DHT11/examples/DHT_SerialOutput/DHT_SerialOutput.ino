#include <dht11.h>

#define DATA_PIN A0

DHT11 dht11(DATA_PIN);

void setup(){
  Serial.begin(9600);
}

/*
  {
      "Protocol": "Bifrost",
      "Device": "DHT11",
      "Properties": {
          "Humidity": 123,
          "Temperature": 456,
          "Checksum": 789
      }
  }
  */
void loop() {
  // put your main code here, to run repeatedly:
  dht11.Read();
  
  Serial.print("{");
    Serial.print("\"Protocol\":"\"Bifrost\",");
    Serial.print("\"Device\":\"DHT11\",");
    Serial.print("\"Properties\":{");
      Serial.print("\"Humidity\":");
      Serial.print(dht11.Humidity());
      Serial.print(",");
      Serial.print("\"Temperature\"");
      Serial.print(dht11.Temperature());
      Serial.print(",");
      Serial.print("\"Checksum\":");
      Serial.println(dht11.Checksum());
    Serial.print("}");
  Serial.print("}");

  delay(2000);
}
