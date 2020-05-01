/*
 Name: Tyler Ailes
 Date: April 26, 2020
 Desc: Pawn Puzzle game for CSCI 156 Final Exam
 Notes: Cant get a winner without getting a memory error when black moves
        Tried switching to White & Black classes instead of Piece but moved memory error to display function, or wouldn't move the Black pawns when a move was made
        Is no way to detect when no moves are possible to ending the game
        Display function is what I'm most proud of getting working
        Had sleep() in the code, but not sure if will be run on windows or mac and since i'm using mac didn't want to get a bunch of potiential errors. Should find a better way to slow the program down when solving automatically
        Maybe add explaination to the steps in PuzzleAnswer()
 
 */

/*
 Instructions:
 Winter 2020 Finale Exam:

 In this Final Exam assignment, you will write your very own chess engine!!! :)

 However, you will not need to write this engine for a full chess board. Rather you will start with a 3x3 board populated only with pawns, the goal of the game will be for white to get a single pawn to the other side of the board. In other words, we will assume that white wins if he gets his pawn to the opposite end of the board, and that black wins if he does not.

 This is a fairly famous puzzle, a video of which, along with the solution, is posted here: Pawn Puzzle (https://www.youtube.com/watch?v=2NZ-3gCGiL0)

 Obviously, you will not be adhering to the strict rules of the game (although a full set of rules can be found here), so here are the rules that you will be playing with:

 Rules

 White moves first *DONE*
 ignore the en passant rule (if you don't know what this is, don't worry about it)
 pawns move only forward, unless they are in the process of capturing another piece
 There will be no time limitations *DONE*
 Program Requirements

 the "y-axis" (a.k.a ranks) will be numbered 1 - 3 *DONE*
 the "x-axis" (a.k.a files) will be lettered a - c *DONE*
 Note that the above are just for the user interface, internally, the program is welcome to use numeric coordinates for piece location
 Keep track of each piece location *DONE*
 record all previous moves *DONE*
 recognize when a win has occurred
 able to play a game against a human (random legal moves are fine) *DONE*
 2 examples of inheritance (note implicitly requires 3 classes)
 all variables dynamically allocated
 Each class must have 3 constructors (default, copy, parameterized) and a destructor
 The initial position will be where all of whites pawns are on the first rank (row) and all of black's pawns are on the 3rd rank (row) *DONE*
 Note that a function to display the state of the board is not required, but it's difficult to see how exactly one would debug without it.*DONE*
 Extra Credit:

 Using a Linked list as one of your classes will gain you 10% Extra Credit - note however, that to get the extra credit this needs to be a linked list that meaningfully contributes to the functioning of the code. An easy way to do this is to, perhaps, overload the operator[] function, and use the linked list as an array.

 If your program can solve the puzzle you will get 25% extra credit - note that this is a large amount of extra credit for a reason, so it's not for the faint of heart.

 Using a move constructor and move-assignment operator in each class will gain you 10% extra credit.
 */


#include <iostream>
#include <string> // for Piece class
#include <sstream> // for movement




using namespace std;

class Piece {
public:
    Piece(void){
        player = 100;
        pieceName = "blank";
    }
    
    Piece(const Piece &obj){
        
    }
    
    ~Piece(void){
    }

    string pieceName;
    int player;
    
    Piece(string n, int p) {
        pieceName = n;
        player = p;
    }
    
    // For testing
    int getID(){
        return player;
    }
    
    void setBoth(string n, int p){
        pieceName = n;
        player = p;
    }
};


class Square: public Piece {
public:
    Square(void) {
        piece = nullptr;
    }
    
    Square(const Square &obj){
        
    }
    
    ~Square(void) {
        
    }
    
    Piece *piece;
    
    
    Square(Piece *p){
        piece = p;
    }
    

};


// Declared below main to look more clean
void Display(Square board[3][3]);
bool Movement(string move, Square board[3][3], int currentPlayer);
void PlayGame(string input);
void PuzzleAnswer();


