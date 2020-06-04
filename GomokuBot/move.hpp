//
//  pos.hpp
//  GomokuBot
//
//  Created by Tran Hoang Long on 6/3/20.
//  Copyright © 2020 Tran Hoang Long. All rights reserved.
//

#ifndef move_hpp
#define move_hpp

#include <stdio.h>

class Move{
private:
    int i;
    int j;
    //bool isMark;
public:
    Move();
    Move(int i, int j);
    //void setMarked(bool mark);
    void setI(int i);
    void setJ(int j);
    //bool isMarked() const;
    int getI() const;
    int getJ() const;
};

#endif /* move_hpp */
