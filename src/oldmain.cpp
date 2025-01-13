// /*
//  ***********
//  * INCLUDE *
//  ***********
// */

// #include "include.h"

// /*
//  *************
//  * BLUETOOTH *
//  *************
// */

// #include "BT/scanner.h"
// #include "BT/analyzer.h"
// #include "BT/jammer.h"
// #include "BT/blejammer.h"
// #include "BT/spoofer.h"
// #include "BT/applespam.h"
// #define CE_PIN 4
// #define CSN_PIN 5
// RF24 radio(CE_PIN, CSN_PIN);
// bool b_isScanner = false;
// bool b_isAnalyzer = false;
// bool b_isJammer = false;
// bool b_isBleJammer = false;
// bool b_isSpoofer = false;
// bool b_isApplespam = false;

// /*
//  ***********
//  * DISPLAY *
//  ***********
// */

// U8G2_SSD1306_128X64_NONAME_F_HW_I2C display(U8G2_R0, U8X8_PIN_NONE);

// const int MAX_ITEM_LENGTH = 20;

// const int MENU_MAX_ITEMS = 6;
// char c_menu_items [6] [MAX_ITEM_LENGTH] = {
//     { "WIFI" },
//     { "BLUETOOTH" },
//     { "SUB-1GHZ" },
//     { "BAD USB" },
//     { "GAMES" },
//     { "SETTINGS" },
// };
// const unsigned char* c_menu_icons[6] = {
//     ICON::MENU::menu_icon_wifi,
//     ICON::MENU::menu_icon_bt,
//     ICON::MENU::menu_icon_sub,
//     ICON::MENU::menu_icon_evilusb,
//     ICON::MENU::menu_icon_games,
//     ICON::MENU::menu_icon_settings
// };

// const int WIFI_MAX_ITEMS = 3;
// char c_wifi_items [3] [MAX_ITEM_LENGTH] = {
//     { "WTEST" },
//     { "WTEST" },
//     { "WTEST" }
// };
// const unsigned char* c_wifi_icons[6] {
//     ICON::MENU::menu_icon_wifi,
//     ICON::MENU::menu_icon_bt,
//     ICON::MENU::menu_icon_sub,
//     ICON::MENU::menu_icon_evilusb,
//     ICON::MENU::menu_icon_games,
//     ICON::MENU::menu_icon_settings
// };

// const int BLUETOOTH_MAX_ITEMS = 6;
// char c_bluetooth_items [6] [MAX_ITEM_LENGTH] = {
//     { "ANALYZER" },
//     { "SCANNER" },
//     { "SPOOFER" },
//     { "JAMMER" },
//     { "BLE JAMMER" },
//     { "APPLE SPAM" }
// };
// const unsigned char* c_bluetooth_icons[6] {
//     ICON::BT::bt_icon_analyzer,
//     ICON::BT::bt_icon_scanner,
//     ICON::BT::bt_icon_spoofer,
//     ICON::BT::bt_icon_jammer,
//     ICON::BT::bt_icon_blejammer,
//     ICON::BT::bt_icon_applespam
// };

// const int SUB_MAX_ITEMS = 3;
// char c_sub_items [3] [MAX_ITEM_LENGTH] = {
//     { "STEST" },
//     { "STEST" },
//     { "STEST" }
// };
// const unsigned char* c_sub_icons[6] {
//     ICON::MENU::menu_icon_wifi,
//     ICON::MENU::menu_icon_bt,
//     ICON::MENU::menu_icon_sub,
//     ICON::MENU::menu_icon_evilusb,
//     ICON::MENU::menu_icon_games,
//     ICON::MENU::menu_icon_settings
// };

// const int BADUSB_MAX_ITEMS = 3;
// char c_badusb_items [3] [MAX_ITEM_LENGTH] = {
//     { "BTEST" },
//     { "BTEST" },
//     { "BTEST" }
// };
// const unsigned char* c_badusb_icons[6] {
//     ICON::MENU::menu_icon_wifi,
//     ICON::MENU::menu_icon_bt,
//     ICON::MENU::menu_icon_sub,
//     ICON::MENU::menu_icon_evilusb,
//     ICON::MENU::menu_icon_games,
//     ICON::MENU::menu_icon_settings
// };

