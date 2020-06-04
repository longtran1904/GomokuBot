//
//  main.cpp
//  GomokuBot
//
//  Created by Tran Hoang Long on 6/1/20.
//  Copyright © 2020 Tran Hoang Long. All rights reserved.
//
#include <iostream>
#include "board.hpp"
#include "evaluator.hpp"
#define row 3
#define column 3
using namespace std;
int main() {
    // insert code here...
    Board _board;
    
    _board.printBoard();
    int win=false;
    int i,j;
    while (win==false)
    {
    //asking user X for coordinates
       
        rx :
        
        cout <<"\nEnter the coordinates where you want to Enter X : ";
        cin >> i >> j;
        //validating coordinates
        if( _board.empty(i, j) && i < row && j < column)
        {
            _board.makemove(i, j, 2);
        }
        else
        {
            cout<<"Wrong Coordinate Entered!!";
            goto rx;
        }
        
        _board.printBoard();
        win = _board.win();   //checking win
        if(win == -10)
        {
            cout<<"Player with X char won!!";
            break;
        }
        cout << endl;
        Evaluator e(_board);
        
//        vector<Piece> p = e.getMoveList();
//        for (Piece m: p)
//        {
//            cout << m.getpos().getI() << " " << m.getpos().getJ() << " " << m.getPlayer() << endl;
//        }
        
//        vector<Move> m = e.getPossibleMoves();
//
//        for (Move mo: m)
//        {
//            cout << mo.getI() << " " << mo.getJ() << endl;
//        }
//
        Move bestMove = e.findBestMove();
        _board.makemove(bestMove.getI(), bestMove.getJ(), 1);
        
        _board.printBoard();

        if (win == 10)
        {
            cout << "Player with O char won!!";
            break;
            
        }
    }
    return 0;
}
