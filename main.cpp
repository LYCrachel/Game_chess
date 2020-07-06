#include <iostream>
#include "Board.h"
#include "Player.h"
#include "vector"
#include <stdlib.h>
#include <ctime>
#include <string>

using namespace std;

int playersMove();
bool moveFirst();
void printTimes(vector<double> &lst);
int userMove(vector<char> &lst);
int hMove(vector<char> &lst, Player p);
int tryPlay();

int main() {
//    int h = 0;
//    int m = 0;
//    int draw = 0;
//    for (int i = 0; i < 10; i++){
//        srand (time(NULL));
//        int res = tryPlay();
//        if (res == 1) h++;
//        if (res == 2) m++;
//        if (res == 0) draw++;
//        cout << "after No. " << i << endl;
//        cout << "h is " << h << endl;
//        cout << "m is " << m << endl;
//        cout << "draw is " << draw << endl;
//    }
    int res = tryPlay();
    return 0;
}

bool moveFirst(){
    char ifFirst;
    cout << "Type Y or y to make move first, otherwise type anything else. " << endl;
    if (cin >> ifFirst ) {
        if (ifFirst == 'Y' || ifFirst == 'y' ){
            return true;
        }
        else return false;
    }
    return false;
}

int playersMove(){
    cout << "Choose a column to make move:" << endl;
    string move;
    cin >> move;
    while ( move.size() != 1 || !(isdigit(move[0]))){
        cout << "Invalid Input! Please input an integer."<< endl;
        cin >> move;
        //cin.clear();
        //cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
    return stoi(move);
}

void printTimes(vector<double> &h){
    for (int i = 0; i < h.size(); i++){
        cout << h[i] << endl;
    }
}

int userMove(vector<char> &lst){
    int pMove = playersMove() - 1;
    while (lst[pMove] != '_'){
        cout << "Please choose a valid column. " << endl;
        pMove = playersMove() - 1;
    }
    return pMove;
}

int tryPlay(){
    Board *board =  new Board();
    Player *player = new Player();
    vector<char> lst;
    lst.assign(42, '_');
    board->setPos(lst);
    board->display();
    int maxSteps = 0;
    int pMove, cMove;
    bool ifFirst = moveFirst();
    if (ifFirst){
        pMove = playersMove()-1;
        while (lst[pMove] != '_'){
            cout << "Please choose a valid column. " << endl;
            pMove = playersMove()-1;
        }
        for (int i = 5; i >= 0; i--){
            if (lst[i*7+pMove] == '_') {
                lst[i*7+pMove] = 'O';
                break;
            }
        }
    }
    board->setPos(lst);
    board->display();
    time_t startM, finishM, startH, finishH;
    vector<double> mTimes, hTimes;
    double diff;
    srand (time(NULL));
    while (maxSteps < 42){

        time(&startM);
        cMove = player->makeMove(lst);
        //cMove = player->makeMoveHeuristic(lst);
        time(&finishM);
        diff = difftime(finishM, startM);
        cout << endl << "Computer(pMCT) make move: "<< cMove+1 << endl;
        cout << endl << "Computer(pMCT) made 5000 random playouts using: "<< diff <<" seconds." << endl;
        //mTimes.push_back(diff);
        maxSteps++;
        for (int i = 5; i >= 0; i--) {
            if (lst[i*7+cMove] == '_') {
                lst[i*7+cMove] = 'X';
                break;
            }
        }
        board->setPos(lst);
        board->display();
        if (board->win('X')) {
            cout << endl << "------------------------ MCT won ----------------------" << endl;
            return 2;
        }


        pMove = userMove(lst);
        //pMove = player->makeMoveHeuristic(lst);

        for (int i = 5; i >= 0; i--){
            if (lst[i*7+pMove] == '_') {
                lst[i*7+pMove] = 'O';
                break;
            }
        }

        maxSteps++;
        board->setPos(lst);
        board->display();
        if (board->win('O')) {
            cout << endl << "------------------------ You won ----------------------" << endl;
            return 1;
        }

    }

    return 0;
}
