//
//  piece.cpp
//  GomokuBot
//
//  Created by Tran Hoang Long on 6/3/20.
//  Copyright © 2020 Tran Hoang Long. All rights reserved.
//

#include "piece.hpp"

Piece::Piece(Move pos, char player)
{
    this->pos = pos;
    this->player = player;
}
Move Piece::getpos() const
{
    return pos;
}
char Piece::getPlayer() const
{
    return player;
}
