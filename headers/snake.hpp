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
            return prev_pieces.back();
        }

        SnakePiece head() {
            return prev_pieces.front();
        }

    private:
        std::queue<SnakePiece> prev_pieces;
        Direction currDirection;
};
