/*
Name: MTR Reflow Plate
Version: 1.0
Description: This program is used to control the temperature of a reflow plate.
Plateform: ESP32 DevKit V1
Author: Ciciliano Altmann (MTR)
Date: 23/07/2023
License: MIT License
*/

#include <Wire.h>
#include <SPI.h>
#include <AutoPID.h>
#include <Adafruit_MAX31865.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

#define RREF 430.0
#define RNOMINAL 100.0

#define OUTPUT_PIN 4
#define LED_PIN 2
#define LED_GREEN 12
#define LED_RED 14
#define LED_BLUE 27
#define LED_WHITE 26
#define LED_YELLOW 32

#define SPI_CS 5
#define SPI_MOSI 23
#define SPI_MISO 19
#define SPI_CLK 18

#define OUTPUT_MIN 0
#define OUTPUT_MAX 255
#define KP 100
#define KI 0.01
#define KD 0.001

bool inZone(unsigned long elapsedMilliseconds, unsigned long zoneDuration);
float getTemperature(float R_NOMINAL, float R_REF);
void setTemperature(float temperature);

double temperature, outputVal, setPoint, manuSetPoint;
int startStopManu = 0;
bool manu = false;

//Sn42Bi58 paste profile
unsigned long preheatingTime = 60;    // Durée de la zone 1 (en millisecondes)
unsigned long recirculationTime = 100; // Durée de la zone 2 (en millisecondes)
unsigned long reflowTime = 90;         // Durée de la zone 3 (en millisecondes)
unsigned long elapsedMilliseconds, startMillis;

float preheatingTemperature = 90;     // Température de la zone 1 (en degrés Celsius)
float recirculationTemperature = 120; // Température de la zone 2 (en degrés Celsius)
float reflowTemperature = 138;        // Température de la zone 3 (en degrés Celsius)
float coolingTemperature = 23;        // Température de la zone 4 (en degrés Celsius)

const char *ssid = "MTR";
const char *password = "mtr12345";

AutoPID myPID(&temperature, &setPoint, &outputVal, OUTPUT_MIN, OUTPUT_MAX, KP, KI, KD);
Adafruit_MAX31865 thermo = Adafruit_MAX31865(SPI_CS, SPI_MOSI, SPI_MISO, SPI_CLK);
AsyncWebServer server(80);

void setup()
{
  Serial.begin(115200);

  pinMode(OUTPUT_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_WHITE, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);

  thermo.begin(MAX31865_3WIRE); // set to 2WIRE or 4WIRE as necessary

  myPID.setBangBang(10);
  myPID.setTimeStep(50);

  if (!SPIFFS.begin())
  {
    Serial.println("Erreur SPIFFS...");
    return;
  }

  File root = SPIFFS.open("/");
  File file = root.openNextFile();

  while (file)
  {
    Serial.print("File: ");
    Serial.println(file.name());
    file.close();
    file = root.openNextFile();
  }

  WiFi.begin(ssid, password);
  Serial.print("Tentative de connexion...");

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(100);
  }

  Serial.println("\n");
  Serial.println("Connexion etablie!");
  Serial.print("Adresse IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/index.html", "text/html"); });

  server.on("/chart", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/chart.html", "text/html"); });

  server.on("/manu", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/manu.html", "text/html"); });

  server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/script.js", "text/javascript"); });

  server.on("/readTemperature", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "text/plain", String(temperature)); });

  server.on("/readSetPoint", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "text/plain", String(setPoint)); });

  server.on("/start", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    startStopManu = 1;
    request->send(204); });

  server.on("/stop", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    startStopManu = 0;
    request->send(204); });

  server.on("/manu", HTTP_POST, [](AsyncWebServerRequest *request)
            {

  if(request->hasParam("manuMode", true)){
      String message;
      message = request->getParam("manuMode", true)->value();
      startStopManu = message.toInt();
    }
    request->send(204); });

  server.on("/manuStart", HTTP_GET, [](AsyncWebServerRequest *request)
          {
  manu = true;
  request->send(204); });

  server.on("/manuStop", HTTP_GET, [](AsyncWebServerRequest *request)
          {
  manu = false;
  request->send(204); });  

  server.on("/params", HTTP_POST, [](AsyncWebServerRequest *request)
            {

  if(request->hasParam("temps_zone_preheating", true)){
      String message;
      message = request->getParam("temps_zone_preheating", true)->value();
      preheatingTime = message.toInt();
  }

  if(request->hasParam("temperature_zone_preheating", true)){
      String message;
      message = request->getParam("temperature_zone_preheating", true)->value();
      preheatingTemperature = message.toInt();
  }

  if(request->hasParam("temps_zone_recirculation", true)){
      String message;
      message = request->getParam("temps_zone_recirculation", true)->value();
      recirculationTime = message.toInt();
  }

  if(request->hasParam("temperature_zone_recirculation", true)){
      String message;
      message = request->getParam("temperature_zone_recirculation", true)->value();
      recirculationTemperature = message.toInt();
  }

  if(request->hasParam("temps_zone_reflow", true)){
      String message;
      message = request->getParam("temps_zone_reflow", true)->value();
      reflowTime = message.toInt();
  }

  if(request->hasParam("temperature_zone_reflow", true)){
      String message;
      message = request->getParam("temperature_zone_reflow", true)->value();
      reflowTemperature = message.toInt();
  }

  if(request->hasParam("temperature_zone_cooling", true)){
      String message;
      message = request->getParam("temperature_zone_cooling", true)->value();
      coolingTemperature = message.toInt();
  }

  request->send(204); });

  server.on("/manuSetTemperature", HTTP_POST, [](AsyncWebServerRequest *request)
            {

  if(request->hasParam("manuTemperature", true)){
      String message;
      message = request->getParam("manuTemperature", true)->value();
      manuSetPoint = message.toInt();
  }

  request->send(204); });

  server.on("/getParams", HTTP_GET, [](AsyncWebServerRequest *request)
            {
  String json = "{";
  json += "\"temps_zone_preheating\":"; 
  json += String(preheatingTime);
  json += ",";

  json += "\"temperature_zone_preheating\":";
  json += String(preheatingTemperature);
  json += ",";

  json += "\"temps_zone_recirculation\":";
  json += String(recirculationTime);
  json += ",";

  json += "\"temperature_zone_recirculation\":";
  json += String(recirculationTemperature);
  json += ",";

  json += "\"temps_zone_reflow\":";
  json += String(reflowTime);
  json += ",";

  json += "\"temperature_zone_reflow\":";
  json += String(reflowTemperature);
  json += ",";

  json += "\"temperature_zone_cooling\":";
  json += String(coolingTemperature);

  json += "}";

  request->send(200, "text/plain", json); });

  server.begin();
  Serial.println("Serveur actif!");
}

