#include <Blynk.h>

#define BLYNK_PRINT Serial

#include <Wire.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>


BlynkTimer timer;
WidgetTable table;
BLYNK_ATTACH_WIDGET(table, V8);

char auth[] = "ZLx7JZGDby2-qj6YLSOMFoR1AIZ_uqrO"; //enter blynk auth token
char ssid[]="esp8266";
char pass[]="";

//pin setting
int energyPin=A0;

//variables used in code
float energyRaw = 0; 
float energyConvert = 0;
float energyMovingAverage[20];
float energyAverage = 0;
float dailyArray[14];
float energyTrip1 = 0;
float energyTrip2 = 0;
float energyTrip3 = 0;
float energyIntegral = 0;
int counter = 0;

int resetTrip1;
BLYNK_WRITE(V3)
{
  resetTrip1 = param.asInt(); // Get value as integer
}

int resetTrip2;
BLYNK_WRITE(V4)
{
  resetTrip2 = param.asInt(); // Get value as integer
}

int resetTrip3;
BLYNK_WRITE(V5)
{
  resetTrip3 = param.asInt(); // Get value as integer
}

void setup()
{
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000, readEnergy);
}


void readEnergy()
{
  energyRaw = analogRead(energyPin);
  Blynk.virtualWrite(V6,energyRaw);

  //energyRaw*convert2amps*120
  energyConvert = energyRaw*(1/5)*120;
  Blynk.virtualWrite(V7,energyConvert);

  //calculate energy integral
  if (counter < 86401) {
    energyIntegral+=energyConvert/3600; //Watt hours 
  }
  Blynk.virtualWrite(V13, energyIntegral);

  //calculate average
  memcpy(energyMovingAverage, &energyMovingAverage[1], sizeof(energyMovingAverage) - sizeof(int));
  energyMovingAverage[20]=energyConvert;
  for (byte n=0; n < sizeof(energyMovingAverage); n+=1){
    energyAverage+=energyMovingAverage[n];
  }
  energyAverage=energyAverage/sizeof(energyMovingAverage);
  Blynk.virtualWrite(V12, energyAverage);
  //increase counter
  counter+=1;

  //reset integral if new day, and print to table
  if (counter > 86400){
    memcpy(dailyArray, &dailyArray[1], sizeof(dailyArray) - sizeof(int));
    dailyArray[14]=energyIntegral;
    table.clear();
    for (byte i=0; i<sizeof(dailyArray); i+=1){
        table.addRow(i, "Day -" + String(i),dailyArray[i]);
    }
    energyIntegral = 0;
    counter = 0;
  }

  //reset trip counters
  if (resetTrip1>0){
    energyTrip1 = 0;
  }
  if (resetTrip2>0){
    energyTrip2 = 0;
  }
  if (resetTrip3>0){
    energyTrip3 = 0;
  }

  //Update trip counters
  energyTrip1+=energyConvert/3600;
  energyTrip2+=energyConvert/3600;
  energyTrip3+=energyConvert/3600;
  Blynk.virtualWrite(V9,energyTrip1);
  Blynk.virtualWrite(V10,energyTrip2);
  Blynk.virtualWrite(V11, energyTrip3);
}

void loop()
{
  Blynk.run();
  timer.run(); // running timer every second

}
