/*****************************************************************
/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
  Based on the Dallas Temperature Library example
  use this link for wiring and reference
  //https://randomnerdtutorials.com/guide-for-ds18b20-temperature-sensor-with-arduino/
*********/

/*****************************************************************/
// The SFE_LSM9DS1 library requires both Wire and SPI be
// included BEFORE including the 9DS1 library.
#include <Wire.h>
#include <SPI.h>
//#include <SparkFunLSM9DS1.h>
#include <SD.h>
#include <OneWire.h>
#include <DallasTemperature.h>

File file;



////////////////////////////
// Sketch Output Settings //
////////////////////////////
#define PRINT_CALCULATED
//#define PRINT_RAW
#define PRINT_SPEED 1000 // 250 ms between prints
static unsigned long lastPrint = 0; // Keep track of print time

//Temperature Settings
// Data wire is conntec to the Arduino digital pin 4
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);


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
  sensors.begin();
  //--------------

}


void printTemp() {
  float Temperature;
   if(SD.exists("testlog.txt")) {
     Serial.println("File Exists!");
     file = SD.open("testlog.txt", FILE_WRITE);
     sensors.requestTemperatures(); 
     //file.print("Celsius temperature: ");
     Temperature=sensors.getTempCByIndex(0);
     file.println(Temperature);
     file.close();
     Serial.println(Temperature);
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

//
//void printAttitude(float ax, float ay, float az, float mx, float my, float mz)
//{
//  float roll = atan2(ay, az);
//  float pitch = atan2(-ax, sqrt(ay * ay + az * az));
//
//  float heading;
//  //-------------------
//
//  if(SD.exists("testlog.txt")) {
//    Serial.println("File Exists!");
//    file = SD.open("testlog.txt", FILE_WRITE);
//
//    
//    file.print(roll, 2);
//    file.print(" ");
//    file.print(heading, 2);
//    file.print(" ");
//    file.print(pitch, 2);
//    file.print(" ");
//    
//    file.print(imu.calcGyro(imu.gx), 2);
//    file.print(" ");
//    file.print(imu.calcGyro(imu.gy), 2);
//    file.print(" ");
//    file.print(imu.calcGyro(imu.gz), 2);
//    file.print(" ");
//    
//    file.print(imu.calcAccel(imu.ax), 2);
//    file.print(" ");
//    file.print(imu.calcAccel(imu.ay), 2);
//    file.print(" ");
//    file.print(imu.calcAccel(imu.az), 2);
//    file.print(" ");
//    
//    file.print(imu.calcMag(imu.mx), 2);
//    file.print(" ");
//    file.print(imu.calcMag(imu.my), 2);
//    file.print(" ");
//    file.println(imu.calcMag(imu.mz), 2);
//    
//    file.close();
//    
//  } else {
//  Serial.println("File Does not exist");
//  }
//
//delay(1000);
//  //---------------------
//
//}
