#pragma once

#include <ncurses.h>

class Scoreboard {
    public:
        Scoreboard() {

        }

        Scoreboard(int width, int y, int x) {
            score_win = newwin(1, width, y, x);  //height of 1 is sufficient for score_win as it will only display score
        }

        void initialize(int initialScore) {
            clear();
            mvwprintw(score_win, 0, 0, "Score:");
            updateScore(initialScore);
            refresh();
        }

        void updateScore(int score) {
            mvwprintw(score_win, 0, score_win->_maxx - 10, "%11i", score);
            //%11i means that pad the score for so that total 11 chars can be printed and 'i' is for integer
        }

        void clear() {
            wclear(score_win);
        }

        void refresh() {
            wrefresh(score_win);
        }

    private:
        WINDOW *score_win;
};
