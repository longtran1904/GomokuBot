//
//  main.cpp
//  GomokuBot
//
//  Created by Tran Hoang Long on 6/1/20.
//  Copyright © 2020 Tran Hoang Long. All rights reserved.
//
#include <iostream>
#include <iomanip>
#include "board.hpp"
#include "evaluator.hpp"
#include "giveScore.hpp"
#define row 10
#define column 10

using namespace std;
int main() {
    
    ios_base::sync_with_stdio(false);
    
    // Storing the game
    Board _board;
    _board.printBoard();
    
    // Evaluator function
    Evaluator e;
    
    
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
        
        // Showing player's move
        _board.printBoard();
        
        //Record time of bot move
        time_t start, end;

        time(&start);

        // AI's turn
        e.updateBoard(_board);
        e.updateStartTime(start);
        Move bestMove = e.findBestMove();

        // Play AI's move
        _board.makemove(bestMove.getI(), bestMove.getJ(), 1);
        _board.printBoard();
        
        cout << e.getcnt() << endl; 
        
        time(&end);

        cout << (double) end - start << setprecision(5) << "sec" << endl;
        
        //checking win
        win = _board.win();
        if(win == -10)
        {
            cout<<"Player with X char won!!";
            break;
        }
        
        cout << endl;
        
//        ro:
//        cout <<"\nEnter the coordinates where you want to Enter O : ";
//        cin >> i >> j;
//        //validating coordinates
//        if( _board.empty(i, j) && i < row && j < column)
//        {
//            _board.makemove(i, j, 1);
//        }
//        else
//        {
//            cout<<"Wrong Coordinate Entered!!";
//            goto ro;
//        }
//        _board.printBoard();
//        cout << GiveScore(_board, 2).GiveTotalScore() << endl;
//
    }
    return 0;
}
