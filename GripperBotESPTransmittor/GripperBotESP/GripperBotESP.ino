#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include "ESPAsyncWebServer.h"

SoftwareSerial NodeMCU_SoftSerial (D1,D2); //Rx,Tx
char c;
String dataIn;
const char* ssid = "ESP8266-Access-Point";
const char* password = "123456789";

AsyncWebServer server(80);

void setup() {
  
  NodeMCU_SoftSerial.begin(9600);
  Serial.begin(115200);
  Serial.println(".");
  Serial.print("Setting AP (Access Point)…");
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  

 server.on("/Gripper", HTTP_GET, [](AsyncWebServerRequest *request) {
 request->send(200, "text/plain", dataIn+"\n");c=0;dataIn="";
 });
   //server.on("/Quanta", HTTP_GET, [](AsyncWebServerRequest *request) {
// request->send(200, "text/plain", "Welcome to Quanta");
//  });

  // Start server
  server.begin();
  

}
void loop() {
  // put your main code here, to run repeatedly:
while(NodeMCU_SoftSerial.available()>0)
{
  c=NodeMCU_SoftSerial.read();
  if(c=='\n')
  { break;
  }
  else
  {
    dataIn+=c;
  }
  
}
//if(c=='\n')
//{
//  Serial.println(dataIn);
//// server.on("/hello", HTTP_GET, [](AsyncWebServerRequest *request) {
//// request->send(200, "text/plain", dataIn);
////  });
////
////  c=0;
////  dataIn="";
//}
}