// const int GAMES_MAX_ITEMS = 3;
// char c_games_items [3] [MAX_ITEM_LENGTH] = {
//     { "GTEST" },
//     { "GTEST" },
//     { "GTEST" }
// };
// const unsigned char* c_games_icons[6] {
//     ICON::MENU::menu_icon_wifi,
//     ICON::MENU::menu_icon_bt,
//     ICON::MENU::menu_icon_sub,
//     ICON::MENU::menu_icon_evilusb,
//     ICON::MENU::menu_icon_games,
//     ICON::MENU::menu_icon_settings
// };

// const int SETTINGS_MAX_ITEMS = 3;
// char c_settings_items [3] [MAX_ITEM_LENGTH] = {
//     { "SETEST" },
//     { "SETEST" },
//     { "SETEST" }
// };
// const unsigned char* c_settings_icons[6] {
//     ICON::MENU::menu_icon_wifi,
//     ICON::MENU::menu_icon_bt,
//     ICON::MENU::menu_icon_sub,
//     ICON::MENU::menu_icon_evilusb,
//     ICON::MENU::menu_icon_games,
//     ICON::MENU::menu_icon_settings
// };

// /*
//  ***********
//  * BUTTONS *
//  ***********
// */

// #define DEBOUNCE_TIME    20
// #define BUTTON_UP_PIN    14
// #define BUTTON_DOWN_PIN  33
// #define BUTTON_LEFT_PIN  32
// #define BUTTON_RIGHT_PIN 15
// #define BUTTON_OK_PIN    27
// #define BUTTON_HOME_PIN  12
// ezButton btn_up(BUTTON_UP_PIN);
// ezButton btn_down(BUTTON_DOWN_PIN);
// ezButton btn_left(BUTTON_LEFT_PIN);
// ezButton btn_right(BUTTON_RIGHT_PIN);
// ezButton btn_ok(BUTTON_OK_PIN);
// ezButton btn_home(BUTTON_HOME_PIN);
// int i_item_selected = 0;
// int i_item_sel_previous;
// int i_item_sel_next;
// int i_current_screen = 0;
// int i_current_selected = 0;
// int i_prev_item_selected;

// /*
//  *******
//  * LED *
//  *******
// */

// #define LED_PIN     26
// #define NUM_LEDS    1
// #define BRIGHTNESS  40
// Adafruit_NeoPixel pixels(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// /*
//  ********
//  * VOID *
//  ********
// */

// void configureRF(RF24 &radio);

// void buttonsLoop();
// void checkButtonOk();
// void checkButtonHome();
// void checkButtonsUpDown();

// void updateDisplay();

// void menuLoop();
// void wifiLoop();
// void bluetoothLoop();
// void subLoop();
// void badusbLoop();
// void gamesLoop();
// void settingsLoop();

// /*
// *********
// * OTHER *
// *********
// */

// bool b_inApp = false;

// /*
//  *********
//  * SETUP *
//  *********
// */

// void setup() {
//     Serial.begin(115200);
    
//     pixels.begin();
//     pixels.setBrightness(BRIGHTNESS);
//     pixels.setPixelColor(0, pixels.Color(150, 0, 0));
//     pixels.show();

//     btn_up.setDebounceTime(DEBOUNCE_TIME);
//     btn_down.setDebounceTime(DEBOUNCE_TIME);
//     btn_left.setDebounceTime(DEBOUNCE_TIME);
//     btn_right.setDebounceTime(DEBOUNCE_TIME);
//     btn_ok.setDebounceTime(DEBOUNCE_TIME);
//     btn_home.setDebounceTime(DEBOUNCE_TIME);

//     configureRF(radio);

//     display.begin();
//     display.setBitmapMode(1);

//     display.clearBuffer();

