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
#include<map>


Evaluator::Evaluator()
{
    cnt = 0;
}

void Evaluator::updateBoard(Board board)
{
    _Board = board;
    updateStartTime();
}

void Evaluator::updateStartTime()
{
    time_t start;
    time(&start);
    t_start = start;
}

Move Evaluator::findBestMove()
{
    // search for next good move for AI
    int bestVal = -1000;
    Move bestMove;
    bestMove.setI(-1);
    bestMove.setJ(-1);
    
    std::vector<Move> moveArray = _Board.getPossibleMoves();
    
    std::array<TreeMoves, maxdepth> sequence;
    int count_seq = 0;
    
    for (Move m : moveArray)
    {
        if (_Board.empty(m.getI(), m.getJ()))
        {
            // Make move at i j
            _Board.makemove(m.getI(), m.getJ(), 1);
            
            std::array<TreeMoves, maxdepth> subsequence;
            int count_sub = 0;
            // Find value of this move
            int moveVal = minimax(1, false, -1000, 1000, subsequence, count_sub);
            
            // Get TreeMoves value
            TreeMoves tree;
            tree._move = m;
            tree.depth = 0;
            tree.player = 'O';
                        
            //Transfer value from sub to sequence
            count_seq = count_sub;
//            for (int i = 0; i < count_seq; i++)
//                sequence[i] = subsequence[i];
//            sequence[++count_seq] = tree;
            
            // Store TreeMoves from minimax to table
            //table.insert(std::pair<unsigned long long, TreeMoves[]>(_Board.getHash(), sequence));
            table[_Board.getHash()] = sequence;
            
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
//        std::vector<TreeMoves> vec = getTree(_Board.getHash());
//        std::cout << vec.size() << std::endl;
//        for (int i = 0; i < vec.size(); i++)
//        {
//            std::cout << vec[i]._move.getI() << " ";
//        }
//        std::cout << std::endl;
//        for (int i = 0; i < vec.size(); i++)
//        {
//            std::cout << vec[i]._move.getJ() << " ";
//        }
//        std::cout << std::endl;
//        for (int i = 0; i < vec.size(); i++)
//        {
//            std::cout << vec[i].depth << " ";
//        }
//        std::cout << std::endl;
//        for (int i = 0; i < vec.size(); i++)
//        {
//            std::cout << vec[i].player << " ";
//        }
//        std::cout << std::endl;
        count_seq = 0;
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
    
    if (depth == 3)
        return true;
    if (!_Board.isMoveLeft())
        return true;
    if (AI >= 1000 || human >= 1000)
            return true;
    return false;
}

int Evaluator::minimax(int depth, bool isMaxing, int alpha, int beta, std::array<TreeMoves, maxdepth>& sequence, int& count_seq)
{

    int AI = GiveScore(_Board, 1).GiveTotalScore();
    int human = GiveScore(_Board, 2).GiveTotalScore();

    //std::cout << AI << " " << human << " " << std::endl;
    
    if (isCutOff(depth, AI, human))
        return evaluateStateScore(AI, human);
    
    if (isMaxing)
        return maxing(depth, isMaxing, alpha, beta, sequence, count_seq);
    else
        return minizing(depth, isMaxing, alpha, beta, sequence, count_seq);
    
}


int Evaluator::maxing(int depth, bool isMaxing, int alpha, int beta, std::array<TreeMoves, maxdepth>& sequence, int& count_seq)
{
    int bestVal = -1000;
    Move bestMove;
    bestMove.setI(-1);
    bestMove.setJ(-1);

    
    
    // Moves to consider to take in this game state
    std::vector<Move> moveArray = _Board.getPossibleMoves();

    for (Move m : moveArray)
    {
        cnt++;
        if ((_Board.value(m.getI(), m.getJ())) == '_')
            {
                
                // Make a move at m.i & m.j
                _Board.makemove(m.getI(), m.getJ(), 1);

                std::array<TreeMoves, maxdepth> subsequence;
                
                int count_sub = 0;
                
                int evaluate = minimax(depth+1, false, alpha, beta, subsequence, count_sub);
                
                if (bestVal < evaluate)
                {
                    bestVal = evaluate;
                    bestMove = m;
                    // update sequence to be subquence of better moves
                    count_seq = count_sub;
//                    for (int i = 0; i < count_sub; i++)
//                        sequence[i] = subsequence[i];
                }
                
                alpha = std::max(alpha, bestVal);
                
                // Remove that move
                _Board.makemove(m.getI(), m.getJ(), 0);
                
                // alpha beta pruning
                if (beta <= alpha)
                {
//                    // insert bestmove to sequence
//
//                    TreeMoves tree;
//                    tree._move = bestMove;
//                    tree.depth = depth;
//                    tree.player = 'O';
//
//                    sequence.push_back(tree);

                    return bestVal;
                }
            }
    }
    
    // insert bestmove to sequence
    
    TreeMoves tree;
    tree._move = bestMove;
    tree.depth = depth;
    tree.player = 'O';
    
    sequence[++count_seq] = tree;

    return bestVal;
}

int Evaluator::minizing(int depth, bool isMaxing, int alpha, int beta, std::array<TreeMoves, maxdepth>& sequence, int& count_seq)
{
    int bestVal = 1000;
    Move bestMove;
    bestMove.setI(-1);
    bestMove.setJ(-1);
    
    // Moves to consider to take in this game state
    std::vector<Move> moveArray = _Board.getPossibleMoves();
    
    for (Move m : moveArray)
    {
        cnt++;
        if (_Board.value(m.getI(), m.getJ()) == '_')
        {
            
            // Make a move at m.i & m.j
            _Board.makemove(m.getI(), m.getJ(), 2);
            
            std::array<TreeMoves, maxdepth> subsequence;
            int count_sub = 0;
            
            int evaluate = minimax(depth+1, true, alpha, beta, subsequence, count_sub);
            
            if (bestVal > evaluate)
            {
                bestVal = evaluate;
                bestMove = m;
                // assign sequence to be subsequence of better moves
                count_seq = count_sub;
//                for (int i = 0; i < count_sub; i++)
//                    sequence[i] = subsequence[i];
            }
            
            beta = std::min(beta,bestVal);
            
            // Remove the move
            _Board.makemove(m.getI(), m.getJ(), 0);
            
            // Alpha beta pruning
            if (beta <= alpha)
            {
                // insert bestmove to sequence
                
//                if (bestMove.getI() != -1 && bestMove.getJ() != -1)
//                {
//                    TreeMoves tree;
//                    tree._move = bestMove;
//                    tree.depth = depth;
//                    tree.player = 'O';
//
//                    sequence.push_back(tree);
//                }
                return bestVal;
            }
        }
    }
    
    // insert move to sequence
    if (bestMove.getI() != -1 && bestMove.getJ() != -1)
    {
        TreeMoves tree;
        tree._move = bestMove;
        tree.depth = depth;
        tree.player = 'X';
        
        sequence[++count_seq] = tree;
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

std::array<TreeMoves, maxdepth> Evaluator::getTree(unsigned long long hash)
{
    std::array<TreeMoves, maxdepth> empty;
    std::map<unsigned long long, std::array<TreeMoves, maxdepth>>::iterator it;
    it = table.find(hash);
    if (it != table.end())
        return it->second;
    return empty;
    
}


std::vector<Piece> Evaluator::getMoveList() const
{
    return _Board.getMoveList();
}

std::vector<Move> Evaluator::getPossibleMoves() const
{
    return _Board.getPossibleMoves();
}
