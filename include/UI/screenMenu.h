#include <Arduino.h>
#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
#include <vector>

class ScreenMenu {
public:
    ScreenMenu();
    void Display();
private:
};