//     display.setFont(u8g2_font_ncenB08_tr);
//     display.setCursor(5, 30);
//     display.print("Be RAT, be silent.");
//     display.setCursor(5, 45);
//     display.print("- espRAT");

//     display.sendBuffer();
//     delay(1000);

//     display.clearBuffer();

//     pixels.clear();
//     pixels.show();
// }

// /*
//  ********
//  * LOOP *
//  ********
// */

// void loop() {
//     buttonsLoop();

//     if (!b_inApp) {
//         display.clearBuffer();

//         checkButtonOk();
//         checkButtonsUpDown();
//         updateDisplay();

//         display.sendBuffer();
//     } else { 
//         updateDisplay();
//     }

//     checkButtonHome();
// }

// /*
//  ********
//  * RF24 *
//  ********
// */

// void configureRF(RF24 &radio) {
//     radio.begin();
//     radio.setAutoAck(false);
//     radio.stopListening();
//     radio.setRetries(0, 0);
//     radio.setPALevel(RF24_PA_MAX, true);
//     radio.setDataRate(RF24_2MBPS);
//     radio.setCRCLength(RF24_CRC_DISABLED);
// }

// /*
// ***********
// * BUTTONS *
// ***********
// */

// void buttonsLoop() {
//     btn_up.loop();
//     btn_down.loop();
//     btn_left.loop();
//     btn_right.loop();
//     btn_ok.loop();
//     btn_home.loop();
// }

// /*
// ******************
// * DISPLAY THINGS *
// ******************
// */
// void checkButtonOk() {
//     if (btn_ok.isReleased()) {
//         i_prev_item_selected = i_item_selected;
//         switch (i_current_screen) {
//             // MENU
//             case 0: 
//                 if (i_item_selected == 0) {
//                     // wifiSetup();
//                     i_current_screen = i_item_selected + 1;
//                     i_current_selected = i_item_selected + 1;
//                     break;
//                 }
//                 if (i_item_selected == 1) {
//                     // bluetoothSetup();
//                     i_current_screen = i_item_selected + 1;
//                     i_current_selected = i_item_selected + 1;
//                     break;
//                 }
//                 if (i_item_selected == 2) {
//                     // subSetup();
//                     i_current_screen = i_item_selected + 1;
//                     i_current_selected = i_item_selected + 1;
//                     break;
//                 }
//                 if (i_item_selected == 3) {
//                     // badusbSetup();
//                     i_current_screen = i_item_selected + 1;
//                     i_current_selected = i_item_selected + 1;
//                     break;
//                 }
//                 if (i_item_selected == 4) {
//                     // gamesSetup();
//                     i_current_screen = i_item_selected + 1;
//                     i_current_selected = i_item_selected + 1;
//                     break;
//                 }
//                 if (i_item_selected == 5) {
//                     // settingsSetup();
//                     i_current_screen = i_item_selected + 1;
//                     i_current_selected = i_item_selected + 1;
//                     break;
//                 }
//                 break;
//             // WIFI
//             case 1:
//                 break;
//             // BT
//             case 2:
//                 if (i_item_selected == 0) {
//                     b_inApp = true;
//                     b_isAnalyzer = true;
//                     analyzerSetup();
//                 }
//                 if (i_item_selected == 5) {
//                     b_inApp = true;
//                     b_isApplespam = true;
//                     applespamSetup();
//                 }
//                 break;
//             // SUB
//             case 3:
//                 break;
//             // BAD USB
//             case 4:
//                 break;
//             // GAMES
//             case 5:
//                 break;
//             // SETTINGS
//             case 6:
//                 break;
//             default:
//                 break;
//         }
//     }
// }

// void checkButtonHome() {
//     if (btn_home.isPressed()) {
//         if (i_current_screen == 0) { return; }
//         i_current_selected = 0;
//         i_current_screen = 0;
//         i_item_selected = i_prev_item_selected;
//         b_inApp = false;

//         b_isApplespam = false;
//         b_isAnalyzer = false;
//     }
// }

