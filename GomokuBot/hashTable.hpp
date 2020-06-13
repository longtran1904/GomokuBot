//
//  hashTable.hpp
//  GomokuBot
//
//  Created by Tran Hoang Long on 6/8/20.
//  Copyright © 2020 Tran Hoang Long. All rights reserved.
//

#ifndef hashTable_hpp
#define hashTable_hpp

#include <stdio.h>
#include "move.hpp"

class HashTable
{
private:
    unsigned long long ZobristHash[20][20][2];
    unsigned long long hashC;
public:
    HashTable();
    
    //setter
    void init();
    void changeHash(int i, int j, char pieceChar);
    
    
    // getter
    bool IsInTable(int hash) const;
    unsigned long long getHash() const;
    
    
};

#endif /* hashTable_hpp */
