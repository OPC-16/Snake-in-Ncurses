#pragma once

#include <ncurses.h>

//This class helps to represent anything on board that has a y and x value
class Drawable {
    public:
        Drawable() :
            y(0), x(0), icon(' ') {  }

        Drawable(int y, int x, chtype ch) :
            y(y), x(x), icon(ch) {  }

        int getX() {
            return x;
        }

        int getY() {
            return y;
        }

        chtype getIcon() {
            return icon;
        }

    protected:
        int y, x;
        chtype icon;
};
