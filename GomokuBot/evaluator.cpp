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
//void increase(std::string& pattern)
//{
//    int n = 0;
//    int carry = 0;
//    for (int i = (int) pattern.size() - 1; i >= 0; i--)
//    {
//        int tmp = pattern[i] - '0';
//        tmp += 1 + carry;
//        carry = 0;
//        if (tmp>2) {
//            carry = 1;
//            tmp = 0;
//        }
//        n = n * 10 + tmp;
//        
//    }
//    if (carry == 1) n = n * 10 + carry;
//    
//    pattern = std::to_string(n);
//    reverse(pattern.begin(), pattern.end());
//}
//
//int give_score(std::string pattern)
//{
//    int count = 0;
//    int maxScore = INT_MIN;
//    for (int i = 0; i < pattern.size(); i++)
//    {
//        // check so dau O lien tiep
//        if (pattern[i] == '1')
//        {
//            count++;
//            if (count == 1) maxScore = std::max(maxScore, 5);
//            if (count == 2) maxScore = std::max(maxScore, 10);
//            if (count == 3) maxScore = std::max(maxScore, 20);
//            if (count == 4) maxScore = std::max(maxScore, 50);
//            if (count >= 5) maxScore = std::max(maxScore, 1000);
//        }
//        else count = 0;
//    }
//    return maxScore;
//}

Evaluator::Evaluator(Board board)
{
    
    //Get board value
    _Board = board;
    // Initialize pattern score
//    string pattern = "0";
//    while (pattern <= "222222222")
//    {
//        int score = give_score(pattern);
//        int pattern_int = stoi(pattern);
//        pattern_score.insert(std::pair<int, int>(pattern_int ,score));
//        increase(pattern);
//    }
}

Move Evaluator::findBestMove()
{
    // search for next good move for AI
    int bestVal = -1000;
    Move bestMove;
    bestMove.setI(-1);
    bestMove.setJ(-1);
    for (int i = 0; i < _Board.getn(); i++)
        for (int j = 0; j < _Board.getm(); j++)
        {
            if (_Board.empty(i, j))
            {
                _Board.makemove(i, j, 1);
                int moveVal = minimax(0, false, -1000, 1000);
                //std::cout << moveVal << std::endl;
                _Board.makemove(i, j, 0);
                if (moveVal > bestVal)
                {
                    bestMove.setI(i);
                    bestMove.setJ(j);
                    bestVal = moveVal;
                }
            }
        }
    return bestMove;
}
int Evaluator::maxing(int depth, bool isMaxing, int alpha, int beta)
{
    int bestVal = -1000;
    
    // Moves to consider to take in this game state
    std::vector<Move> moveArray = _Board.getPossibleMoves();
    
    
    for (Move m: moveArray)
    {
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
                {
                    break;
                }
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
            {
                break;
            }
        }
    }
    return bestVal;

}

bool equals3(char a,char b,char c) {
  return a == b && b == c && a != '_';
}

//int Evaluator::evaluateScore() const
//{
//
//}

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
int Evaluator::minimax(int depth, bool isMaxing, int alpha, int beta)
{
    
    // get this game state score
    int score = checkwinner();
    
    // if maximizer of minimizer win the game
    if (score == 10 || score == -10)
        return score;
    
    // return 0 if there is no move left
    if (!_Board.isMoveLeft() || depth == 5) return 0;
    
    if (isMaxing)
    {
        return maxing(depth, isMaxing, alpha, beta);
    }
    else
    {
        return minizing(depth, isMaxing, alpha, beta);
    }
    
}

std::vector<Piece> Evaluator::getMoveList() const
{
    return _Board.getMoveList();
}

std::vector<Move> Evaluator::getPossibleMoves() const
{
    return _Board.getPossibleMoves();
}
