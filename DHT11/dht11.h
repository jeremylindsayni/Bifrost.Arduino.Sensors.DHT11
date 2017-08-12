#ifndef DHT11_h
#define DHT11_h

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

class DHT11
{
  public:
    DHT11(int dataPin);
	void Read();
    byte Humidity();
	byte Temperature();
	byte Checksum();
	void ToSerial();
  private:
	int _dataPin;
    byte _humidity;
    byte _temperature;
	byte _checksum;
	short deviceValues[40];
	short environmentValues[5];
	void ConvertRawDataToValues(short byteArray[]);
	bool LogicLevel(byte value);
};

#endif