#include <ESP32CamLib.h>
#include <ArduinoJson.h>
#include <iostream>
#include <string>
#include "SD_MMC.h"

#define BAUDRATE_SERIAL_DEBUG 115200
#define SERIAL_READING_TIME 1000

int firstTime;
long randomNumber;
char jsonName[200];
char fileName[200];

File JSONfile;

StaticJsonDocument<400> doc;

void readJson()
{
  String Json = Serial.readString();
  deserializeJson(doc, Json);
}

void WriteFile()
{
  serializeJson(doc, JSONfile);
  JSONfile.println(",");
}

void setup()
{
  Serial.begin(BAUDRATE_SERIAL_DEBUG);
  init_tasks();
}

void CreateFileName()
{
  randomNumber = rand() + millis();
  sprintf(fileName, "cherrytracker%d", randomNumber);
}

void startRecording()
{

  if (firstTime == 0)
  {
    readJson();
    Serial.println("Iniciando a gravação");
    CreateFileName();
    start_handler(fileName);
    sprintf(jsonName, "/%s.json", fileName);
    JSONfile = SD_MMC.open(jsonName, FILE_WRITE);
    JSONfile.print("[");

    firstTime = 1;
  }
}

void endRecording()
{
  if (firstTime == 1 && millis() > 25000)
  {
    stop_handler();
    JSONfile.print("{}]");
    JSONfile.close();
    Serial.println("finalizando a gravação");
    firstTime = 2;
  }
}

void start()
{

  while (true)
  {
    startRecording();
    endRecording();
    readJson();
    WriteFile();
    delay(SERIAL_READING_TIME);
  }
}

void loop()
{
  start();
}
