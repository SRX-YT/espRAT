#pragma once

#include <vector>
#include <string>
#include <pgmspace.h>

class MenuItem {
public:
    MenuItem(std::string item) {
        this->s_name = item;
    }

    void Add(std::string item) {
        this->v_listItems.push_back(item);
        this->i_size = this->v_listItems.size();
    }

    void SetIcon(unsigned char* PROGMEM item) {
        this->icon = item;
    }

    const unsigned char* GetIcon() const {
        return this->icon;
    }

    std::string GetName() {
        return this->s_name;
    }

private:
    int i_size;
    unsigned char* PROGMEM icon;
    std::string s_name;
    std::vector<std::string> v_listItems;
};