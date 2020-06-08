//
//  evaluator.cpp
//  GomokuBot
//
//  Created by Tran Hoang Long on 6/3/20.
//  Copyright © 2020 Tran Hoang Long. All rights reserved.
//

#include "evaluator.hpp"
#include "string"
#include "iostream"
#include "algorithm"
#include "chrono"

Evaluator::Evaluator()
{
    cnt = 0;
    currentHash = 0;
}

void Evaluator::updateBoard(Board board)
{
    _Board = board;
}

void Evaluator::updateStartTime(time_t time)
{
    t_start = time;
}

Move Evaluator::findBestMove()
{
    // search for next good move for AI
    int bestVal = -1000;
    Move bestMove;
    bestMove.setI(-1);
    bestMove.setJ(-1);
    
    std::vector<Move> moveArray = _Board.getPossibleMoves();
    
    for (Move m : moveArray)
    {
        if (_Board.empty(m.getI(), m.getJ()))
        {
            // Make move at i j
            _Board.makemove(m.getI(), m.getJ(), 1);
            
            // Find value of this move
            int moveVal = minimax(0, false, -1000, 1000);
            //std::cout << moveVal << std::endl;
            
            // Remove move
            _Board.makemove(m.getI(), m.getJ(), 0);
            
            //Update bestVal & bestMove
            if (moveVal > bestVal)
            {
                bestMove.setI(m.getI());
                bestMove.setJ(m.getJ());
                bestVal = moveVal;
            }
        }
    }
    
    return bestMove;
}
int Evaluator::evaluateStateScore(int AI, int human) const
{
    if (_Board.getplayer() == 'X')
        human*=2;
    else AI*=2;
    return (AI-human);
}

bool Evaluator::isCutOff(int depth, int AI, int human) const
{
    time_t end;
    time(&end);
    
    if ((double) (end-t_start) >= 5)
        return true;
    
    if (depth == 2)
        return true;
    if (!_Board.isMoveLeft())
        return true;
    if (AI >= 1000 || human >= 1000)
            return true;
    return false;
}

int Evaluator::minimax(int depth, bool isMaxing, int alpha, int beta)
{

    int AI = GiveScore(_Board, 1).GiveTotalScore();
    int human = GiveScore(_Board, 2).GiveTotalScore();

    //std::cout << AI << " " << human << " " << std::endl;
    
    if (isCutOff(depth, AI, human))
        return evaluateStateScore(AI, human);
    
    if (isMaxing)
        return maxing(depth, isMaxing, alpha, beta);
    else
        return minizing(depth, isMaxing, alpha, beta);
    
}


int Evaluator::maxing(int depth, bool isMaxing, int alpha, int beta)
{
    int bestVal = -1000;
    
    // Moves to consider to take in this game state
    std::vector<Move> moveArray = _Board.getPossibleMoves();
    
    for (Move m : moveArray)
    {
        cnt++;
        if ((_Board.value(m.getI(), m.getJ())) == '_')
            {
                // Make a move at m.i & m.j
                _Board.makemove(m.getI(), m.getJ(), 1);
                
                bestVal = std::max(bestVal,minimax(depth+1, false, alpha, beta));
                alpha = std::max(alpha, bestVal);
                
                // Remove that move
                _Board.makemove(m.getI(), m.getJ(), 0);
                
                // alpha beta pruning
                if (beta <= alpha)
                    return bestVal;
            }
    }
    return bestVal;
}

int Evaluator::minizing(int depth, bool isMaxing, int alpha, int beta)
{
    int bestVal = 1000;
    
    // Moves to consider to take in this game state
    std::vector<Move> moveArray = _Board.getPossibleMoves();

    for (Move m : moveArray)
    {
        cnt++;
        if (_Board.value(m.getI(), m.getJ()) == '_')
        {
            // Make a move at m.i & m.j
            _Board.makemove(m.getI(), m.getJ(), 2);

            bestVal = std::min(bestVal,minimax(depth+1, true, alpha, beta));
            beta = std::min(beta,bestVal);
            
            // Remove the move
            _Board.makemove(m.getI(), m.getJ(), 0);
            
            // Alpha beta pruning
            if (beta <= alpha)
                return bestVal;
        }
    }
    return bestVal;

}


bool equals3(char a,char b,char c) {
  return a == b && b == c && a != '_';
}

// Checker for 3x3 board

int Evaluator::checkwinner() const
{

   // Win conditions for tic tac toe (3x3)

  // horizontal
  for (int i = 0; i < 3; i++) {
      if (equals3(_Board.value(i, 0), _Board.value(i, 1), _Board.value(i, 2))) {
          if (_Board.value(i, 0) == _Board.getplayer()) return -10;
          if (_Board.value(i, 0) == _Board.getAI()) return 10;
    }
  }

  // Vertical
  for (int i = 0; i < 3; i++) {
      if (equals3(_Board.value(0, i), _Board.value(1, i), _Board.value(2, i))) {
          if (_Board.value(0, i) == _Board.getplayer()) return -10;
          if (_Board.value(0, i) == _Board.getAI()) return 10;
    }
  }

  // Diagonal
    if (equals3(_Board.value(0, 0), _Board.value(1, 1), _Board.value(2, 2))) {
        if (_Board.value(0, 0) == _Board.getplayer()) return -10;
        if (_Board.value(0, 0) == _Board.getAI()) return 10;
  }
    if (equals3(_Board.value(2, 0), _Board.value(1, 1), _Board.value(0, 2))) {
        if (_Board.value(2, 0) == _Board.getplayer()) return -10;
        if (_Board.value(2, 0) == _Board.getAI()) return 10;
  }
    return 0;
}




std::vector<Piece> Evaluator::getMoveList() const
{
    return _Board.getMoveList();
}

std::vector<Move> Evaluator::getPossibleMoves() const
{
    return _Board.getPossibleMoves();
}
