#include <Arduino.h>
#include "stateMachine/StateMachine.h"

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    advanceStateMachine();
}
