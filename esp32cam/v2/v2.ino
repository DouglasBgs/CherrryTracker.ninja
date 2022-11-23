#include <ESP32CamLib.h>
#include <sstream>
#include <string>
#include <iostream>
#include <ArduinoJson.h>
#include "SD_MMC.h"

#define BAUDRATE_SERIAL_DEBUG 115200
#define TEMPO_LEITURA_SERIAL 1000

int firstTime;
long randomNumber;
char jsonName[130];

File JSONfile;

StaticJsonDocument<400> doc;

void readJson()
{
  String readJson = Serial.readString();
  deserializeJson(doc, readJson);
  serializeJson(doc, JSONfile);
  JSONfile.println(",");
}

void setup()
{

  Serial.begin(BAUDRATE_SERIAL_DEBUG);
  init_tasks();
  inicio();
}

void inicio()
{

  while (true)
  {
    if (firstTime == 0 && millis() > 3000)
    {
      start_handler();
      Serial.println("Iniciando a gravação");
      randomNumber = rand();
      sprintf(jsonName, "/%dtestedouglas%d.json", randomNumber, millis());

      JSONfile = SD_MMC.open(jsonName, FILE_WRITE);
      JSONfile.print("[");
      firstTime = 1;
    }
    if (firstTime == 1 && millis() > 25000)
    {
      stop_handler();
      JSONfile.print("{}]");
      JSONfile.close();
      Serial.println("finalizando a gravação");
      firstTime = 10;
    }

    readJson();

    delay(TEMPO_LEITURA_SERIAL);
  }
}

void loop()
{
}
