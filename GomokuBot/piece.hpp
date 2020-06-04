//
//  piece.hpp
//  GomokuBot
//
//  Created by Tran Hoang Long on 6/3/20.
//  Copyright © 2020 Tran Hoang Long. All rights reserved.
//

#ifndef piece_hpp
#define piece_hpp

#include <stdio.h>

#include "move.hpp"
class Piece
{
private:
    Move pos;
    char player;
public:
    Piece(Move pos, char player);
    void setPos(Move pos);
    void setPlayer(char player);
    Move getpos() const;
    char getPlayer() const;
};

#endif /* piece_hpp */
