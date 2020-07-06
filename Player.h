//
// Created by Yuechen Liu on 2019-07-26.
//

#ifndef A5_PLAYER_H
#define A5_PLAYER_H

#include "vector"


class Player{

public:
    Player();

    int playout(std::vector<char> &pos, int move);

    int makeMove(std::vector<char> &pos);

    int makeMoveHeuristic(std::vector<char> &pos);

    int heuristic(std::vector<char> &pos, int move);

    int heuristic1(std::vector<char> &pos, int move);

    std::vector<int> updateLegalMove(std::vector<char> &pos);


private:

    std::vector<char> copyLst(std::vector<char> &lst);

};

#endif //A5_PLAYER_H
