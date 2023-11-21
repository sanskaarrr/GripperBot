#include <Servo.h>
Servo myservo;
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti WiFiMulti;


const char* ssid = "ESP8266-Access-Point";
const char* password = "123456789";

const char* serverNameGripper = "http://192.168.4.1/Gripper";

String direc="";
unsigned long previousMillis = 0;
const long interval = 500;
bool opened = true;
bool closed = true;

int in1 = D0;
int in2 = D1;
int in3 = D2;
int in4 = D3;
/* Defining L298N enable pins */
int ENB = D6;/* Right Motor Enable Pin GPIO14(D5) */
int ENA = D5;/* Right Motor Enable Pin GPIO12(D6)  */



void setup()
{
  Serial.begin(115200);
  Serial.println();
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(ENA, OUTPUT);
  myservo.attach(2);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to WiFi");
}


void loop() {
  unsigned long currentMillis = millis();
  
  if(currentMillis - previousMillis >= interval) {
     // Check WiFi connection status
    if ((WiFiMulti.run() == WL_CONNECTED)) {
      direc = httpGETRequest(serverNameGripper);
      Serial.println("Data is\n" + direc);
      
     
      
      // save the last HTTP GET Request
      previousMillis = currentMillis;
    }
    else {
      Serial.println("WiFi Disconnected");
    }
  }
  //for movement
    if (direc[0] == 'F') {
    move_forward(); /* If direction F moves forward */
  }
  else if (direc[0] == 'B') {
    move_backward(); /* If direction B moves backward */
  }
  else if (direc[0] == 'R') {
    turn_right(); /* If direction R turns right */
  }
  else if (direc[0] == 'L') {
    turn_left(); /* If direction L  turns left */
  }
  else if (direc[0] == 'S') {
    move_stop(); /* If direction S stops moving */
  }
  if(direc[1]=='O' && closed == true)
  {
    myservo.write(0);
    delay(300);
   myservo.write(90);
    opened = true;
    closed = false;
  }
  else if(direc[1]=='C' && opened == true)
  {
    myservo.write(180);
    delay(300);
   myservo.write(90);
    closed = true;
    opened = false;
  }
  
}


String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    
  // Your IP address with path or Domain name with URL path 
  http.begin(client, serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "--"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();

  return payload;
}
void move_forward() {
  analogWrite(ENA, 130);
  analogWrite(ENB, 130);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

/* Move Backward */
void move_backward() {
  analogWrite(ENA, 130);
  analogWrite(ENB, 130);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

/* Turn Right */
void turn_right() {
   analogWrite(ENA, 140);
  analogWrite(ENB, 100);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

/* Turn Left */
void turn_left() {
   analogWrite(ENA, 140);
   analogWrite(ENB, 100);
   digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

/* Stop Move */
void move_stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
