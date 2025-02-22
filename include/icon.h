#pragma once

namespace ICON {
    namespace MENU {
        // 'BT', 16x16px
        const unsigned char menu_icon_bt [] PROGMEM = {
          0x80, 0x03, 0x80, 0x07, 0x82, 0x0D, 0x86, 0x19, 0x8C, 0x11, 0x98, 0x19, 
  0xB0, 0x0D, 0xE0, 0x07, 0xE0, 0x07, 0xB0, 0x0D, 0x98, 0x19, 0x8C, 0x11, 
  0x86, 0x19, 0x82, 0x0D, 0x80, 0x07, 0x80, 0x03,
        };
        // 'EVILUSB', 16x16px
        const unsigned char menu_icon_evilusb [] PROGMEM = {
          0xE0, 0x07, 0xF8, 0x1F, 0x1C, 0x38, 0x06, 0x60, 0x13, 0xC8, 0x3B, 0xDC, 
  0x93, 0xC9, 0x83, 0xC1, 0x5E, 0x7A, 0xFE, 0x7F, 0xF0, 0x0F, 0x06, 0x60, 
  0xFF, 0xFF, 0xFE, 0x7F, 0xFF, 0xFF, 0x06, 0x60,
        };
        // 'GAMES', 16x16px
        const unsigned char menu_icon_games [] PROGMEM = {
          0x00, 0x00, 0x00, 0x00, 0xFC, 0x3F, 0xFC, 0x3F, 0x03, 0xC0, 0x03, 0xD8, 
  0x33, 0xD8, 0x7B, 0xC0, 0x7B, 0xC6, 0x33, 0xC6, 0x03, 0xC0, 0xFC, 0x3F, 
  0xFC, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        };
        // 'SETTINGS', 16x16px
        const unsigned char menu_icon_settings [] PROGMEM = {
          0x00, 0x18, 0x00, 0x1C, 0x00, 0x0C, 0x00, 0xCC, 0x00, 0xFE, 0x00, 0x7F, 
  0x80, 0x0F, 0xC0, 0x07, 0xE0, 0x03, 0xF0, 0x01, 0xFE, 0x00, 0x7F, 0x00, 
  0x33, 0x00, 0x30, 0x00, 0x38, 0x00, 0x18, 0x00,
        };
        // 'SUB 1GHZ', 16x16px
        const unsigned char menu_icon_sub [] PROGMEM = {
          0x0C, 0x30, 0x0C, 0x30, 0x66, 0x66, 0x66, 0x66, 0x36, 0x6C, 0xB6, 0x6D, 
  0xB6, 0x6D, 0xB6, 0x6D, 0x46, 0x62, 0x46, 0x62, 0x6C, 0x36, 0xEC, 0x37, 
  0xE0, 0x07, 0x30, 0x0C, 0x30, 0x0C, 0x30, 0x0C,
        };
        // 'WIFI', 16x16px
        const unsigned char menu_icon_wifi [] PROGMEM = {
          0x00, 0x00, 0x00, 0x00, 0xF0, 0x0F, 0xFC, 0x3F, 0x0F, 0xF0, 0x03, 0xC0, 
  0xE0, 0x07, 0xF8, 0x1F, 0x1E, 0x78, 0x06, 0x60, 0xC0, 0x03, 0xF0, 0x0F, 
  0x30, 0x0C, 0x00, 0x00, 0x80, 0x01, 0x80, 0x01,
        };
    };
    
    namespace BT {
        const unsigned char bt_icon_analyzer [] PROGMEM = {
          0xF8, 0x00, 0xFC, 0x01, 0x06, 0x03, 0x03, 0x06, 0x03, 0x06, 0x03, 0x06, 
  0x03, 0x06, 0x03, 0x06, 0x06, 0x03, 0xFC, 0x07, 0xF8, 0x0E, 0x00, 0x1C, 
  0x00, 0x38, 0x00, 0x70, 0x00, 0xE0, 0x00, 0xC0,
        };
        const unsigned char bt_icon_applespam [] PROGMEM = {
          0x00, 0x06, 0x00, 0x07, 0x00, 0x03, 0x00, 0x00, 0x78, 0x1E, 0xFC, 0x3F, 
  0xFE, 0x7F, 0xFE, 0x7F, 0xFE, 0x7F, 0xFE, 0x7F, 0xFE, 0x7F, 0xFE, 0x7F, 
  0xFC, 0x3F, 0xFC, 0x3F, 0xF8, 0x1F, 0xF0, 0x0F,
        };
        const unsigned char bt_icon_blejammer [] PROGMEM = {
          0x03, 0xC0, 0x06, 0x60, 0x0C, 0x30, 0x18, 0x18, 0x30, 0x0C, 0x60, 0x06, 
  0xC0, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xAB, 0xEA, 0xFF, 0xFF, 0xEF, 0xDE, 
  0xBB, 0xDB, 0xEF, 0xDE, 0xFF, 0xFF, 0xFF, 0xFF,
        };
        const unsigned char bt_icon_jammer [] PROGMEM = {
          0x00, 0xC0, 0x00, 0x60, 0x00, 0x30, 0x00, 0x18, 0x00, 0x0C, 0x00, 0x06, 
  0x00, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0xC0, 0xFF, 0xFF, 0xAB, 0xDA, 
  0xAB, 0xDA, 0xAB, 0xDA, 0xFF, 0xFF, 0xFF, 0xFF,
        };
        const unsigned char bt_icon_scanner [] PROGMEM = {
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x01, 0xFF, 0x03, 0x00, 0x07, 
  0x00, 0x0E, 0x7F, 0x1C, 0xFF, 0x18, 0xC0, 0x19, 0x80, 0x19, 0x9F, 0x19, 
  0x9F, 0x19, 0x98, 0x19, 0x9B, 0x19, 0x9B, 0x19,
        };
        const unsigned char bt_icon_spoofer [] PROGMEM = {
          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x60, 0x36, 0x6C, 0x33, 0xCC, 
  0x1B, 0xD8, 0x9B, 0xD9, 0x9B, 0xD9, 0x1B, 0xD8, 0x33, 0xCC, 0x36, 0x6C, 
  0x06, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        };
    };
};

namespace UI {
    // 'SCROLLBAR', 8x64px
    const unsigned char bitmap_scrollbar_background [] PROGMEM = {
  0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 
  0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 
  0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 
  0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 
  0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 
  0x00, 0x40, 0x00, 0x00, };
    // 'SELECT OUTLINE', 128x21px 
    const unsigned char bitmap_item_sel_outline [] PROGMEM = {
        0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0x03, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x02, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 
  0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x0C, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x02, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 
  0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x0C, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x02, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 
  0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x0C, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x02, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 
  0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x0C, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x02, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 
  0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x0C, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x02, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 
  0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x0C, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0xF8, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 
    };
}