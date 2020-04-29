/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
  Based on the Dallas Temperature Library example
  use this link for wiring and reference
  //https://randomnerdtutorials.com/guide-for-ds18b20-temperature-sensor-with-arduino/
*********/

#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is conntec to the Arduino digital pin 4
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

void setup(void)
{
  // Start serial communication for debugging purposes
  Serial.begin(9600);
  // Start up the library
  sensors.begin();
}

void loop(void){ 
  // Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
  printTemp();
  delay(1000);
}


void printTemp() {
  float Temperature;
  sensors.requestTemperatures(); 
  Serial.print("Celsius temperature: ");
  Temperature=sensors.getTempCByIndex(0);
  Serial.println(Temperature);
}
