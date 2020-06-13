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
#include <map>
#include <utility>
#include <array>
#include "board.hpp"
#include "move.hpp"
#include "piece.hpp"
#include "giveScore.hpp"
#include "hashTable.hpp"

#define maxdepth 3

struct TreeMoves
{
    Move _move;
    int depth;
    char player;
};

class Evaluator
{
private:
    Board _Board;
    int cnt;
    time_t t_start;
    std::map<unsigned long long, std::array<TreeMoves, maxdepth>> table;

public:
    Evaluator();
    
    void updateBoard(Board board);
    void updateStartTime();
    int minimax(int depth, bool isMaxing, int alpha, int beta, std::array<TreeMoves, maxdepth>& sequence, int& count_seq);
    int maxing(int depth, bool isMaxing, int alpha, int beta, std::array<TreeMoves, maxdepth>& sequence, int& count_seq);
    int minizing(int depth, bool isMaxing, int alpha, int beta, std::array<TreeMoves, maxdepth>& sequence, int& count_seq);
    Move findBestMove();
    
    bool isCutOff(int depth, int AI, int human) const;
    int evaluateStateScore(int AI, int human) const;
    int checkwinner() const;
    std::vector<Piece> getMoveList() const;
    std::vector<Move> getPossibleMoves() const;
    std::array<TreeMoves, maxdepth> getTree(unsigned long long hash);
    int getcnt() const
    {
        return cnt;
    };
};
#endif /* evaluator_hpp */
