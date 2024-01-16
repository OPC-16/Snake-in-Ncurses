#include <ncurses.h>
#include "headers/board.hpp"

int main() {
    initscr();
    refresh();

    getch();
    endwin();
}
