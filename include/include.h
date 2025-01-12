#pragma once

#include <Arduino.h>
#include <U8g2lib.h>
#include <ezButton.h>
#include <Adafruit_NeoPixel.h>
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
#include <RF24.h>
#include "icon.h"
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include "esp_bt.h"
#include "esp_wifi.h"
#include <SPI.h>