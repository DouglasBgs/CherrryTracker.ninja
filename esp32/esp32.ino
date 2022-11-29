#include <TinyGPS++.h>
#include <ArduinoJson.h>
#include <sstream>
#include <string>

#define BAUDRATE_SERIAL_GPS 9600
#define LED_BUILTIN 2

#define TIME_READING_SERIAL_GPS 2000
#define BAUDRATE_SERIAL_DEBUG 115200

typedef struct TPosition_GPS
{
  float latitude;
  float longitude;
  float altitude;
  float velocity;
  int numberSatellites;
  int second;
  int minute;
  int hour;
  int day;
  int month;
  int year;
};

TinyGPSPlus gps;

StaticJsonDocument<400> doc;

TPosition_GPS position_gps;

std::stringstream ss_data, ss_hour;
std::string data, hour;

void castToSerial()
{
  serializeJson(doc, Serial);
  Serial.println();
}

void convertDate()
{
  ss_data << position_gps.day << "-" << position_gps.month << "-" << position_gps.year;
  data = ss_data.str();
}

void convertHour()
{
  ss_hour << position_gps.hour << ":" << position_gps.minute << ":" << position_gps.second;
  hour = ss_hour.str();
}
static void convertToJson(TPosition_GPS position_gps)
{
  doc["latitude"] = position_gps.latitude;
  doc["longitude"] = position_gps.longitude;
  doc["altitude"] = position_gps.altitude;
  doc["velocidade"] = position_gps.velocity;
  doc["numeroSatelites"] = position_gps.numberSatellites;
  convertDate();
  doc["data"] = data;
  convertHour();
  doc["hora"] = hour;

  castToSerial();
}

void GPSRead()
{

  if (true) // if (gps.charsProcessed() > 10) quando gps estiver captando sinal
  {
    gps.encode(Serial2.read());
    position_gps.latitude = gps.location.lat();
    position_gps.longitude = gps.location.lng();
    position_gps.altitude = gps.altitude.kilometers();
    position_gps.velocity = gps.speed.kmph();
    position_gps.numberSatellites = gps.satellites.value();
    position_gps.year = gps.date.year();
    position_gps.month = gps.date.month();
    position_gps.day = gps.date.day();
    position_gps.hour = gps.time.hour();
    position_gps.minute = gps.time.minute();
    position_gps.second = gps.time.second();

    digitalWrite(LED_BUILTIN, HIGH);
    convertToJson(position_gps);
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
  }
}

void setup()
{

  Serial.begin(BAUDRATE_SERIAL_DEBUG);
  while (!Serial)
    continue;
  Serial2.begin(BAUDRATE_SERIAL_GPS);

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  GPSRead();
  delay(TIME_READING_SERIAL_GPS);
}
