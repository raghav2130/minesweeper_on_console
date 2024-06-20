#ifndef CELL_H
#define CELL_H

class Cell {

public:
    
    Cell();
    bool isMine;
    bool isRevealed;
    bool isFlagged;
    int adjacentMines;
};

#endif // CELL_H
