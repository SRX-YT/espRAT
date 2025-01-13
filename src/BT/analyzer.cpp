// #include "include.h"
// #include "BT/analyzer.h"

// extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C display;

// #define NRF24_CONFIG      0x00
// #define NRF24_EN_AA       0x01
// #define NRF24_RF_CH       0x05
// #define NRF24_RF_SETUP    0x06
// #define NRF24_RPD         0x09

// #define SCREEN_WIDTH 128
// #define SCREEN_HEIGHT 64

// #define N 128
// uint8_t values[N];

// #define CE  4
// #define CSN 5

// #define CHANNELS  64
// int CHannel[CHANNELS];

// byte getRegister(byte r);
// void enable();
// void setRX();
// void setRegister(byte r, byte v);
// void scanChannels();
// void writeRegister(uint8_t reg, uint8_t value);
// uint8_t readRegister(uint8_t reg);
// void disable();
// void powerUp();
// void startListening();
// void stopListening();
// bool carrierDetected();
// void setChannel(uint8_t CHannel);

// void setChannel(uint8_t CHannel) {
//     writeRegister(NRF24_RF_CH, CHannel);
// }

// void startListening() {
//     digitalWrite(CE, HIGH);
// }

// void stopListening() {
//     digitalWrite(CE, LOW);
// }

// bool carrierDetected() {
//     return readRegister(NRF24_RPD) & 0x01;
// }

// byte getRegister(byte r) {
//     byte c;

//     digitalWrite(CSN, LOW);
//     SPI.transfer(r & 0x1F);
//     c = SPI.transfer(0);
//     digitalWrite(CSN, HIGH);

//     return c;
// }

// void enable() {
//     digitalWrite(CE, HIGH);
// }

// void setRX() {
//     setRegister(NRF24_CONFIG, getRegister(NRF24_CONFIG) | 0x01);
//     enable();
//     delayMicroseconds(100);
// }

// void setRegister(byte r, byte v) {
//     digitalWrite(CSN, LOW);
//     SPI.transfer((r & 0x1F) | 0x20);
//     SPI.transfer(v);
//     digitalWrite(CSN, HIGH);
// }

// void scanChannels() {
//     disable();
//     for (int i = 0; i < CHANNELS; i++) {
//         setRegister(NRF24_RF_CH, (128 * i) / CHANNELS);
//         setRX();
//         delayMicroseconds(40);
//         disable();
//         if (getRegister(NRF24_RPD) > 0) {
//             CHannel[i]++;
//         }
//     }
// }

// void writeRegister(uint8_t reg, uint8_t value) {
//     digitalWrite(CSN, LOW);
//     SPI.transfer(reg | 0x20);
//     SPI.transfer(value);
//     digitalWrite(CSN, HIGH);
// }

// uint8_t readRegister(uint8_t reg) {
//     digitalWrite(CSN, LOW);
//     SPI.transfer(reg & 0x1F);
//     uint8_t result = SPI.transfer(0x00);
//     digitalWrite(CSN, HIGH);
//     return result;
// }

// void disable() {
//     digitalWrite(CE, LOW);
// }

// void powerUp() {
//     uint8_t config = readRegister(NRF24_CONFIG);
//     writeRegister(NRF24_CONFIG, config | 0x02);
//     delay(5);
// }

// void analyzerSetup() {
//     esp_bt_controller_deinit();
//     esp_wifi_stop();
//     esp_wifi_deinit();

//     pinMode(CE, OUTPUT);
//     pinMode(CSN, OUTPUT);

//     SPI.begin(18, 19, 23, 5);
//     SPI.setDataMode(SPI_MODE0);
//     SPI.setFrequency(10000000);
//     SPI.setBitOrder(MSBFIRST);

//     display.begin();
//     display.clearBuffer();
//     display.sendBuffer();

//     digitalWrite(CSN, HIGH);
//     digitalWrite(CE, LOW);

//     disable();
//     powerUp();

//     writeRegister(NRF24_EN_AA, 0x00);
//     writeRegister(NRF24_RF_SETUP, 0x0F);
// }

// void analyzerLoop() {
//     scanChannels();

//     memset(values, 0, sizeof(values));

//     int n = 50;
//     while (n--) {
//         int i = N;
//         while (i--) {
//             setChannel(i);
//             startListening();
//             delayMicroseconds(128);
//             stopListening();
//             if (carrierDetected()) {
//                 ++values[i];
//             }
//         }
//     }

//     display.clearBuffer();
//     int barWidth = SCREEN_WIDTH / N;
//     int x = 0;
//     for (int i = 0; i < N; ++i) {
//         int v = 63 - values[i] * 3;
//         if (v < 0) {
//             v = 0;
//         }
//         display.drawVLine(x, v - 10, 64 - v);
//         x += barWidth;
//     }

//     display.setFont(u8g2_font_ncenB08_tr);
//     display.setCursor(0, 64);
//     display.print("1...5...10...25..50...80...128");
//     display.sendBuffer();

//     delay(50);
// }