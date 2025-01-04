/*
 ***********
 * INCLUDE *
 ***********
*/

#include <Arduino.h>
#include <Wire.h>
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
void displayHud(bool wifi, bool bt, bool charging, int percent, std::string title);

/*
 *********
 * START *
 *********
*/

void setup() {
    Serial.begin(9600);

    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
        Serial.println(F("SSD1306 allocation failed"));
        for(;;);
    }

    btn_up.setDebounceTime(DEBOUNCE_TIME);
    btn_down.setDebounceTime(DEBOUNCE_TIME);
    btn_ok.setDebounceTime(DEBOUNCE_TIME);
    btn_back.setDebounceTime(DEBOUNCE_TIME);

    p_where = WhereAt::MENU;

    MenuItem wifiMenu("WIFI");
    wifiMenu.SetIcon(IMAGES::icon_wifi);
    v_menuItems.push_back(wifiMenu);

    MenuItem bluetoothMenu("BLUETOOTH");
    bluetoothMenu.SetIcon(IMAGES::icon_bt);
    v_menuItems.push_back(bluetoothMenu);

    MenuItem subMenu("SUB 1GHZ");
    v_menuItems.push_back(subMenu);

    MenuItem badusbMenu("BADUSB");
    badusbMenu.SetIcon(IMAGES::icon_evilusb);
    v_menuItems.push_back(badusbMenu);

    MenuItem gamesMenu("GAMES");
    gamesMenu.SetIcon(IMAGES::icon_games);
    v_menuItems.push_back(gamesMenu);

    MenuItem settingsMenu("SETTINGS");
    settingsMenu.SetIcon(IMAGES::icon_settings);
    v_menuItems.push_back(settingsMenu);

    MenuItem shutdownMenu("TURN OFF");
    shutdownMenu.SetIcon(IMAGES::icon_turnoff);
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

}

void splashScreen() {
    display.clearDisplay();
    display.drawBitmap(0, 9, IMAGES::splashScreen_bmp, 128, 64, 1);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(10, 7);
    display.println("Be RAT, be silent.");
    display.display();
    delay(3000);
}

void displayMenuItems() {
    display.clearDisplay();
    displayHud(b_isConnectedToWifi, b_isConnectedToBT, b_isCharging, i_batteryPercent, "");
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
        display.printf("%d. %s", i + 1, v_menuItems[i].GetName());
        //display.drawBitmap(114, 20 * (j + 1), IMAGES::icon_wifi, 11, 11, WHITE);
        j++;
    }
    display.display();
}

void displayHud(bool wifi, bool bt, bool charging, int percent, std::string title) {
    // STROKE
    display.drawLine(0, 15, 128, 15, WHITE);
    // WIFI
    if (wifi) {
      display.drawBitmap(0, 1, IMAGES::icon_wifi, 11, 11, 1);
    } else {
      display.drawBitmap(0, 1, IMAGES::icon_nowifi, 11, 11, 1);
    }
    // BLUETOOTH
    if (bt) {
      display.drawBitmap(15, 1, IMAGES::icon_bt, 11, 11, 1);
    } else {
      display.drawBitmap(15, 1, IMAGES::icon_nobt, 11, 11, 1);
    }
    // TITLE
    // CHARGING
    if (charging) {
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(98, 4);
      display.print("+");
    }
    // PERCENT OF BATTERY
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(104, 4);
    display.printf("%d%%", percent);
}