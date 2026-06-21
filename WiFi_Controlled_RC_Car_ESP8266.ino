/*
  ESP8266 WiFi Controlled Car
  Board: NodeMCU ESP8266
  Motor Driver: L298N

  Project: WiFi Controlled RC Car using ESP8266
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// L298N Motor Driver Pins
#define ENA   14   // D5 - Right motor speed
#define ENB   12   // D6 - Left motor speed

#define IN_1  15   // D8 - Right motor IN1
#define IN_2  13   // D7 - Right motor IN2
#define IN_3  2    // D4 - Left motor IN3
#define IN_4  0    // D3 - Left motor IN4

String command;
int speedCar = 800;
int speed_Coeff = 3;

// WiFi Access Point credentials
const char* ssid = "Make DIY";
const char* password = "12345678";   // minimum 8 characters

ESP8266WebServer server(80);

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);

  stopRobot();

  Serial.begin(115200);
  delay(1000);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();

  Serial.print("WiFi Name: ");
  Serial.println(ssid);

  Serial.print("WiFi Password: ");
  Serial.println(password);

  Serial.print("AP IP address: ");
  Serial.println(myIP);

  server.on("/", HTTP_handleRoot);
  server.onNotFound(HTTP_handleRoot);
  server.begin();

  Serial.println("Server started");
}

void goAhead() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, speedCar);
}

void goBack() {
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, speedCar);
}

void goRight() {
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, speedCar);
}

void goLeft() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, speedCar);
}

void goAheadRight() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, speedCar / speed_Coeff);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, speedCar);
}

void goAheadLeft() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, speedCar / speed_Coeff);
}

void goBackRight() {
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, speedCar / speed_Coeff);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, speedCar);
}

void goBackLeft() {
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, speedCar / speed_Coeff);
}

void stopRobot() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, 0);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, 0);
}

void loop() {
  server.handleClient();

  if (server.hasArg("State")) {
    command = server.arg("State");
    Serial.println(command);

    if (command == "F") goAhead();
    else if (command == "B") goBack();
    else if (command == "L") goLeft();
    else if (command == "R") goRight();
    else if (command == "I") goAheadRight();
    else if (command == "G") goAheadLeft();
    else if (command == "J") goBackRight();
    else if (command == "H") goBackLeft();

    else if (command == "0") speedCar = 400;
    else if (command == "1") speedCar = 470;
    else if (command == "2") speedCar = 540;
    else if (command == "3") speedCar = 610;
    else if (command == "4") speedCar = 680;
    else if (command == "5") speedCar = 750;
    else if (command == "6") speedCar = 820;
    else if (command == "7") speedCar = 890;
    else if (command == "8") speedCar = 960;
    else if (command == "9") speedCar = 1023;

    else if (command == "S") stopRobot();
  }
}

void HTTP_handleRoot() {
  server.send(200, "text/html", "OK");
}
