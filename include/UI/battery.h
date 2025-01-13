#include <Arduino.h>
#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

class Battery {
public:
    Battery();
    void Display();
    void Start();
private:
    int i_percent;
    bool b_isCharging;
};