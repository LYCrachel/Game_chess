//
// Created by Yuechen Liu on 2019-07-26.
//

#ifndef A5_BOARD_H
#define A5_BOARD_H

#include "vector"

class Board {

public:
    Board();
    void display();
    bool win(char x);
    void setPos(std::vector<char> &positions);
    std::vector<char> getPos();

private:
    std::vector<char> positions;
};


#endif //A5_BOARD_H
