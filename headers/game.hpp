#pragma once

#include <ncurses.h>
#include <time.h>
#include <cstdlib>

#include "apple.hpp"
#include "board.hpp"
#include "drawable.hpp"
#include "empty.hpp"
#include "snake.hpp"

class Game {
    public:
        Game(int height, int width) {
            board = Board(height, width);
            initialize();
        }

        ~Game() {
            delete apple;
        }

        void initialize() {
            apple = nullptr;
            board.initialize();
            game_over = false;

            //initialize our random seed
            srand(time(NULL));

            //initialize the snake
            snake.setDirection(down);

            SnakePiece next = SnakePiece(1, 1);
            board.add(next);
            snake.addPiece(next);

            next = snake.nextHead();
            board.add(next);
            snake.addPiece(next);

            next = snake.nextHead();
            board.add(next);
            snake.addPiece(next);

            snake.setDirection(right);

            next = snake.nextHead();
            board.add(next);
            snake.addPiece(next);
        }

        void processInput() {
            chtype input = board.getInput();
            //TODO: process the input
        }

        void updateState() {
            if (apple == nullptr) {
                int y, x;
                board.getEmptyCoordinates(y, x);
                apple = new Apple(y, x);
                board.add(*apple);
            }

            //handling the snake animation
            SnakePiece next = snake.nextHead();
            if (next.getX() != apple->getX() && next.getY() != apple->getY()) {//if next pos is not apple then we assume that it is blank & we can proceed with this pos
                int emptyRow = snake.tail().getY();
                int emptyCol = snake.tail().getX();
                board.add(Empty(emptyRow, emptyCol)); //this will remove/empty the tail pos of the snake
                snake.removePiece();
            }
            board.add(next);
            snake.addPiece(next);
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
        Snake snake;
        bool game_over;
};
