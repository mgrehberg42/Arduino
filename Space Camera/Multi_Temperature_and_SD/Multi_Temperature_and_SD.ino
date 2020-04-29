/*****************************************************************
/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
  Based on the Dallas Temperature Library example
  use this link for wiring and reference

  
Temp Sensor wiring //https://randomnerdtutorials.com/guide-for-ds18b20-temperature-sensor-with-arduino/
*********/
//SD Card wiring https://www.instructables.com/id/Micro-SD-Card-Tutorial/


/*****************************************************************/
// The SFE_LSM9DS1 library requires both Wire and SPI be
// included BEFORE including the 9DS1 library.
#include <Wire.h>
#include <SPI.h>
//#include <SparkFunLSM9DS1.h>
#include <SD.h>
#include <OneWire.h>
#include <DallasTemperature.h>
unsigned long time;

File file;



////////////////////////////
// Sketch Output Settings //
////////////////////////////
#define PRINT_CALCULATED
//#define PRINT_RAW
#define PRINT_SPEED 10000 // 250 ms between prints
static unsigned long lastPrint = 0; // Keep track of print time

//Temperature Settings
// Data wire is connected to the Arduino digital pin 4
#define ONE_WIRE_BUS 2
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

int numberOfDevices; // Number of temperature devices found

DeviceAddress tempDeviceAddress;


//Function definitions
void printTemp();


void setup(){
  Serial.begin(9600);

  //-------------

Serial.println("Initialising SD Card...");


  
if(!SD.begin(4)) {
  Serial.println("Initialising SD Failed...");
  return; 
}
 Serial.println("Initialising Successful!");
 Serial.println("Creating File...");

 file = SD.open("testlog.txt", FILE_WRITE);
 file.print("Time,");
 file.print("Temperature C: dev 0,");
 file.print("Temperature C: dev 1,");
 file.print("Temperature C: dev 2");
 file.println();
    
 file.close();

 Serial.println("File Created!");


// Start up the library
  sensors.begin();
  
  // Grab a count of devices on the wire
  numberOfDevices = sensors.getDeviceCount();
  //--------------

}


void printTemp() {
 if(SD.exists("testlog.txt")) {
  sensors.requestTemperatures(); // Send the command to get temperatures
  
  file = SD.open("testlog.txt", FILE_WRITE);
  time = millis();
  file.print(time); file.print(",");
  // Loop through each device, print out temperature data
  for(int i=0;i<numberOfDevices; i++) {
    // Search the wire for address
    if(sensors.getAddress(tempDeviceAddress, i)){
    
    // Output the device ID
    // Print the data
    float tempC = sensors.getTempC(tempDeviceAddress);
    //Serial.print("Temp C: ");
    file.print(tempC); file.print(",");
    Serial.print(tempC);

  } else {
  Serial.println("File Does not exist");
   }
  }
  file.println();
  file.close();
 }
}
void loop()
{
  
//
  if ((lastPrint + PRINT_SPEED) < millis())
  { printTemp();
    lastPrint = millis(); // Update lastPrint time
  }
}
