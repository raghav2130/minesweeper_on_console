#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// Herer i created a class for a particular cell
// Thus its status will be defined by its attributes
// And one for the board
// Cell.h, Board.h and Game.h
#include "Cell.h"
#include "Board.h"
#include "Game.h"


using namespace std;

// building cell now with its constructor
Cell::Cell() : isMine(false), isRevealed(false), isFlagged(false), adjacentMines(0) {}

// constructor for board

Board::Board(int width,int height,int mines):width(width),height(height),mines(mines),cells(height,vector<Cell>(width)){
    placeMines();
    calculateAdjacentMines();
}

void Board::placeMines() {
    srand(time(0));
    int minesPlaced = 0;
    while (minesPlaced < mines){

        int x = rand() % width;
        int y = rand() % height;

        if (!cells[y][x].isMine){
            cells[y][x].isMine = true;
            minesPlaced++;
        }
    }
}

void Board::calculateAdjacentMines() {

    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){
            if (!cells[y][x].isMine){
                int count = 0;
                for (int i = -1; i <= 1; i++){
                    for (int j = -1; j <= 1; j++){
                        int newY = y + i;
                        int newX = x + j;
                        if (newX >= 0 && newX < width && newY >= 0 && newY < height && cells[newY][newX].isMine) {
                            count++;
                        }
                    }
                }
                cells[y][x].adjacentMines = count;
            }
        }
    }
}

void Board::display() const {
    cout << "   ";
    for (int x = 0; x < width; x++) {
        cout << x << " ";
    }
    cout << endl;

    for (int y = 0; y < height; y++) {
        cout << y << " ";
        if (y < 10) cout << " ";
        for (int x = 0; x < width; x++) {
            if (cells[y][x].isRevealed) {
                if (cells[y][x].isMine) {
                    cout << "* ";
                } else {
                    cout << cells[y][x].adjacentMines << " ";
                }
            } else if (cells[y][x].isFlagged) {
                cout << "F ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
}

void Board::revealCell(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height || cells[y][x].isRevealed || cells[y][x].isFlagged) return;
    cells[y][x].isRevealed = true;
    if (cells[y][x].adjacentMines == 0 && !cells[y][x].isMine) {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                revealCell(x + j, y + i);
            }
        }
    }
}

void Board::toggleFlag(int x, int y) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        cells[y][x].isFlagged = !cells[y][x].isFlagged;
    }
}

bool Board::checkWin() const {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (!cells[y][x].isMine && !cells[y][x].isRevealed && !cells[y][x].isFlagged) return false;
        }
    }
    return true;
}

bool Board::checkLose(int x, int y) const {
    return cells[y][x].isMine && cells[y][x].isRevealed;
}

// Actua game starts from here

Game::Game(int width, int height, int mines) : board(width, height, mines) {}

void Game::play() {
    bool gameOver = false;
    bool win = false;

    while (!gameOver && !win) {
        board.display();
        int x, y;
        char action;
        cout << "Enter action (r for reveal, f for flag) followed by coordinates (x y): ";
        cin >> action >> x >> y;

        if (action == 'r') {
            board.revealCell(x, y);
            if (board.checkLose(x, y)) {
                gameOver = true;
                cout << "You hit a mine! Game Over." << endl;
            }
        } else if (action == 'f') {
            board.toggleFlag(x, y);
        }

        if (board.checkWin()) {
            win = true;
            cout << "Congratulations! You've cleared the minefield." << endl;
        }
    }

    board.display();  // Final display of the board
}

int main() {
    Game game(10, 10, 10);
    game.play();
    return 0;
}

