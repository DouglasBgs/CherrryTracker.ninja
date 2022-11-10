#include "ESP32CamLib.h"


void setup()
{
  init_tasks();
}

void loop()
{
  int first;
  if (first == 0 && millis() > 5000)
  {
    start_handler();
    first = 1;
  }
  if (first == 1 && millis() > 25000)
  {
    stop_handler();
    first = 10;
  }

  delay(1000);
}
