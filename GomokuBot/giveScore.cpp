//
//  giveScore.cpp
//  GomokuBot
//
//  Created by Tran Hoang Long on 6/4/20.
//  Copyright © 2020 Tran Hoang Long. All rights reserved.
//

#include "giveScore.hpp"
#include "iostream"
GiveScore::GiveScore(Board _board, int p)
{
    n = _board.getn();
    m = _board.getm();

    player = p-1;
    
    

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            HashColumn[i][j] = 0;
            HashRow[i][j] = 0;
        }
    
    for (int i = 0; i < 38; i++)
        for (int j = 0; j < 10; j++)
        {
            HashDiagonal[i][j] = 0;
        }
    
    Five = 0;
    StraightFour = 0;
    Four = 0;
    Three = 0;
    ThreeBounded = 0;
    BrokenThree = 0;
    Two = 0;
    TwoBounded = 0;
    isHaveThreat = false;
    
    diagonal_count = 0;
    
    SetHashBoard(_board);

}

void GiveScore::SetHashBoard(Board _board)
{
    board = _board.getBoardInt();
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            if (j == 0) HashRow[i][j] = board[i][0];
            else HashRow[i][j] = HashRow[i][j-1] * 3 + board[i][j];
            
            if (j == 0) HashColumn[i][j] = board[j][i];
            else HashColumn[i][j] = HashColumn[i][j-1] * 3 + board[j][i];
        }
    
    // Hash for diagonals

    // hash for half bottom main diagonals of the board
    for (int i = 0; i < n; i++)
    {
        HashDiagonal[diagonal_count][0] = board[i][0];
        for (int j = 1; j < m - i; j++)
        {
            HashDiagonal[diagonal_count][j] = HashDiagonal[diagonal_count][j-1] * 3 + board[i+j][j];
        }
        diagonal_count++;
    }
    
    // hash for half upper main diagonals of the board
    for (int j = 1; j < m; j++)
    {
        HashDiagonal[diagonal_count][0] = board[0][j];
        for (int i = 1; i < n - j; i++)
        {
            HashDiagonal[diagonal_count][i] = HashDiagonal[diagonal_count][i-1] * 3 + board[i][i+j];
        }
        diagonal_count++;
    }
    
    // hash for half bottom sub diagonals of the board
    for (int i = 0; i < n; i++)
    {
        HashDiagonal[diagonal_count][0] = board[i][m - 1];
        for (int j = 1; j < m - i; j++)
        {
            HashDiagonal[diagonal_count][j] = HashDiagonal[diagonal_count][j-1] * 3 + board[i+j][n - 1 - j];
        }
        diagonal_count++;
    }
    
    // hash for half upper sub diagonals of the board
    for (int j = 1; j < m; j++)
    {
        HashDiagonal[diagonal_count][0] = board[0][m - 1 - j];
        for (int i = 1; i < n - j; i++)
        {
            HashDiagonal[diagonal_count][i] = HashDiagonal[diagonal_count][i-1] * 3 + board[i][n - 1 - j - i];
        }
        diagonal_count++;
    }
    
}
void GiveScore::CheckForTwo(int value, int index)
{
    if (value == TwoValueBounded1[index] || value == TwoValueBounded2[index])
    {
        TwoBounded++;
        setHaveThreat(true);
    }
    
    if (value == TwoValue[index])
    {
        Two++;
        setHaveThreat(true);
    }

}

void GiveScore::CheckForFiveThree(int value, int index)
{
    if (value == FiveValue[index])
    {
        Five++;
        setHaveThreat(true);
    }
    
    if (value == ThreeValueBounded1[index] || value == ThreeValueBounded2[index])
    {
        ThreeBounded++;
        setHaveThreat(true);
    }
    
    if (value == ThreeValue[index])
    {
        Three++;
        setHaveThreat(true);
    }

}

