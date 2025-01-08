/*
 ***********
 * INCLUDE *
 ***********
*/

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <string>
#include <vector>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <images.h>
#include <menuItem.h>
#include <RF24.h>
#include <esp_bt.h>
#include <esp_wifi.h>

/*
 **********
 * DEFINE *
 **********
*/

#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64
#define LOGO_HEIGHT   128
#define LOGO_WIDTH    64
#define DEBOUNCE_TIME 20

/*
 *********************
 * DEVICE PARAMETERS *
 *********************
*/

bool b_isConnectedToWifi = true;
bool b_isConnectedToBT   = true;
bool b_isCharging        = true;
int  i_batteryPercent    = 100;
int  i_currentSelection  = 0;

/*
 *********
 * OTHER *
 *********
*/

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
enum WhereAt {
  MENU,
  WIFI,
  BLUETOOTH,
  SUB,
  BADUSB,
  GAMES,
  SETTINGS,
  IDLE
} p_where;
std::vector<MenuItem> v_menuItems;

/*
 *********
 * VOIDS *
 *********
*/

void splashScreen();
void displayMenuItems();
void displayHud(int percent, const char* title, bool charging);
void displayWifi();
void displayBluetooth();
void displaySub();
void displayBad();
void displayGames();
void displaySettings();

void configureRadio(RF24 &radio, int channel, SPIClass &spi);
void jamBLE();
void jamBluetooth();
void jamAll();

/*
 ************
 * MENUITEM *
 ************
*/

MenuItem wifiMenu("WIFI");
MenuItem bluetoothMenu("BLUETOOTH");
MenuItem subMenu("SUB 1GHZ");
MenuItem badusbMenu("BADUSB");
MenuItem gamesMenu("GAMES");
MenuItem settingsMenu("SETTINGS");
MenuItem shutdownMenu("REBOOT");

/*
 ********
 * RF24 *
 ********
*/

constexpr int SPI_SPEED = 16000000;
SPIClass spiVSPI;
RF24 radioVSPI(16, 5, SPI_SPEED);
int i_bluetoothChannels[] = {32, 34, 46, 48, 50, 52, 0, 1, 2, 4, 6, 8, 22, 24, 26, 28, 30, 74, 76, 78, 80};
int i_ble_channels[] = {2, 26, 80};
int i_currentMode = 0;

/*
 *********
 * START *
 *********
*/

void setup() {
    Serial.begin(115200);

    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
        Serial.println(F("SSD1306 allocation failed"));
        for(;;);
    }

    p_where = WhereAt::MENU;

    v_menuItems.push_back(wifiMenu);
    wifiMenu.Add("WTEST");

    v_menuItems.push_back(bluetoothMenu);
    bluetoothMenu.Add("JAM BLE");
    bluetoothMenu.Add("JAM BT");
    bluetoothMenu.Add("TRY JAM ALL");

    v_menuItems.push_back(subMenu);
    subMenu.Add("STEST");

    v_menuItems.push_back(badusbMenu);
    badusbMenu.Add("BATEST");

    v_menuItems.push_back(gamesMenu);
    gamesMenu.Add("GTEST");

    v_menuItems.push_back(settingsMenu);
    settingsMenu.Add("STEST");

    v_menuItems.push_back(shutdownMenu);

    splashScreen();
    displayMenuItems();

    esp_bt_controller_deinit();
    esp_wifi_stop();
    esp_wifi_deinit();
    esp_wifi_disconnect();

    spiVSPI.begin(18, 19, 23, 5);
    configureRadio(radioVSPI, i_ble_channels[0], spiVSPI);

    if (!radioVSPI.begin()) {
    Serial.println("Radio hardware is not responding!");
    while (1);
    }
    Serial.println("nRF24L01 module initialized successfully.");
}

/*
 **********
 * UPDATE *
 **********
*/

