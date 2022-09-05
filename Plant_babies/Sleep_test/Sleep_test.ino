/*
 * ESP8266 Deep sleep mode example
 * Rui Santos 
 * Complete Project Details http://randomnerdtutorials.com
 */

#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "grabSRcrFTg85W1HM8HmWo_ceN-zARy9";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Vanessas";
char pass[] = "iamagoddess";



SimpleTimer timer;

 
void setup() {
 //digitalWrite(D3,LOW);
 Blynk.begin(auth, ssid, pass);
 timer.setInterval(5000L,ReadSensor);

}

void loop() {
  Blynk.run();
  timer.run();

}
void ReadSensor() {

  while (Blynk.connect() == false) {
  // Wait until connected
  }
  ESP.deepSleep(1e6);
  delay(100);

}
