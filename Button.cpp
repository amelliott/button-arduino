#include "Button.h"
#include "Arduino.h"

int ButtonManager::mNumButtons = 0;
Button ButtonManager::mButtons[NUM_BUTTONS];

void ButtonManager::registerButton(int pin, int bounceTime, void (*onPress)(), void (*onRelease)())
{
    pinMode(pin, INPUT);
    digitalWrite(pin, HIGH);
    attachInterrupt(pin, onInterrupt, CHANGE);
    
    Button * newButton = &mButtons[mNumButtons];
    newButton->pin = pin;
    newButton->lastChange = 0;
    newButton->onPress = onPress;
    newButton->onRelease = onRelease;
    ++mNumButtons;
}

// pos, turn, oldVal
void ButtonManager::onInterrupt()
{
    //Serial.println("onInterrupt");
    for (int i = 0; i < mNumButtons; ++i)
    {
        Button * button = &mButtons[i];
        // FIXME: could get a read when the pin is low or high, need to track last state for buttons
        int value = digitalRead(button->pin);
        // check state change
        unsigned long time = millis();
        if (time - button->lastChange > button->bounceTime)
        {
            button->lastChange = time;
            if (value == HIGH)
            {
                if (button->onRelease != 0)
                {
                    button->onRelease();
                }
            }
            else
            {
                if (button->onPress != 0)
                {
                    button->onPress();
                }
            }
        }
    }
}
