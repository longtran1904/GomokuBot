//
//  pos.cpp
//  GomokuBot
//
//  Created by Tran Hoang Long on 6/3/20.
//  Copyright © 2020 Tran Hoang Long. All rights reserved.
//

#include "move.hpp"

Move::Move()
{
    i = 0;
    j = 0;
}
Move::Move(int i,int j)
{
    this->i = i;
    this->j = j;
  
}
void Move::setI(int i)
{
    this->i = i;
}
void Move::setJ(int j)
{
    this->j = j;
}
//void Move::setMarked(bool mark)
//{
//    isMark = mark;
//}
//bool Move::isMarked() const
//{
//    return isMark;
//}
int Move::getI() const
{
    return i;
}
int Move::getJ() const
{
    return j;
}

