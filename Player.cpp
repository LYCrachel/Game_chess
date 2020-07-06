//
// Created by Yuechen Liu on 2019-07-26.
//

#include "Player.h"
#include "Board.h"
#include "iostream"
#include "random"
#include <stdlib.h>
#include <time.h>

Player::Player(){}

std::vector<char> Player::copyLst(std::vector<char> &lst) {
    std::vector<char> res;
    for (int i = 0; i < lst.size(); i++){
        res.push_back(lst[i]);
    }
    return res;
}


int Player::playout(std::vector<char> &pos, int move) { // move: exact column index of the element to be removed
    Board *b = new Board();
    b->setPos(pos);
    std::vector<char> copy = Player::copyLst(pos);
    if (pos[move] != '_') return -1;
    for (int i = 5; i >= 0; i--){
        if (copy[i*7+move] == '_') {
            //std::cout<< "inside placing first X" << std::endl;
            copy[i*7+move] = 'X';
            b->setPos(copy);
            //b->display();
            break;
        }
    }
    if (b->win('X')) return 5;
    std::vector<int> legal = updateLegalMove(copy);

    int randO, randX;
    //srand (time(NULL));
    while (legal.size() > 0 ){
        int randNum = rand() % (legal.size());
        //std::cout<< "randNum for O: "<< randNum << std::endl;
        randO = legal[randNum];
        for (int i = 5; i >= 0; i--){
            if (copy[i*7+randO] == '_') {
                //std::cout<< "inside placing simulated O" << std::endl;
                copy[i*7+randO] = 'O';
                b->setPos(copy);
                //b->display();
                legal = updateLegalMove(copy);
                break;
            }
        }
        if (b->win('O')) return 0;
        if (legal.size()==0) return 2;

        randNum = rand() % (legal.size());
        //std::cout<< "randNum for X: "<< randNum << std::endl;
        randX = legal[randNum];
        for (int i = 5; i >= 0; i--){
            if (copy[i*7+randX] == '_') {
                //std::cout<< "inside placing simulated X" << std::endl;
                copy[i*7+randX] = 'X';
                b->setPos(copy);
                //b->display();
                legal = updateLegalMove(copy);
                break;
            }
        }
        if (b->win('X')) return 5;
    }
    return 2;
}

std::vector<int>  Player::updateLegalMove(std::vector<char> &pos) {
    std::vector<int> res;
    for (int i = 0; i < 7; i++){
        if (pos[i] == '_') {
            res.push_back(i);
        }

    }
    return res;
}


int  Player::makeMove(std::vector<char> &pos) {
    std::vector<int> marks;
    int maxIndex = -1;
    int maxValue = -1;
    marks.assign(7, 0);
    for (int i = 0; i < 7; i++){
        int loop = 0;
        while (loop < 5000){
            marks[i] += playout(pos, i);
            loop++;
        }
        if (marks[i] > maxValue) {
            maxIndex = i;
            maxValue = marks[i];
        }
    }
    for (int j = 0; j < 7; j++){
        std::cout << j << " is " << marks[j] << std::endl;
    }
    return maxIndex;
}

int Player::makeMoveHeuristic(std::vector<char> &pos) {
    std::vector<int> marks;
    int maxIndex = -1;
    int maxValue = -1;
    marks.assign(7, 0);
    for (int i = 0; i < 7; i++){
        int loop = 0;
        while (loop < 5000){
            marks[i] += heuristic(pos, i);
            loop++;
        }
        if (marks[i] > maxValue) {
            maxIndex = i;
            maxValue = marks[i];
        }
    }
    //if (marks[3] == maxValue) maxIndex = 3;
    for (int j = 0; j < 7; j++){
        std::cout << j << " is " << marks[j] << std::endl;
    }
    return maxIndex;
}

int Player::heuristic(std::vector<char> &pos, int move){

    int playoutRes = playout(pos, move);
    Board *b = new Board();
    b->setPos(pos);
    std::vector<char> copy = Player::copyLst(pos);
    int evaluate = playoutRes;
    int thisPos;
    if (copy[move] != '_') return -1;
    for (int i = 5; i >= 0; i--){
        if (copy[i*7+move] == '_') {
            thisPos = i*7+move;
        }
    }

    if (move == 0){
        if (copy[thisPos+1] == 'O') {
            evaluate += 1;
            if (copy[thisPos+2] == 'O') {
                evaluate+= 1;
                if (copy[thisPos+3] != '_') evaluate -= 2;
            }
        }
        if (copy[thisPos+1] == 'X'){
            evaluate += 1;
            if (copy[thisPos+2] == 'X') {
                evaluate+= 1;
                if (copy[thisPos+3] != '_') evaluate += 1;
            }
        }
    }
    else if (move == 6){
        if (copy[thisPos-1] == 'O') {
            evaluate += 1;
            if (copy[thisPos-2] == 'O') {
                evaluate+= 1;
                //if (copy[thisPos-3]!= '_') evaluate -= 2;
            }
        }
        if (copy[thisPos-1] == 'X'){
            evaluate += 1;
            if (copy[thisPos-2] == 'X') {
                evaluate+= 1;
                //if (copy[thisPos-3] != '_') evaluate += 1;
            }
        }
    }
    else if (move >= 1 && copy[thisPos+1] == copy[thisPos+2] ) evaluate += 1;
    else if (move <= 5 && copy[thisPos-1] == copy[thisPos-2] ) evaluate += 1;
    else if (move <= 5 && move >= 1 && copy[thisPos-1] == copy[thisPos+1] && copy[thisPos-1] != '_') evaluate += 1;


    for (int i = 5; i >= 0; i--){
        if (copy[i*7+move] == '_') {
            copy[i*7+move] = 'O';
            b->setPos(copy);
            break;
        }
    }
    if (b->win('O')) return evaluate + 5;
    std::vector<int> legal = updateLegalMove(copy);

    int randO, randX;
    while (legal.size() > 0 ){
        int randNum = rand() % (legal.size());
        randO = legal[randNum];
        for (int i = 5; i >= 0; i--){
            if (copy[i*7+randO] == '_') {
                copy[i*7+randO] = 'X';
                b->setPos(copy);
                legal = updateLegalMove(copy);
                break;
            }
        }
        if (b->win('X')) return 0;
        if (legal.size()==0) return evaluate + 2;

        randNum = rand() % (legal.size());
        randX = legal[randNum];
        for (int i = 5; i >= 0; i--){
            if (copy[i*7+randX] == '_') {
                copy[i*7+randX] = 'O';
                b->setPos(copy);
                legal = updateLegalMove(copy);
                break;
            }
        }
        if (b->win('O')) return evaluate + 5;
    }
    return evaluate + 2;
}