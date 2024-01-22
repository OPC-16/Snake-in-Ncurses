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

    int speed = 300;
    Game game(BOARD_ROWS, BOARD_COLS, speed);

    while (!game.isOver()) {
        game.processInput();
        game.updateState();
        game.redraw();
    }

    endwin();

    std::cout << "Game Over!" << std::endl;
    std::cout << "You Scored: " << game.getScore() << std::endl;
}
