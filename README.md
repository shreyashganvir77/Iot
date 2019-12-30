# Wireless-Monitoring-of-Substation-using-IoT
In a discrepancy with the limitations of the present substation monitoring system, this paper shows us how the wireless network system can be used to monitor and analyze the substation from anywhere in the world. This system is concise of NodeMCU and Arduino with Arduino connected to different sensors for measurement of different parameters like current, voltage, power factor and frequency of supply at a substation. NodeMCU is the control center of this system which sends this data to ThingSpeak and then the remote user can take actions based upon the readings received. The innovations of this paper brought efficient monitoring and controlling. 
This project presents only the monitoring of substation which further can be used to monitor and control switchgear and power generation stations. The data and trends for a particular month can be used to predict the power requirement in future and productive power can be generated.
Here Arduino is used for controlling NodeMCU. BLYNK app is also used to monitor different parameters and their values. With this app, users can control the circuit breakers and relays from anywhere in the world. Node MCU is a wi-fi module used as a control system that receives data from Arduino and sends values of various parameters to the cloud(ThingSpeak).

In this project we measure 5 parameters of Substation namely:
1.Temperature of Transformer
2.Current
3.Voltage
4.Frequency of Suppply
5.Power Factor of Supply and 
Wireless Control of Relays and Circuit Breakers.

Temperature is measured with the help of DHT11 sensor orDS18B20 can be used for more precision. On increase of rated temperature of transformer automatic fan is turned ON to cool it.

The current is measured with the help of ACS712 current sensor is used to measure ac current through the line. The sensor works on principle of hall effect. Each current sensor has its own offset valuesfor rated current.(Therfore, before use check offset value of your current sensor)

Voltage across the transformer is measured with the help of voltage divider circuit made with use of proper resistors and the these valuses are mapped accordingly with supply voltage for precision reading of voltages.

Frequency and Power factor of the supply is measured with the help schmitt trigger and XoR gate IC.
Schmitt trigger converts the sine wave into square wave and measuring the ON and OFF time in square wave gives us Frequncy. The ON and OFF time of the square wave is measured with pulseIn command of in ArduinoIDE.
Similarly, for measurement of power factor XoR gate is used which calculates difference of on and off in current and voltage waveforms. Calculating that time helps us measuring power factor with formula as cos(phi)=360*f*dt.

Relays and Circuit breakers are controlled with BLYNK and NodeMCU(ESP8266) with IoT.