void GiveScore::CheckForFourBrokenThree(int value, int index)
{
    if (value == StraighFourValue[index])
    {
        StraightFour++;
        setHaveThreat(true);
    }
    if (value == FourValueBounded1[index] || value == FourValueBounded2[index])
    {
        Four++;
        setHaveThreat(true);
    }
    if (value == BrokenThreeValue1[index] || value == BrokenThreeValue2[index])
    {
        BrokenThree++;
        setHaveThreat(true);
    }
}
    

    
void GiveScore::ExamineRowColumn(int hash[20][20])
{
    int val;
    setHaveThreat(false);
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m - 4; j++)
        {
            val = (j == 0) ? hash[i][j+4] : hash[i][j+4] - hash[i][j-1] * POW[5];
            CheckForFiveThree(val, player);
            if (isThreat()) break;
        }
        
        if (isThreat()) continue;
        
        for (int j = 0; j < m - 5; j++)
        {
            val = (j==0) ? hash[i][j+5] : hash[i][j+5] - hash[i][j-1] * POW[6];
            CheckForFourBrokenThree(val, player);
            if (isThreat()) break;
        }
        
        if (isThreat()) continue;
        
        for (int j = 0; j < m - 3; j++)
        {
            val = (j==0) ? hash[i][j+3] : hash[i][j+3] - hash[i][j-1] * POW[4];
            CheckForTwo(val, player);
            if (isThreat()) break;
        }
    }
    
    
}

void GiveScore::ExamineDiagonal(int first, int last)
{
    int val;
    int cnt = 0;
    setHaveThreat(false);
    
    for (int i = first; i < last; i++)
    {
        // No moves played on this direction
        if (HashDiagonal[i][n-cnt-1] == 0
            && HashDiagonal[i][n-cnt-2] == 0) continue;
        
        
        for (int j = 0; j < n - cnt - 4; j++)
        {
            val = (j==0) ? HashDiagonal[i][j+4] : HashDiagonal[i][j+4] - HashDiagonal[i][j-1] * POW[5];
            CheckForFiveThree(val, player);
            if (isThreat()) break;
            //std::cout << hash[i][j] << " ";
        }
        //std::cout << std::endl;
        
        if (isThreat()) continue;
        
        for (int j = 0; j < n - cnt - 5; j++)
        {
            val = (j==0) ? HashDiagonal[i][j+5] : HashDiagonal[i][j+5] - HashDiagonal[i][j-1] * POW[6];
            CheckForFourBrokenThree(val, player);
            if (isThreat()) break;
        }
        
        if (isThreat()) continue;
            
        for (int j = 0; j < n - cnt - 3; j++)
        {
            val = (j==0) ? HashDiagonal[i][j+3] : HashDiagonal[i][j+3] - HashDiagonal[i][j-1]*POW[4];
            CheckForTwo(val, player);
            if (isThreat()) break;
        }
        cnt++;
    }
}

int GiveScore::GiveTotalScore()
{
    ExamineRowColumn(HashRow);
    ExamineRowColumn(HashColumn);

//    int cnt = 0;
//    for (int i = 0; i < 10; i++)
//    {
//        for (int j = 0; j < m - cnt; j++)
//            std::cout << HashDiagonal[i][j] << " ";
//        cnt++;
//        std::cout << std::endl;
//    }
//    cnt = 0;
//    for (int i = 10; i < 19; i++)
//    {
//        for (int j = 0; j < m - cnt; j++)
//            std::cout << HashDiagonal[i][j] << " ";
//        cnt++;
//        std::cout << std::endl;
//    }
//    cnt = 0;
//    for (int i = 19; i < 29; i++)
//    {
//        for (int j = 0; j < m - cnt; j++)
//            std::cout << HashDiagonal[i][j] << " ";
//        cnt++;
//        std::cout << std::endl;
//    }
//    cnt = 0;
//    for (int i = 29; i < 38; i++)
//    {
//        for (int j = 0; j < m - cnt; j++)
//            std::cout << HashDiagonal[i][j] << " ";
//        cnt++;
//        std::cout << std::endl;
//    }
//
    ExamineDiagonal(0, 10);
    ExamineDiagonal(10, 19);
    ExamineDiagonal(19, 29);
    ExamineDiagonal(29, 38);
    int score = 0;
//    std::cout << "Five: " << Five << std::endl;
//    std::cout << "StraightFour: " << StraightFour << std::endl;
//    std::cout << "Four " << Four << std::endl;
//    std::cout << "Three: " << Three << std::endl;
//    std::cout << "ThreeBounded: " << ThreeBounded << std::endl;
    
    
    
    score = Five * weight[0] + StraightFour * weight[1] + Four * weight[2] + Three * weight[3] + ThreeBounded * weight[4] + BrokenThree * weight[5] + Two * weight[6] + TwoBounded * weight[7];
    return score;
    
}

bool GiveScore::isThreat() const
{
    return isHaveThreat;
}

void GiveScore::setHaveThreat(bool threat)
{
    isHaveThreat = threat;
}