void loop() {
    if (Serial.available()) {
        String command = Serial.readStringUntil('\n');
        if (command == "W") {
            if (i_currentSelection > 0) {
                i_currentSelection -= 1;
            } else {
                i_currentSelection = v_menuItems.size() - 1;
            }
            displayMenuItems();
        }
        if (command == "S") {
            if (i_currentSelection < v_menuItems.size() - 1) {
                i_currentSelection += 1;
            } else {
                i_currentSelection = 0;
            }
            displayMenuItems();
        }
        if (command == "A") {

        }
        if (command == "D") {

        }
        if (command == "E") {
            if (p_where == WhereAt::MENU) {
                switch (i_currentSelection) {
                    case 0:
                        p_where = WhereAt::WIFI;
                        i_currentSelection = 0;
                        displayWifi();
                        break;
                    case 1:
                        p_where = WhereAt::BLUETOOTH;
                        i_currentSelection = 0;
                        displayBluetooth();
                        break;
                    case 2:
                        p_where = WhereAt::SUB;
                        i_currentSelection = 0;
                        displaySub();
                        break;
                    case 3:
                        p_where = WhereAt::BADUSB;
                        i_currentSelection = 0;
                        displayBad();
                        break;
                    case 4:
                        p_where = WhereAt::GAMES;
                        i_currentSelection = 0;
                        displayGames();
                        break;
                    case 5:
                        p_where = WhereAt::SETTINGS;
                        i_currentSelection = 0;
                        displaySettings();
                        break;
                    case 6:
                        ESP.restart();
                        break;
                    default:
                        break;
                }
            }
            if (p_where == WhereAt::BLUETOOTH) {
                switch(i_currentSelection) {
                    case 0:
                        i_currentMode = 0;
                        jamBLE();
                        break;
                    case 1:
                        i_currentMode = 1;
                        jamBluetooth();
                        break;
                    case 2:
                        i_currentMode = 2;
                        jamAll();
                        break;
                    default:
                        break;
                }
            }
        }
        if (command == "H") {
            i_currentSelection = 0;
            i_currentMode = 10;
            p_where = WhereAt::MENU;
            displayMenuItems();
        }
    }

    // WAIT BLE BT JAMMING
    if (p_where == WhereAt::BLUETOOTH) {
        switch (i_currentMode)
        {
        case 0: 
            jamBLE();
            break;
        case 1:
            jamBluetooth();
            break;
        case 2:
            jamAll();
            break;
        default:
            break;
        }
    }

    jamBluetooth();
}

void splashScreen() {
    display.clearDisplay();
    display.drawBitmap(0, 9, IMAGES::splashScreen_bmp, 128, 64, 1);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(10, 7);
    display.println("Be RAT, be silent.");
    display.display();
    delay(1000);
    
}

void displayMenuItems() {
    // CLEAR
    display.clearDisplay();
    // HUD
    displayHud(i_batteryPercent, "MENU", b_isCharging);
    // CYCLE
    int j = 0;
    for (int i = i_currentSelection; i < v_menuItems.size(); i++) {
        if (i == i_currentSelection) {
            display.setTextColor(BLACK);
            display.fillRoundRect(0, 20 * (j + 1) - 3, 110, 18, 3, WHITE);
        } else {
            display.setTextColor(WHITE);
            display.drawRoundRect(0, 20 * (j + 1) - 3, 110, 18, 3, WHITE);
        }
        display.setTextSize(1);
        display.setCursor(4, 20 * (j + 1) + 2);
        display.print(v_menuItems[i].GetName());
        if (v_menuItems[i].GetName() == "WIFI")      { display.drawBitmap(114, 20 * (j + 1), IMAGES::icon_wifi, 11, 11, WHITE); }
        if (v_menuItems[i].GetName() == "BLUETOOTH") { display.drawBitmap(114, 20 * (j + 1), IMAGES::icon_bt, 11, 11, WHITE); }
        if (v_menuItems[i].GetName() == "BADUSB")    { display.drawBitmap(114, 20 * (j + 1), IMAGES::icon_evilusb, 11, 11, WHITE); }
        if (v_menuItems[i].GetName() == "SETTINGS")  { display.drawBitmap(114, 20 * (j + 1), IMAGES::icon_settings, 11, 11, WHITE); }
        if (v_menuItems[i].GetName() == "REBOOT")    { display.drawBitmap(114, 20 * (j + 1), IMAGES::icon_turnoff, 11, 11, WHITE); }
        if (v_menuItems[i].GetName() == "GAMES")     { display.drawBitmap(114, 20 * (j + 1), IMAGES::icon_games, 11, 11, WHITE);}
        if (v_menuItems[i].GetName() == "SUB 1GHZ")  { display.drawBitmap(114, 20 * (j + 1), IMAGES::icon_sub, 11, 11, WHITE);}
        j++;
    }
    // DISPLAY
    display.display();
}

void displayHud(int percent, const char* title, bool charging) {
    // STROKE
    display.drawLine(0, 15, 128, 15, WHITE);
    // TITLEf
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(20, 4);
    display.print(title);
    // CHARGING
    if (charging) {
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(78, 4);
        display.print("+");
    }
    // PERCENT OF BATTERY
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(84, 4);
    display.printf("%d%%", percent);
}

void displayWifi() {
    display.clearDisplay();
    displayHud(i_batteryPercent, "WIFI", b_isCharging);
    int j = 0;
    for (int i = i_currentSelection; i < wifiMenu.GetSize(); i++) {
        if (i == i_currentSelection) {
            display.setTextColor(BLACK);
            display.fillRoundRect(0, 20 * (j + 1) - 3, 110, 18, 3, WHITE);
        } else {
            display.setTextColor(WHITE);
            display.drawRoundRect(0, 20 * (j + 1) - 3, 110, 18, 3, WHITE);
        }
        display.setTextSize(1);
        display.setCursor(4, 20 * (j + 1) + 2);
        display.print(wifiMenu.GetItems()[i]);
        j++;
    }
    display.display();
}

