#include "Button.h"

void onPress()
{
  Serial.println("onPress");
}

void onRelease()
{
  Serial.println("onRelease");
}

void setup()
{
  Serial.begin(115200);
  ButtonManager::registerButton(0, 25, onPress, onRelease);
}


void loop()
{
}
