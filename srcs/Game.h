#ifndef GAME_H
#define GAME_H

#include "Board.h"

class Game {
    
public:

    Game(int width, int height, int mines);
    void play();

private:

    Board board;

};

#endif // GAME_H