int main(void) {

    // Input
    string input;
    char yn = ' ';

    // Explaining rules
    cout<<"Welcome to the Pawn Puzzle!"<<endl<<endl;
    cout<<"White moves first, and is represented by \"P\", and Black is represented by \"p\"."<<endl;
    cout<<"White wins when a White Pawn reaches row 3, and Black wins if that does not happen."<<endl<<endl;
    
    cout<<"Would you like to see the solution to the Puzzle? (Y/N)"<<endl;
    cout<<"Enter N to attempt the Puzzle yourself."<<endl<<endl;
    
    
    while (yn != 'Y' || yn != 'N'){
        cin>>yn;
    
        if (yn == 'Y'){
            PuzzleAnswer();
            cout<<"Scroll to the top to see how to solve the Puzzle!"<<endl<<endl;
            break;
        } else if (yn == 'N'){
            cout<<endl<<endl;
            PlayGame(input);
        } else {
            cout<<"Invalid Input"<<endl<<"Enter Again:"<<endl;
        }
    }

    return 0;
}



// Game declaration
void PlayGame(string input){
    Square board[3][3];
    string u = "User";
    string c = "Computer";
    
    
    // Declaring pawns: white = user, black = computer
    // and player id's: 1 = user, 20 = computer, 2 = other user
    // FIXME: make able to set black to a user with id 2, instead of forcing computer (FIXED)
    Piece WhitePawn1("Pawn", 1);
    Piece WhitePawn2("Pawn", 1);
    Piece WhitePawn3("Pawn", 1);
    Piece BlackPawn1;
    Piece BlackPawn2;
    Piece BlackPawn3;
    
    // Getting user input on whether they want to play computer or other user, then declaring id to correspond
    // FIXME: maybe eventually add the functionality to actually play a computer, got in way over my head when started writing the cout's
    cout<<"Would you like to play against another user, or against the computer?(Enter 'User' or 'Computer')"<<endl;
    while (input.compare(c) != 0 || input.compare(u) != 0){
        getline(cin, input);
        if (input.compare(c) == 0){
            // Assigns black as computer
//            BlackPawn1.setBoth("Pawn", 20);
//            BlackPawn2.setBoth("Pawn", 20);
//            BlackPawn3.setBoth("Pawn", 20);
//            break;
            cout<<"Computer does not currently work, please select User"<<endl;
        } else if (input.compare(u) == 0){
            // Assigns black as user
            BlackPawn1.setBoth("pawn", 2);
            BlackPawn2.setBoth("pawn", 2);
            BlackPawn3.setBoth("pawn", 2);
            break;
        } else {
            cout<<"Invalid Input"<<endl<<"Enter Again:"<<endl;
        }
    }
    
    
    // Place pieces onto the board
    board[0][0].piece = &WhitePawn1;
    board[0][1].piece = &WhitePawn2;
    board[0][2].piece = &WhitePawn3;

    board[2][0].piece = &BlackPawn1;
    board[2][1].piece = &BlackPawn2;
    board[2][2].piece = &BlackPawn3;

    int currentPlayer = 2; // start as black to switch to player 1 immediately
    string move;
    string name;
    //int winner = 0; // used to determine if white won DOESNT WORK
    
    // Main Game Loop
    while(true){
        
        // Player switcher
        if (currentPlayer == 1){
            currentPlayer = 2;
            name = "User2";
        } else {
            currentPlayer = 1;
            name = "User";
        }
        
        Display(board);
        
        
        cout<<name<<" please enter your move (Ex: A1 to A2):";
        getline(cin, move);
        
        
        while (Movement(move, board, currentPlayer) == false){
            cout<<"Please re-enter your move."<<endl;
            getline(cin, move);
        }
        

    }
    
}

