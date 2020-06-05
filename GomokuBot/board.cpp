//
//  board.cpp
//  GomokuBot
//
//  Created by Tran Hoang Long on 6/1/20.
//  Copyright © 2020 Tran Hoang Long. All rights reserved.
//

#include "board.hpp"
#include "iostream"
#include "time.h"
#include "stdlib.h"
#include "vector"
#define Min(a,b) ((a) < (b) ? (a) : (b))
#define Max(a,b) ((a) > (b) ? (a) : (b))
#define pathFunc(x, y) (x*m + y + 1)
using namespace std;
Board::Board()
{
    n = 3;
    m = 3;
    _Board = new char*[n];
    for (int i = 0; i < n; i++)
        _Board[i] = new char[m];
    init();
}

int Board::getn() const
{
    return n;
}

int Board::getm() const
{
    return m;
}

char** Board::getBoard() const
{
    return _Board;
}

char Board::value(int i, int j) const
{
    return _Board[i][j];
}

char Board::getplayer() const
{
    return player;
}

char Board::getAI() const
{
    return AI;
}

void Board::init()
{
    // Initialize board with empty
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            _Board[i][j] = '_';

}

void Board::makemove(int i, int j, int color)
{
    // Make a move on game board
    char c = ' ';
    switch (color)
    {
        case 0: c = '_'; break;
        case 1: c = 'O'; break;
        case 2: c = 'X'; break;
    }
    _Board[i][j] = c;
    
    // Storing moves played in the game
    Piece p(Move(i,j), c);
    move.push_back(p);
}
void Board::printBoard() const
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            cout << _Board[i][j];
        cout << endl;
    }
}
int powerOf3(int exp, int moduloR)
{
    if (exp <= 0) return 1;
    if (exp == 1) return 3;
    int tmp = powerOf3(exp >> 1, moduloR);
    tmp = 1LL * tmp * tmp % moduloR;
    return (exp & 1) ? (1LL * tmp * 3 % moduloR) : tmp;
}
int Board::getHash(const int moduloR = 1000000007) const
{
    // find first existing position
    int min_i = INT_MAX, min_j = INT_MAX,
        max_i = INT_MIN, max_j = INT_MIN;
    
    //
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (_Board[i][j] != 0)
            {
                min_i = Min(min_i, i);
                min_j = Min(min_j, j);
                max_i = Max(max_i, i);
                max_j = Max(max_j, j);
            }
        
    int hashC = 0;
    for (int i = min_i; i <= max_i; i++)
        for (int j = min_j; j <= max_j; j++)
            hashC = (1LL * (_Board[i][j] + 1) * powerOf3(pathFunc(i - min_i, j - min_j), moduloR) + hashC) % moduloR;
    return hashC;
    
}

bool Board::empty(int i, int j) const
{
    return _Board[i][j] == '_';
}

int Board::win() const
{
    // CHECK IF X OR O IS 5 IN A ROW
    int count;
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= m-5; j++)
        {
            count = 0;
            for (int k = 0; k < 5; k++)
            {
                if (_Board[i][j+k] == 'O') count++;
                else if (_Board[i][j+k] == 'X') count--;
            }
            if (count >=5) return 10;
            if (count <=-5) return -10;
        }
    // CHECK IF X OR O IS 5 IN A COLUMN
    
    for (int i = 0; i <= n-5; i++)
        for (int j = 0; j < m; j++)
        {
            int count = 0;
            for (int k = 0; k < 5; k++)
            {
                if (_Board[i+k][j] == 'O') count++;
                else if (_Board[i+k][j] == 'X') count--;
            }
            if (count >=5) return 10;
            if (count <=-5) return -10;
        }
    
    // CHECK IF X OR O IS 5 IN MAIN DIAGONAL
    
    for (int i = 0; i <= n-5; i++)
        for (int j = 0; j <= m-5; j++)
        {
            int count = 0;
            for (int k = 0; k < 5; k++)
            {
                if (_Board[i+k][j+k] == 'O') count++;
                else if (_Board[i+k][j+k] == 'X') count--;
            }
            if (count >=5) return 10;
            if (count <=-5) return -10;
        }
            
    // CHECK IF X OR O IS 5 IN SUB DIAGONAL
    
    for (int i = 0; i <= n-5; i++)
        for (int j = 4; j < m; j++)
        {
            int count = 0;
            for (int k = 0; k < 5; k++)
            {
                if (_Board[i+k][j-k] == 'O') count++;
                else if (_Board[i+k][j-k] == 'X') count--;
            }
            if (count >=5) return 10;
            if (count <=-5) return -10;
        }
    
    return 0;

}

bool Board::inBoard(int x, int y) const
{
    return (x >= 0 && x < n && y >= 0 && y < m);
}

bool Board::isMoveLeft() const
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (_Board[i][j] == '_') return true;
    return false;
}

std::vector<Move> Board::getPossibleMoves() const
{
    
    bool yes[n][m];
    std::vector<Move> res;
    
    // Initialize mark array
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            yes[i][j] = false;
    
    // Generate moves based on moves played in game
    for (Piece p : this->move)
    {
        int x = p.getpos().getI();
        int y = p.getpos().getJ();
        for (int i = -1; i <= 1; i++)
            for (int j = -1; j <= 1; j++)
            {
                int dimX = x + i;
                int dimY = y + j;
                if (inBoard(dimX,dimY) && _Board[dimX][dimY] == '_')
                    yes[dimX][dimY] = true;
            }
    }
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (yes[i][j])
            {
                res.push_back(Move(i,j));
            }
    
    return res;
}

std::vector<Piece> Board::getMoveList() const
{
    return move;
}
