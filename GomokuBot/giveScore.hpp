//
//  giveScore.hpp
//  GomokuBot
//
//  Created by Tran Hoang Long on 6/4/20.
//  Copyright © 2020 Tran Hoang Long. All rights reserved.
//

#ifndef giveScore_hpp
#define giveScore_hpp

#include <stdio.h>

#include "board.hpp"
class GiveScore
{
private:
    int n;
    int m;
    int** board;
    int HashRow[20][20];
    int HashColumn[20][20];
    int HashDiagonal[80][20];
    int FiveValue[2] = {121,242};
    int StraighFourValue[2] = {120,240};
    //need to be determined
    int FourValueBounded1[2] = {606,483};
    int FourValueBounded2[2] = {122,241};
    int ThreeValue[2] = {39,78};
    int ThreeValueBounded1[2] = {201, 159};
    int ThreeValueBounded2[2] = {41, 79};
    int BrokenThreeValue1[2] = {111,222};
    int BrokenThreeValue2[2] = {93,186};
    int TwoValue[2] = {12, 24};
    int TwoValueBounded1[2] = {14, 25};
    int TwoValueBounded2[2] = {22, 17};
    
    int POW[7] = { 1, 3, 9, 27, 81, 243, 729 };
    int weight[10] = { 1000, 500, 100, 70, 30, 20, 10, 5};
    int player;
    int Five, StraightFour, Four, Three, ThreeBounded, BrokenThree, Two, TwoBounded;
    
    bool isHaveThreat;
    int diagonal_count;
public:
    GiveScore(Board _board, int p);
    void SetHashBoard(Board _board);
    void ComputeThreatRowColumn(int** hash);
    void ComputeThreatDiagonal();
    void setHaveThreat(bool threat);
    void CheckForFiveThree(int value, int index);
    void CheckForFourBrokenThree(int value, int index);
    void CheckForTwo(int value, int index);
    void CheckForTwoBounded(int value, int index);
    void ExamineRowColumn(int hash[20][20]);
    void ExamineDiagonal(int first, int last);
    
    int GiveTotalScore();
    bool isThreat() const;
    
};

#endif /* giveScore_hpp */
