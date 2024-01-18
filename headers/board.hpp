#pragma once

#include <ncurses.h>

class Board {
    public:
        Board(int height, int width) {
            int yMax, xMax;
            getmaxyx(stdscr, yMax, xMax);

            board_win = newwin(height, width, (yMax/2)-height/2, (xMax/2)-width/2);
        }

        void initialize() {
            clear();
            refresh();
        }

        void addBorder() {
            box(board_win, 0, 0);
        }

        void addAt(int y, int x, chtype ch) {
            mvwaddch(board_win, y, x, ch);
        }

        chtype getInput() {
            return wgetch(board_win);
        }

        void clear() {
            wclear(board_win);
            box(board_win, 0, 0);
        }

        void refresh() {
            wrefresh(board_win);
        }

    private:
        WINDOW *board_win;
};
