#include <iostream>
#include <string.h>
#include <cstdlib>
#include <utility>
#include<iomanip>
using namespace std;

int board[4][4], score = 0;
int dirLine[] = {1, 0, -1, 0};
int dirCol[] = {0, 1, 0, -1};

pair<int, int> randPos() {
    int line, col, obs = 1;
    while(obs) {
        line = rand() % 4;
        col = rand() % 4;
        if(board[line][col] == 0) {
            obs = 0;
        }
    }
    return make_pair(line, col);
}
/*function which returns a random position in order to
generate another 2*/

void printStart() {
    system("cls");
    int i, j;
    for(i = 0 ; i < 4; i++) {
        for(j = 0 ; j < 4; j++) {
            if(board[i][j] == 0) {
                cout << setw(4) << ".";
            } else {
                cout << setw(4) << board[i][j];
            }
        }
        cout << endl;
    }
    cout << "n -> new game" << endl;
    cout << "q -> exit" << endl;
    cout << "w -> up" << endl;
    cout << "s -> down" << endl;
    cout << "a -> left" << endl;
    cout << "d -> right" << endl;
    cout << "SCORE : " << score << endl;
}
/*function for setup and instructions*/

bool canDoMove(int i, int j, int inou, int jnou) {
    if(inou < 0 || inou >= 4 || jnou < 0 || jnou >=4 || board[i][j] != board[inou][jnou] && board[inou][jnou] != 0) {
        return false;
    }
    return true;
}
/*verifying whether a move can be done or not*/

void add() {
    pair<int, int> pos = randPos();
    board[pos.first][pos.second] = 2;
}
/*adding the random 2 in the board*/

void Move(int dir) {
    int moves = 0, canmoves = 0;
    int startLine = 0, startCol = 0, stepL = 1, stepC = 1, i, j, inou, jnou;
    if(dir == 0) {
       startLine = 3;
       stepL = -1;
    }
    if(dir == 1) {
        startCol = 3;
        stepC = -1;
    }

    do {
        moves = 0;
        for(i = startLine; i >= 0 && i < 4; i = i + stepL) {
            for(j = startCol; j >= 0 && j < 4; j = j + stepC) {
                inou = i + dirLine[dir];
                jnou = j + dirCol[dir];
                if(canDoMove(i, j , inou, jnou) && board[i][j]) {
                    board[inou][jnou] = board[inou][jnou] + board[i][j];
                    if(board[inou][jnou] == 2048) {
                        cout << "Congratulations, you won!";
                        system("cls");
                    }
                    if(board[i][j] != board[inou][jnou]) {
                        score = score + board[inou][jnou];
                    }
                    board[i][j] = 0;
                    moves = 1;
                    canmoves = 1;
                }
            }
        }
        printStart();
    } while(moves);

    if(canmoves) {
        add();
    } else {
        cout << "Game over!";
        system("cls");
    }
}
/*moving all numbers in the matrix according to the input*/

void newGame() {
    int i, j;
    for( i = 0; i < 4; i++) {
        for(j = 0 ; j < 4; j++) {
            board[i][j] = 0;
        }
    }
    add();
}

int main()
{
    char inptoDir[200];
    inptoDir['s'] = 0;
    inptoDir['d'] = 1;
    inptoDir['w'] = 2;
    inptoDir['a'] = 3;
    char inp;
    newGame();
    while(true) {
        printStart();
        cout << "Input command is:";
        cin >> inp;
        if(inp == 'n') {
            newGame();
            score = 0;
        } else {
            if(inp == 'q') {
                break;
            } else {
                int currDir = inptoDir[inp];
                Move(currDir);
            }
        }
    }
    return 0;
}
