#include <Arduino.h>

HardwareSerial pc(PA10, PA9);//注意，在STM32中，一般大序号在前，小序号在后

void setup()
{
  // put your setup code here, to run once:
  pc.begin(115200);
}

void loop()
{
  pc.print("millis:");
  pc.print((int)millis());

  pc.print("PA0:");
  pc.println(analogRead(PA0));   
}
