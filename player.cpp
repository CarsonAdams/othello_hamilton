#include "player.h"
#define MIN       (-200)
#define comp(tempH, H, pm)           ((pm) == 1 ? (tempH) > (H) : (tempH) < (H))

/*
 * PLAYERNAME = hamilton
 */

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side mySide) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    side = mySide;
    other = (side == BLACK) ? WHITE : BLACK;
    board = new Board();
    depth = 6;
    mult = 6;
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be NULL.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return NULL.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {

    board->doMove(opponentsMove, other);
    vector<Move> moves = board->getMoves(side);
    int size = moves.size();
    if (size)
    {
        int H = MIN;
        int moveIdx = 0;
        for (int i = 0; i<size; i++)
        {
            Board *temp = board->copy();
            temp->doMove((&moves[i]), side);
            int tempH = minimaxScore(temp, other, depth-1);
            if (tempH > H)
            {
                H = tempH;
                moveIdx = i;
            }
        }
        Move * move = new Move(moves[moveIdx]);
        board->doMove(move, side);
        return move;
    }

    return NULL;
}

/*
 * Compute minimax score.
 */

int Player::minimaxScore(Board *cboard, Side cside, int cdepth) {

    int pm = -2*(side^cside) + 1;
    Side cother = (cside == BLACK) ? WHITE : BLACK;

    if (cdepth == 0) return (cboard->score(side));

    vector<Move> cmoves = cboard->getMoves(cside);
    int csize = cmoves.size();

    if (csize)
    {
        int H = pm * MIN;
        for (int i = 0; i < csize; i++)
        {
            Board *ctemp = cboard->copy();
            ctemp->doMove((&cmoves[i]), cside);
            int tempH = minimaxScore(ctemp, cother, cdepth-1);
            int x = (cmoves[i]).getX();
            int y = (cmoves[i]).getY();
            if ((x == 0 && y == 0) || (x == 7 && y == 0) ||
                (x == 0 && y == 7) || (x == 7 && y == 7))
            {
                tempH = tempH + pm * mult;
            }
            if (comp(tempH, H, pm))
            {
                H = tempH;
            }
        }
        return H;
    }
    else return minimaxScore(cboard->copy(), cother, cdepth-1);

}