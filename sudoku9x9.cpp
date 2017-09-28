//
//  sudoku9x9.cpp
//  Sudoku
//
//  Created by Juan Parra on 4/17/16.
//  Copyright © 2016 Juan Parra. All rights reserved.
//
#include <iostream>
#include "sudoku.h"

using namespace std;

// Global variable to simplify code
#define TOTAL_PIECES 81
#define ROW_SIZE 9

//------------------------------------------------------------------------------
// Display the instructions on how to play sudoku to user.

void displayInstructions()
{
    cout << "Welcome to  Sudoku. \n"
    << "The rules of the game are simple: each of the nine blocks has to \n"
    << "contain  all the numbers 1-9 within its squares. Each number can only \n"
    << "appear once in a row, column or box. To make a move, enter the row \n"
    << "letter and column number corresponding to the square (Ex. A7) and then \n"
    << "the digit to be placed there or the digit 0 to blank it out. Enter 'x'\n"
    << "to exit the program.  \n\n";
}


//------------------------------------------------------------------------------
// Displays menu options the user can chose
void printOptions()
{


    cout << "1. Play the game \n"
            "2. Exit \n" << endl;

}

//------------------------------------------------------------------------------
// This method returns the piece index value given the row letter and column number

int indexOfRowAndCol( char rowLetter, char colNumber)
{
    return ( toupper(rowLetter) - 'A') * 9 + (colNumber - '0');
}


//------------------------------------------------------------------------------
//Initialize the board playing pieces to blanks or some other value.

void initializeTheBoard( int &numberOfSquaresFilledIn, char board[])
{
    // initialize globally declared board starting values
    for (int i=1; i<= TOTAL_PIECES; i++)
    {
        board[ i] = ' ';
    }

    /* Pre initializes 43 values on the sudoku board. Due to time constraints
     * relatively easy sudoku board is chosen. */

    board[indexOfRowAndCol('A','5')] = '4';  board[indexOfRowAndCol('A','8')] = '7';
    board[indexOfRowAndCol('A','9')] = '8';

    board[indexOfRowAndCol('B','3')] = '2';  board[indexOfRowAndCol('B','4')] = '7';
    board[indexOfRowAndCol('B','5')] = '8';  board[indexOfRowAndCol('B','7')] = '1';
    board[indexOfRowAndCol('B','9')] = '4';

    board[indexOfRowAndCol('C','1')] = '4';  board[indexOfRowAndCol('C','3')] = '8';
    board[indexOfRowAndCol('C','6')] = '1';  board[indexOfRowAndCol('C','7')] = '6';

    board[indexOfRowAndCol('D','1')] = '7';  board[indexOfRowAndCol('D','5')] = '6';
    board[indexOfRowAndCol('D','6')] = '2';  board[indexOfRowAndCol('D','7')] = '9';
    board[indexOfRowAndCol('D','9')] = '1';

    board[indexOfRowAndCol('E','3')] = '5';  board[indexOfRowAndCol('E','4')] = '1';
    board[indexOfRowAndCol('E','6')] = '4';  board[indexOfRowAndCol('E','8')] = '8';

    board[indexOfRowAndCol('F','1')] = '8';  board[indexOfRowAndCol('F','2')] = '2';
    board[indexOfRowAndCol('F','3')] = '1';  board[indexOfRowAndCol('F','4')] = '9';
    board[indexOfRowAndCol('F','5')] = '7';  board[indexOfRowAndCol('F','7')] = '4';
    board[indexOfRowAndCol('F','8')] = '3';

    board[indexOfRowAndCol('G','1')] = '1';  board[indexOfRowAndCol('G','4')] = '3';
    board[indexOfRowAndCol('G','6')] = '9';  board[indexOfRowAndCol('G','9')] = '7';

    board[indexOfRowAndCol('H','1')] = '2';  board[indexOfRowAndCol('H','6')] = '7';
    board[indexOfRowAndCol('H','7')] = '3';

    board[indexOfRowAndCol('I','2')] = '4';  board[indexOfRowAndCol('I','3')] = '7';
    board[indexOfRowAndCol('I','4')] = '6';  board[indexOfRowAndCol('I','5')] = '5';
    board[indexOfRowAndCol('I','6')] = '8';  board[indexOfRowAndCol('I','7')] = '2';
    board[indexOfRowAndCol('I','8')] = '1';  board[indexOfRowAndCol('I','9')] = '9';

    /* set the number of squares filled in so far, to use in checking for
     * end of game */
    numberOfSquaresFilledIn = 43;
}


//------------------------------------------------------------------------------
// This method prints/displays the sudoku board

void displayBoard( char board[])
{
    char rowLabel = 'A';   // used to display row values as letters

    // display column labels
    cout << "    1   2   3   4   5   6   7   8   9  " << endl;
    cout << "  -------------------------------------" << endl;

    // for each row
    for (int row=1; row<=ROW_SIZE; row++)
    {
        cout << rowLabel++ << " | ";

        // for each column
        for( int col=1; col<= ROW_SIZE; col++)
        {
            cout << board[ (row-1)* ROW_SIZE + col] << " | ";
        }
        cout << endl;
        cout << "  -------------------------------------"  << endl;

    }
}



//------------------------------------------------------------------------------
/* This method checks to see if the game is finished, by checking the number of
 * squares that have been filled in on the board. */

bool gameNotFinished( int numberOfPiecesOnBoard)
{
    if( numberOfPiecesOnBoard >= TOTAL_PIECES) {
        return false;   // game is done
    }
    else
    {
        return true;    // game not done
    }
}


//------------------------------------------------------------------------------
/* This method checks to see if the user input is valid in terms of range of
 * values that can be entered. */

