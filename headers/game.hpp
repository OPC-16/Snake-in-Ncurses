#pragma once

#include <ncurses.h>
#include <time.h>
#include <cstdlib>

#include "apple.hpp"
#include "board.hpp"
#include "drawable.hpp"
#include "empty.hpp"
#include "snake.hpp"
#include "scoreboard.hpp"

class Game {
    public:
        Game(int height, int width, int speed) {
            board = Board(height, width, speed);
            //creating scoreboard
            int sbRow = board.getStartRow() + height;
            int sbCol = board.getStartCol();
            scoreboard = Scoreboard(width, sbRow, sbCol);
            initialize();
        }

        ~Game() {
            delete apple;
        }

        void initialize() {
            apple = nullptr;
            board.initialize();
            game_over = false;

            //initializing scoreboard
            score = 0;
            scoreboard.initialize(score);

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
            scoreboard.refresh();
        }

        int getScore() {
            return score;
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
                case 'q':
                    game_over = true;
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

        void eatApple() {
            delete apple;
            apple = nullptr;
            //when snake eats apple score gets incremented
            score += 100;
            scoreboard.updateScore(score);
        }

        void handleNextPiece(SnakePiece next) {
            if (apple != nullptr) {
                //check what is there at the new head of the snake
                switch (board.getCharAt(next.getY(), next.getX())) {
                    case 'A':  //if it is an apple
                        eatApple();
                        break;
                    case ' ': {  //if blank space then just move the snake forward in curr dir by one block
                            int emptyRow = snake.tail().getY();
                            int emptyCol = snake.tail().getX();
                            board.add(Empty(emptyRow, emptyCol)); //this will remove/empty the tail pos of the snake
                            snake.removePiece();
                            break;
                        } //weird thing about C++: if we declare variables in switch statement then we need to enclose that case's logic in { }
                    default:        //this case is for snake colliding with Wall or itself
                        game_over = true;
                        break;
                }
            }
            board.add(next);
            snake.addPiece(next);
        }

    private:
        Board board;
        Apple *apple;
        Snake snake;
        Scoreboard scoreboard;
        int score;
        bool game_over;
};
