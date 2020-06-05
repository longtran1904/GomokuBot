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

    // Storing the game
    Board _board;
    
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
        
        // Showing player move
        _board.printBoard();
        
        //checking win
        win = _board.win();
        if(win == -10)
        {
            cout<<"Player with X char won!!";
            break;
        }
        
        cout << endl;
        
        
        // Evaluator to find next good move
        
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
        
        // If there is any empty move to go
        if (_board.isMoveLeft())
        {
            // find a good move to go
            Move bestMove = e.findBestMove();
            
            // make the move on the game board
            _board.makemove(bestMove.getI(), bestMove.getJ(), 1);
            
            // print game after AI's move
            _board.printBoard();
            
            if (win == 10)
            {
                cout << "Player with O char won!!";
                break;
                
            }
        }
        else cout << "DRAW";
    }
    return 0;
}
