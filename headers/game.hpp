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

            handleNextPiece(SnakePiece(1, 1));
            handleNextPiece(snake.nextHead());
            handleNextPiece(snake.nextHead());
            snake.setDirection(right);
            handleNextPiece(snake.nextHead());

            //making apple appear in the initialization phase
            if (apple == nullptr) {
                createApple();
            }
        }

        void updateState() {
            //handling the snake animation
            handleNextPiece(snake.nextHead());

            if (apple == nullptr) {
                createApple();
            }
        }

        void redraw() {
            board.refresh();
        }

        bool isOver() {
            return game_over;
        }

        void processInput() {
            chtype input = board.getInput();
            switch (input) {
                case KEY_UP:
                case 'k':
                    snake.setDirection(up);
                    break;
                case KEY_DOWN:
                case 'j':
                    snake.setDirection(down);
                    break;
                case KEY_LEFT:
                case 'h':
                    snake.setDirection(left);
                    break;
                case KEY_RIGHT:
                case 'l':
                    snake.setDirection(right);
                    break;
                case 'p':  //condition for pausing the game
                    board.setTimeout(-1);   //it will make the wgetch blocking, so that it'll wait forever for user to press key
                    while (board.getInput() != 'p');
                    board.setTimeout(1000);     //after pressing 'p' again, we set original timeout again
                    break;
                default:
                    break;
            }
        }

    private:
        void createApple() {
            int y, x;
            board.getEmptyCoordinates(y, x);
            apple = new Apple(y, x);
            board.add(*apple);
        }

        void deleteApple() {
            delete apple;
            apple = nullptr;
        }

        void handleNextPiece(SnakePiece next) {
            //if next pos is not apple then we assume that it is blank & we proceed with this pos
            if (apple != nullptr && (next.getX() != apple->getX() || next.getY() != apple->getY())) {
                int emptyRow = snake.tail().getY();
                int emptyCol = snake.tail().getX();
                board.add(Empty(emptyRow, emptyCol)); //this will remove/empty the tail pos of the snake
                snake.removePiece();
            }
            else {
                deleteApple();
            }
            board.add(next);
            snake.addPiece(next);
        }

    private:
        Board board;
        Apple *apple;
        Snake snake;
        bool game_over;
};
