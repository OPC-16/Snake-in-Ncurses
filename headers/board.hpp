#pragma once

#include "drawable.hpp"
#include <cstdlib>
#include <ncurses.h>

class Board {
    public:
        Board() {
            construct(0, 0);
        }

        Board(int height, int width) {
            construct(height, width);
        }

        void initialize() {
            clear();
            refresh();
        }

        void addBorder() {
            box(board_win, 0, 0);
        }

        void add(Drawable drawable) {
            addAt(drawable.getY(), drawable.getX(), drawable.getIcon());
        }

        chtype getInput() {
            return wgetch(board_win);  //wgetch also performs an addtionnal wrefresh on the board_win
        }

        void clear() {
            wclear(board_win);
            box(board_win, 0, 0);
        }

        void refresh() {
            wrefresh(board_win);
        }

        // it loops thr the board_win checking if the randomly selected y & x are ' ',
        // and if there indeed blank it sets the values of y & x (remember both parameters are passed as reference)
        void getEmptyCoordinates(int& y, int& x) {
            while (mvwinch(board_win, y = rand() % height, x = rand() % width) != ' ');
        }

    private:
        WINDOW *board_win;
        int height, width;

        void construct(int height, int width) {
            int yMax, xMax;
            getmaxyx(stdscr, yMax, xMax);

            board_win = newwin(height, width, (yMax/2) - height/2, (xMax/2) - width/2);

            this->height = height;
            this->width = width;
        }

        void addAt(int y, int x, chtype ch) {
            mvwaddch(board_win, y, x, ch);
        }
};
