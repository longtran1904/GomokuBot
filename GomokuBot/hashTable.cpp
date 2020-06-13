//
//  hashTable.cpp
//  GomokuBot
//
//  Created by Tran Hoang Long on 6/8/20.
//  Copyright © 2020 Tran Hoang Long. All rights reserved.
//

#include "hashTable.hpp"
#include "random"
std::mt19937 mt(01234567);
  
// Generates a Randome number from 0 to 2^64-1
unsigned long long int randomInt()
{
    std::uniform_int_distribution<unsigned long long int>
                                 dist(0, UINT64_MAX);
    return dist(mt);
}

HashTable::HashTable()
{
    hashC = 0;
    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 20; j++)
            for (int k = 0; k < 2; k++)
                ZobristHash[i][j][k] = randomInt();
    

}

void HashTable::changeHash(int i, int j, char pieceChar)
{

    int piece;
    switch (pieceChar) {
        case 1:
            piece = 0;
            break;
        case 2:
            piece = 1;
            break;
        default:
            piece = -1;
            break;
    }
    
    hashC ^= ZobristHash[i][j][piece];
}

unsigned long long HashTable::getHash() const
{
    return hashC;
}
