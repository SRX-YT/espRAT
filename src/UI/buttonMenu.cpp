#include "UI/buttonMenu.h"

unsigned char c_icon[32];

ButtonMenu::ButtonMenu(String name, unsigned char icon[32]) {
    this->s_name = name;
    this->i_size_small = 16;
    this->i_size_big = i_size_small * 2;
    c_icon = icon;
}