// void checkButtonsUpDown() {
//     if (i_current_screen == 0) {
//         if (btn_up.isReleased()) {
//             i_item_selected -= 1;
//             if (i_item_selected < 0) {
//                 i_item_selected = MENU_MAX_ITEMS - 1;
//             }
//         }
//         if (btn_down.isReleased()) {
//             i_item_selected += 1;
//             if (i_item_selected >= MENU_MAX_ITEMS) {
//                 i_item_selected = 0;
//             }
//         }
//     }
//     if (i_current_screen == 1) {
//         if (btn_up.isReleased()) {
//             i_item_selected -= 1;
//             if (i_item_selected < 0) {
//                 i_item_selected = WIFI_MAX_ITEMS - 1;
//             }
//         }
//         if (btn_down.isReleased()) {
//             i_item_selected += 1;
//             if (i_item_selected >= WIFI_MAX_ITEMS) {
//                 i_item_selected = 0;
//             }
//         }
//     }
//     if (i_current_screen == 2) {
//         if (btn_up.isReleased()) {
//             i_item_selected -= 1;
//             if (i_item_selected < 0) {
//                 i_item_selected = BLUETOOTH_MAX_ITEMS - 1;
//             }
//         }
//         if (btn_down.isReleased()) {
//             i_item_selected += 1;
//             if (i_item_selected >= BLUETOOTH_MAX_ITEMS) {
//                 i_item_selected = 0;
//             }
//         }
//     }
//     if (i_current_screen == 3) {
//         if (btn_up.isReleased()) {
//             i_item_selected -= 1;
//             if (i_item_selected < 0) {
//                 i_item_selected = SUB_MAX_ITEMS - 1;
//             }
//         }
//         if (btn_down.isReleased()) {
//             i_item_selected += 1;
//             if (i_item_selected >= SUB_MAX_ITEMS) {
//                 i_item_selected = 0;
//             }
//         }
//     }
//     if (i_current_screen == 4) {
//         if (btn_up.isReleased()) {
//             i_item_selected -= 1;
//             if (i_item_selected < 0) {
//                 i_item_selected = BADUSB_MAX_ITEMS - 1;
//             }
//         }
//         if (btn_down.isReleased()) {
//             i_item_selected += 1;
//             if (i_item_selected >= BADUSB_MAX_ITEMS) {
//                 i_item_selected = 0;
//             }
//         }
//     }
//     if (i_current_screen == 5) {
//         if (btn_up.isReleased()) {
//             i_item_selected -= 1;
//             if (i_item_selected < 0) {
//                 i_item_selected = GAMES_MAX_ITEMS - 1;
//             }
//         }
//         if (btn_down.isReleased()) {
//             i_item_selected += 1;
//             if (i_item_selected >= GAMES_MAX_ITEMS) {
//                 i_item_selected = 0;
//             }
//         }
//     }
//     if (i_current_screen == 6) {
//         if (btn_up.isReleased()) {
//             i_item_selected -= 1;
//             if (i_item_selected < 0) {
//                 i_item_selected = SETTINGS_MAX_ITEMS - 1;
//             }
//         }
//         if (btn_down.isReleased()) {
//             i_item_selected += 1;
//             if (i_item_selected >= SETTINGS_MAX_ITEMS) {
//                 i_item_selected = 0;
//             }
//         }
//     }
// }

// void updateDisplay() {
//     if (!b_inApp) {
//         switch (i_current_selected) {
//         case 0:
//             menuLoop();
//             break;
//         case 1:
//             wifiLoop();
//             break;
//         case 2:
//             bluetoothLoop();
//             break;
//         case 3:
//             subLoop();
//             break;
//         case 4:
//             badusbLoop();
//             break;
//         case 5:
//             gamesLoop();
//             break;
//         case 6:
//             settingsLoop();
//             break;
//         default:
//             break;
//         }
//     }
//     else if (b_inApp) {
//         if (b_isApplespam) {
//             applespamLoop();
//         }
//         if (b_isAnalyzer) {
//             analyzerLoop();
//         }
//     }
// }

