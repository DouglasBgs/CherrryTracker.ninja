/****************************************************************************
 *   ESP32 Hacks (c) 2021 Marcio Teixeira                                   *
 *                                                                          *
 *   https://github.com/marciot/esp32-hacks                                 *
 *                                                                          *
 *   This program is free software: you can redistribute it and/or modify   *
 *   it under the terms of the GNU General Public License as published by   *
 *   the Free Software Foundation, either version 3 of the License, or      *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   This program is distributed in the hope that it will be useful,        *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU General Public License for more details.                           *
 *                                                                          *
 *   To view a copy of the GNU General Public License, go to the following  *
 *   location: <http://www.gnu.org/licenses/>.                              *
 ****************************************************************************/

#include <SD_MMC.h>
#include "esp_camera.h"
#include <ArduinoJson.h>

// Pins for ESP32-CAM

#define FLASH_PIN         4
// Camera pins
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

typedef struct
{
    float latitude;
    float longitude;
    float altitude;
    float velocidade;
    int numeroSatelites;
    char hora;
    char data;
} TPosicao_GPS;

StaticJsonDocument<200> doc;

TPosicao_GPS posicao_gps;

String filename = "";

bool startMicroSD() {
  Serial.print("Starting microSD... ");

  // Pin 13 needs to be pulled-up
  // https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/sd_pullup_requirements.html#pull-up-conflicts-on-gpio13
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  if(SD_MMC.begin("/sdcard", true)) {
    Serial.println("OKAY");
    return true;
  } else {
    Serial.println("FAILED");
    return false;
  }
}

bool startCamera() {
  // Turn off the flash
  pinMode(FLASH_PIN, OUTPUT);
  digitalWrite(FLASH_PIN, LOW);

  // Initialize the camera hardware
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  
  // Set resolution based on whether we have extra memory
  if(psramFound()){
    Serial.println("PSRAM found. Maximum XGA resolution supported.");
    config.frame_size = FRAMESIZE_XGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    Serial.println("PSRAM not found. Maximum SVGA resolution supported.");
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

  // Start the camera
  Serial.print("Starting camera... ");
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.println("FAILED");
    return false;
  } else {
    Serial.println("OKAY");
    return true;
  }
}

void takePhoto(String filename) { 
  // Take a photo and get the data

  camera_fb_t *fb = esp_camera_fb_get();
  if (!fb) {
    Serial.println("Unable to take a photo");
    return;
  }

  // Make sure it is a JPEG
  if (fb->format != PIXFORMAT_JPEG) {
     Serial.println("Capture format not JPEG");
     esp_camera_fb_return(fb); // Return the photo data
     return;
  }

  // Save the picture to the SD card

  File file = SD_MMC.open(filename.c_str(), "w");
  if(file) {
    Serial.println("Saving " + filename);
    file.write(fb->buf, fb->len);
    file.close();

    // Momentarily blink the flash
    digitalWrite(FLASH_PIN, HIGH);
    delay(100);
    digitalWrite(FLASH_PIN, LOW);
    delay(500);
  } else {
    Serial.println("Unable to write " + filename);
  }

  // Return the picture data
  esp_camera_fb_return(fb);
}

void serialRead() {
    DeserializationError error = deserializeJson(doc, Serial.readString());

  // Test if parsing succeeds.
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  posicao_gps.latitude = doc["latitude"];
  posicao_gps.longitude = doc["longitude"];
  posicao_gps.altitude = doc["altitude"];
  posicao_gps.velocidade = doc["velocidade"];
  posicao_gps.numeroSatelites = doc["numeroSatelites"];
  posicao_gps.data = doc["data"];
  posicao_gps.hora = doc["hora"];

}

void newFileName() {
  unsigned long time;
  time = millis();
  String newName = "";
  filename = "/photo_";
  newName += posicao_gps.latitude;
  newName += "_";
  newName += posicao_gps.longitude;
  newName += "_";
  newName += posicao_gps.altitude;
  newName += "_";
  newName += posicao_gps.numeroSatelites;
  newName += "_";
  newName += posicao_gps.velocidade;
  newName += "_";
  newName += time;
  newName.replace(".", "");
  filename += newName;
  filename += ".jpg";
  
}

void setup() {
  // Initialize the peripherals
  Serial.begin(115200);
  while(!Serial) delay(100);
  

  startMicroSD();
  startCamera();

  delay(5000); // Delay 5 seconds before first photo
}

void loop() {
  // Keep a count of the number of photos we have taken
  static int number = 0;
  number++;

  serialRead();

  // Construct a filename that looks like "/photo_0001.jpg"
  newFileName();
  
  
  takePhoto(filename);

  // Delay until the next photo

  delay( 15);
}
