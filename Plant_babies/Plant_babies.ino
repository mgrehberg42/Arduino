#include <Blynk.h>

#define BLYNK_PRINT Serial



//#include "RTClib.h"
#include <Wire.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>
#include <SPI.h>

//Temperature libraries
//#include <OneWire.h>
//#include <DallasTemperature.h>


char auth[] = "grabSRcrFTg85W1HM8HmWo_ceN-zARy9"; //enter blynk auth token
char ssid[]="ESP8266";
char pass[]="";

//RTC_DS1307 rtc;
//DateTime now;
BlynkTimer timer;


// Data wire is conntec to the Arduino digital pin 4
//#define ONE_WIRE_BUS 4


int MoistureRawValue=A0;
int SensorPower=D0;
int PumpPower=D5;
// watering display = V2
// wateringthresh = V5
//


//constants used in the code

int wateringTime; //Set the watering time (20 sec for a start)


//variables used in code
float soilMoistureRaw = 0; //Raw analog input of soil moisture sensor (volts)
float soilMoisturePercent = 0; //Raw analog input of soil moisture sensor (volts)
float soilMoistureOld = 0;
//bool wateredToday = false;


//float wateringThreshold;

//Get the watering threshold from blynk
int wateringThreshold;
BLYNK_WRITE(V1)
{
  wateringThreshold = param.asInt(); // Get value as integer
}
int wateringSeconds;
BLYNK_WRITE(V3)
{
  wateringSeconds = param.asInt(); // Get value as integer
}

int Enable;
BLYNK_WRITE(V4)
{
  Enable = param.asInt(); // Get value as integer
 // Serial.print("Enable: ");
//  Serial.println(Enable);
}

//digitalWrite(PumpPower,LOW);


void setup()
{
  // Debug console
//  digitalWrite(PumpPower,LOW);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(60e3, GetMoistureTimer);
  //timer.setInterval(86400000,resetWateredDate);
 
}

//every 30 seconds it will run the moisture timer
//the timer is set to go into deep sleep for 10 seconds after running
//so I should see the app active for 20 seconds

void GetMoistureTimer()
{
//    while (Blynk.connect() == false) {
//  // Wait until connected
//  }
  
   //Test the soil moisture percentage
  digitalWrite(SensorPower,HIGH);
  delay(1000);
  //digitalWrite(D1,HIGH);
  soilMoistureRaw=analogRead(MoistureRawValue);
  soilMoistureOld=soilMoisturePercent;
  soilMoisturePercent=((soilMoistureRaw * -100)/(1024-400)+(100*1024/(1024-400)));
  Blynk.virtualWrite(V5,soilMoistureRaw);
  Blynk.virtualWrite(V6,soilMoisturePercent);
  Blynk.virtualWrite(V7,(soilMoistureOld-soilMoisturePercent));
  //delay(100);
  digitalWrite(SensorPower,LOW);

  delay(1000);


  if ((soilMoisturePercent < wateringThreshold)&& (Enable==1)){ //&& (wateredToday==false) 
    Blynk.virtualWrite(V2,50);
    digitalWrite(PumpPower,HIGH);
    delay(wateringSeconds*1000);
    digitalWrite(PumpPower,LOW);
//    wateredToday=true;
    Blynk.virtualWrite(V2,0);
  }

  //ESP.deepSleep(5e6);
  delay(100);
}

void loop()
{
  Blynk.run();
  timer.run(); // running timer every second

}
