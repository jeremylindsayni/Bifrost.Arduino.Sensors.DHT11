#include "Arduino.h"
#include "DHT11.h"

DHT11::DHT11(int dataPin)
{
    _dataPin = dataPin;
}

void DHT11::Read()
{
    unsigned long lowStart, highStart;
    byte timeLow, timeHigh;

    // Allow device to settle.
    delay(1000);
    
    // Set the pin to be an output
    pinMode(_dataPin, OUTPUT);

    // Let's activate the chip by writing low for at least 18ms and high for 40us.
    digitalWrite(_dataPin, LOW);
    delay(20); //20ms, greater than 18ms
    digitalWrite(_dataPin, HIGH);
    delayMicroseconds(40); // 40 microseconds

    // Now change the pin mode to be an input
    pinMode(_dataPin, INPUT);

    lowStart = micros();
    // ideally low for 54 micro seconds
    while(digitalRead(_dataPin) == LOW);  
    timeLow = micros() - lowStart;

    highStart = micros();
    // ideally high for 80 micro seconds
    while(digitalRead(_dataPin) == HIGH);
    timeHigh = micros() - highStart;

    lowStart = micros();
    for (short i = 0; i < 40; i++)
    {
        while(digitalRead(_dataPin) == LOW);
        while(digitalRead(_dataPin) == HIGH);
        deviceValues[i] = micros() - lowStart;
        lowStart = micros();
    }
    
    ConvertRawDataToValues(deviceValues);
}

byte DHT11::Humidity()
{
    return _humidity;
}

byte DHT11::Temperature()
{
    return _temperature;
}

byte DHT11::Checksum()
{
    return _checksum;
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
void DHT11::ToSerial()
{
    Serial.print("{");
        Serial.print("\"Protocol\":"\"Bifrost\",");
        Serial.print("\"Device\":\"DHT11\",");
        Serial.print("\"Properties\":{");
            Serial.print("\"Humidity\":");
            Serial.print(Humidity());
            Serial.print(",");
            Serial.print("\"Temperature\"");
            Serial.print(Temperature());
            Serial.print(",");
            Serial.print("\"Checksum\":");
            Serial.println(Checksum());
        Serial.print("}");
    Serial.println("}");
}

void DHT11::ConvertRawDataToValues(short byteArray[])
{
    byte outputValue = 0;
    for (short i = 0; i < 5; i++)
    {
        outputValue = 0;
        
        for(short j = 8 * i; j < 8 * i + 8; j++)
        {
            outputValue += LogicLevel(byteArray[j]) << (7 - j % 8);
        }
        
        environmentValues[i] = outputValue;
    }
    
    _humidity = environmentValues[0];
    _temperature = environmentValues[2];
    _checksum = environmentValues[4];
}

bool DHT11::LogicLevel(byte value)
{
    if (value > 100)
    {
        return 1;
    }
    
    return 0;
}