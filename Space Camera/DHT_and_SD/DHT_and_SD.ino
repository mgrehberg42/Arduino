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
#include <SimpleDHT.h>
int pinDHT11 = 2;
SimpleDHT11 dht11;


File file;



////////////////////////////
// Sketch Output Settings //
////////////////////////////
#define PRINT_CALCULATED
//#define PRINT_RAW
#define PRINT_SPEED 250 // 250 ms between prints
static unsigned long lastPrint = 0; // Keep track of print time


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
    
 file.print("Temperature C ");

    
 file.close();

 Serial.println("File Created!");


// Start up the library
//  sensors.begin();
  //--------------

}


void printTemp() {
  float Temperature;
   if(SD.exists("testlog.txt")) {
     Serial.println("File Exists!");
     file = SD.open("testlog.txt", FILE_WRITE);
     byte temperature = 0;
     byte humidity = 0;
     byte data[40] = {0};
     if (dht11.read(pinDHT11, &temperature, &humidity, data)) {
    //Serial.print("Read DHT11 failed");
      return;
    }
     Serial.print((int)temperature);
     //file.print("Celsius temperature: ");
     //Temperature=sensors.getTempCByIndex(0);
     file.println(temperature);
     file.close();
     Serial.println(temperature);
  } else {
  Serial.println("File Does not exist");
  }
}
void loop()
{
  
//
  if ((lastPrint + PRINT_SPEED) < millis())
  { printTemp();
//    printGyro();  // Print "G: gx, gy, gz"
//    printAccel(); // Print "A: ax, ay, az"
//    printMag();   // Print "M: mx, my, mz"
//    // Print the heading and orientation for fun!
//    // Call print attitude. The LSM9DS1's mag x and y
//    // axes are opposite to the accelerometer, so my, mx are
//    // substituted for each other.
//    printAttitude(imu.ax, imu.ay, imu.az,
//                  -imu.my, -imu.mx, imu.mz);
//    Serial.println();
    lastPrint = millis(); // Update lastPrint time
  }


}
