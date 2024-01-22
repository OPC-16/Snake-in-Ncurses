#include <ncurses.h>
#include <iostream>

#include "headers/game.hpp"

#define BOARD_DIM 15
#define BOARD_ROWS BOARD_DIM
#define BOARD_COLS (BOARD_DIM * 2.5)

int main() {
    initscr();
    refresh();
    noecho();
    curs_set(0); //hide the cursor

    Game game(BOARD_ROWS, BOARD_COLS);

    while (!game.isOver()) {
        game.processInput();
        game.updateState();
        game.redraw();
    }

    endwin();

    std::cout << "Game Over!" << std::endl;
}
