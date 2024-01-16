#include <ncurses.h>
#include "headers/board.hpp"

#define board_dim 18
#define board_rows board_dim
#define board_cols (board_dim * 2.5)

int main() {
    initscr();
    refresh();

    Board board(board_rows, board_cols);

    getch();
    endwin();
}