// void menuLoop() {
//     // SHOW PREV AND NEXT ITEMS IN MENU CAROUSEL
//     i_item_sel_previous = i_item_selected - 1;
//     if (i_item_sel_previous < 0) { i_item_sel_previous = MENU_MAX_ITEMS - 1; }
//     i_item_sel_next = i_item_selected + 1;
//     if (i_item_sel_next >= MENU_MAX_ITEMS) { i_item_sel_next = 0; }

//     display.drawXBMP(0, 22, 128, 21, UI::bitmap_item_sel_outline);
//     // PREV
//     display.setFont(u8g_font_7x14);
//     display.drawStr(25, 15, c_menu_items[i_item_sel_previous]);
//     display.drawXBMP(4, 2, 16, 16, c_menu_icons[i_item_sel_previous]);
//     // CURRENT
//     display.setFont(u8g_font_7x14B);
//     display.drawStr(25, 15 + 20 + 2, c_menu_items[i_item_selected]);
//     display.drawXBMP(4, 24, 16, 16, c_menu_icons[i_item_selected]);
//     // NEXT
//     display.setFont(u8g_font_7x14);
//     display.drawStr(25, 15 + 20 + 20 + 2 + 2, c_menu_items[i_item_sel_next]);
//     display.drawXBMP(4, 46, 16, 16, c_menu_icons[i_item_sel_next]);
//     // UI SCROLLBAR
//     display.drawXBMP(128 - 8, 0, 8, 64, UI::bitmap_scrollbar_background);
//     // UI SCROLLBAR BOX
//     int temp = 64 / MENU_MAX_ITEMS;
//     display.drawBox(125, temp * i_item_selected, 3, temp);
// }
// void wifiLoop() {
//     // SHOW PREV AND NEXT ITEMS IN MENU CAROUSEL
//     i_item_sel_previous = i_item_selected - 1;
//     if (i_item_sel_previous < 0) { i_item_sel_previous = WIFI_MAX_ITEMS - 1; }
//     i_item_sel_next = i_item_selected + 1;
//     if (i_item_sel_next >= WIFI_MAX_ITEMS) { i_item_sel_next = 0; }

//     display.drawXBMP(0, 22, 128, 21, UI::bitmap_item_sel_outline);
//     // PREV
//     display.setFont(u8g_font_7x14);
//     display.drawStr(25, 15, c_wifi_items[i_item_sel_previous]);
//     display.drawXBMP(4, 2, 16, 16, c_wifi_icons[i_item_sel_previous]);
//     // CURRENT
//     display.setFont(u8g_font_7x14B);
//     display.drawStr(25, 15 + 20 + 2, c_wifi_items[i_item_selected]);
//     display.drawXBMP(4, 24, 16, 16, c_wifi_icons[i_item_selected]);
//     // NEXT
//     display.setFont(u8g_font_7x14);
//     display.drawStr(25, 15 + 20 + 20 + 2 + 2, c_wifi_items[i_item_sel_next]);
//     display.drawXBMP(4, 46, 16, 16, c_wifi_icons[i_item_sel_next]);
//     // UI SCROLLBAR
//     display.drawXBMP(128 - 8, 0, 8, 64, UI::bitmap_scrollbar_background);
//     // UI SCROLLBAR BOX
//     int temp = 64 / WIFI_MAX_ITEMS;
//     display.drawBox(125, temp * i_item_selected, 3, temp);
// }
// void bluetoothLoop() {
//     // SHOW PREV AND NEXT ITEMS IN MENU CAROUSEL
//     i_item_sel_previous = i_item_selected - 1;
//     if (i_item_sel_previous < 0) { i_item_sel_previous = BLUETOOTH_MAX_ITEMS - 1; }
//     i_item_sel_next = i_item_selected + 1;
//     if (i_item_sel_next >= BLUETOOTH_MAX_ITEMS) { i_item_sel_next = 0; }

