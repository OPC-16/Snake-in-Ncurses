#pragma once

#include <ncurses.h>
#include "board.hpp"

class Game {
    public:
        Game(int height, int width) {
            board = Board(height, width);
            board.initialize();
            game_over = false;
        }

        void processInput() {
            chtype input = board.getInput();
            //TODO: process the input
        }

        void updateState() {
            //TODO
        }

        void redraw() {
            board.refresh();
        }

        bool isOver() {
            return game_over;
        }

    private:
        Board board;
        bool game_over;
};
