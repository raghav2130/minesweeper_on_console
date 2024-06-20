#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Cell.h"

class Board {

public:

    Board(int width, int height, int mines);
    void placeMines();
    void calculateAdjacentMines();
    void display() const;
    void revealCell(int x, int y);
    void toggleFlag(int x, int y);
    bool checkWin() const;
    bool checkLose(int x, int y) const;

private:

    int width;
    int height;
    int mines;
    std::vector<std::vector<Cell>> cells;
};

#endif // BOARD_H