bool userInputIsInvalid( char positionLetter, char positionNumber, char positionValue)
{
    // The rows can only be the chars ranging from A-I (9 rows)
    // The columns can only be the chars ranging from 1-9 (9 columns)
    /* The values of that the user can input ranges from 0-9. 0 being that the
     * user decided to blank out a value in a certain row and col */

    if ( ((positionLetter < 'A') || (positionLetter > 'I')) ||
        ((positionNumber < '1') || (positionNumber > '9')) ||
        ((positionValue < '0') || (positionValue > '9'))
        )
    {
        return true;       // part of the move IS invalid
    }
    else
    {
        return false;       // move is valid
    }
}


//------------------------------------------------------------------------------
/*  This method checks to see if a move is invalid. If the move is invalid, an
 *  error message is displayed according to what type of error it was. This method
 *  also combines the method used to check the rows, colums and, 3x3 squares*/

bool moveIsInvalid( char positionLetter, char positionNumber, char positionValue, char board[])
{
    // check rows
    int rowStart = (positionLetter - 'A')*9 + 1;    // get starting index for row
    for (int i=rowStart; i< rowStart+9; i++) {
        if( positionValue == board[ i]) {
            cout << " Row " << positionLetter
            << " already has that value.  Please retry" << endl;
            return true;    // move is invalid
        }
    }

    // check columns
    int colStart = (positionNumber - '0');
    for (int i=colStart; i<= colStart+72; i+=9) {
        if( positionValue == board[ i]) {
            cout << " Column " << positionNumber
            << " already has that value.  Please retry" << endl;
            return true;    // move is invalid
        }
    }

    // Checks 3x3 squares
    // get index of move position
    int index = indexOfRowAndCol( positionLetter, positionNumber);

    // set index to be one of the values in column 1 or colum 4
    int colChange = (index - 1) % 3;
    index = index - colChange;

    // now compensate for even or odd rows, converting index into an even row value
    int rowChange = (positionLetter - 'A') % 3 * 9;
    index = index - rowChange;

  /* This code accountants for all possible 81 squares in the 9x9 sudoku board. The indexs
   * represent each new 3x3 square(Ex. 1, 4, 7 ,28, 31, 34, 55, 58, and 61). These numbers
   * are each a new 3x3 square. The math involed below gets all possible 81 numbers by adding
   * the 9 indexies so that no two numbers will equal the same. */

    if (  (positionValue == board[index])    || (positionValue == board[index + 1])  ||
        (positionValue == board[index + 2])  || (positionValue == board[index + 9])  ||
        (positionValue == board[index + 10]) || (positionValue == board[index + 11]) ||
        (positionValue == board[index + 18]) || (positionValue == board[index + 19]) ||
        (positionValue == board[index + 20])
        )
    {
        cout << " Square starting at " << index
        << " already has that value.  Please retry" << endl;
        return true;     // move is invalid
    }

    return false;       // move is valid
}


//------------------------------------------------------------------------------
//The main method that puts all the methods together and displays the final program

int main()
{
    // local variable declarations
    char positionLetter;          // row letter
    char positionNumber;          // column number
    char positionValue;           // value in spcified row/col
    int numberOfPiecesOnBoard = 0;   // total number of non-blanks on the board
    char board[ TOTAL_PIECES + 1]; // add an extra piece to array so that we can ignore the piece in position 0

    int choice = 0;



    // display identifying information and instructions

    displayInstructions();
    cout<< endl;
    printOptions();
    cout<<endl;

    // Initialize the board
    initializeTheBoard( numberOfPiecesOnBoard, board);

    // display the board
    displayBoard( board);

    while (choice != 2)
    {
        cout << "\nChoice - ";
        cin >> choice;

        switch(choice)
        {

            case 1:
            {
                // main program loop
                while ( gameNotFinished( numberOfPiecesOnBoard) )
                {

                    // Ask user for input
                    cout << "Enter row letter, column number, and value: ";
                    cin >> positionLetter;

                    // fold into upper case if user input lowercase leter
                    positionLetter = toupper( positionLetter);

                    // See if 'x' for exit was chosen.
                    if( positionLetter == 'X')
                    {

                        break;		// exit program
                    }

                    //Get user col num and value
                    cin >> positionNumber;
                    cin >> positionValue;

                    // Validate the range for user entry piece letter
                    if( userInputIsInvalid( positionLetter, positionNumber, positionValue) )
                    {
                        cout << " Invalid input values, please retry." << endl;
                        continue;	// loop back up to top of main loop
                    }

                    // Move position and values are within range.
                    // Now validate move according to other pieces on the board
                    if ( moveIsInvalid( positionLetter, positionNumber, positionValue, board) )
                    {


                        continue;
                    }

                    /* If user had entered '0' to clear a position, change it to a blank ' '
                     * before storing it. */
                    if ( positionValue == '0')
                    {
                        positionValue = ' ';
                        numberOfPiecesOnBoard--;    // will blank out one piece
                    }
                    else
                    {
                        numberOfPiecesOnBoard++;    // increment number of pieces on board
                    }
                    board[ indexOfRowAndCol(positionLetter, positionNumber)] = positionValue;


                    cout<<endl;

                    // displays the board
                    displayBoard( board);

                }

                // Verifies to user if they solved correctly or not
                if ( gameNotFinished( numberOfPiecesOnBoard)) {
                    cout << "Better luck next time. \n\n";
                }
                else {
                    // game was finished, with all pieces filled in
                    cout << "Congratulations you did it! Nice job. \n\n";
                }



                break;
            }


            case 2:
            {
                {break;}
            }

        }
    }


    return 0;
}