void displayBluetooth() {
    display.clearDisplay();
    displayHud(i_batteryPercent, "BLUETOOTH", b_isCharging);
    int j = 0;
    for (int i = i_currentSelection; i < bluetoothMenu.GetSize(); i++) {
        if (i == i_currentSelection) {
            display.setTextColor(BLACK);
            display.fillRoundRect(0, 20 * (j + 1) - 3, 110, 18, 3, WHITE);
        } else {
            display.setTextColor(WHITE);
            display.drawRoundRect(0, 20 * (j + 1) - 3, 110, 18, 3, WHITE);
        }
        display.setTextSize(1);
        display.setCursor(4, 20 * (j + 1) + 2);
        display.print(bluetoothMenu.GetItems()[i]);
        j++;
    }
    display.display();
}

void displaySub() {
    display.clearDisplay();
    displayHud(i_batteryPercent, "SUB 1GHZ", b_isCharging);
    int j = 0;
    for (int i = i_currentSelection; i < subMenu.GetSize(); i++) {
        if (i == i_currentSelection) {
            display.setTextColor(BLACK);
            display.fillRoundRect(0, 20 * (j + 1) - 3, 110, 18, 3, WHITE);
        } else {
            display.setTextColor(WHITE);
            display.drawRoundRect(0, 20 * (j + 1) - 3, 110, 18, 3, WHITE);
        }
        display.setTextSize(1);
        display.setCursor(4, 20 * (j + 1) + 2);
        display.print(subMenu.GetItems()[i]);
        j++;
    }
    display.display();
}

void displayBad() {
    display.clearDisplay();
    displayHud(i_batteryPercent, "BADUSB", b_isCharging);
    int j = 0;
    for (int i = i_currentSelection; i < badusbMenu.GetSize(); i++) {
        if (i == i_currentSelection) {
            display.setTextColor(BLACK);
            display.fillRoundRect(0, 20 * (j + 1) - 3, 110, 18, 3, WHITE);
        } else {
            display.setTextColor(WHITE);
            display.drawRoundRect(0, 20 * (j + 1) - 3, 110, 18, 3, WHITE);
        }
        display.setTextSize(1);
        display.setCursor(4, 20 * (j + 1) + 2);
        display.print(badusbMenu.GetItems()[i]);
        j++;
    }
    display.display();
}

void displayGames() {
    display.clearDisplay();
    displayHud(i_batteryPercent, "GAMES", b_isCharging);
    int j = 0;
    for (int i = i_currentSelection; i < gamesMenu.GetSize(); i++) {
        if (i == i_currentSelection) {
            display.setTextColor(BLACK);
            display.fillRoundRect(0, 20 * (j + 1) - 3, 110, 18, 3, WHITE);
        } else {
            display.setTextColor(WHITE);
            display.drawRoundRect(0, 20 * (j + 1) - 3, 110, 18, 3, WHITE);
        }
        display.setTextSize(1);
        display.setCursor(4, 20 * (j + 1) + 2);
        display.print(gamesMenu.GetItems()[i]);
        j++;
    }
    display.display();
}

void displaySettings() {
    display.clearDisplay();
    displayHud(i_batteryPercent, "SETTINGS", b_isCharging);
    int j = 0;
    for (int i = i_currentSelection; i < settingsMenu.GetSize(); i++) {
        if (i == i_currentSelection) {
            display.setTextColor(BLACK);
            display.fillRoundRect(0, 20 * (j + 1) - 3, 110, 18, 3, WHITE);
        } else {
            display.setTextColor(WHITE);
            display.drawRoundRect(0, 20 * (j + 1) - 3, 110, 18, 3, WHITE);
        }
        display.setTextSize(1);
        display.setCursor(4, 20 * (j + 1) + 2);
        display.print(settingsMenu.GetItems()[i]);
        j++;
    }
    display.display();
}

void configureRadio(RF24 &radio, int channel, SPIClass &spi) {
    if (radio.begin()) {
        radio.setAutoAck(false);
        radio.stopListening();
        radio.setRetries(0, 0);
        radio.setPALevel(RF24_PA_MAX, true);
        radio.setDataRate(RF24_2MBPS);
        radio.setCRCLength(RF24_CRC_DISABLED);
        radio.startConstCarrier(RF24_PA_HIGH, channel);
    }
}

void jamBLE() {
    display.clearDisplay();
    displayHud(i_batteryPercent, "JAM BLE", b_isCharging);
    int randomIndex = random(0, sizeof(i_ble_channels) / sizeof(i_ble_channels[0]));
    int channel = i_ble_channels[randomIndex];
    radioVSPI.setChannel(channel);
    display.display();
    Serial.println("JAMMING BLE");
}

void jamBluetooth() {
    display.clearDisplay();
    displayHud(i_batteryPercent, "JAM BT", b_isCharging);
    int randomIndex = random(0, sizeof(i_bluetoothChannels) / sizeof(i_bluetoothChannels[0]));
    int channel = i_bluetoothChannels[randomIndex];
    radioVSPI.setChannel(channel);
    display.display();
    Serial.println("JAMMING BT");
}

void jamAll() {
    if (random(0, 2)) {
        jamBluetooth();
    } else {
        jamBLE();
    }
}