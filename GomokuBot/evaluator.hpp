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

class Evaluator
{
private:
    std::map<int, int> pattern_score;
    Board _Board;
//    Table _table;
public:
    Evaluator(Board board);
    //void setBoard(Board board);
    int minimax(int depth, bool isMaxing, int alpha, int beta);
    int maxing(int depth, bool isMaxing, int alpha, int beta);
    int minizing(int depth, bool isMaxing, int alpha, int beta);
    Move findBestMove();
    int evaluateScore() const;
    int checkwinner() const;
    std::vector<Piece> getMoveList() const;
    std::vector<Move> getPossibleMoves() const;
};
#endif /* evaluator_hpp */
