#include "player.h"
#define MIN       (-64)

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
            temp->doMove(&(moves[i]), side);
            vector<Move> moves2 = temp->getMoves(other);
            int size2 = moves2.size();
            int tempH;
            if (size2)
            {
                int H2 = -MIN;
                for (int j = 0; j<size2; j++)
                {
                    Board *temp2 = temp->copy();
                    temp2->doMove(&(moves2[j]), other);
                    int tempH2 = temp2->count(side) - temp2->count(other);
                    if (tempH2 < H2)
                    {
                        H2 = tempH2;
                    }
                }
                tempH = H2;
            }
            else
            {
                tempH = temp->count(side) - temp->count(other);
            }
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
