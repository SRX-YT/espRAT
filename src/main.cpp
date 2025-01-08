/*
 ***********
 * INCLUDE *
 ***********
*/

#include <Arduino.h>
#include <U8g2lib.h>
#include <ezButton.h>

#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

/*
 *************
 * BLUETOOTH *
 *************
*/

#include <RF24.h>
#include "BT/scanner.h"
#include "BT/analyzer.h"
#include "BT/jammer.h"
#include "BT/blejammer.h"
#include "BT/spoofer.h"
#include "BT/applespam.h"
#define CE_PIN 4
#define CSN_PIN 5
RF24 radio(CE_PIN, CSN_PIN);

/*
 ***********
 * DISPLAY *
 ***********
*/

#include "MENU/WIFI.h"
#include "MENU/BLUETOOTH.h"
#include "MENU/BADUSB.h"
#include "MENU/GAMES.h"
#include "MENU/SETTINGS.h"
#include "MENU/SUB.h"
#include "icon.h"
WIFI wifi;
BLUETOOTH bluetooth;
BADUSB badusb;
GAMES games;
SETTINGS settings;
SUB sub;
U8G2_SSD1306_128X64_NONAME_F_HW_I2C display(U8G2_R0, U8X8_PIN_NONE);
const unsigned char* c_bitmap_icons[6] = {
    ICON::bitmap_icon_wifi,
    ICON::bitmap_icon_bt,
    ICON::bitmap_icon_sub,
    ICON::bitmap_icon_evilusb,
    ICON::bitmap_icon_games,
    ICON::bitmap_icon_settings
};
const int NUM_ITEMS = 6;
const int MAX_ITEM_LENGTH = 20;
char menu_items [NUM_ITEMS] [MAX_ITEM_LENGTH] = {
    { "WIFI" },
    { "BLUETOOTH" },
    { "SUB-1GHZ" },
    { "BAD USB" },
    { "GAMES" },
    { "SETINGS" },
};

/*
 ***********
 * BUTTONS *
 ***********
*/

#define DEBOUNCE_TIME    20
#define BUTTON_UP_PIN    14
#define BUTTON_DOWN_PIN  33
#define BUTTON_LEFT_PIN  32
#define BUTTON_RIGHT_PIN 15
#define BUTTON_OK_PIN    27
#define BUTTON_HOME_PIN  12
ezButton btn_up(BUTTON_UP_PIN);
ezButton btn_down(BUTTON_DOWN_PIN);
ezButton btn_left(BUTTON_LEFT_PIN);
ezButton btn_right(BUTTON_RIGHT_PIN);
ezButton btn_ok(BUTTON_OK_PIN);
ezButton btn_home(BUTTON_HOME_PIN);
int i_item_selected = 0;
int i_item_sel_previous;
int i_item_sel_next;
int i_current_screen = 0;
int i_current_selected = 0;

/*
 ********
 * VOID *
 ********
*/

void configureRF(RF24 &radio);
void setup();

/*
 *********
 * SETUP *
 *********
*/

void setup() {
    btn_up.setDebounceTime(DEBOUNCE_TIME);
    btn_down.setDebounceTime(DEBOUNCE_TIME);
    btn_left.setDebounceTime(DEBOUNCE_TIME);
    btn_right.setDebounceTime(DEBOUNCE_TIME);
    btn_ok.setDebounceTime(DEBOUNCE_TIME);
    btn_home.setDebounceTime(DEBOUNCE_TIME);

    configureRF(radio);

    display.begin();
    display.setBitmapMode(1);

    display.clearBuffer();

    display.setFont(u8g2_font_ncenB08_tr);
    display.setCursor(5, 30);
    display.print("Be RAT, be silent.");
    display.setCursor(5, 45);
    display.print("- espRAT");

    display.sendBuffer();
    delay(1000);

    display.clearBuffer();
}

/*
 ********
 * LOOP *
 ********
*/

