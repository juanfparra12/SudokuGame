

#include "sudoku.h"
#include <iostream>
using namespace std;

// Global constants
#define NUMBER_OF_PIECES 36
#define ROW_SIZE 6





//------------------------------------------------------------------------------
// Display the instructions on how to play sudoku to user.

void displayInstructions()
{
    cout << "Welcome to Sudoku. \n"
    << "The rules of the game are simple: each of the six blocks has to \n"
    << "contain  all the numbers 1-6 within its squares. Each number can only \n"
    << "appear once in a row, column or box. To make a move, enter the row \n"
    << "letter and column number corresponding to the square (Ex. A5x) and then \n"
    << "the digit to be placed there or the digit 0 to blank it out. Enter 'x'\n"
    << "to exit the program.  \n\n";
}

//--------------------------------------------------------------------------------
void printOptions() {


    cout << "1. Sudoku Problem \n"
    "2. Play the game \n"
    "3. Exit \n" << endl;

}

//-----------------------------------------------------------
// indexOfRowAndCol
//      Given the row letter and column number, return the
//      piece index value.
//
int indexOfRowAndCol( char rowLetter, char colNumber)
{
    return ( toupper(rowLetter) - 'A') * 6 + (colNumber - '0');
}


//------------------------------------------------------------------------------
//Initialize the board playing pieces to blanks or some other value.

void initializeTheBoard( int &numberOfSquaresFilledIn, char board[])
{
    // initialize globally declared board starting values
    for (int i=1; i<= NUMBER_OF_PIECES; i++) {
        board[ i] = ' ';
    }

    // now set the pieces that are non-blanks in the board:
    //   1 2 3 4 5 6
    // -------------
    //A | |2|3| |5| |       1  2  3  4  5  6
    //B |1|6| |3| | |       7  8  9 10 11 12
    //C | | | | | |5|      13 14 15 16 17 18
    //D |3| |6| |4|1|      19 20 21 22 23 24
    //E | | | | | | |      25 26 27 28 29 30
    //F | | |1| | | |      31 32 33 34 35 36
    board[indexOfRowAndCol('A','1')] = '5';  board[indexOfRowAndCol('A','3')] = '1';
    board[indexOfRowAndCol('A','4')] = '6';  board[indexOfRowAndCol('A','5')] = '3';

    board[indexOfRowAndCol('B','2')] = '4';  board[indexOfRowAndCol('B','4')] = '5';


    board[indexOfRowAndCol('C','1')] = '1'; board[indexOfRowAndCol('C','4')] = '2';
    board[indexOfRowAndCol('C','5')] = '4';

    board[indexOfRowAndCol('D','2')] = '6';  board[indexOfRowAndCol('D','4')] = '3';

    board[indexOfRowAndCol('F','1')] = '3';  board[indexOfRowAndCol('F','3')] = '6';
    board[indexOfRowAndCol('F','4')] = '4';

    // set the number of squares filled in so far, to use in checking for end of game
    numberOfSquaresFilledIn = 14;
}


//-----------------------------------------------------------
// displayBoard()
//		display the board
//
void displayBoard( char board[])
{
    char rowLabel = 'A';   // used to display row values as letters

    // display column labels
    cout << "    1   2   3   4   5   6  " << endl;
    cout << "  -------------------------" << endl;

    // for each row
    for (int row=1; row<=ROW_SIZE; row++) {
        cout << rowLabel++ << " | ";

        // for each column
        for( int col=1; col<=ROW_SIZE; col++) {
            cout << board[ (row-1)* ROW_SIZE + col] << " | ";
        }
        cout << endl;
        cout << "  -------------------------" << endl;
    }
}


//-----------------------------------------------------------
// gameNotFinished()
//		see if the game is finished, by checking the number of squares that
//      have been filled in on the board.
//
bool gameNotFinished( int numberOfPiecesOnBoard)
{
    if( numberOfPiecesOnBoard >= NUMBER_OF_PIECES) {
        return false;   // game IS finished
    }
    else {
        return true;    // game is NOT yet finished
    }
}


//-----------------------------------------------------------
// userInputIsInvalid()
//      See if user input is valid in terms of range of values
//      that can be entered.
bool userInputIsInvalid( char positionLetter, char positionNumber, char positionValue)
{
    if ( ((positionLetter < 'A') || (positionLetter > 'F')) ||
        ((positionNumber < '1') || (positionNumber > '6')) ||
        ((positionValue < '0') || (positionValue > '6'))
        ) {
        return true;       // part of the move IS invalid
    }
    else {
        return false;       // move is valid
    }
}


