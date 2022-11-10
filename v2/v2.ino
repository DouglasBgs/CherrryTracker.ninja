#include <ESP32CamLib.h>

ESP32CamLib cam

void setup()
{
  cam.init_tasks();
}

void loop()
{
  int first;
  if (first == 0 && millis() > 5000)
  {
    cam.start_handler();
    first = 1;
  }
  if (first == 1 && millis() > 25000)
  {
    cam.stop_handler();
    first = 10;
  }

  delay(1000);
}
