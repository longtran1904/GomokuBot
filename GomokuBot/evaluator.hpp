//
//  evaluator.hpp
//  GomokuBot
//
//  Created by Tran Hoang Long on 6/3/20.
//  Copyright © 2020 Tran Hoang Long. All rights reserved.
//

#ifndef evaluator_hpp
#define evaluator_hpp

#include <stdio.h>
#include "board.hpp"
#include "move.hpp"
#include "piece.hpp"
#include "giveScore.hpp"
#include "hashTable.hpp"
class Evaluator
{
private:
    Board _Board;
    int cnt;
    time_t t_start;
    HashTable table;
    unsigned long long currentHash;
//    Table _table;
public:
    Evaluator();
    
    void updateBoard(Board board);
    void updateStartTime(time_t time);
    int minimax(int depth, bool isMaxing, int alpha, int beta);
    int maxing(int depth, bool isMaxing, int alpha, int beta);
    int minizing(int depth, bool isMaxing, int alpha, int beta);
    Move findBestMove();
    
    bool isCutOff(int depth, int AI, int human) const;
    int evaluateStateScore(int AI, int human) const;
    int checkwinner() const;
    std::vector<Piece> getMoveList() const;
    std::vector<Move> getPossibleMoves() const;
    int getcnt() const
    {
        return cnt;
    };
};
#endif /* evaluator_hpp */