// Display declaration
void Display(Square board[3][3]){
    //should be 20x13 or 13x20, but couldnt get it to fit right
    char displayBoard[38][53] = {

        {' ', ' ', ' ', ' ', ' ', ' ', ' ', 'A', ' ', ' ', ' ', ' ', ' ', 'B', ' ', ' ', ' ', ' ', ' ', 'C', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#'},
        {' ', ' ', '3', ' ', '#', ' ', ' ', 'p', ' ', ' ', '#', ' ', ' ', 'p', ' ', ' ', '#', ' ', ' ', 'p', ' ', ' ', '#'},
        {' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#'},
        {' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#'},
        {' ', ' ', '2', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#'},
        {' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#'},
        {' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#'},
        {' ', ' ', '1', ' ', '#', ' ', ' ', 'P', ' ', ' ', '#', ' ', ' ', 'P', ' ', ' ', '#', ' ', ' ', 'P', ' ', ' ', '#'},
        {' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#'},
        {' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    };

    // "displayRow"...converts the standard board coordinates to display coordinates
    int dR1 = 11;
    int dR2 = 7;
    int dR3 = 3;


    // "displayColumn"
    int dC1 = 7;
    int dC2 = 13;
    int dC3 = 19;

    // values set to 3 instead of 0 because when set to 0, 'P' was being placed in all spots of the 3rd column when it shouldnt have been
    int tempRow = 0;
    int tempColumn = 0;

    // updates real piece locations on the "display board"
    for(int i = 0; i < 3; i++){

        if(i == 0)
            tempRow = dR1;
        else if(i == 1)
            tempRow = dR2;
        else if(i == 2)
            tempRow = dR3;

        
    
    for(int j = 0; j < 3; j++){
        

        if(j == 0)
            tempColumn = dC1;
        else if(j == 1)
            tempColumn = dC2;
        else if(j == 2)
            tempColumn = dC3;

        // update display board pieces to match user moves
        // insirpation gathered from google
        if(board[i][j].piece == nullptr)
            displayBoard[tempRow][tempColumn] = ' ';
        // Cap P for user
        else if(board[i][j].piece->pieceName.compare("Pawn") == 0 && board[i][j].piece->player == 1)
            displayBoard[tempRow][tempColumn] = 'P';
        // Lowercase p for computer
        else if(board[i][j].piece->pieceName.compare("pawn") == 0 && board[i][j].piece->player == 2)
        displayBoard[tempRow][tempColumn] = 'p';

        }
    }




    for(int i = 0; i < 16; i++){

        cout<<endl;
    
        for(int j = 0; j < 30; j++){
        
            cout<<displayBoard[i][j];
        
        }
    }
    
}

// Puzzle explaination
void PuzzleAnswer(){
    // Declaring board and pieces
    Square board[3][3];
    Piece WhitePawn1("Pawn", 1);
    Piece WhitePawn2("Pawn", 1);
    Piece WhitePawn3("Pawn", 1);
    Piece BlackPawn1("pawn", 2);
    Piece BlackPawn2("pawn", 2);
    Piece BlackPawn3("pawn", 2);
    
    // Place pieces onto the board
    board[0][0].piece = &WhitePawn1;
    board[0][1].piece = &WhitePawn2;
    board[0][2].piece = &WhitePawn3;

    board[2][0].piece = &BlackPawn1;
    board[2][1].piece = &BlackPawn2;
    board[2][2].piece = &BlackPawn3;
    
    
    string move;
    string name;
    int currentPlayer = 1;
    
    // display starting board
    Display(board);
    
    // making first move
    move = "B1 to B2";
    Movement(move, board, currentPlayer);
    Display(board);
    
    currentPlayer = 2;
    move = "C3 to B2";
    Movement(move, board, currentPlayer);
    Display(board);
    
    currentPlayer = 1;
    move = "A1 to A2";
    Movement(move, board, currentPlayer);
    Display(board);
    
    currentPlayer = 2;
    move = "B3 to A2";
    Movement(move, board, currentPlayer);
    Display(board);
    
    currentPlayer = 1;
    move = "C1 to C2";
    Movement(move, board, currentPlayer);
    Display(board);
    
    currentPlayer = 2;
    move = "A2 to A1";
    Movement(move, board, currentPlayer);
    Display(board);
    
    currentPlayer = 1;
    move = "C2 to C3";
    Movement(move, board, currentPlayer);
    Display(board);
    
}

// Movement declaration
bool Movement(string move, Square board[3][3], int currentPlayer) {
    
    // Ensuring the format of the move is right
    // making sure it starts with a valid letter
    if(move[0] != 'A' && move[0] != 'B' && move[0] != 'C'){
        return false;
    }
    // making sure it starts with a valid number
    if(move[1] != '1' && move[1] != '2' && move[1] != '3'){
        return false;
    }
    // making sure middle word is 'to'
    if(move[3] != 't' || move[4] != 'o'){
        return false;
    }
    // making sure destination starts with valid letter
    if(move[6] != 'A' && move[6] != 'B' && move[6] != 'C'){
        return false;
        }
    // making sure destination starts with a valid number
    if(move[7] != '1' && move[7] != '2' && move[7] != '3'){
        return false;
    }

    // used to convert 'string move' to ints that can be used to move pieces
    stringstream convert;
    
    int letter1;
    int num1;
    
    convert<<move[1];
    convert>>num1;
    convert.clear();
    num1 = num1 - 1;
    
    int letter2;
    int num2;
    
    convert<<move[7];
    convert>>num2;
    num2 = num2 - 1;
    
    // if statements change letters into numbers
    if(move[0] == 'A'){
        letter1 = 0;
    } else if(move[0] == 'B'){
        letter1 = 1;
    }else{
        letter1 = 2;
    }
    
    if(move[6] == 'A'){
        letter2 = 0;
    } else if(move[6] == 'B'){
        letter2 = 1;
    }else {
        letter2 = 2;
    }
    
    int rowDiff = num1 - num2;
    int colDiff = letter1 - letter2;
    
    // User 1's pawn movement rules
    if(currentPlayer == 1){

        // rowDiff must ALWAYS be negative to prevent backwards movement
        if(rowDiff >= 0){
            
            cout<<"Pawns can't move like that."<<endl<<endl;
            return false;
        }

        // can only go one collumn over at a time
        else if(abs(colDiff) > 1){
            
            cout<<"Pawns can't move like that."<<endl<<endl;
            return false;
        }
        // can only move diagonal if there is an enemy peice there
        else if(abs(colDiff) == 1 && rowDiff == -1 && board[num2][letter2].piece == nullptr){
            
            cout<<"There must be an enemy piece at "<<letter2<<num2<<" for you to move there."<<endl<<endl;
            return false;
        }

        // can't move forward with an enemy in front
        else if(rowDiff == -1 && colDiff == 0 && board[num2][letter2].piece != nullptr && (board[num2][letter2].piece->player == 2 || board[num2][letter2].piece->player == 20)){

            cout<<"An enemy piece is blocking your move!"<<endl<<endl;
            return false;
        }
        
        // taking an enemy pawn
        else if(rowDiff == -1 && abs(colDiff) == 1 && (board[num2][letter2].piece->player == 2 || board[num2][letter2].piece->player == 20)){

            cout<<"You have taken the enemy's "<<board[num2][letter2].piece->pieceName<<"!"<<endl<<endl;

            board[num2][letter2].piece = board[num1][letter1].piece;    //piece taken
            board[num1][letter1].piece = nullptr;

            return true;
        }
        
        // forward movement
        else{

            cout<<"Move successful!"<<endl<<endl;
            board[num2][letter2].piece = board[num1][letter1].piece;
            board[num1][letter1].piece = nullptr;
            
            return true;
        }
    }
    
    // User2 / Computer Pawn movement
    else if(currentPlayer == 2){

        // rowDiff must ALWAYS be negative to prevent backwards movement
        if(rowDiff <= 0){

            cout<<"Pawns can't move like that."<<endl<<endl;
            return false;
        }
        
        // can only go one collumn over at a time
        else if(abs(colDiff) > 1){

            cout<<"Pawns can't move like that."<<endl<<endl;
            return false;
        }

        // can only move diagonal if there is an enemy peice there
        else if(abs(colDiff) == 1 && rowDiff == 1 && board[num2][letter2].piece == nullptr){
        
            cout<<"There must be an enemy piece at "<<letter2<<num2<<" for you to move there."<<endl<<endl;
            return false;
        }

        // can't move forward with an enemy in front
        else if(rowDiff == 1 && colDiff == 0 && board[num2][letter2].piece != nullptr && board[num2][letter2].piece->player == 1){
        
            cout<<"An enemy piece is blocking your move!"<<endl<<endl;
            return false;
        }

        // taking an enemy pawn
        else if(rowDiff == 1 && abs(colDiff) == 1 && board[num2][letter2].piece->player == 1){

            cout<<"You have taken the enemy's "<<board[num2][letter2].piece->pieceName<<"!"<<endl<<endl;

            board[num2][letter2].piece = board[num1][letter1].piece;    //piece taken
            board[num1][letter1].piece = nullptr;

            return true;
        
        }

        // forward movement
        else{
        
            cout<<"Move successful!"<<endl<<endl;
            board[num2][letter2].piece = board[num1][letter1].piece;
            board[num1][letter1].piece = nullptr;
            
            return true;
        }
    }
    
    else return false;
}

