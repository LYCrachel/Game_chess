//
// Created by Yuechen Liu on 2019-07-26.
//

#include "Board.h"
#include <iostream>

Board::Board(){};

void Board::setPos(std::vector<char> &pos){
    positions.clear();
    for (int i = 0; i < pos.size(); i++){
        positions.push_back(pos[i]);
    }
}

std::vector<char>  Board::getPos() {
    return positions;
}

bool Board::win(char x){
    int cur = 0;
    // horizontal
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 4; j++){
            cur = i * 7 + j;
            if (positions[cur] == positions[cur+1] && positions[cur+1] == positions[cur+2]
                && positions[cur+2] == positions[cur+3] && positions[cur] == x) return true;
        }
    }

    // vertical
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 7; j++){
            cur = i * 7 + j;
            if (positions[cur] == positions[cur+7] && positions[cur+7] == positions[cur+14]
                && positions[cur+14] == positions[cur+21] && positions[cur] == x) return true;
        }
    }

    // diagonal
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 4; j++){
            cur = i * 7 + j;


            if (positions[cur] == positions[cur+8] && positions[cur+8] == positions[cur+16]
                && positions[cur+16] == positions[cur+24] && positions[cur] == x) return true;
        }
    }
    for (int i = 0; i < 3; i++){
        for (int j = 3; j < 7; j++){
            cur = i * 7 + j;
            if (positions[cur] == positions[cur+6] && positions[cur+6] == positions[cur+12]
                && positions[cur+12] == positions[cur+18] && positions[cur] == x) return true;
        }
    }
    return false;
}

void Board::display() {
    std::cout << "\n| 1 | 2 | 3 | 4 | 5 | 6 | 7 | \n";
    std::cout << "----------------------------- \n";
    for (int i = 0; i < 6; i++){
        std::cout << "| ";
        for (int j = 0; j < 6; j++){
            std::cout << positions[i*7+j] << " | ";
        }
        std::cout << positions[i*7+6]<< " | \n";
    }
}