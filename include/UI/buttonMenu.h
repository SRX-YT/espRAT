#include <Arduino.h>


class ButtonMenu {
public:
    ButtonMenu(String name, unsigned char icon[32]);
private:
    String s_name;
    int i_size_small;
    int i_size_big;
};