#pragma once

#include <ncurses.h>
#include <time.h>
#include <cstdlib>

#include "apple.hpp"
#include "board.hpp"
#include "drawable.hpp"
#include "empty.hpp"

class Game {
    public:
        Game(int height, int width) {
            board = Board(height, width);
            board.initialize();
            game_over = false;

            //initialize our random seed
            srand(time(NULL));
        }

        ~Game() {
            delete apple;
        }

        void processInput() {
            chtype input = board.getInput();
            //TODO: process the input
        }

        void updateState() {
            int y, x;
            board.getEmptyCoordinates(y, x);

            if (apple != nullptr) {         //if previous apple is present
                board.add(Empty(apple->getY(), apple->getX())); //removing the previous apple by replacing it with ' '
            }
            apple = new Apple(y, x);
            board.add(*apple);

            board.add(Drawable(3, 3, '#'));
        }

        void redraw() {
            board.refresh();
        }

        bool isOver() {
            return game_over;
        }

    private:
        Board board;
        Apple *apple;
        bool game_over;
};