//     display.drawXBMP(0, 22, 128, 21, UI::bitmap_item_sel_outline);
//     // PREV
//     display.setFont(u8g_font_7x14);
//     display.drawStr(25, 15, c_bluetooth_items[i_item_sel_previous]);
//     display.drawXBMP(4, 2, 16, 16, c_bluetooth_icons[i_item_sel_previous]);
//     // CURRENT
//     display.setFont(u8g_font_7x14B);
//     display.drawStr(25, 15 + 20 + 2, c_bluetooth_items[i_item_selected]);
//     display.drawXBMP(4, 24, 16, 16, c_bluetooth_icons[i_item_selected]);
//     // NEXT
//     display.setFont(u8g_font_7x14);
//     display.drawStr(25, 15 + 20 + 20 + 2 + 2, c_bluetooth_items[i_item_sel_next]);
//     display.drawXBMP(4, 46, 16, 16, c_bluetooth_icons[i_item_sel_next]);
//     // UI SCROLLBAR
//     display.drawXBMP(128 - 8, 0, 8, 64, UI::bitmap_scrollbar_background);
//     // UI SCROLLBAR BOX
//     int temp = 64 / BLUETOOTH_MAX_ITEMS;
//     display.drawBox(125, temp * i_item_selected, 3, temp);
// }
// void subLoop() {
//     // SHOW PREV AND NEXT ITEMS IN MENU CAROUSEL
//     i_item_sel_previous = i_item_selected - 1;
//     if (i_item_sel_previous < 0) { i_item_sel_previous = SUB_MAX_ITEMS - 1; }
//     i_item_sel_next = i_item_selected + 1;
//     if (i_item_sel_next >= SUB_MAX_ITEMS) { i_item_sel_next = 0; }

//     display.drawXBMP(0, 22, 128, 21, UI::bitmap_item_sel_outline);
//     // PREV
//     display.setFont(u8g_font_7x14);
//     display.drawStr(25, 15, c_sub_items[i_item_sel_previous]);
//     display.drawXBMP(4, 2, 16, 16, c_sub_icons[i_item_sel_previous]);
//     // CURRENT
//     display.setFont(u8g_font_7x14B);
//     display.drawStr(25, 15 + 20 + 2, c_sub_items[i_item_selected]);
//     display.drawXBMP(4, 24, 16, 16, c_sub_icons[i_item_selected]);
//     // NEXT
//     display.setFont(u8g_font_7x14);
//     display.drawStr(25, 15 + 20 + 20 + 2 + 2, c_sub_items[i_item_sel_next]);
//     display.drawXBMP(4, 46, 16, 16, c_sub_icons[i_item_sel_next]);
//     // UI SCROLLBAR
//     display.drawXBMP(128 - 8, 0, 8, 64, UI::bitmap_scrollbar_background);
//     // UI SCROLLBAR BOX
//     int temp = 64 / SUB_MAX_ITEMS;
//     display.drawBox(125, temp * i_item_selected, 3, temp);
// }
// void badusbLoop() {
//     // SHOW PREV AND NEXT ITEMS IN MENU CAROUSEL
//     i_item_sel_previous = i_item_selected - 1;
//     if (i_item_sel_previous < 0) { i_item_sel_previous = BADUSB_MAX_ITEMS - 1; }
//     i_item_sel_next = i_item_selected + 1;
//     if (i_item_sel_next >= BADUSB_MAX_ITEMS) { i_item_sel_next = 0; }

