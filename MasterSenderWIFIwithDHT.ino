/* MASTER SENDER 
 *  CONNECTIONS
 *  2- esp8266-01 tx
 *  3- esp8266-01 rx
 * 
 * SDA- SDA, SCL to SCL
 * 
 * Things to edit in below code
 *  authentication code from blynk
 *  WIFI SSID and Password
 */

#include <Wire.h>
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266_SoftSer.h>
#include <BlynkSimpleShieldEsp8266_SoftSer.h>
#include <SoftwareSerial.h>
#include "DHT.h"
#include <SimpleTimer.h>
SimpleTimer timer;
DHT dht;
SoftwareSerial EspSerial(2, 3); // RX, TX

ESP8266 wifi(EspSerial);

char auth[] = "xx......"; // authentication code from blynk goes here
void setup() {
  Serial.begin(9600);           
  delay(10);
  dht.setup(7); 
  Wire.begin(8);
  EspSerial.begin(9600);
  delay(10);
 
  Blynk.begin(auth, wifi, "ssid", "password"); // WIFI SSID and Password goes here
}
 BLYNK_WRITE(V0)
{ int i = param.asInt();
 if(i==1)
comm(2);
 
 else
comm(6);
}
 BLYNK_WRITE(V1)
{ int i = param.asInt();
 if(i==1)
comm(3);
 else
comm(7);
}
 BLYNK_WRITE(V2)
{ int i = param.asInt();
 if(i==1)
comm(4);
 else
comm(8);
}
 BLYNK_WRITE(V3)
{ int i = param.asInt();
 if(i==1)
comm(5);

 else
comm(9);
}

void sendUptime()
{
  Blynk.virtualWrite(V4, dht.getTemperature());
  Blynk.virtualWrite(V5, dht.getHumidity());
}

void loop() {
  Blynk.run();
  timer.run(); 
   timer.setInterval(10000L, sendUptime);
}

void comm(int x){
  Wire.beginTransmission(8); // transmit to device #8      
  Wire.write(x);              // sends one byte
  Wire.endTransmission(); 
  }




