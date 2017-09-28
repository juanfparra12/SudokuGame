//
//  sudoku.h
//  Sudoku
//
//  Created by Juan Parra on 4/15/16.
//  Copyright © 2016 Juan Parra. All rights reserved.
//

#ifndef sudoku_h
#define sudoku_h
#include <iostream>

using namespace std;

class Sudoku
{
private:


    int indexOfRowAndCol( char rowLetter, char colNumber);
    void initializeTheBoard( int &numberOfSquaresFilledIn, char board[]);
    bool gameNotFinished( int numberOfPiecesOnBoard);
    bool userInputIsInvalid( char positionLetter, char positionNumber, char positionValue);
    bool moveIsInvalid( char positionLetter, char positionNumber, char positionValue, char board[]);

public:


    void displayInstructions();
    void displayBoard( char board[]);
    void printOptions();


};
#endif /* sudoku_h */
