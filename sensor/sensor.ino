#include <SoftwareSerial.h>
#include <Arduino.h>
#include <dht11.h>
#define DHT11PIN A0
#define Sensor_AO A1                                  
#define Sensor_DO 2
#define led 7
SoftwareSerial mySerial(10,11); // TX, RX
unsigned int sensorValue = 0;
dht11 DHT11;
typedef struct message
{
  float tem;
  float hum;
  int ser;
}msg;
void setup()
{
  pinMode(Sensor_DO, INPUT);
  Serial.begin(9600);
}
void loop()
{
  sensorValue = analogRead(Sensor_AO);
  Serial.print("Harmful gas concentration: ");
  Serial.println(sensorValue);
  int chk = DHT11.read(DHT11PIN);
  Serial.print("Humidity (%): ");
//湿度读取
  Serial.println((float)DHT11.humidity, 2);
//温度读取
  Serial.print("Temperature (oC): ");
  Serial.println((float)DHT11.temperature, 2);
  Serial.print("\n");
  msg m;
  m.tem = DHT11.temperature;
  m.hum = DHT11.humidity;
  m.ser = sensorValue;
  byte *tobyte = (byte*)&m;
  while(mySerial.available())
  {
    Serial.write(tobyte,sizeof(m));
  }
  delay(2000);
  if (sensorValue > 300 || DHT11.temperature < 20 || DHT11.temperature >= 26)
  {  
    digitalWrite(led, HIGH);
  }
  else
  {  
    digitalWrite(led, LOW);
  }
}