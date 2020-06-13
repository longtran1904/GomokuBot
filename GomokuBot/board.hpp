//
//  board.hpp
//  GomokuBot
//
//  Created by Tran Hoang Long on 6/1/20.
//  Copyright © 2020 Tran Hoang Long. All rights reserved.
//

#ifndef board_hpp
#define board_hpp
#include <stdio.h>
#include "vector"
#include "map"
#include "move.hpp"
#include "piece.hpp"
//class Tree{
//private:
//    std::vector<info> ListMove;
//
//public:
//    Tree();
//    void push_back(int _score, int hash, Move move);
//    Move GetNextMove() const;
//    int GetHash() const;
//};
//
//
//class Table
//{
//private:
//    std::map<int, Tree> _map;
//public:
//    Table();
//    void add_route();
//    int get_hash(int i, int j) const;
//
//};

#include "hashTable.hpp"

class Board
{
protected:
    int n,m;
    char** _Board;
    std::vector<Piece> move;
    HashTable currentState;
//    Player currentPlayer;
    char player = 'X';
    char AI = 'O';
    
public:
    Board();
    void init();
    void makemove(int i, int j, int color);
    void printBoard() const;
    bool empty(int i, int j) const;
    unsigned long long getHash() const;
    int win() const;
    void next_move() const;
    bool isMoveLeft() const;
    char value(int i, int j) const;
    char getplayer() const;
    char getAI() const;
    char** getBoard() const;
    int getn() const;
    int getm() const;
    bool inBoard(int x, int y) const;
    std::vector<Move> getPossibleMoves() const;
    std::vector<Piece> getMoveList() const;
    int** getBoardInt() const;
    
    
};



#endif /* board_hpp */

