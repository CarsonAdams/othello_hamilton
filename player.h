#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.h"
#include "board.h"
using namespace std;

class Player {

private:
    Side side;
    Side other;

public:
    Board *board;
    int depth;

    Player(Side mySide);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);
    int minimaxScore(Board *cboard, Move *cmove, Side cside, int cdepth);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
