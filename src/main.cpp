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
#include <ezButton.h>
#include <images.h>
#include <menuItem.h>

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
 ***********
 * BUTTONS *
 ***********
*/

ezButton btn_up(32);
ezButton btn_down(33);
ezButton btn_ok(27);
ezButton btn_back(14);

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

    btn_up.setDebounceTime(DEBOUNCE_TIME);
    btn_down.setDebounceTime(DEBOUNCE_TIME);
    btn_ok.setDebounceTime(DEBOUNCE_TIME);
    btn_back.setDebounceTime(DEBOUNCE_TIME);

    p_where = WhereAt::MENU;

    v_menuItems.push_back(wifiMenu);
    wifiMenu.Add("WTEST");

    v_menuItems.push_back(bluetoothMenu);
    bluetoothMenu.Add("BTEST");

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
}

/*
 **********
 * UPDATE *
 **********
*/

void loop() {
    btn_up.loop();
    btn_down.loop();
    btn_ok.loop();
    btn_back.loop();

    if (btn_up.isReleased()) {
        if (i_currentSelection > 0) {
            i_currentSelection -= 1;
        } else {
            i_currentSelection = v_menuItems.size() - 1;
        }
        displayMenuItems();
    }
    if (btn_down.isReleased()) {
        if (i_currentSelection < v_menuItems.size() - 1) {
            i_currentSelection += 1;
        } else {
            i_currentSelection = 0;
        }
        displayMenuItems();
    }
    if (btn_back.isReleased()) {
        i_currentSelection = 0;
        p_where = WhereAt::MENU;
        displayMenuItems();
    }
    if (btn_ok.isReleased()) {
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
    }
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
