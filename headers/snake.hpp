#pragma once

#include <ncurses.h>
#include <queue>

#include "drawable.hpp"

enum Direction {
    up = 0, down, left, right
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
            currDirection = d;
        }

        //using current position of head of snake and current direction, this will give a SnakePiece
        SnakePiece nextHead() {
            //current position of the head
            int row = head().getY();
            int col = head().getX();

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
