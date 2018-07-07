#include <dht11.h>

#define DATA_PIN A0

DHT11 dht11(DATA_PIN);

void setup(){
    Serial.begin(9600);
}

void loop() {
    dht11.Read();

    dht11.ToSerial();

    delay(2000);
}