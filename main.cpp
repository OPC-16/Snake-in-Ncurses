#include <ncurses.h>

#include "headers/game.hpp"

#define BOARD_DIM 18
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

    getch();
    endwin();
}
