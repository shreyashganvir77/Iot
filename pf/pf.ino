#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int pin = 7;
const int pulsePin = 8;
float rads = 57.29577951; // 1 radian = approx 57 deg.
float degree = 360;
float frequency = 50;
float nano = 1 * pow (10,-6); // Multiplication factor to convert nano seconds into seconds

// Define floats to contain calculations

float pf;
float angle;
unsigned long pulsewidth;

int pulseHigh; // Integer variable to capture High time of the incoming pulse
int pulseLow; // Integer variable to capture Low time of the incoming pulse
float pulseTotal; // Float variable to capture Total time of the incoming pulse
float Frequency;

void setup()
{
 pinMode(pin, INPUT);
 pinMode(pulsePin,INPUT);
 pinMode(A0,INPUT);
 Serial.begin(9600);
}

void loop()
{
  pulsewidth = pulseIn(pin, HIGH);
  angle = (((pulsewidth * nano)* degree)* frequency);
  pf = cos(angle/rads);
  Serial.print(angle);
  Serial.print(", ");
  Serial.println(pf);
  pulseHigh = pulseIn(pulsePin,HIGH);
  pulseLow = pulseIn(pulsePin,LOW);
    
  pulseTotal = pulseHigh + pulseLow; // Time period of the pulse in microseconds
  Frequency=1000000/pulseTotal;
  Serial.print(Frequency);
  Serial.println(" Hz");
  int m=analogRead(A0);
  float n=m*0.2228739;
  Serial.print("AC Voltage: ");
  Serial.print(n);
  Serial.println(" V");
  delay(100);
  
}
