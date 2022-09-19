#include <TinyGPS++.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <sstream>
#include <string>

/* Definições gerais */
/* o módulo GPS da placa está ligado na serial 1 do ESP32 */
#define BAUDRATE_SERIAL_GPS 9600
#define LED_BUILTIN 2

#define TEMPO_LEITURA_SERIAL_GPS 1500 // ms

/* Baudrate da serial usada para debug (serial monitor) */
#define BAUDRATE_SERIAL_DEBUG 115200

/* Filas */
/* Fila para armazenar posições GPS */
QueueHandle_t xQueue_GPS;

/* Semáforos */
SemaphoreHandle_t xSerial_semaphore;

/* Estrutura de dados de posição */
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

/* Demais objetos e variáveis globais */
TinyGPSPlus gps;

StaticJsonDocument<200> doc;

/* Protótipos das funções das tarefas */

void setup()
{
  /* Inicializa serial para debug */
  Serial.begin(BAUDRATE_SERIAL_DEBUG);

  /* Inicializa serial para comunicar com GPS */
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
}

void loop()
{

  TPosicao_GPS posicao_gps;
  unsigned long timestamp_start = 0;

  /* Faz a leitura de todos os dados do GPS (por alguns milissegundos) */
  timestamp_start = millis();
  do
  {
    while (Serial2.available())
      gps.encode(Serial2.read());
  } while ((millis() - timestamp_start) < TEMPO_LEITURA_SERIAL_GPS);
  if (gps.charsProcessed() > 10)
  {
    /* Obtem e envia posição / localização para outras tasks usando uma fila*/
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
    Serial.println();
    convertJson(posicao_gps);
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
  }
  Serial.println();
  Serial.println(Serial.readString());
}