//     display.drawXBMP(0, 22, 128, 21, UI::bitmap_item_sel_outline);
//     // PREV
//     display.setFont(u8g_font_7x14);
//     display.drawStr(25, 15, c_badusb_items[i_item_sel_previous]);
//     display.drawXBMP(4, 2, 16, 16, c_badusb_icons[i_item_sel_previous]);
//     // CURRENT
//     display.setFont(u8g_font_7x14B);
//     display.drawStr(25, 15 + 20 + 2, c_badusb_items[i_item_selected]);
//     display.drawXBMP(4, 24, 16, 16, c_badusb_icons[i_item_selected]);
//     // NEXT
//     display.setFont(u8g_font_7x14);
//     display.drawStr(25, 15 + 20 + 20 + 2 + 2, c_badusb_items[i_item_sel_next]);
//     display.drawXBMP(4, 46, 16, 16, c_badusb_icons[i_item_sel_next]);
//     // UI SCROLLBAR
//     display.drawXBMP(128 - 8, 0, 8, 64, UI::bitmap_scrollbar_background);
//     // UI SCROLLBAR BOX
//     int temp = 64 / BADUSB_MAX_ITEMS;
//     display.drawBox(125, temp * i_item_selected, 3, temp);
// }
// void gamesLoop() {
//     // SHOW PREV AND NEXT ITEMS IN MENU CAROUSEL
//     i_item_sel_previous = i_item_selected - 1;
//     if (i_item_sel_previous < 0) { i_item_sel_previous = GAMES_MAX_ITEMS - 1; }
//     i_item_sel_next = i_item_selected + 1;
//     if (i_item_sel_next >= GAMES_MAX_ITEMS) { i_item_sel_next = 0; }

//     display.drawXBMP(0, 22, 128, 21, UI::bitmap_item_sel_outline);
//     // PREV
//     display.setFont(u8g_font_7x14);
//     display.drawStr(25, 15, c_games_items[i_item_sel_previous]);
//     display.drawXBMP(4, 2, 16, 16, c_games_icons[i_item_sel_previous]);
//     // CURRENT
//     display.setFont(u8g_font_7x14B);
//     display.drawStr(25, 15 + 20 + 2, c_games_items[i_item_selected]);
//     display.drawXBMP(4, 24, 16, 16, c_games_icons[i_item_selected]);
//     // NEXT
//     display.setFont(u8g_font_7x14);
//     display.drawStr(25, 15 + 20 + 20 + 2 + 2, c_games_items[i_item_sel_next]);
//     display.drawXBMP(4, 46, 16, 16, c_games_icons[i_item_sel_next]);
//     // UI SCROLLBAR
//     display.drawXBMP(128 - 8, 0, 8, 64, UI::bitmap_scrollbar_background);
//     // UI SCROLLBAR BOX
//     int temp = 64 / GAMES_MAX_ITEMS;
//     display.drawBox(125, temp * i_item_selected, 3, temp);
// }
// void settingsLoop() {
//     // SHOW PREV AND NEXT ITEMS IN MENU CAROUSEL
//     i_item_sel_previous = i_item_selected - 1;
//     if (i_item_sel_previous < 0) { i_item_sel_previous = SETTINGS_MAX_ITEMS - 1; }
//     i_item_sel_next = i_item_selected + 1;
//     if (i_item_sel_next >= SETTINGS_MAX_ITEMS) { i_item_sel_next = 0; }

//     display.drawXBMP(0, 22, 128, 21, UI::bitmap_item_sel_outline);
//     // PREV
//     display.setFont(u8g_font_7x14);
//     display.drawStr(25, 15, c_settings_items[i_item_sel_previous]);
//     display.drawXBMP(4, 2, 16, 16, c_settings_icons[i_item_sel_previous]);
//     // CURRENT
//     display.setFont(u8g_font_7x14B);
//     display.drawStr(25, 15 + 20 + 2, c_settings_items[i_item_selected]);
//     display.drawXBMP(4, 24, 16, 16, c_settings_icons[i_item_selected]);
//     // NEXT
//     display.setFont(u8g_font_7x14);
//     display.drawStr(25, 15 + 20 + 20 + 2 + 2, c_settings_items[i_item_sel_next]);
//     display.drawXBMP(4, 46, 16, 16, c_settings_icons[i_item_sel_next]);
//     // UI SCROLLBAR
//     display.drawXBMP(128 - 8, 0, 8, 64, UI::bitmap_scrollbar_background);
//     // UI SCROLLBAR BOX
//     int temp = 64 / SETTINGS_MAX_ITEMS;
//     display.drawBox(125, temp * i_item_selected, 3, temp);
// }

// /*
// *********
// * OTHER *
// *********
// */
