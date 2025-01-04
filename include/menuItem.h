#pragma once

#include <vector>
#include <pgmspace.h>

class MenuItem {
public:
    MenuItem(String item) {
        this->s_name = item;
    }

    void Add(String item) {
        this->v_listItems.push_back(item);
        this->i_size = this->v_listItems.size();
    }

    String GetName() {
        return this->s_name;
    }

private:
    int i_size;
    String s_name;
    std::vector<String> v_listItems;
};