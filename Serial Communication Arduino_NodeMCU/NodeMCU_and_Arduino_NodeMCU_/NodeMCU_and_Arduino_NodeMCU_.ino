#include <ArduinoJson.h>
#include <SoftwareSerial.h>
SoftwareSerial s(D6,D5);
int Relay1;

#define BLYNK_PRINT Serial                                            // Blynk Libraries
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <TimeLib.h>
#include <WidgetRTC.h>

#include <WiFiClient.h>;                                              // Libraries for ThingSpeak Servers
#include <ThingSpeak.h>;

BlynkTimer timer;
WidgetRTC rtc;

char auth[] = "*****************************";
char ssid[] = "Note 5 Pro";
char pass[] = "12345678";

WiFiClient client;
unsigned long myChannelNumber =*******;                             //Your Channel Number
const char * myWriteAPIKey = "*****************";     
 
void setup() {
  Serial.begin(115200);
  s.begin(115200);
  pinMode(A0, INPUT);
  while (!Serial) continue;

  rtc.begin();
  Blynk.begin(auth, ssid, pass);

  ThingSpeak.begin(client);
 
}
 
void loop() {
  Blynk.run();
  timer.run();
  
  String currentTime = String(hour()) + ":" + minute() + ":" + second();
  String currentDate = String(day()) + " " + month() + " " + year();
  Serial.print("Current time: ");
  Serial.print(currentTime);
  Serial.print(" ");
  Serial.print(currentDate);
  Serial.println();
  
  Blynk.virtualWrite(V1, currentTime);
  Blynk.virtualWrite(V2, currentDate);
  
  
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(s);

  if (root == JsonObject::invalid())
  {
    return;
  }

  root.prettyPrintTo(Serial);

  Serial.println("");
  Serial.print("Frequency ");
  int data1=root["Frequency"];
  Serial.println(data1);

  Serial.println("");
  Serial.print("voltage ");
  int data2=root["voltage"];
  Serial.println(data2);

  Serial.println("");
  Serial.print("ampsRMS ");
  int data3=root["ampsRMS"];
  Serial.println(data3);

  Serial.println("");
  Serial.print("temp_val ");
  int data4=root["temp_val"];
  Serial.println(data4);

  Relay1 = digitalRead(D3);
  if (Relay1==HIGH){
    Serial.println("Relay1-ON");
    }
  else{
    Serial.println("Relay1-OFF");
    }

  ThingSpeak.writeField(myChannelNumber, 1, data4, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 2, data1, myWriteAPIKey); 
  ThingSpeak.writeField(myChannelNumber, 3, data2, myWriteAPIKey);  
  delay(50); 
  }