void loop()
{

  temperature = getTemperature(RNOMINAL, RREF);

  if(startStopManu == 0)
    digitalWrite(LED_WHITE, 1);
  else
    digitalWrite(LED_WHITE, 0);

  if(startStopManu == 2)
    digitalWrite(LED_YELLOW, 1);
  else
    digitalWrite(LED_YELLOW, 0);

  if(startStopManu == 1 || manu == true)
    digitalWrite(LED_BLUE, 1);
  else
    digitalWrite(LED_BLUE, 0);


  if (startStopManu == 1)
  {

    elapsedMilliseconds = millis() - startMillis;

    myPID.run();
    analogWrite(OUTPUT_PIN, outputVal);
    digitalWrite(LED_RED, myPID.atSetPoint(1));

    // Zone 1: Preheating
    if (inZone(elapsedMilliseconds, preheatingTime))
    {
      setTemperature(preheatingTemperature);
    }
    // Zone 2: Recirculation
    else if (inZone(elapsedMilliseconds - preheatingTime, recirculationTime))
    {
      setTemperature(recirculationTemperature);
    }
    // Zone 3: Reflow
    else if (inZone(elapsedMilliseconds - preheatingTime - recirculationTime, reflowTime))
    {
      setTemperature(reflowTemperature);
      digitalWrite(LED_GREEN, 1);
    }
    // Zone 4: Cooling
    else
    {
      setTemperature(coolingTemperature);
      digitalWrite(LED_GREEN, 0);
      startStopManu = 0;
    }
  }
  else if (startStopManu == 2)
  {
    startMillis = millis();
    setPoint = manuSetPoint;

    if(manu)
    {
      myPID.run();
      analogWrite(OUTPUT_PIN, outputVal);
    }
    else
    {
      analogWrite(OUTPUT_PIN, 0);
    }
  }
  else if (startStopManu == 0)
  {
    analogWrite(OUTPUT_PIN, 0);
    setPoint = 0;
    startMillis = millis();
  }
}

float getTemperature(float R_NOMINAL, float R_REF)
{
  float temp = thermo.temperature(R_NOMINAL, R_REF);
  return temp;
}

bool inZone(unsigned long elapsedMilliseconds, unsigned long zoneDuration)
{
  return (elapsedMilliseconds < zoneDuration);
}

// Set the temperature of the heating plate
void setTemperature(float temperature)
{
  setPoint = temperature;
}

void loop2()
{
  temperature = getTemperature(RNOMINAL, RREF);
  Serial.println(temperature);
  delay(1000);
}