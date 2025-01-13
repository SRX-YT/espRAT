#include <Arduino.h>

/*
******
* UI *
******
*/

#include "UI/battery.h"
Battery battery = Battery();

void setup() {
    Serial.begin(115200);

    battery.Start();
}

void loop() {
    battery.Display();
}