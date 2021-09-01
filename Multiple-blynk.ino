#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#define DHTPIN 2          
#define DHTTYPE DHT11     
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

char auth[] = ".............";
char ssid[] = ".............";
char pass[] = ".............";

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}
void setup()
{
  Serial.begin(9600); // See the connection status in Serial Monitor
  Blynk.begin(auth, ssid, pass);

  pinMode(5, OUTPUT); //s0
  pinMode(4, OUTPUT); //s1
  pinMode(14, OUTPUT); //s2
  
  dht.begin();
  timer.setInterval(1000L, sendSensor);
}

void pin1() //y0
{
  digitalWrite(5, 0); 
  digitalWrite(4, 0);
  digitalWrite(14, 0);
  Blynk.virtualWrite(V0, analogRead(A0));
}

void pin2() //y1
{
  digitalWrite(5, 1);
  digitalWrite(4, 0);
  digitalWrite(14, 0);
  Blynk.virtualWrite(V1, analogRead(A0));
}

void pin3() //y2
{
  digitalWrite(5, 0);
  digitalWrite(4, 1);
  digitalWrite(14, 0);
  Blynk.virtualWrite(V2, analogRead(A0));
}

void loop()
{
  Blynk.run();
  timer.run();
  
  pin1();     //read sensor value from y0
  delay(500);
  pin2();     //read sensor value from y1
  delay(500);
  pin3();     //read sensor value from y2
  delay(500);
}
