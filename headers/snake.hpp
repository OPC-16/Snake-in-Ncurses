#pragma once

#include <ncurses.h>
#include <queue>

#include "drawable.hpp"

//the directions are such coz to avoid illegal moves by player
//illegal move eg - 'snake is going in right and player presses KEY_LEFT'
//so in following enum values are assigned in such format that sum of illegal move's direction is zero
enum Direction {
    up = 1,
    down = -1,
    left = 2,
    right = -2,
};

class SnakePiece : public Drawable {
    public:
        SnakePiece() {
            this->y = this->x = 0;
            this->icon = '#';
        }

        SnakePiece(int y, int x) {
            this->y = y;
            this->x = x;
            this->icon = '#';
        }
};

class Snake {
    public:
        Snake() {
            currDirection = down;
        }

        void addPiece(SnakePiece piece) {
            prev_pieces.push(piece);
        }

        void removePiece() {
            prev_pieces.pop();
        }

        SnakePiece tail() {
            return prev_pieces.front();
        }

        SnakePiece head() {
            return prev_pieces.back();
        }

        Direction getDirection() {
            return currDirection;
        }

        void setDirection(Direction d) {
            if (currDirection + d != 0)  //if the sum is not zero then it is valid move and then only we change direction
                currDirection = d;
        }

        //using current position of head of snake and current direction, this will give a SnakePiece
        SnakePiece nextHead() {
            //current position of the head
            int row = this->head().getY();
            int col = this->head().getX();

            switch (currDirection) {
                case down:
                    row++;
                    break;
                case up:
                    row--;
                    break;
                case left:
                    col--;
                    break;
                case right:
                    col++;
                    break;
            }

            return SnakePiece(row, col);
        }

    private:
        std::queue<SnakePiece> prev_pieces;
        Direction currDirection;
};