void loop() {
    btn_up.loop();
    btn_down.loop();
    btn_left.loop();
    btn_right.loop();
    btn_ok.loop();
    btn_home.loop();

    if (i_current_screen == 0) {
        if (btn_up.isReleased()) {
            i_item_selected -= 1;
            if (i_item_selected < 0) {
                i_item_selected = NUM_ITEMS - 1;
            }
        }
        if (btn_down.isReleased()) {
            i_item_selected += 1;
            if (i_item_selected >= NUM_ITEMS) {
                i_item_selected = 0;
            }
        }
    }
    if (i_current_screen == 1) {
        if (btn_up.isReleased()) {
            i_item_selected -= 1;
            if (i_item_selected < 0) {
                i_item_selected = wifi.getSize() - 1;
            }
        }
        if (btn_down.isReleased()) {
            i_item_selected += 1;
            if (i_item_selected >= wifi.getSize()) {
                i_item_selected = 0;
            }
        }
    }
    if (i_current_screen == 2) {
        if (btn_up.isReleased()) {
            i_item_selected -= 1;
            if (i_item_selected < 0) {
                i_item_selected = bluetooth.getSize() - 1;
            }
        }
        if (btn_down.isReleased()) {
            i_item_selected += 1;
            if (i_item_selected >= bluetooth.getSize()) {
                i_item_selected = 0;
            }
        }
    }
    if (i_current_screen == 3) {
        if (btn_up.isReleased()) {
            i_item_selected -= 1;
            if (i_item_selected < 0) {
                i_item_selected = sub.getSize() - 1;
            }
        }
        if (btn_down.isReleased()) {
            i_item_selected += 1;
            if (i_item_selected >= sub.getSize()) {
                i_item_selected = 0;
            }
        }
    }
    if (i_current_screen == 4) {
        if (btn_up.isReleased()) {
            i_item_selected -= 1;
            if (i_item_selected < 0) {
                i_item_selected = badusb.getSize() - 1;
            }
        }
        if (btn_down.isReleased()) {
            i_item_selected += 1;
            if (i_item_selected >= badusb.getSize()) {
                i_item_selected = 0;
            }
        }
    }
    if (i_current_screen == 5) {
        if (btn_up.isReleased()) {
            i_item_selected -= 1;
            if (i_item_selected < 0) {
                i_item_selected = games.getSize() - 1;
            }
        }
        if (btn_down.isReleased()) {
            i_item_selected += 1;
            if (i_item_selected >= games.getSize()) {
                i_item_selected = 0;
            }
        }
    }
    if (i_current_screen == 6) {
        if (btn_up.isReleased()) {
            i_item_selected -= 1;
            if (i_item_selected < 0) {
                i_item_selected = settings.getSize() - 1;
            }
        }
        if (btn_down.isReleased()) {
            i_item_selected += 1;
            if (i_item_selected >= settings.getSize()) {
                i_item_selected = 0;
            }
        }
    }

    if (btn_ok.isReleased()) {
        switch (i_current_screen) {
            // MENU
            case 0: 
                if (i_item_selected == 0) {
                    wifi.wifiSetup();
                    i_current_screen = i_item_selected + 1;
                    i_current_selected = i_item_selected + 1;
                    break;
                }
                if (i_item_selected == 1) {
                    bluetooth.bluetoothSetup();
                    i_current_screen = i_item_selected + 1;
                    i_current_selected = i_item_selected + 1;
                    break;
                }
                if (i_item_selected == 2) {
                    sub.subSetup();
                    i_current_screen = i_item_selected + 1;
                    i_current_selected = i_item_selected + 1;
                    break;
                }
                if (i_item_selected == 3) {
                    badusb.badusbSetup();
                    i_current_screen = i_item_selected + 1;
                    i_current_selected = i_item_selected + 1;
                    break;
                }
                if (i_item_selected == 4) {
                    games.gamesSetup();
                    i_current_screen = i_item_selected + 1;
                    i_current_selected = i_item_selected + 1;
                    break;
                }
                if (i_item_selected == 5) {
                    settings.settingsSetup();
                    i_current_screen = i_item_selected + 1;
                    i_current_selected = i_item_selected + 1;
                    break;
                }
                break;
            // WIFI
            case 1:
                break;
            // BLUETOOTH
            case 2:
                break;
            // SUB
            case 3:
                break;
            // BAD USB
            case 4:
                break;
            // GAMES
            case 5:
                break;
            // SETTINGS
            case 6:
                break;
            default:
                break;
        }
    }

    // UPDATE DISPLAY
    switch (i_current_selected) {
        case 1:
            wifi.wifiLoop();
            break;
        case 2:
            bluetooth.bluetoothLoop();
            break;
        case 3:
            sub.subLoop();
            break;
        case 4:
            badusb.badusbLoop();
            break;
        case 5:
            games.gamesLoop();
            break;
        case 6:
            settings.settingsLoop();
            break;
        default:
            break;
    }

    if (btn_home.isReleased()) {
        if (i_current_screen == 0) { return; }
        i_current_selected = 0;
        i_current_screen = 0;
        i_item_selected = 0;
    }

    // SHOW PREV AND NEXT ITEMS IN MENU CAROUSEL
    i_item_sel_previous = i_item_selected - 1;
    if (i_item_sel_previous < 0) { i_item_sel_previous = NUM_ITEMS - 1; }
    i_item_sel_next = i_item_selected + 1;
    if (i_item_sel_next >= NUM_ITEMS) { i_item_sel_next = 0; }

    display.clearBuffer();

    // DRAW DISPLAY
    if (i_current_screen == 0) {
        // UI OUTLINE
        display.drawXBMP(0, 22, 128, 21, UI::bitmap_item_sel_outline);

        // PREV
        display.setFont(u8g_font_7x14);
        display.drawStr(25, 15, menu_items[i_item_sel_previous]);
        display.drawXBMP(4, 2, 16, 16, c_bitmap_icons[i_item_sel_previous]);

        // CURRENT
        display.setFont(u8g_font_7x14B);
        display.drawStr(25, 15 + 20 + 2, menu_items[i_item_selected]);
        display.drawXBMP(4, 24, 16, 16, c_bitmap_icons[i_item_selected]);

        // NEXT
        display.setFont(u8g_font_7x14);
        display.drawStr(25, 15 + 20 + 20 + 2 + 2, menu_items[i_item_sel_next]);
        display.drawXBMP(4, 46, 16, 16, c_bitmap_icons[i_item_sel_next]);

        // UI SCROLLBAR
        display.drawXBMP(128 - 8, 0, 8, 64, UI::bitmap_scrollbar_background);

        // UI SCROLLBAR BOX
        int temp = 64 / NUM_ITEMS;
        display.drawBox(125, temp * i_item_selected, 3, temp);
    }

    display.sendBuffer();
}

/*
 ********
 * RF24 *
 ********
*/

void configureRF(RF24 &radio) {
    radio.begin();
    radio.setAutoAck(false);
    radio.stopListening();
    radio.setRetries(0, 0);
    radio.setPALevel(RF24_PA_MAX, true);
    radio.setDataRate(RF24_2MBPS);
    radio.setCRCLength(RF24_CRC_DISABLED);
}