//-----------------------------------------------------------
// moveIsInvalid()
//      See if move is invalid.  If the move is invalid, display
//  an appropriate error message.
//  Note that given ONLY the board square position, you can calculate the
//  the row letter as:
//        (position-1)/6 + 'A'
//  and to find the column number:
//         (position-1)%6 + 1 + '0'
//  These are necessary to use when calling this function, if you have the position
//  value, but not the row letter or column number.
bool moveIsInvalid( char positionLetter,   // the row letter, as a char
                   char positionNumber,   // the column number, as a char
                   char positionValue,    // the value to put in the row,col
                   char board[]
                   )
{
    // check row
    int rowStart = (positionLetter - 'A')*6 + 1;    // get starting index for row
    for (int i=rowStart; i< rowStart+6; i++) {
        if( positionValue == board[ i]) {
            cout << "*** Row " << positionLetter
            << " already has that value.  Please retry" << endl;
            return true;    // move is, in fact, invalid
        }
    }

    // check column
    int colStart = (positionNumber - '0');
    for (int i=colStart; i<= colStart+30; i+=6) {
        if( positionValue == board[ i]) {
            cout << "*** Column " << positionNumber
            << " already has that value.  Please retry" << endl;
            return true;    // move is, in fact, invalid
        }
    }

    // Check rectangle
    // Each rectangle is denoted by the index in the upper-left corner of that
    // 2 x 3 rectangle.
    //      To find which rectangle we are in, first we take the
    // current piece index and use a mod function to place it into either column
    // 1 values or column 4 values.
    //      Then we determine if it was in an even (A,C,E)
    // or odd (B,D,F) row, subtracting 6 from the index value if it was on an
    // odd row.
    //      This converts the current move index into one of the six values
    // shown in the playing board at left below.  From there we can check the
    // rectangle relative to the upper-left hand corner piece.
    //    1  2  3  4  5  6
    //  -------------------
    //A | 1|  |  | 4|  |  |       1  2  3  4  5  6
    //B |  |  |  |  |  |  |       7  8  9 10 11 12
    //C |13|  |  |16|  |  |      13 14 15 16 17 18
    //D |  |  |  |  |  |  |      19 20 21 22 23 24
    //E |25|  |  |28|  |  |      25 26 27 28 29 30
    //F |  |  |  |  |  |  |      31 32 33 34 35 36

    // get index of move position
    int index = indexOfRowAndCol( positionLetter, positionNumber);
    // set index to be one of the values in column 1 or column 4 (1,7,13,... or 4,10,16,...)
    int colChange = (index-1) % 3;
    index = index - colChange;    //1,2,3 -> 1;  4,5,6 -> 4; 7,8,9 -> 7; etc...
    // now compensate for even or odd rows, converting index into an even row value
    int rowChange = (positionLetter - 'A')%2 * 6;
    index = index - rowChange;
    // Now index is one of the values 1, 4, 13, 16, 25, or 28, which is the upper
    // left corner of the rectangle in question.  Check the 6 squares in rectangle.
    if ( (positionValue == board[index]) || (positionValue == board[index+1]) ||
        (positionValue == board[index+2]) ||
        (positionValue == board[index+6]) ||(positionValue == board[index+7]) ||
        (positionValue == board[index+8])
        ) {
        cout << "*** Rectangle starting at " << index
        << " already has that value.  Please retry" << endl;
        return true;     // move is invalid
    }

    return false;       // move is valid
}


//-----------------------------------------------------------
// main()
//		main part of the program
int main()
{
    // local variable declarations
    char positionLetter;          // user input of row letter
    char positionNumber;          // user input of column number
    char positionValue;           // user input of value to be placed
    int pieceIndex;               // pieceIndex calculated using row & col values
    int numberOfPiecesOnBoard = 0;   // total number of non-blanks on the board
    char board[ NUMBER_OF_PIECES + 1]; // add an extra piece to array so that we
    // can ignore the piece in position 0, so
    // that this code corresponds to the
    // previous non-array version.


    int choice = 0;



    // display identifying information and instructions

    displayInstructions();
    cout<< endl;
    printOptions();
    cout<<endl;

    // Initialize the board
    initializeTheBoard( numberOfPiecesOnBoard, board);


    while (choice != 3)
    {
        cout << "\nchoice - ";
        cin >> choice;

        switch(choice)
        {
            case 1 :
            {
                cout<< endl;
                // display the board
                displayBoard( board);
                break;
            }
            case 2:
            {
                // main program loop
                while ( gameNotFinished( numberOfPiecesOnBoard) ) {

                    // Prompt for user input.  Handle 'x' for exit
                    cout << "Enter row letter, column number, and value: ";
                    cin >> positionLetter;
                    positionLetter = toupper( positionLetter);    // fold into upper case
                    // See if 'x' for exit was chosen.
                    if( positionLetter == 'X') {
                        cout << "The exit option was selected. \n"
                        << "\n";
                        break;		// exit was chosen, so exit program
                    }
                    cin >> positionNumber;	// exit was not chosen, so get second part of user input
                    cin >> positionValue;

                    // Validate the range for user entry piece letter
                    if( userInputIsInvalid( positionLetter, positionNumber, positionValue) ) {
                        cout << "*** Invalid input values, please retry." << endl;
                        continue;	// loop back up to top of main loop
                    }

                    // Move position and values are within range.
                    // Now validate move according to other pieces on the board
                    if ( moveIsInvalid( positionLetter, positionNumber, positionValue, board) ) {
                        // above function call already displayed appropriate error message
                        continue;
                    }

                    // Now that user input and position have been validated, actually make the move
                    // If user had entered '0' to clear a position, change it to a blank ' '
                    // before storing it.
                    if ( positionValue == '0') {
                        positionValue = ' ';
                        numberOfPiecesOnBoard--;    // will blank out one piece
                    }
                    else {
                        numberOfPiecesOnBoard++;    // increment number of pieces on board
                    }
                    board[ indexOfRowAndCol(positionLetter, positionNumber)] = positionValue;


                    cout<<endl;

                    // display the board
                    displayBoard( board);

                }
                // display appropriate ending message
                if ( gameNotFinished( numberOfPiecesOnBoard)) {
                    cout << "Better luck next time. \n\n";
                }
                else {
                    // game was finished, with all pieces filled in
                    cout << "Congratulations you did it! Nice job. \n\n";
                }



                break;
            }


            case 3:
            {
                {break;}
            }

        }
    }
    return 0;

}
