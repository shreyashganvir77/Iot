#include <SoftwareSerial.h>
#include <ArduinoJson.h>
SoftwareSerial s(5,6);

int m;
float n;

int pin = 7;
const int pulsePin = 8;

float pf;
float angle;
unsigned long pulsewidth;

int pulseHigh;
int pulseLow;
float pulseTotal;
float Frequency; 
float rads = 57.29577951; // 1 radian = approx 57 deg.
float degree = 360;
float frequency = 50;
float nano = 1 * pow (10,-6);

void setup() {
  s.begin(115200);
  Serial.begin(115200);
  pinMode(7,INPUT);
  pinMode(pulsePin,INPUT);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
}


void loop() {

  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  pulseHigh = pulseIn(pulsePin,HIGH);
  pulseLow = pulseIn(pulsePin,LOW);
  pulseTotal = pulseHigh + pulseLow; 
  Frequency=1000000/pulseTotal; 
  Serial.println(Frequency);

  m=analogRead(A0);
  n=m*0.64602961;
  Serial.print("ac voltage: ");
  Serial.println(n);

  int rVal = 0;
  int sampleDuration = 100;       // 100ms
  int sampleCount = 0;
  unsigned long rSquaredSum = 0;
  int rZero = 511;  // For illustrative purposes only - should be measured to calibrate sensor.
  
  uint32_t startTime = millis();  // take samples for 100ms
  while((millis()-startTime) < sampleDuration)
  {
    rVal = analogRead(A1) - rZero;
    rSquaredSum += rVal * rVal;
    sampleCount++;
  }

  double voltRMS = 5.0 * sqrt(rSquaredSum / sampleCount) / 1024.0;

  // x 1000 to convert volts to millivolts
  // divide by the number of millivolts per amp to determine amps measured
  // the 20A module 100 mv/A (so in this case ampsRMS = 10 * voltRMS
  double ampsRMS = voltRMS * (1000/185) + .13;
  Serial.println(ampsRMS);
  
  int temp_adc_val;
  float temp_val;
  temp_adc_val = analogRead(A2);  /* Read Temperature */
  temp_val = (temp_adc_val * .488)-9; /* Convert adc value to equivalent voltage */
  Serial.print("Temperature = ");
  Serial.print(temp_val);
  Serial.print(" Degree Celsius\n");
  
  if ( isnan(frequency) || isnan(n) || isnan(ampsRMS)) {
    return;
  } 

  root["Frequency"] = Frequency;
  root["n"] = n;
  root["ampsRMS"] = ampsRMS;
  root["temp_val"] = temp_val;

  if(s.available()>0)
{
 root.printTo(s);
}

  
}



  
  
