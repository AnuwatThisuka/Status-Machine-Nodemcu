#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

const char* ssid     = "iPhone";
const char* password = "Anu096279";

//ip host
const char* host = ".................................";
const char* host1 = "google.co.th";

//รหัส Blynk
char auth[] = "ONBkinvEfvLm661cyF-lCw8z4Sr56xgv";

#define BLYNK_PRINT Serial
const int inputcount = 4;
int val1;
int count = 0;
int press = 0;
int xxx = 0;
int Status;
int Data;
int TestCountxxx();

const int inputMachine1 = 5;
int buttonState = 0;
BLYNK_CONNECTED()
{
  Blynk.syncAll();
}
WidgetLED Machine1(V0);
WidgetLED Machine2(V1);
WidgetLED Machine3(V2);
WidgetLCD Lcd(V5);
WidgetLCD Lcd1(V6);
WidgetLCD Lcd2(V7);

void setup() 
{
   Serial.begin(9600);
   pinMode(2,OUTPUT);
   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) 
   {
      delay(250);
      Serial.print(".");
      digitalWrite(2,LOW);
      delay(500);
      digitalWrite(2,HIGH);
      delay(500);
   }
   Serial.println("WiFi connected");  
   Serial.println("IP address: ");
   Serial.println(WiFi.localIP());
   digitalWrite(2,LOW);
   Blynk.begin(auth, "ssid", "pass");
   pinMode(inputMachine1, INPUT);
   pinMode(inputcount, INPUT);
}
int value = 0;

void PLC(){
  buttonState = digitalRead(inputMachine1);
  if (buttonState == LOW)
  {
    Machine3.on();
    Serial.println("ON");
    if (digitalRead(4) == HIGH)
  {
    if (press == 0)
    {
      count++;
      Lcd2.clear();
      Lcd2.print(0, 0,"Bending work");
      Lcd2.print(0, 1, count);
      Serial.println(count);
      press = 1;
      //ฝั่งSerVer
 Serial.print("connecting to ");
  Serial.println(host);
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
      String url = "/To_databases3.php?";
      url += "machine3=";
      url += count;
      url += "&Statusmachine3=";
      url += "ON";
      Serial.print("Requesting URL: ");
      Serial.println(url);
      client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                                "Host: " + host + "\r\n" + 
                                "Connection: close\r\n\r\n");
                                delay(4000);
                                 delay(10);
  while(client.available()){
    String line = client.readStringUntil('\r');
    //Serial.print(line);
    Serial.println();
    if(line.indexOf("บันทึกสำเร็จ") != -1)
    {
      Serial.println("success");
    } else if(line.indexOf("บันทึกสำเร็จ") != -1)
    {
      Serial.println("success");
    }
  }
  Serial.println("success");
  Serial.println("closing connection");
    }     
  }
  else
  {
    press = 0;
  }
  }
  else
  {
    Machine3.off();
    Serial.println("OFF");
    ///ฝั่งserver
    Serial.print("connecting to ");
  Serial.println(host);
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
      String url = "/To_databases3.php?";
      url += "machine3=";
      url += count;
      url += "&Statusmachine3=";
      url += "OFF";
      Serial.print("Requesting URL: ");
      Serial.println(url);
      client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                                "Host: " + host + "\r\n" + 
                                "Connection: close\r\n\r\n");
                                delay(5000);
                                 delay(10);
  while(client.available()){
    String line = client.readStringUntil('\r');
    //Serial.print(line);
    Serial.println();
    if(line.indexOf("บันทึกสำเร็จ") != -1)
    {
      Serial.println("success");
    } else if(line.indexOf("บันทึกสำเร็จ") != -1)
    {
      Serial.println("success");
    }
  }
  Serial.println("success");
  Serial.println("closing connection");
}
}

void loop() 
{
   //ส่วนแสดงเมื่อไม่ได้เชื่อมต่อไวไฟ
   WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host1, httpPort)) {
    Serial.println("connection failed");
    digitalWrite(2,LOW);
    delay(500);
    digitalWrite(2,HIGH);
    delay(500);
  }
  else
  {
    digitalWrite(2,LOW);
    Blynk.run();
    delay(500);
    PLC();
  }
}
