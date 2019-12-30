#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

const int pulsePin = 8; // Input signal connected to Pin 8 of Arduino

int pulseHigh; // Integer variable to capture High time of the incoming pulse
int pulseLow; // Integer variable to capture Low time of the incoming pulse
float pulseTotal; // Float variable to capture Total time of the incoming pulse
float frequency; // Calculated Frequency

void setup()

{
    Serial.begin(115200);
    pinMode(pulsePin,INPUT);
    lcd.begin(16, 2);
    lcd.setCursor(0,0);
    lcd.print("IoT Substation");
    delay(5000);
}
void loop()
{
    lcd.setCursor(0,0);
    lcd.print("Frequency is    ");
    lcd.setCursor(0,1);
    lcd.print("                ");
    
    pulseHigh = pulseIn(pulsePin,HIGH);
    pulseLow = pulseIn(pulsePin,LOW);
    
    pulseTotal = pulseHigh + pulseLow; // Time period of the pulse in microseconds
    frequency=1000000/pulseTotal; // Frequency in Hertz (Hz)
    
    lcd.setCursor(0,1);
    lcd.print(frequency);
    Serial.println(frequency);
    lcd.print(" Hz");
    delay(500);
}
