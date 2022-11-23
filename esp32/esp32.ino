#include <TinyGPS++.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <sstream>
#include <string>

#define BAUDRATE_SERIAL_GPS 9600
#define LED_BUILTIN 2

#define TEMPO_LEITURA_SERIAL_GPS 2000
#define BAUDRATE_SERIAL_DEBUG 115200

typedef struct
{
  float latitude;
  float longitude;
  float altitude;
  float velocidade;
  int numeroSatelites;
  int segundo;
  int minuto;
  int hora;
  int dia;
  int mes;
  int ano;
} TPosicao_GPS;

TinyGPSPlus gps;

StaticJsonDocument<400> doc;

void setup()
{

  Serial.begin(BAUDRATE_SERIAL_DEBUG);
  while (!Serial)
    continue;
  Serial2.begin(BAUDRATE_SERIAL_GPS);

  pinMode(LED_BUILTIN, OUTPUT);
}
static void convertJson(TPosicao_GPS posicao_gps)
{
  std::stringstream ss, ss2;
  doc["latitude"] = posicao_gps.latitude;
  doc["longitude"] = posicao_gps.longitude;
  doc["altitude"] = posicao_gps.altitude;
  doc["velocidade"] = posicao_gps.velocidade;
  doc["numeroSatelites"] = posicao_gps.numeroSatelites;
  ss << posicao_gps.dia << "/" << posicao_gps.mes << "/" << posicao_gps.ano;
  std::string data = ss.str();
  doc["data"] = data;
  ss2 << posicao_gps.hora << ":" << posicao_gps.minuto << ":" << posicao_gps.segundo;
  std::string hora = ss2.str();
  doc["hora"] = hora;

  serializeJson(doc, Serial);
  Serial.println();
}

void GPSRead()
{
  TPosicao_GPS posicao_gps;

  if (true) // if (gps.charsProcessed() > 10) quando gps estiver captando sinal
  {
    gps.encode(Serial2.read());
    posicao_gps.latitude = gps.location.lat();
    posicao_gps.longitude = gps.location.lng();
    posicao_gps.altitude = gps.altitude.kilometers();
    posicao_gps.velocidade = gps.speed.kmph();
    posicao_gps.numeroSatelites = gps.satellites.value();
    posicao_gps.ano = gps.date.year();
    posicao_gps.mes = gps.date.month();
    posicao_gps.dia = gps.date.day();
    posicao_gps.hora = gps.time.hour();
    posicao_gps.minuto = gps.time.minute();
    posicao_gps.segundo = gps.time.second();

    digitalWrite(LED_BUILTIN, HIGH);
    convertJson(posicao_gps);
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
  }
}

void loop()
{

  GPSRead();
  delay(TEMPO_LEITURA_SERIAL_GPS);
}
