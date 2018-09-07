#include "Piece.h"
#include "UserInterface.h"
#include <vector>
using namespace std;

//===========================================================
//PIECE IMPLEMTNATION (BASE CLASS) (ABSTRACT CLASS)
//===========================================================
//The code below includes the implementation of my piece base class//

///Piece constructor//
//initializes all bounding boxes of pieces to (3,0) and sets their orientation to 0
Piece::Piece():x(3),y(0), orientation(0)
{}

//Piece setter & getter method implementations//
int Piece::getBoxX()
{
    return x;
}
int Piece::getBoxY()
{
    return y;
}
int Piece::getOrient()
{
    return orientation;
}
void Piece::setBoxX(int value)
{
    x = value;
}
void Piece::setBoxY(int value)
{
    y = value;
}
void Piece::incrementOrient()
{
    //if orientation is 3, reset it back to 0; otherwise, increment it
    if(orientation == 3)
        orientation = 0;
    else
        orientation += 1;
}

//===========================================================
//I-PIECE IMPLEMTNATION
//===========================================================
//The code below includes the implementation of my I-piece//
//orient 0,2 = horizontal//
//orient 1,3 = vertical//

//iPiece constructor//
iPiece::iPiece()
{}

//////////////////////////////////////
//////////////canBeAdded//////////////
//////////////////////////////////////
//checks if piece can be added//
//only used when piece is added in the beginning//
//does not check for outOfBounds//
bool iPiece::canBeAdded(vector<vector<char> > &board)
{
    //checks to see if piece can be inserted at it's current location
    if(board[getBoxX()][getBoxY()+1] != ' ' || board[getBoxX()+1][getBoxY()+1] != ' ' ||  board[getBoxX()+2][getBoxY()+1] != ' ' || board[getBoxX()+3][getBoxY()+1] != ' ')
        return false;
    else
        return true;
}

//////////////////////////////////////
//////////////addToBoard//////////////
//////////////////////////////////////
//adds piece to board//
//does not check for outOfBounds//
bool iPiece::addToBoard(vector<vector<char> > & board)
{
    if(getOrient()==0 || getOrient()==2) //inserts the piece horizontally onto the board
    {
        board[getBoxX()][getBoxY()+1] = '#';
        board[getBoxX()+1][getBoxY()+1] = '#';
        board[getBoxX()+2][getBoxY()+1] = '#';
        board[getBoxX()+3][getBoxY()+1] = '#';
    }
    else                                 //inserts the piece vertically onto the board
    {
        board[getBoxX()+1][getBoxY()] = '#';
        board[getBoxX()+1][getBoxY()+1] = '#';
        board[getBoxX()+1][getBoxY()+2] = '#';
        board[getBoxX()+1][getBoxY()+3] = '#';
    }
    
     //if we succesfully insert, return true
    return true;
}

//////////////////////////////////////
///////////removeFromBoard////////////
//////////////////////////////////////
//removes piece from board//
bool iPiece::removeFromBoard(vector<vector<char> > &board)
{
    //sets everything to empty space based on orientation
    if(getOrient()==0 || getOrient()==2)
    {
        board[getBoxX()][getBoxY()+1] = ' ';
        board[getBoxX()+1][getBoxY()+1] = ' ';
        board[getBoxX()+2][getBoxY()+1] = ' ';
        board[getBoxX()+3][getBoxY()+1] = ' ';
    }
    else
    {
        board[getBoxX()+1][getBoxY()] = ' ';
        board[getBoxX()+1][getBoxY()+1] = ' ';
        board[getBoxX()+1][getBoxY()+2] = ' ';
        board[getBoxX()+1][getBoxY()+3] = ' ';
    }
    
    return true;
}

//////////////////////////////////////
/////////////////fall/////////////////
//////////////////////////////////////
//if possible, checks if we can fall/move down in board//
//if we can't move, returns false//
bool iPiece::fall(vector<vector<char> > & board)
{
     //The following code checks if we are able to move it//
    if((getOrient() == 0 || getOrient() == 2))
    {
         //checks if it hits bottom of well
        if(getBoxY()+2 >= board[0].size())
            return false;
         //checks if it hits another piece
        else if(board[getBoxX()][getBoxY()+2] != ' ' || board[getBoxX()+1][getBoxY()+2] != ' ' || board[getBoxX()+2][getBoxY()+2] != ' ' || board[getBoxX()+3][getBoxY()+2] != ' ')
            return false;
    }
    else if((getOrient() == 1 || getOrient() == 3))
    {
         //checks to see if we're at bottom
        if(getBoxY()+4 >= board[0].size())
           return false;
        else if(board[getBoxX()+1][getBoxY()+4] != ' ' )
            return false;
    }
    
     //The following code actually moves the piece//
    removeFromBoard(board); //erase piece from board
    setBoxY(getBoxY()+1);   //increase y coord of piece
    addToBoard(board);      //re-add piece w/new coords
    
     //returns true if we succesfully fall
    return true;
    
}

//////////////////////////////////////
/////////////moveLeft/////////////////
//////////////////////////////////////
//if possible, checks if we can move left in board//
//if we can't move to left, returns false//
bool iPiece::moveLeft(vector<vector<char> > & board)
{
     //The following code checks if we are able to move it//
    if(getOrient() == 0 || getOrient() == 2)
    {
       if(getBoxX()-1 < 0)                              //checks if its in bounds
           return false;
        else if(board[getBoxX()-1][getBoxY()+1] != ' ') //checks if its empty
            return false;
    }
    else if(getOrient() == 1 || getOrient() == 3)
    {
        if(getBoxX() < 0)
            return false;
        else if(board[getBoxX()][getBoxY()] != ' ' || board[getBoxX()][getBoxY()+1] != ' ' || board[getBoxX()][getBoxY()+2] != ' ' || board[getBoxX()][getBoxY()+3] != ' ' )
            return false;
    }
    
     //The following code actually moves the piece//
    removeFromBoard(board); //erase piece from board
    setBoxX(getBoxX()-1);   //decrease x coord of piece
    addToBoard(board);      //re-add piece w/new coords
    
    return true;
}

//////////////////////////////////////
/////////////moveRight////////////////
//////////////////////////////////////
//if possible, checks if we can move right in board//
//if we can't move to right, returns false//
bool iPiece::moveRight(vector<vector<char> > &board)
{
    
     //The following code checks if we are able to move it//
    if(getOrient() == 0 || getOrient() == 2)
    {
        if(getBoxX()+4 >= board.size())                  //checks if its in bounds
            return false;
        else if(board[getBoxX()+4][getBoxY()+1] != ' ')  //checks if its empty
            return false;
    }
    else if(getOrient() == 1 || getOrient() == 3)
    {
        if(getBoxX()+2 >= board.size())
            return false;
        else if(board[getBoxX()+2][getBoxY()] != ' ' || board[getBoxX()+2][getBoxY()+1] != ' ' || board[getBoxX()+2][getBoxY()+2] != ' ' || board[getBoxX()+2][getBoxY()+3] != ' ' )
            return false;
    }
    
     //The following code actually moves the piece//
    removeFromBoard(board); //erase piece from board
    setBoxX(getBoxX()+1);   //increase x coord of piece
    addToBoard(board);      //re-add piece w/new coords
    
     //return true if we succesfully moved
    return true;
}

//////////////////////////////////////
/////////////rotate()////////////////
//////////////////////////////////////
//if possible, checks if we can rotate in board//
//if we can't rotate, returns false//
bool iPiece::rotate(vector<vector<char> > &board)
{
     //The following code checks to see if we can rotate//
    if(getOrient() == 0 || getOrient() == 2)
    {
        if(getBoxY()+3>= board[0].size())
            return false;
        if(board[getBoxX()+1][getBoxY()] != ' ' || board[getBoxX()+1][getBoxY()+2] != ' ' || board[getBoxX()+1][getBoxY()+3] != ' ')
            return false;
    }
    else if(getOrient() == 1 || getOrient() == 3)
    {
        if(getBoxX()<0 || getBoxX()+3 >= board.size())              //checks bounds
            return false;
        if(board[getBoxX()][getBoxY()+1] != ' ' || board[getBoxX()+2][getBoxY()+1] != ' ' || board[getBoxX()+3][getBoxY()+1] != ' ') //checks for other pieces
            return false;
    }
    
     //The following code actually rotates the piece//
    removeFromBoard(board);
    incrementOrient();
    addToBoard(board);
    
     //returns true if succesfully rotated
    return true;
}

//////////////////////////////////////
/////////////makePerm////////////////
//////////////////////////////////////
//turns # into $//
//used when piece is done falling//
void iPiece::makePerm(vector<vector<char> > &board)
{
     //changes I-piece values to $ depending on its orientation
    if(getOrient()==0 || getOrient()==2)
    {
        board[getBoxX()][getBoxY()+1] = '$';
        board[getBoxX()+1][getBoxY()+1] = '$';
        board[getBoxX()+2][getBoxY()+1] = '$';
        board[getBoxX()+3][getBoxY()+1] = '$';
    }
    else
    {
        board[getBoxX()+1][getBoxY()] = '$';
        board[getBoxX()+1][getBoxY()+1] = '$';
        board[getBoxX()+1][getBoxY()+2] = '$';
        board[getBoxX()+1][getBoxY()+3] = '$';
    }
    
}

//////////////////////////////////////
/////////////printToScreen////////////
//////////////////////////////////////
//draws piece on screen based on x & y parameters//
//used to draw nextPiece thing in the upper right//
void iPiece::printToScreen(Screen &screen, int x, int y)
{
     //prints the piece on the screen w/bounding box at x,y
    for(int i = 0; i<4; i++)
    {
        if(getOrient()==0 || getOrient()==2)
            screen.gotoXY(x+i, y+1);
        else
            screen.gotoXY(x+1, y+i);
        screen.printChar('#');
    }
}

//===========================================================
//O-PIECE IMPLEMTNATION
//===========================================================
//The code below includes the implementation of my O-piece//
//orient 0,1,2,3 are the SAME//

//oPiece constructor//
oPiece::oPiece()
{}

//////////////////////////////////////
//////////////canBeAdded//////////////
//////////////////////////////////////
//checks if piece can be added//
//only used when piece is added in the beginning//
//does not check for outOfBounds//
bool oPiece::canBeAdded(vector<vector<char> > &board)
{
    for(int i = getBoxX(); i < getBoxX()+2; i++)
    {
        for( int j = getBoxY(); j < getBoxY()+2; j++)
        {
            if(board[i][j] != ' ')  //checks that the spots have an empty space
                return false;
        }
    }
    return true;
}

//////////////////////////////////////
//////////////addToBoard//////////////
//////////////////////////////////////
//adds piece to board//
//does not check for outOfBounds//
bool oPiece::addToBoard(vector<vector<char> > & board)
{
    for(int i = getBoxX(); i < getBoxX()+2; i++)
    {
        for( int j = getBoxY(); j < getBoxY()+2; j++)
        {
            board[i][j] = '#';  //adds # to the spots
        }
    }
    
    //if we succesfully insert, return true
    return true;
}

//////////////////////////////////////
///////////removeFromBoard////////////
//////////////////////////////////////
//removes piece from board//
bool oPiece::removeFromBoard(vector<vector<char> > &board)
{
    //sets everything to empty space based on orientation
    for(int i = getBoxX(); i < getBoxX()+2; i++)
    {
        for( int j = getBoxY(); j < getBoxY()+2; j++)
        {
            board[i][j] = ' ';
        }
    }
    
    return true;
}

//////////////////////////////////////
/////////////////fall/////////////////
//////////////////////////////////////
//if possible, checks if we can fall/move down in board//
//if we can't move, returns false//
bool oPiece::fall(vector<vector<char> > & board)
{
    //The following code checks if we are able to move it//
    if(getBoxY()+2 >= board[0].size() || board[getBoxX()][getBoxY()+2] != ' ' || board[getBoxX()+1][getBoxY()+2] != ' ')
        return false;
    
    //The following code actually moves the piece//
    removeFromBoard(board); //erase piece from board
    setBoxY(getBoxY()+1);   //increase y coord of piece
    addToBoard(board);      //re-add piece w/new coords
    
    //returns true if we succesfully fall
    return true;
    
}

//////////////////////////////////////
/////////////moveLeft/////////////////
//////////////////////////////////////
//if possible, checks if we can move left in board//
//if we can't move to left, returns false//
bool oPiece::moveLeft(vector<vector<char> > & board)
{
    //The following code checks if we are able to move it//
    if(getBoxX()-1 < 0)                              //checks if its in bounds
        return false;
    else if(board[getBoxX()-1][getBoxY()] != ' ' || board[getBoxX()-1][getBoxY()+1] != ' '  ) //checks if its empty
        return false;
    
    //The following code actually moves the piece//
    removeFromBoard(board); //erase piece from board
    setBoxX(getBoxX()-1);   //decrease x coord of piece
    addToBoard(board);      //re-add piece w/new coords
    
    return true;
}

//////////////////////////////////////
/////////////moveRight////////////////
//////////////////////////////////////
//if possible, checks if we can move right in board//
//if we can't move to right, returns false//
bool oPiece::moveRight(vector<vector<char> > &board)
{
    
    //The following code checks if we are able to move it//
    if(getBoxX()+2 >= board.size())
        return false;
    else if(board[getBoxX()+2][getBoxY()] != ' ' || board[getBoxX()+2][getBoxY()+1] != ' ')
        return false;
    
    //The following code actually moves the piece//
    removeFromBoard(board); //erase piece from board
    setBoxX(getBoxX()+1);   //increase x coord of piece
    addToBoard(board);      //re-add piece w/new coords
    
    //return true if we succesfully moved
    return true;
}

//////////////////////////////////////
/////////////rotate()////////////////
//////////////////////////////////////
//if possible, checks if we can rotate in board//
//if we can't rotate, returns false//
bool oPiece::rotate(vector<vector<char> > &board)
{
     //oPiece can always be rotated
    return true;
}

//////////////////////////////////////
/////////////makePerm////////////////
//////////////////////////////////////
//turns # into $//
//used when piece is done falling//
void oPiece::makePerm(vector<vector<char> > &board)
{
    for(int i = getBoxX(); i < getBoxX()+2; i++)
    {
        for( int j = getBoxY(); j < getBoxY()+2; j++)
        {
            board[i][j] = '$';
        }
    }
}

//////////////////////////////////////
/////////////printToScreen////////////
//////////////////////////////////////
//draws piece on screen based on x & y parameters//
//used to draw nextPiece thing in the upper right//
void oPiece::printToScreen(Screen &screen, int x, int y)
{
    //prints the piece on the screen w/bounding box at x,y
    for(int i = 0; i<2; i++)
    {
        for( int j = 0; j<2; j++)
        {
            screen.gotoXY(x+i,y+j);
            screen.printChar('#');
        }
    }
}

//===========================================================
//T-PIECE IMPLEMTNATION
//===========================================================
//The code below includes the implementation of my T-piece//
//orient 0,1,2,3 are all different//

//tPiece constructor//
tPiece::tPiece()
{}

//////////////////////////////////////
//////////////canBeAdded//////////////
//////////////////////////////////////
//checks if piece can be added//
//only used when piece is added in the beginning//
//does not check for outOfBounds//
bool tPiece::canBeAdded(vector<vector<char> > &board)
{
     //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    switch(getOrient())
    {
         //checks if there is room for each orientation
        case 0:
            if(board[x+1][y] != ' ' || board[x+1][y+1] != ' ' || board[x][y+1] != ' ' || board[x+2][y+1] != ' ')
                return false;
            break;
        case 1:
            if(board[x+1][y] != ' ' || board[x+1][y+1] != ' ' || board[x+1][y+2] != ' ' || board[x+2][y+1] != ' ')
                return false;
            break;
        case 2:
            if(board[x+1][y+1] != ' ' || board[x][y+1] != ' ' || board[x+2][y+1] != ' ' || board[x+1][y+2] != ' ')
                return false;
            break;
        case 3:
            if(board[x+1][y] != ' ' || board[x+1][y+1] != ' ' || board[x][y+1] != ' ' || board[x+1][y+2] != ' ')
                return false;
            break;
    }
    
     //returns true if there is room
    return true;
}

//////////////////////////////////////
//////////////addToBoard//////////////
//////////////////////////////////////
//adds piece to board//
//does not check for outOfBounds//
bool tPiece::addToBoard(vector<vector<char> > & board)
{
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();

    switch(getOrient())
    {
         //adds each piece to board based on orientation
        case 0:
            board[x+1][y] = '#';
            board[x+1][y+1] = '#';
            board[x][y+1] = '#';
            board[x+2][y+1] = '#';
            break;
        case 1:
            board[x+1][y] = '#';
            board[x+1][y+1] = '#';
            board[x+1][y+2] = '#';
            board[x+2][y+1] = '#';
            break;
        case 2:
            board[x+1][y+1] = '#';
            board[x][y+1] = '#';
            board[x+2][y+1] = '#';
            board[x+1][y+2] = '#';
            break;
        case 3:
            board[x+1][y] = '#';
            board[x+1][y+1] = '#';
            board[x][y+1] = '#';
            board[x+1][y+2] = '#';
            break;
    }
    
     //if we succesfully insert, return true
    return true;
}

//////////////////////////////////////
///////////removeFromBoard////////////
//////////////////////////////////////
//removes piece from board//
bool tPiece::removeFromBoard(vector<vector<char> > &board)
{
    //sets everything to empty space based on orientation
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    switch(getOrient())
    {
         //adds each piece to board based on orientation
        case 0:
            board[x+1][y] = ' ';
            board[x+1][y+1] = ' ';
            board[x][y+1] = ' ';
            board[x+2][y+1] = ' ';
            break;
        case 1:
            board[x+1][y] = ' ';
            board[x+1][y+1] = ' ';
            board[x+1][y+2] = ' ';
            board[x+2][y+1] = ' ';
            break;
        case 2:
            board[x+1][y+1] = ' ';
            board[x][y+1] = ' ';
            board[x+2][y+1] = ' ';
            board[x+1][y+2] = ' ';
            break;
        case 3:
            board[x+1][y] = ' ';
            board[x+1][y+1] = ' ';
            board[x][y+1] = ' ';
            board[x+1][y+2] = ' ';
            break;
    }
    
     //if we successfully remove, return true
    return true;
}

//////////////////////////////////////
/////////////////fall/////////////////
//////////////////////////////////////
//if possible, checks if we can fall/move down in board//
//if we can't move, returns false//
bool tPiece::fall(vector<vector<char> > & board)
{
     //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
     //The following code checks if we are able to move it//
    switch(getOrient())
    {
         //adds each piece to board based on orientation
        case 0:
            if(y+2>= board[0].size())   //checks board
                return false;
            if(board[x][y+2] != ' ' || board[x+1][y+2] != ' ' || board [x+2][y+2] != ' ') //checks that its empty
                return false;
            break;
        case 1:
            if(y+3 >= board[0].size())  //checks board
                return false;
            if(board[x+1][y+3] != ' ' || board[x+2][y+2] != ' ')  //checks that its empty
                return false;
            break;
        case 2:
            if(y+3 >= board[0].size())  //checks board
                return false;
            if(board[x+1][y+3] != ' ' || board[x][y+2] != ' ' || board[x+2][y+2] != ' ')  //checks that its empty
                return false;
            break;
        case 3:
            if(y+3 >= board[0].size())  //checks board
                return false;
            if(board[x+1][y+3] != ' ' || board[x][y+2] != ' ')  //checks that its empty
                return false;
            break;
    }
    
    //The following code actually moves the piece//
    removeFromBoard(board); //erase piece from board
    setBoxY(getBoxY()+1);   //increase y coord of piece
    addToBoard(board);      //re-add piece w/new coords
    
    //returns true if we succesfully fall
    return true;
    
}

//////////////////////////////////////
/////////////moveLeft/////////////////
//////////////////////////////////////
//if possible, checks if we can move left in board//
//if we can't move to left, returns false//
bool tPiece::moveLeft(vector<vector<char> > & board)
{
    //The following code checks if we are able to move it//
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    //The following code checks if we are able to move it//
    switch(getOrient())
    {
            //adds each piece to board based on orientation
        case 0:
            if(x-1 < 0)                   //checks board
                return false;
            if(board[x-1][y+1] != ' ' || board[x][y] != ' ')    //checks that its empty
                return false;
            break;
        case 2:
            if(x-1 < 0)                   //checks board
                return false;
            if(board[x-1][y+1] != ' ' || board[x][y+2] != ' ')    //checks that its empty
                return false;
            break;
        case 3:
            if(x-1 < 0)                   //checks board
                return false;
            if(board[x-1][y+1] != ' ' || board[x][y] != ' ' || board[x][y+2] != ' ')    //checks that its empty
                return false;
            break;
        case 1:
            if(x < 0)                     //checks board
                return false;
            if(board[x][y] != ' ' || board[x][y+1] != ' ' || board[x][y+2] != ' ' ) //checks that its empty
                return false;
            break;
    }
    
    //The following code actually moves the piece//
    removeFromBoard(board); //erase piece from board
    setBoxX(getBoxX()-1);   //decrease x coord of piece
    addToBoard(board);      //re-add piece w/new coords
    
    return true;
}

//////////////////////////////////////
/////////////moveRight////////////////
//////////////////////////////////////
//if possible, checks if we can move right in board//
//if we can't move to right, returns false//
bool tPiece::moveRight(vector<vector<char> > &board)
{
    
    //The following code checks if we are able to move it//
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    //The following code checks if we are able to move it//
    switch(getOrient())
    {
            //adds each piece to board based on orientation
        case 0:
            if(x+3 >= board.size())                   //checks board
                return false;
            if(board[x+3][y+1] != ' ' || board[x+2][y] != ' ')    //checks that its empty
                return false;
            break;
        case 1:
            if(x+3 >= board.size())                   //checks board
                return false;
            if(board[x+3][y+1] != ' ' || board[x+2][y] != ' ' || board[x+2][y+2] != ' ')    //checks that its empty
                return false;
            break;
        case 2:
            if(x+3 >= board.size())                   //checks board
                return false;
            if(board[x+3][y+1] != ' ' || board[x+2][y+2] != ' ')    //checks that its empty
                return false;
            break;
        case 3:
            if(x+2 >= board.size())                     //checks board
                return false;
            if(board[x+2][y] != ' ' || board[x+2][y+1] != ' ' || board[x+2][y+2] != ' ' ) //checks that its empty
                return false;
            break;
    }
    
    //The following code actually moves the piece//
    removeFromBoard(board); //erase piece from board
    setBoxX(getBoxX()+1);   //increase x coord of piece
    addToBoard(board);      //re-add piece w/new coords
    
    //return true if we succesfully moved
    return true;
}

//////////////////////////////////////
/////////////rotate()////////////////
//////////////////////////////////////
//if possible, checks if we can rotate in board//
//if we can't rotate, returns false//
bool tPiece::rotate(vector<vector<char> > &board)
{
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    //The following code checks if piece can be rotated//
    switch(getOrient())
    {
            //adds each piece to board based on orientation
        case 0:
            if(y+2 >= board[0].size())  //checks board
                return false;
            if(board[x+1][y+2] != ' ')  //checks that its empty
                return false;
            break;
        case 1:
            if(x <0)                    //checks board
                return false;
            if(board[x][y+1] != ' ')    //checks that its empty
                return false;
            break;
        case 2:
            if(y < 0)                   //checks board
                return false;
            if(board[x+1][y] != ' ')    //checks that its empty
                return false;
            break;
        case 3:
            if(x+2 >= board.size())     //checks board
                return false;
            if(board[x+2][y+1] != ' ')    //checks that its empty
                return false;
            break;
    }
    
    //The following code actually rotates the piece//
    removeFromBoard(board);
    incrementOrient();
    addToBoard(board);
    
    //returns true if succesfully rotated
    return true;
}

//////////////////////////////////////
/////////////makePerm////////////////
//////////////////////////////////////
//turns # into $//
//used when piece is done falling//
void tPiece::makePerm(vector<vector<char> > &board)
{
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    switch(getOrient())
    {
            //adds each piece to board based on orientation
        case 0:
            board[x+1][y] = '$';
            board[x+1][y+1] = '$';
            board[x][y+1] = '$';
            board[x+2][y+1] = '$';
            break;
        case 1:
            board[x+1][y] = '$';
            board[x+1][y+1] = '$';
            board[x+1][y+2] = '$';
            board[x+2][y+1] = '$';
            break;
        case 2:
            board[x+1][y+1] = '$';
            board[x][y+1] = '$';
            board[x+2][y+1] = '$';
            board[x+1][y+2] = '$';
            break;
        case 3:
            board[x+1][y] = '$';
            board[x+1][y+1] = '$';
            board[x][y+1] = '$';
            board[x+1][y+2] = '$';
            break;
    }
}

//////////////////////////////////////
/////////////printToScreen////////////
//////////////////////////////////////
//draws piece on screen based on x & y parameters//
//used to draw nextPiece thing in the upper right//
//only deals with orientation 0//
void tPiece::printToScreen(Screen &screen, int x, int y)
{
    //prints the piece on the screen w/bounding box at x,y
    screen.gotoXY(x+1,y);
    screen.printChar('#');
    screen.gotoXY(x+1,y+1);
    screen.printChar('#');
    screen.gotoXY(x,y+1);
    screen.printChar('#');
    screen.gotoXY(x+2,y+1);
    screen.printChar('#');
}

//===========================================================
//L-PIECE IMPLEMTNATION
//===========================================================
//The code below includes the implementation of my L-piece//
//orient 0,1,2,3 are all different//

//lPiece constructor//
lPiece::lPiece()
{}

//////////////////////////////////////
//////////////canBeAdded//////////////
//////////////////////////////////////
//checks if piece can be added//
//only used when piece is added in the beginning//
//does not check for outOfBounds//
bool lPiece::canBeAdded(vector<vector<char> > &board)
{
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    switch(getOrient())
    {
            //checks if there is room for each orientation
        case 0:
            if(board[x][y+1] != ' ' || board[x][y+2] != ' ' || board[x+1][y+1] != ' ' || board[x+2][y+1] != ' ')
                return false;
            break;
        case 1:
            if(board[x+1][y] != ' ' || board[x+2][y] != ' ' || board[x+2][y+1] != ' ' || board[x+2][y+2] != ' ')
                return false;
            break;
        case 2:
            if(board[x][y+2] != ' ' || board[x+1][y+2] != ' ' || board[x+2][y+2] != ' ' || board[x+2][y+1] != ' ')
                return false;
            break;
        case 3:
            if(board[x+1][y+1] != ' ' || board[x+1][y+2] != ' ' || board[x+1][y+3] != ' ' || board[x+2][y+3] != ' ')
                return false;
            break;
    }
    
    //returns true if there is room
    return true;
}

//////////////////////////////////////
//////////////addToBoard//////////////
//////////////////////////////////////
//adds piece to board//
//does not check for outOfBounds//
bool lPiece::addToBoard(vector<vector<char> > & board)
{
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    switch(getOrient())
    {
            //adds each piece to board based on orientation
        case 0:
            board[x][y+1] = '#';
            board[x][y+2] = '#';
            board[x+1][y+1] = '#';
            board[x+2][y+1] = '#';
            break;
        case 1:
            board[x+1][y] = '#';
            board[x+2][y] = '#';
            board[x+2][y+1] = '#';
            board[x+2][y+2] = '#';
            break;
        case 2:
            board[x][y+2] = '#';
            board[x+1][y+2] = '#';
            board[x+2][y+2] = '#';
            board[x+2][y+1] = '#';
            break;
        case 3:
            board[x+1][y+1] = '#';
            board[x+1][y+2] = '#';
            board[x+1][y+3] = '#';
            board[x+2][y+3] = '#';
            break;
    }
    
    //if we succesfully insert, return true
    return true;
}

//////////////////////////////////////
///////////removeFromBoard////////////
//////////////////////////////////////
//removes piece from board//
bool lPiece::removeFromBoard(vector<vector<char> > &board)
{
    //sets everything to empty space based on orientation
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    switch(getOrient())
    {
            //adds each piece to board based on orientation
        case 0:
            board[x][y+1] = ' ';
            board[x][y+2] = ' ';
            board[x+1][y+1] = ' ';
            board[x+2][y+1] = ' ';
            break;
        case 1:
            board[x+1][y] = ' ';
            board[x+2][y] = ' ';
            board[x+2][y+1] = ' ';
            board[x+2][y+2] = ' ';
            break;
        case 2:
            board[x][y+2] = ' ';
            board[x+1][y+2] = ' ';
            board[x+2][y+2] = ' ';
            board[x+2][y+1] = ' ';
            break;
        case 3:
            board[x+1][y+1] = ' ';
            board[x+1][y+2] = ' ';
            board[x+1][y+3] = ' ';
            board[x+2][y+3] = ' ';
            break;
    }
    
    //if we successfully remove, return true
    return true;
}

//////////////////////////////////////
/////////////////fall/////////////////
//////////////////////////////////////
//if possible, checks if we can fall/move down in board//
//if we can't move, returns false//
bool lPiece::fall(vector<vector<char> > & board)
{
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    //The following code checks if we are able to move it//
    switch(getOrient())
    {
            //adds each piece to board based on orientation
        case 0:
            if(y+3>= board[0].size())   //checks board
                return false;
            if(board[x][y+3] != ' ' || board[x+1][y+2] != ' ' || board [x+2][y+2] != ' ') //checks that its empty
                return false;
            break;
        case 1:
            if(y+3 >= board[0].size())  //checks board
                return false;
            if(board[x+1][y+1] != ' ' || board[x+2][y+3] != ' ')  //checks that its empty
                return false;
            break;
        case 2:
            if(y+3 >= board[0].size())  //checks board
                return false;
            if(board[x][y+3] != ' ' || board[x+1][y+3] != ' ' || board[x+2][y+3] != ' ')  //checks that its empty
                return false;
            break;
        case 3:
            if(y+4 >= board[0].size())  //checks board
                return false;
            if(board[x+1][y+4] != ' ' || board[x+2][y+4] != ' ')  //checks that its empty
                return false;
            break;
    }
    
    //The following code actually moves the piece//
    removeFromBoard(board); //erase piece from board
    setBoxY(getBoxY()+1);   //increase y coord of piece
    addToBoard(board);      //re-add piece w/new coords
    
    //returns true if we succesfully fall
    return true;
    
}

//////////////////////////////////////
/////////////moveLeft/////////////////
//////////////////////////////////////
//if possible, checks if we can move left in board//
//if we can't move to left, returns false//
bool lPiece::moveLeft(vector<vector<char> > & board)
{
    //The following code checks if we are able to move it//
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    //The following code checks if we are able to move it//
    switch(getOrient())
    {
            //adds each piece to board based on orientation
        case 0:
            if(x-1 < 0)                   //checks board
                return false;
            if(board[x-1][y+1] != ' ' || board[x-1][y+2] != ' ')    //checks that its empty
                return false;
            break;
        case 1:
            if(x < 0)                     //checks board
                return false;
            if(board[x][y] != ' ' || board[x+1][y+1] != ' ' || board[x+1][y+2] != ' ')    //checks that its empty
                return false;
            break;
        case 2:
            if(x-1 < 0)                   //checks board
                return false;
            if(board[x-1][y+2] != ' ' || board[x+1][y+1] != ' ')    //checks that its empty
                return false;
            break;
        case 3:
            if(x < 0)                     //checks board
                return false;
            if(board[x][y+1] != ' ' || board[x][y+2] != ' ' || board[x][y+3] != ' ' ) //checks that its empty
                return false;
            break;
    }
    
    //The following code actually moves the piece//
    removeFromBoard(board); //erase piece from board
    setBoxX(getBoxX()-1);   //decrease x coord of piece
    addToBoard(board);      //re-add piece w/new coords
    
    return true;
}

//////////////////////////////////////
/////////////moveRight////////////////
//////////////////////////////////////
//if possible, checks if we can move right in board//
//if we can't move to right, returns false//
bool lPiece::moveRight(vector<vector<char> > &board)
{
    
    //The following code checks if we are able to move it//
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    //The following code checks if we are able to move it//
    switch(getOrient())
    {
            //adds each piece to board based on orientation
        case 0:
            if(x+3 >= board.size())                   //checks board
                return false;
            if(board[x+3][y+1] != ' ' || board[x+1][y+2] != ' ')    //checks that its empty
                return false;
            break;
        case 1:
            if(x+3 >= board.size())                   //checks board
                return false;
            if(board[x+3][y] != ' ' || board[x+3][y+1] != ' ' || board[x+3][y+2] != ' ')    //checks that its empty
                return false;
            break;
        case 2:
            if(x+3 >= board.size())                   //checks board
                return false;
            if(board[x+3][y+1] != ' ' || board[x+3][y+2] != ' ')    //checks that its empty
                return false;
            break;
        case 3:
            if(x+3 >= board.size())                     //checks board
                return false;
            if(board[x+2][y+1] != ' ' || board[x+2][y+2] != ' ' || board[x+3][y+3] != ' ' ) //checks that its empty
                return false;
            break;
    }
    
    //The following code actually moves the piece//
    removeFromBoard(board); //erase piece from board
    setBoxX(getBoxX()+1);   //increase x coord of piece
    addToBoard(board);      //re-add piece w/new coords
    
    //return true if we succesfully moved
    return true;
}

//////////////////////////////////////
/////////////rotate()////////////////
//////////////////////////////////////
//if possible, checks if we can rotate in board//
//if we can't rotate, returns false//
bool lPiece::rotate(vector<vector<char> > &board)
{
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    //The following code checks if piece can be rotated//
    switch(getOrient())
    {
        //adds each piece to board based on orientation
        case 0:
            if(y < 0)                   //checks board
                return false;
            if(board[x+1][y] != ' ' || board[x+2][y] != ' ' || board[x+2][y+2] != ' ')  //checks that its empty
                return false;
            break;
        case 1:
            if(x < 0)
                return false;
            if(board[x][y+2] != ' ' || board[x+1][y+2] != ' ')    //checks that its empty
                return false;
            break;
        case 2:
            if(y+3 >= board[0].size())   //checks board
                return false;
            if(board[x+1][y+1] != ' ' || board[x+1][y+3] != ' ' || board[x+2][y+3] != ' ')    //checks that its empty
                return false;
            break;
        case 3:
            if(x < 0)      //checks board
                return false;
            if(board[x][y+1] != ' ' || board[x][y+2] != ' ' || board[x+2][y+1] != ' ')    //checks that its empty
                return false;
            break;
    }
    
    //The following code actually rotates the piece//
    removeFromBoard(board);
    incrementOrient();
    addToBoard(board);
    
    //returns true if succesfully rotated
    return true;
}

//////////////////////////////////////
/////////////makePerm////////////////
//////////////////////////////////////
//turns # into $//
//used when piece is done falling//
void lPiece::makePerm(vector<vector<char> > &board)
{
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    switch(getOrient())
    {
            //changes # to $
        case 0:
            board[x][y+1] = '$';
            board[x][y+2] = '$';
            board[x+1][y+1] = '$';
            board[x+2][y+1] = '$';
            break;
        case 1:
            board[x+1][y] = '$';
            board[x+2][y] = '$';
            board[x+2][y+1] = '$';
            board[x+2][y+2] = '$';
            break;
        case 2:
            board[x][y+2] = '$';
            board[x+1][y+2] = '$';
            board[x+2][y+2] = '$';
            board[x+2][y+1] = '$';
            break;
        case 3:
            board[x+1][y+1] = '$';
            board[x+1][y+2] = '$';
            board[x+1][y+3] = '$';
            board[x+2][y+3] = '$';
            break;
    }
}

//////////////////////////////////////
/////////////printToScreen////////////
//////////////////////////////////////
//draws piece on screen based on x & y parameters//
//used to draw nextPiece thing in the upper right//
//only deals with orientation 0//
void lPiece::printToScreen(Screen &screen, int x, int y)
{
    //prints the piece on the screen w/bounding box at x,y
    screen.gotoXY(x,y+1);
    screen.printChar('#');
    screen.gotoXY(x,y+2);
    screen.printChar('#');
    screen.gotoXY(x+1,y+1);
    screen.printChar('#');
    screen.gotoXY(x+2,y+1);
    screen.printChar('#');
}

//===========================================================
//J-PIECE IMPLEMTNATION
//===========================================================
//The code below includes the implementation of my J-piece//
//orient 0,1,2,3 are all different//

//jPiece constructor//
jPiece::jPiece()
{}

//////////////////////////////////////
//////////////canBeAdded//////////////
//////////////////////////////////////
//checks if piece can be added//
//only used when piece is added in the beginning//
//does not check for outOfBounds//
bool jPiece::canBeAdded(vector<vector<char> > &board)
{
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    switch(getOrient())
    {
            //checks if there is room for each orientation
        case 0:
            if(board[x+3][y+1] != ' ' || board[x+3][y+2] != ' ' || board[x+1][y+1] != ' ' || board[x+2][y+1] != ' ')
                return false;
            break;
        case 1:
            if(board[x+1][y+3] != ' ' || board[x+2][y+3] != ' ' || board[x+2][y+1] != ' ' || board[x+2][y+2] != ' ')
                return false;
            break;
        case 2:
            if(board[x+1][y+1] != ' ' || board[x+1][y+2] != ' ' || board[x+2][y+2] != ' ' || board[x+3][y+2] != ' ')
                return false;
            break;
        case 3:
            if(board[x+2][y] != ' ' || board[x+1][y] != ' ' || board[x+1][y+1] != ' ' || board[x+1][y+2] != ' ')
                return false;
            break;
    }
    
    //returns true if there is room
    return true;
}

//////////////////////////////////////
//////////////addToBoard//////////////
//////////////////////////////////////
//adds piece to board//
//does not check for outOfBounds//
bool jPiece::addToBoard(vector<vector<char> > & board)
{
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    switch(getOrient())
    {
            //adds each piece to board based on orientation
        case 0:
            board[x+1][y+1] = '#';
            board[x+2][y+1] = '#';
            board[x+3][y+1] = '#';
            board[x+3][y+2] = '#';
            break;
        case 1:
            board[x+2][y+1] = '#';
            board[x+2][y+2] = '#';
            board[x+2][y+3] = '#';
            board[x+1][y+3] = '#';
            break;
        case 2:
            board[x+1][y+1] = '#';
            board[x+1][y+2] = '#';
            board[x+2][y+2] = '#';
            board[x+3][y+2] = '#';
            break;
        case 3:
            board[x+1][y+1] = '#';
            board[x+2][y] = '#';
            board[x+1][y] = '#';
            board[x+1][y+2] = '#';
            break;
    }
    
    //if we succesfully insert, return true
    return true;
}

//////////////////////////////////////
///////////removeFromBoard////////////
//////////////////////////////////////
//removes piece from board//
bool jPiece::removeFromBoard(vector<vector<char> > &board)
{
    //sets everything to empty space based on orientation
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    switch(getOrient())
    {
            //adds each piece to board based on orientation
        case 0:
            board[x+1][y+1] = ' ';
            board[x+2][y+1] = ' ';
            board[x+3][y+1] = ' ';
            board[x+3][y+2] = ' ';
            break;
        case 1:
            board[x+2][y+1] = ' ';
            board[x+2][y+2] = ' ';
            board[x+2][y+3] = ' ';
            board[x+1][y+3] = ' ';
            break;
        case 2:
            board[x+1][y+1] = ' ';
            board[x+1][y+2] = ' ';
            board[x+2][y+2] = ' ';
            board[x+3][y+2] = ' ';
            break;
        case 3:
            board[x+1][y+1] = ' ';
            board[x+2][y] = ' ';
            board[x+1][y] = ' ';
            board[x+1][y+2] = ' ';
            break;
    }
    
    //if we successfully remove, return true
    return true;
}

//////////////////////////////////////
/////////////////fall/////////////////
//////////////////////////////////////
//if possible, checks if we can fall/move down in board//
//if we can't move, returns false//
bool jPiece::fall(vector<vector<char> > & board)
{
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    //The following code checks if we are able to move it//
    switch(getOrient())
    {
            //adds each piece to board based on orientation
        case 0:
            if(y+3>= board[0].size())   //checks board
                return false;
            if(board[x+1][y+2] != ' ' || board[x+2][y+2] != ' ' || board [x+3][y+3] != ' ') //checks that its empty
                return false;
            break;
        case 1:
            if(y+4 >= board[0].size())  //checks board
                return false;
            if(board[x+1][y+4] != ' ' || board[x+2][y+4] != ' ')  //checks that its empty
                return false;
            break;
        case 2:
            if(y+3 >= board[0].size())  //checks board
                return false;
            if(board[x+1][y+3] != ' ' || board[x+2][y+3] != ' ' || board[x+3][y+3] != ' ')  //checks that its empty
                return false;
            break;
        case 3:
            if(y+3 >= board[0].size())  //checks board
                return false;
            if(board[x+1][y+3] != ' ' || board[x+2][y+1] != ' ')  //checks that its empty
                return false;
            break;
    }
    
    //The following code actually moves the piece//
    removeFromBoard(board); //erase piece from board
    setBoxY(getBoxY()+1);   //increase y coord of piece
    addToBoard(board);      //re-add piece w/new coords
    
    //returns true if we succesfully fall
    return true;
    
}

//////////////////////////////////////
/////////////moveLeft/////////////////
//////////////////////////////////////
//if possible, checks if we can move left in board//
//if we can't move to left, returns false//
bool jPiece::moveLeft(vector<vector<char> > & board)
{
    //The following code checks if we are able to move it//
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    //The following code checks if we are able to move it//
    switch(getOrient())
    {
            //adds each piece to board based on orientation
        case 0:
            if(x < 0)                   //checks board
                return false;
            if(board[x][y+1] != ' ' || board[x+2][y+2] != ' ')    //checks that its empty
                return false;
            break;
        case 1:
            if(x < 0)                     //checks board
                return false;
            if(board[x][y+3] != ' ' || board[x+1][y+2] != ' ' || board[x+1][y+1] != ' ')    //checks that its empty
                return false;
            break;
        case 2:
            if(x < 0)                   //checks board
                return false;
            if(board[x][y+1] != ' ' || board[x][y+2] != ' ')    //checks that its empty
                return false;
            break;
        case 3:
            if(x < 0)                     //checks board
                return false;
            if(board[x][y+1] != ' ' || board[x][y+2] != ' ' || board[x][y] != ' ' ) //checks that its empty
                return false;
            break;
    }
    
    //The following code actually moves the piece//
    removeFromBoard(board); //erase piece from board
    setBoxX(getBoxX()-1);   //decrease x coord of piece
    addToBoard(board);      //re-add piece w/new coords
    
    return true;
}

//////////////////////////////////////
/////////////moveRight////////////////
//////////////////////////////////////
//if possible, checks if we can move right in board//
//if we can't move to right, returns false//
bool jPiece::moveRight(vector<vector<char> > &board)
{
    
    //The following code checks if we are able to move it//
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    //The following code checks if we are able to move it//
    switch(getOrient())
    {
            //adds each piece to board based on orientation
        case 0:
            if(x+4 >= board.size())                   //checks board
                return false;
            if(board[x+4][y+1] != ' ' || board[x+4][y+2] != ' ')    //checks that its empty
                return false;
            break;
        case 1:
            if(x+3 >= board.size())                   //checks board
                return false;
            if(board[x+3][y+3] != ' ' || board[x+3][y+1] != ' ' || board[x+3][y+2] != ' ')    //checks that its empty
                return false;
            break;
        case 2:
            if(x+4 >= board.size())                   //checks board
                return false;
            if(board[x+2][y+1] != ' ' || board[x+4][y+2] != ' ')    //checks that its empty
                return false;
            break;
        case 3:
            if(x+3 >= board.size())                     //checks board
                return false;
            if(board[x+3][y] != ' ' || board[x+2][y+2] != ' ' || board[x+2][y+1] != ' ' ) //checks that its empty
                return false;
            break;
    }
    
    //The following code actually moves the piece//
    removeFromBoard(board); //erase piece from board
    setBoxX(getBoxX()+1);   //increase x coord of piece
    addToBoard(board);      //re-add piece w/new coords
    
    //return true if we succesfully moved
    return true;
}

//////////////////////////////////////
/////////////rotate()////////////////
//////////////////////////////////////
//if possible, checks if we can rotate in board//
//if we can't rotate, returns false//
bool jPiece::rotate(vector<vector<char> > &board)
{
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    //The following code checks if piece can be rotated//
    switch(getOrient())
    {
            //adds each piece to board based on orientation
        case 0:
            if(y+3 >= board[0].size())                   //checks board
                return false;
            if(board[x+2][y+2] != ' ' || board[x+2][y+3] != ' ' || board[x+1][y+3] != ' ')  //checks that its empty
                return false;
            break;
        case 1:
            if(x+3 >= board.size())
                return false;
            if(board[x+3][y+2] != ' ' || board[x+1][y+2] != ' ' || board[x+1][y+1] != ' ')    //checks that its empty
                return false;
            break;
        case 2:
            if(y < 0)   //checks board
                return false;
            if(board[x+1][y] != ' ' || board[x+2][y] != ' ')    //checks that its empty
                return false;
            break;
        case 3:
            if(x+3 >= board.size())      //checks board
                return false;
            if(board[x+2][y+1] != ' ' || board[x+3][y+1] != ' ' || board[x+3][y+2] != ' ')    //checks that its empty
                return false;
            break;
    }
    
    //The following code actually rotates the piece//
    removeFromBoard(board);
    incrementOrient();
    addToBoard(board);
    
    //returns true if succesfully rotated
    return true;
}

//////////////////////////////////////
/////////////makePerm////////////////
//////////////////////////////////////
//turns # into $//
//used when piece is done falling//
void jPiece::makePerm(vector<vector<char> > &board)
{
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    switch(getOrient())
    {
            //adds each piece to board based on orientation
        case 0:
            board[x+1][y+1] = '$';
            board[x+2][y+1] = '$';
            board[x+3][y+1] = '$';
            board[x+3][y+2] = '$';
            break;
        case 1:
            board[x+2][y+1] = '$';
            board[x+2][y+2] = '$';
            board[x+2][y+3] = '$';
            board[x+1][y+3] = '$';
            break;
        case 2:
            board[x+1][y+1] = '$';
            board[x+1][y+2] = '$';
            board[x+2][y+2] = '$';
            board[x+3][y+2] = '$';
            break;
        case 3:
            board[x+1][y+1] = '$';
            board[x+2][y] = '$';
            board[x+1][y] = '$';
            board[x+1][y+2] = '$';
            break;
    }
}

//////////////////////////////////////
/////////////printToScreen////////////
//////////////////////////////////////
//draws piece on screen based on x & y parameters//
//used to draw nextPiece thing in the upper right//
//only deals with orientation 0//
void jPiece::printToScreen(Screen &screen, int x, int y)
{
    //prints the piece on the screen w/bounding box at x,y
    screen.gotoXY(x+1,y+1);
    screen.printChar('#');
    screen.gotoXY(x+2,y+1);
    screen.printChar('#');
    screen.gotoXY(x+3,y+1);
    screen.printChar('#');
    screen.gotoXY(x+3,y+2);
    screen.printChar('#');
}

//===========================================================
//S-PIECE IMPLEMTNATION
//===========================================================
//The code below includes the implementation of my S-piece//
//orient 0, 2 same//
//orient 1, 3 same//

//sPiece constructor//
sPiece::sPiece()
{}

//////////////////////////////////////
//////////////canBeAdded//////////////
//////////////////////////////////////
//checks if piece can be added//
//only used when piece is added in the beginning//
//does not check for outOfBounds//
//can be added is only used at orientation 0//
bool sPiece::canBeAdded(vector<vector<char> > &board)
{
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();

    //checks if theres space for s-piece orientation 0
    if(board[x][y+2] != ' ' || board[x+1][y+1] != ' ' || board[x+1][y+2] != ' ' || board[x+2][y+1] != ' ')
        return false;
    
    //returns true if there is room
    return true;
}

//////////////////////////////////////
//////////////addToBoard//////////////
//////////////////////////////////////
//adds piece to board//
//does not check for outOfBounds//
bool sPiece::addToBoard(vector<vector<char> > & board)
{
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    switch(getOrient())
    {
            //adds each piece to board based on orientation
        case 0:
        case 2:
            board[x][y+2] = '#';
            board[x+1][y+1] = '#';
            board[x+1][y+2] = '#';
            board[x+2][y+1] = '#';
            break;
        case 1:
        case 3:
            board[x+1][y] = '#';
            board[x+1][y+1] = '#';
            board[x+2][y+1] = '#';
            board[x+2][y+2] = '#';
            break;
    }
    
    //if we succesfully insert, return true
    return true;
}

//////////////////////////////////////
///////////removeFromBoard////////////
//////////////////////////////////////
//removes piece from board//
bool sPiece::removeFromBoard(vector<vector<char> > &board)
{
    //sets everything to empty space based on orientation
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    switch(getOrient())
    {
            //adds each piece to board based on orientation
        case 0:
        case 2:
            board[x][y+2] = ' ';
            board[x+1][y+1] = ' ';
            board[x+1][y+2] = ' ';
            board[x+2][y+1] = ' ';
            break;
        case 1:
        case 3:
            board[x+1][y] = ' ';
            board[x+1][y+1] = ' ';
            board[x+2][y+1] = ' ';
            board[x+2][y+2] = ' ';
            break;
    }
    
    //if we successfully remove, return true
    return true;
}

//////////////////////////////////////
/////////////makePerm////////////////
//////////////////////////////////////
//turns # into $//
//used when piece is done falling//
void sPiece::makePerm(vector<vector<char> > &board)
{
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    switch(getOrient())
    {
            //adds each piece to board based on orientation
        case 0:
        case 2:
            board[x][y+2] = '$';
            board[x+1][y+1] = '$';
            board[x+1][y+2] = '$';
            board[x+2][y+1] = '$';
            break;
        case 1:
        case 3:
            board[x+1][y] = '$';
            board[x+1][y+1] = '$';
            board[x+2][y+1] = '$';
            board[x+2][y+2] = '$';
            break;
    }
}


//////////////////////////////////////
/////////////////fall/////////////////
//////////////////////////////////////
//if possible, checks if we can fall/move down in board//
//if we can't move, returns false//
bool sPiece::fall(vector<vector<char> > & board)
{
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    //The following code checks if we are able to move it//
    switch(getOrient())
    {
            //adds each piece to board based on orientation
        case 0:
        case 2:
            if(y+3>= board[0].size())   //checks board
                return false;
            if(board[x][y+3] != ' ' || board[x+1][y+3] != ' ' || board [x+2][y+2] != ' ') //checks that its empty
                return false;
            break;
        case 1:
        case 3:
            if(y+3 >= board[0].size())  //checks board
                return false;
            if(board[x+1][y+2] != ' ' || board[x+2][y+3] != ' ')  //checks that its empty
                return false;
            break;
    }
    
    //The following code actually moves the piece//
    removeFromBoard(board); //erase piece from board
    setBoxY(getBoxY()+1);   //increase y coord of piece
    addToBoard(board);      //re-add piece w/new coords
    
    //returns true if we succesfully fall
    return true;
    
}

//////////////////////////////////////
/////////////moveLeft/////////////////
//////////////////////////////////////
//if possible, checks if we can move left in board//
//if we can't move to left, returns false//
bool sPiece::moveLeft(vector<vector<char> > & board)
{
    //The following code checks if we are able to move it//
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    //The following code checks if we are able to move it//
    switch(getOrient())
    {
            //adds each piece to board based on orientation
        case 0:
        case 2:
            if(x-1 < 0)                   //checks board
                return false;
            if(board[x-1][y+2] != ' ' || board[x][y+1] != ' ')    //checks that its empty
                return false;
            break;
        case 1:
        case 3:
            if(x < 0)                     //checks board
                return false;
            if(board[x][y] != ' ' || board[x][y+1] != ' ' || board[x+1][y+2] != ' ')    //checks that its empty
                return false;
            break;
    }
    
    //The following code actually moves the piece//
    removeFromBoard(board); //erase piece from board
    setBoxX(getBoxX()-1);   //decrease x coord of piece
    addToBoard(board);      //re-add piece w/new coords
    
    return true;
}

//////////////////////////////////////
/////////////moveRight////////////////
//////////////////////////////////////
//if possible, checks if we can move right in board//
//if we can't move to right, returns false//
bool sPiece::moveRight(vector<vector<char> > &board)
{
    
    //The following code checks if we are able to move it//
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    //The following code checks if we are able to move it//
    switch(getOrient())
    {
            //adds each piece to board based on orientation
        case 0:
        case 2:
            if(x+3 >= board.size())                   //checks board
                return false;
            if(board[x+3][y+1] != ' ' || board[x+2][y+2] != ' ')    //checks that its empty
                return false;
            break;
        case 1:
        case 3:
            if(x+3 >= board.size())                   //checks board
                return false;
            if(board[x+2][y] != ' ' || board[x+3][y+1] != ' ' || board[x+3][y+2] != ' ')    //checks that its empty
                return false;
            break;
    }
    
    //The following code actually moves the piece//
    removeFromBoard(board); //erase piece from board
    setBoxX(getBoxX()+1);   //increase x coord of piece
    addToBoard(board);      //re-add piece w/new coords
    
    //return true if we succesfully moved
    return true;
}

//////////////////////////////////////
/////////////rotate()////////////////
//////////////////////////////////////
//if possible, checks if we can rotate in board//
//if we can't rotate, returns false//
bool sPiece::rotate(vector<vector<char> > &board)
{
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    //The following code checks if piece can be rotated//
    switch(getOrient())
    {
            //adds each piece to board based on orientation
        case 0:
        case 2:
            if(y < 0)                   //checks board
                return false;
            if(board[x+1][y] != ' ' || board[x+2][y+2] != ' ')  //checks that its empty
                return false;
            break;
        case 1:
        case 3:
            if(x < 0)
                return false;
            if(board[x][y+2] != ' ' || board[x+1][y+2] != ' ')    //checks that its empty
                return false;
            break;
    }
    
    //The following code actually rotates the piece//
    removeFromBoard(board);
    incrementOrient();
    addToBoard(board);
    
    //returns true if succesfully rotated
    return true;
}

//////////////////////////////////////
/////////////printToScreen////////////
//////////////////////////////////////
//draws piece on screen based on x & y parameters//
//used to draw nextPiece thing in the upper right//
//only deals with orientation 0//
void sPiece::printToScreen(Screen &screen, int x, int y)
{
    //prints the piece on the screen w/bounding box at x,y
    screen.gotoXY(x,y+2);
    screen.printChar('#');
    screen.gotoXY(x+1,y+1);
    screen.printChar('#');
    screen.gotoXY(x+1,y+2);
    screen.printChar('#');
    screen.gotoXY(x+2,y+1);
    screen.printChar('#');
}

//===========================================================
//Z-PIECE IMPLEMTNATION
//===========================================================
//The code below includes the implementation of my Z-piece//
//orient 0, 2 same//
//orient 1, 3 same//

//zPiece constructor//
zPiece::zPiece()
{}

//////////////////////////////////////
//////////////canBeAdded//////////////
//////////////////////////////////////
//checks if piece can be added//
//only used when piece is added in the beginning//
//does not check for outOfBounds//
//can be added is only used at orientation 0//
bool zPiece::canBeAdded(vector<vector<char> > &board)
{
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    //checks if theres space for s-piece orientation 0
    if(board[x][y+1] != ' ' || board[x+1][y+1] != ' ' || board[x+1][y+2] != ' ' || board[x+2][y+2] != ' ')
        return false;
    
    //returns true if there is room
    return true;
}

//////////////////////////////////////
//////////////addToBoard//////////////
//////////////////////////////////////
//adds piece to board//
//does not check for outOfBounds//
bool zPiece::addToBoard(vector<vector<char> > & board)
{
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    switch(getOrient())
    {
            //adds each piece to board based on orientation
        case 0:
        case 2:
            board[x][y+1] = '#';
            board[x+1][y+1] = '#';
            board[x+1][y+2] = '#';
            board[x+2][y+2] = '#';
            break;
        case 1:
        case 3:
            board[x+2][y] = '#';
            board[x+2][y+1] = '#';
            board[x+1][y+1] = '#';
            board[x+1][y+2] = '#';
            break;
    }
    
    //if we succesfully insert, return true
    return true;
}

//////////////////////////////////////
///////////removeFromBoard////////////
//////////////////////////////////////
//removes piece from board//
bool zPiece::removeFromBoard(vector<vector<char> > &board)
{
    //sets everything to empty space based on orientation
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    switch(getOrient())
    {
            //adds each piece to board based on orientation
        case 0:
        case 2:
            board[x][y+1] = ' ';
            board[x+1][y+1] = ' ';
            board[x+1][y+2] = ' ';
            board[x+2][y+2] = ' ';
            break;
        case 1:
        case 3:
            board[x+2][y] = ' ';
            board[x+2][y+1] = ' ';
            board[x+1][y+1] = ' ';
            board[x+1][y+2] = ' ';
            break;
    }
    
    //if we successfully remove, return true
    return true;
}

//////////////////////////////////////
/////////////makePerm////////////////
//////////////////////////////////////
//turns # into $//
//used when piece is done falling//
void zPiece::makePerm(vector<vector<char> > &board)
{
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    switch(getOrient())
    {
            //adds each piece to board based on orientation
        case 0:
            case 2:
                board[x][y+1] = '$';
                board[x+1][y+1] = '$';
                board[x+1][y+2] = '$';
                board[x+2][y+2] = '$';
                break;
            case 1:
            case 3:
                board[x+2][y] = '$';
                board[x+2][y+1] = '$';
                board[x+1][y+1] = '$';
                board[x+1][y+2] = '$';
                break;
        }
}


//////////////////////////////////////
/////////////////fall/////////////////
//////////////////////////////////////
//if possible, checks if we can fall/move down in board//
//if we can't move, returns false//
bool zPiece::fall(vector<vector<char> > & board)
{
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    //The following code checks if we are able to move it//
    switch(getOrient())
    {
            //adds each piece to board based on orientation
        case 0:
        case 2:
            if(y+3>= board[0].size())   //checks board
                return false;
            if(board[x][y+2] != ' ' || board[x+1][y+3] != ' ' || board [x+2][y+3] != ' ') //checks that its empty
                return false;
            break;
        case 1:
        case 3:
            if(y+3 >= board[0].size())  //checks board
                return false;
            if(board[x+1][y+3] != ' ' || board[x+2][y+2] != ' ')  //checks that its empty
                return false;
            break;
    }
    
    //The following code actually moves the piece//
    removeFromBoard(board); //erase piece from board
    setBoxY(getBoxY()+1);   //increase y coord of piece
    addToBoard(board);      //re-add piece w/new coords
    
    //returns true if we succesfully fall
    return true;
    
}

//////////////////////////////////////
/////////////moveLeft/////////////////
//////////////////////////////////////
//if possible, checks if we can move left in board//
//if we can't move to left, returns false//
bool zPiece::moveLeft(vector<vector<char> > & board)
{
    //The following code checks if we are able to move it//
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    //The following code checks if we are able to move it//
    switch(getOrient())
    {
            //adds each piece to board based on orientation
        case 0:
        case 2:
            if(x-1 < 0)                   //checks board
                return false;
            if(board[x-1][y+1] != ' ' || board[x][y+2] != ' ')    //checks that its empty
                return false;
            break;
        case 1:
        case 3:
            if(x < 0)                     //checks board
                return false;
            if(board[x+1][y] != ' ' || board[x][y+1] != ' ' || board[x][y+2] != ' ')    //checks that its empty
                return false;
            break;
    }
    
    //The following code actually moves the piece//
    removeFromBoard(board); //erase piece from board
    setBoxX(getBoxX()-1);   //decrease x coord of piece
    addToBoard(board);      //re-add piece w/new coords
    
    return true;
}

//////////////////////////////////////
/////////////moveRight////////////////
//////////////////////////////////////
//if possible, checks if we can move right in board//
//if we can't move to right, returns false//
bool zPiece::moveRight(vector<vector<char> > &board)
{
    
    //The following code checks if we are able to move it//
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    //The following code checks if we are able to move it//
    switch(getOrient())
    {
            //adds each piece to board based on orientation
        case 0:
        case 2:
            if(x+3 >= board.size())                   //checks board
                return false;
            if(board[x+2][y+1] != ' ' || board[x+3][y+2] != ' ')    //checks that its empty
                return false;
            break;
        case 1:
        case 3:
            if(x+3 >= board.size())                   //checks board
                return false;
            if(board[x+3][y] != ' ' || board[x+3][y+1] != ' ' || board[x+2][y+2] != ' ')    //checks that its empty
                return false;
            break;
    }
    
    //The following code actually moves the piece//
    removeFromBoard(board); //erase piece from board
    setBoxX(getBoxX()+1);   //increase x coord of piece
    addToBoard(board);      //re-add piece w/new coords
    
    //return true if we succesfully moved
    return true;
}

//////////////////////////////////////
/////////////rotate()////////////////
//////////////////////////////////////
//if possible, checks if we can rotate in board//
//if we can't rotate, returns false//
bool zPiece::rotate(vector<vector<char> > &board)
{
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    //The following code checks if piece can be rotated//
    switch(getOrient())
    {
            //adds each piece to board based on orientation
        case 0:
        case 2:
            if(y < 0)                   //checks board
                return false;
            if(board[x+2][y] != ' ' || board[x+2][y+1] != ' ')  //checks that its empty
                return false;
            break;
        case 1:
        case 3:
            if(x < 0)
                return false;
            if(board[x+2][y+2] != ' ' || board[x][y+1] != ' ')    //checks that its empty
                return false;
            break;
    }
    
    //The following code actually rotates the piece//
    removeFromBoard(board);
    incrementOrient();
    addToBoard(board);
    
    //returns true if succesfully rotated
    return true;
}

//////////////////////////////////////
/////////////printToScreen////////////
//////////////////////////////////////
//draws piece on screen based on x & y parameters//
//used to draw nextPiece thing in the upper right//
//only deals with orientation 0//
void zPiece::printToScreen(Screen &screen, int x, int y)
{
    //prints the piece on the screen w/bounding box at x,y
    screen.gotoXY(x,y+1);
    screen.printChar('#');
    screen.gotoXY(x+1,y+1);
    screen.printChar('#');
    screen.gotoXY(x+1,y+2);
    screen.printChar('#');
    screen.gotoXY(x+2,y+2);
    screen.printChar('#');
}

//===========================================================
//VAPOR BOMB IMPLEMTNATION
//===========================================================
//The code below includes the implementation of my Vapor Bomb//
//orient 0, 2 same//
//orient 1, 3 same//

//vaporBomb constructor//
vaporBomb::vaporBomb()
{}

//////////////////////////////////////
//////////////canBeAdded//////////////
//////////////////////////////////////
//checks if piece can be added//
//only used when piece is added in the beginning//
//does not check for outOfBounds//
//can be added is only used at orientation 0//
bool vaporBomb::canBeAdded(vector<vector<char> > &board)
{
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    //checks if theres space for s-piece orientation 0
    if(board[x+1][y] != ' ' || board[x+2][y] != ' ')
        return false;
    
    //returns true if there is room
    return true;
}

//////////////////////////////////////
//////////////addToBoard//////////////
//////////////////////////////////////
//adds piece to board//
//does not check for outOfBounds//
bool vaporBomb::addToBoard(vector<vector<char> > & board)
{
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    board[x+1][y] = '#';
    board[x+2][y] = '#';
    
    //if we succesfully insert, return true
    return true;
}

//////////////////////////////////////
///////////removeFromBoard////////////
//////////////////////////////////////
//removes piece from board//
bool vaporBomb::removeFromBoard(vector<vector<char> > &board)
{
    //sets everything to empty space based on orientation
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    board[x+1][y] = ' ';
    board[x+2][y] = ' ';
    
    //if we successfully remove, return true
    return true;
}

//////////////////////////////////////
/////////////makePerm////////////////
//////////////////////////////////////
//for vapor bomb, instead of making pieces perm, it explodes//
void vaporBomb::makePerm(vector<vector<char> > &board)
{
    explode(board);
}


//////////////////////////////////////
/////////////////fall/////////////////
//////////////////////////////////////
//if possible, checks if we can fall/move down in board//
//if we can't move, returns false//
bool vaporBomb::fall(vector<vector<char> > & board)
{
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    if(y+1 >= board[0].size())
        return false;
    if(board[x+1][y+1] != ' ' || board[x+2][y+1] != ' ')
        return false;
    
    //The following code actually moves the piece//
    removeFromBoard(board); //erase piece from board
    setBoxY(getBoxY()+1);   //increase y coord of piece
    addToBoard(board);      //re-add piece w/new coords
    
    //returns true if we succesfully fall
    return true;
    
}

//////////////////////////////////////
/////////////moveLeft/////////////////
//////////////////////////////////////
//if possible, checks if we can move left in board//
//if we can't move to left, returns false//
bool vaporBomb::moveLeft(vector<vector<char> > & board)
{
    //The following code checks if we are able to move it//
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    if(x<0)
        return false;
    if(board[x][y] != ' ')
        return false;
    
    //The following code actually moves the piece//
    removeFromBoard(board); //erase piece from board
    setBoxX(getBoxX()-1);   //decrease x coord of piece
    addToBoard(board);      //re-add piece w/new coords
    
    return true;
}

//////////////////////////////////////
/////////////moveRight////////////////
//////////////////////////////////////
//if possible, checks if we can move right in board//
//if we can't move to right, returns false//
bool vaporBomb::moveRight(vector<vector<char> > &board)
{
    
    //The following code checks if we are able to move it//
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    if(x+3 >= board.size())
        return false;
    if(board[x+3][y] != ' ')
        return false;
    
    //The following code actually moves the piece//
    removeFromBoard(board); //erase piece from board
    setBoxX(getBoxX()+1);   //increase x coord of piece
    addToBoard(board);      //re-add piece w/new coords
    
    //return true if we succesfully moved
    return true;
}

//////////////////////////////////////
/////////////rotate()////////////////
//////////////////////////////////////
//vapor bomb can always be rotated//
bool vaporBomb::rotate(vector<vector<char> > &board)
{
    return true;
}

//////////////////////////////////////
/////////////printToScreen////////////
//////////////////////////////////////
//draws piece on screen based on x & y parameters//
//used to draw nextPiece thing in the upper right//
//only deals with orientation 0//
void vaporBomb::printToScreen(Screen &screen, int x, int y)
{
    //prints the piece on the screen w/bounding box at x,y
    screen.gotoXY(x+1,y);
    screen.printChar('#');
    screen.gotoXY(x+2,y);
    screen.printChar('#');
 
}

///////////////////////////////////
/////////////explode()////////////
//////////////////////////////////
void vaporBomb::explode(vector<vector<char> > & board)
{
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    //explodes things two rows under
    if(y+1 < board[0].size()) //only deletes if we're within well
    {
        //deletes at below
        board[x+1][y+1] = ' ';
        board[x+2][y+1] = ' ';
        
        if(y+2 < board[0].size())
        {
            //deletes two rows below
            board[x+1][y+2] = ' ';
            board[x+2][y+2] = ' ';
        }
    }
    
    //explodes things two rows above
    if(y -1 >= 0)
    {
        //deletes above
        board[x+1][y-1] = ' ';
        board[x+2][y+-1] = ' ';
        
        if(y-2 >= 0)
        {
            //deletes two rows above
            board[x+1][y-2] = ' ';
            board[x+2][y-2] = ' ';
        }
    }
    
    //deletes itself
    removeFromBoard(board);
}

//===========================================================
//FOAM BOMB IMPLEMENTATION
//===========================================================
//The code below includes the implementation of my Foam Bomb//

//foamBomb constructor//
foamBomb::foamBomb()
{}

//////////////////////////////////////
//////////////canBeAdded//////////////
//////////////////////////////////////
//checks if piece can be added//
//only used when piece is added in the beginning//
//does not check for outOfBounds//
//can be added is only used at orientation 0//
bool foamBomb::canBeAdded(vector<vector<char> > &board)
{
    if(board[getBoxX()+1][getBoxY()+1] != ' ')
        return false;
    
    //returns true if there is room
    return true;
}

//////////////////////////////////////
//////////////addToBoard//////////////
//////////////////////////////////////
//adds piece to board//
//does not check for outOfBounds//
bool foamBomb::addToBoard(vector<vector<char> > & board)
{
    board[getBoxX()+1][getBoxY()+1] = '#';
    
    //if we succesfully insert, return true
    return true;
}

//////////////////////////////////////
///////////removeFromBoard////////////
//////////////////////////////////////
//removes piece from board//
bool foamBomb::removeFromBoard(vector<vector<char> > &board)
{
    //sets everything to empty space based on orientation
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    board[x+1][y+1] = ' ';
    
    //if we successfully remove, return true
    return true;
}

//////////////////////////////////////
/////////////makePerm////////////////
//////////////////////////////////////
//for vapor bomb, instead of making pieces perm, it explodes//
void foamBomb::makePerm(vector<vector<char> > &board)
{
    puff(board, getBoxX()+1, getBoxY()+1);
}


//////////////////////////////////////
/////////////////fall/////////////////
//////////////////////////////////////
//if possible, checks if we can fall/move down in board//
//if we can't move, returns false//
bool foamBomb::fall(vector<vector<char> > & board)
{
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    if(y+2 >= board[0].size())
        return false;
    if(board[x+1][y+2] != ' ')
        return false;
    
    //The following code actually moves the piece//
    removeFromBoard(board); //erase piece from board
    setBoxY(getBoxY()+1);   //increase y coord of piece
    addToBoard(board);      //re-add piece w/new coords
    
    //returns true if we succesfully fall
    return true;
    
}

//////////////////////////////////////
/////////////moveLeft/////////////////
//////////////////////////////////////
//if possible, checks if we can move left in board//
//if we can't move to left, returns false//
bool foamBomb::moveLeft(vector<vector<char> > & board)
{
    //The following code checks if we are able to move it//
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    if(x<0)
        return false;
    if(board[x][y+1] != ' ')
        return false;
    
    //The following code actually moves the piece//
    removeFromBoard(board); //erase piece from board
    setBoxX(getBoxX()-1);   //decrease x coord of piece
    addToBoard(board);      //re-add piece w/new coords
    
    return true;
}

//////////////////////////////////////
/////////////moveRight////////////////
//////////////////////////////////////
//if possible, checks if we can move right in board//
//if we can't move to right, returns false//
bool foamBomb::moveRight(vector<vector<char> > &board)
{
    
    //The following code checks if we are able to move it//
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    if(x+2 >= board.size())
        return false;
    if(board[x+2][y+1] != ' ')
        return false;
    
    //The following code actually moves the piece//
    removeFromBoard(board); //erase piece from board
    setBoxX(getBoxX()+1);   //increase x coord of piece
    addToBoard(board);      //re-add piece w/new coords
    
    //return true if we succesfully moved
    return true;
}

//////////////////////////////////////
/////////////rotate()////////////////
//////////////////////////////////////
//foam bomb can always be rotated//
bool foamBomb::rotate(vector<vector<char> > &board)
{
    return true;
}

//////////////////////////////////////
/////////////printToScreen////////////
//////////////////////////////////////
//draws piece on screen based on x & y parameters//
//used to draw nextPiece thing in the upper right//
//only deals with orientation 0//
void foamBomb::printToScreen(Screen &screen, int x, int y)
{
    //prints the piece on the screen w/bounding box at x,y
    screen.gotoXY(x+1,y+1);
    screen.printChar('#');
    
}

///////////////////////////////////
////////////////puff()////////////
//////////////////////////////////
void foamBomb::puff(vector<vector<char> > & board, int x, int y)
{
    //does not puff if we are more than 2 spaces away from original loc
    if(x == getBoxX()+4 || x == getBoxX()-2 || y == getBoxY()+4 || y == getBoxY()-2 )
        return;
    
    //current block gets filled with *
    board[x][y] = '*';
    
    //puffs NORTH
    if(y-1 >= 0 && board[x][y-1] == ' ')
        puff(board, x, y-1);
    //puffs EAST
    if(x+1 < board.size() && board[x+1][y] == ' ')
        puff(board, x+1, y);
    //puffs SOUTH
    if(y+1 <board[0].size() && board[x][y+1] == ' ')
        puff(board, x, y+1);
    //puffs WEST
    if(x-1 >= 0 && board[x-1][y] == ' ')
        puff(board, x-1, y);
    
}

//===========================================================
//CRAZY SHAPE IMPLEMTNATION
//===========================================================
//The code below includes the implementation of my crazy shape//
//orient 0,1,2,3 are all different//

//crazy shape constructor//
crazyShape::crazyShape()
{}

//////////////////////////////////////
//////////////canBeAdded//////////////
//////////////////////////////////////
//checks if piece can be added//
//only used when piece is added in the beginning//
//does not check for outOfBounds//
//checks only orientation 0//
bool crazyShape::canBeAdded(vector<vector<char> > &board)
{
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    //checks if it can be inserted
    if(board[x][y] != ' ' || board[x+1][y+1] != ' ' || board[x+2][y+1] != ' ' || board[x+3][y] != ' ')
        return false;
    
    //returns true if there is room
    return true;
}

//////////////////////////////////////
//////////////addToBoard//////////////
//////////////////////////////////////
//adds piece to board//
//does not check for outOfBounds//
bool crazyShape::addToBoard(vector<vector<char> > & board)
{
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    switch(getOrient())
    {
            //adds each piece to board based on orientation
        case 0:
            board[x][y] = '#';
            board[x+1][y+1] = '#';
            board[x+2][y+1] = '#';
            board[x+3][y] = '#';
            break;
        case 1:
            board[x+3][y] = '#';
            board[x+2][y+1] = '#';
            board[x+2][y+2] = '#';
            board[x+3][y+3] = '#';
            break;
        case 2:
            board[x][y+3] = '#';
            board[x+1][y+2] = '#';
            board[x+2][y+2] = '#';
            board[x+3][y+3] = '#';
            break;
        case 3:
            board[x][y] = '#';
            board[x+1][y+1] = '#';
            board[x+1][y+2] = '#';
            board[x+0][y+3] = '#';
            break;
    }
    
    //if we succesfully insert, return true
    return true;
}

//////////////////////////////////////
///////////removeFromBoard////////////
//////////////////////////////////////
//removes piece from board//
bool crazyShape::removeFromBoard(vector<vector<char> > &board)
{
    //sets everything to empty space based on orientation
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    switch(getOrient())
    {
            //adds each piece to board based on orientation
        case 0:
            board[x][y] = ' ';
            board[x+1][y+1] = ' ';
            board[x+2][y+1] = ' ';
            board[x+3][y] = ' ';
            break;
        case 1:
            board[x+3][y] = ' ';
            board[x+2][y+1] = ' ';
            board[x+2][y+2] = ' ';
            board[x+3][y+3] = ' ';
            break;
        case 2:
            board[x][y+3] = ' ';
            board[x+1][y+2] = ' ';
            board[x+2][y+2] = ' ';
            board[x+3][y+3] = ' ';
            break;
        case 3:
            board[x][y] = ' ';
            board[x+1][y+1] = ' ';
            board[x+1][y+2] = ' ';
            board[x+0][y+3] = ' ';
            break;
    }
    
    //if we successfully remove, return true
    return true;
}

//////////////////////////////////////
/////////////////fall/////////////////
//////////////////////////////////////
//if possible, checks if we can fall/move down in board//
//if we can't move, returns false//
bool crazyShape::fall(vector<vector<char> > & board)
{
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    //The following code checks if we are able to move it//
    switch(getOrient())
    {
            //adds each piece to board based on orientation
        case 0:
            if(y+2>= board[0].size())   //checks board
                return false;
            if(board[x][y+1] != ' ' || board[x+1][y+2] != ' ' || board [x+2][y+2] != ' ' || board [x+3][y+1] != ' ') //checks that its empty
                return false;
            break;
        case 1:
            if(y+4 >= board[0].size())  //checks board
                return false;
            if(board[x+2][y+3] != ' ' || board[x+3][y+4] != ' ' || board[x+3][y+1] != ' ')  //checks that its empty
                return false;
            break;
        case 2:
            if(y+4 >= board[0].size())  //checks board
                return false;
            if(board[x][y+4] != ' ' || board[x+1][y+3] != ' ' || board[x+2][y+3] != ' ' || board[x+3][y+4] != ' ')  //checks that its empty
                return false;
            break;
        case 3:
            if(y+4 >= board[0].size())  //checks board
                return false;
            if(board[x][y+1] != ' ' || board[x+1][y+3] != ' ' || board[x][y+4] != ' ')  //checks that its empty
                return false;
            break;
    }
    
    //The following code actually moves the piece//
    removeFromBoard(board); //erase piece from board
    setBoxY(getBoxY()+1);   //increase y coord of piece
    addToBoard(board);      //re-add piece w/new coords
    
    //returns true if we succesfully fall
    return true;
    
}

//////////////////////////////////////
/////////////moveLeft/////////////////
//////////////////////////////////////
//MOVES CRAZY PIECE RIGHT//
bool crazyShape::moveLeft(vector<vector<char> > & board)
{
    //The following code checks if we are able to move it//
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    //The following code checks if we are able to move it//
    switch(getOrient())
    {
            //adds each piece to board based on orientation
        case 0:
            if(x+4>= board.size())   //checks board
                return false;
            if(board[x+1][y] != ' ' || board[x+3][y+1] != ' ' || board [x+4][y] != ' ') //checks that its empty
                return false;
            break;
        case 1:
            if(x+4 >= board.size())  //checks board
                return false;
            if(board[x+4][y] != ' ' || board[x+3][y+1] != ' ' || board[x+3][y+2] != ' ' || board[x+4][y+3] != ' ')  //checks that its empty
                return false;
            break;
        case 2:
            if(x+4 >= board.size())  //checks board
                return false;
            if(board[x+1][y+3] != ' ' || board[x+3][y+2] != ' ' || board[x+4][y+3] != ' ')  //checks that its empty
                return false;
            break;
        case 3:
            if(x+2 >= board.size())  //checks board
                return false;
            if(board[x+1][y] != ' ' || board[x+2][y+1] != ' ' || board[x+2][y+2] != ' ' || board[x+1][y+3] != ' ')  //checks that its empty
                return false;
            break;
    }
    
    //The following code actually moves the piece//
    //because its crazy, the moveLeft function actually moves it to the right//
    removeFromBoard(board); //erase piece from board
    setBoxX(getBoxX()+1);   //increases x coord of piece
    addToBoard(board);      //re-add piece w/new coords
    
    return true;
}

//////////////////////////////////////
/////////////moveRight////////////////
//////////////////////////////////////
//MOVES CRAZY PIECE LEFT//
bool crazyShape::moveRight(vector<vector<char> > &board)
{
    
    //The following code checks if we are able to move it//
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    //The following code checks if we are able to move it//
    switch(getOrient())
    {
            //adds each piece to board based on orientation
        case 0:
            if(x-1 <0)   //checks board
                return false;
            if(board[x-1][y] != ' ' || board[x][y+1] != ' ' || board [x+2][y] != ' ') //checks that its empty
                return false;
            break;
        case 1:
            if(x+1 <0)  //checks board
                return false;
            if(board[x+2][y] != ' ' || board[x+1][y+1] != ' ' || board[x+1][y+2] != ' ' || board[x+2][y+3] != ' ')  //checks that its empty
                return false;
            break;
        case 2:
            if(x-1<0)  //checks board
                return false;
            if(board[x-1][y+3] != ' ' || board[x][y+2] != ' ' || board[x+2][y+3] != ' ')  //checks that its empty
                return false;
            break;
        case 3:
            if(x-1<0)  //checks board
                return false;
            if(board[x-1][y] != ' ' || board[x][y+1] != ' ' || board[x][y+2] != ' ' || board[x-1][y+3] != ' ')  //checks that its empty
                return false;
            break;
    }
    
    //The following code actually moves the piece//
    //moves to the left (crazy piece)
    removeFromBoard(board); //erase piece from board
    setBoxX(getBoxX()-1);   //increase x coord of piece
    addToBoard(board);      //re-add piece w/new coords
    
    //return true if we succesfully moved
    return true;
}

//////////////////////////////////////
/////////////rotate()////////////////
//////////////////////////////////////
//if possible, checks if we can rotate in board//
//if we can't rotate, returns false//
bool crazyShape::rotate(vector<vector<char> > &board)
{
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    //The following code checks if piece can be rotated//
    switch(getOrient())
    {
            //adds each piece to board based on orientation
        case 0:
            if(y+3 >= board[0].size())                   //checks board
                return false;
            if(board[x+2][y+2] != ' ' || board[x+3][y+3] != ' ')  //checks that its empty
                return false;
            break;
        case 1:
            if(x < 0)
                return false;
            if(board[x][y+3] != ' ' || board[x+1][y+2] != ' ')  //checks that its empty
                return false;
            break;
        case 2:
            if(y < 0)   //checks board
                return false;
            if(board[x+1][y+1] != ' ' || board[x][y] != ' ')    //checks that its empty
                return false;
            break;
        case 3:
            if(x+3 >= board.size())      //checks board
                return false;
            if(board[x+2][y+1] != ' ' || board[x+3][y] != ' ')    //checks that its empty
                return false;
            break;
    }
    
    //The following code actually rotates the piece//
    removeFromBoard(board);
    incrementOrient();
    addToBoard(board);
    
    //returns true if succesfully rotated
    return true;
}

//////////////////////////////////////
/////////////makePerm////////////////
//////////////////////////////////////
//turns # into $//
//used when piece is done falling//
void crazyShape::makePerm(vector<vector<char> > &board)
{
    //store coords in x & y
    int x = getBoxX();
    int y = getBoxY();
    
    switch(getOrient())
    {
            //adds each piece to board based on orientation
        case 0:
            board[x][y] = '$';
            board[x+1][y+1] = '$';
            board[x+2][y+1] = '$';
            board[x+3][y] = '$';
            break;
        case 1:
            board[x+3][y] = '$';
            board[x+2][y+1] = '$';
            board[x+2][y+2] = '$';
            board[x+3][y+3] = '$';
            break;
        case 2:
            board[x][y+3] = '$';
            board[x+1][y+2] = '$';
            board[x+2][y+2] = '$';
            board[x+3][y+3] = '$';
            break;
        case 3:
            board[x][y] = '$';
            board[x+1][y+1] = '$';
            board[x+1][y+2] = '$';
            board[x+0][y+3] = '$';
            break;
    }
}

//////////////////////////////////////
/////////////printToScreen////////////
//////////////////////////////////////
//draws piece on screen based on x & y parameters//
//used to draw nextPiece thing in the upper right//
//only deals with orientation 0//
void crazyShape::printToScreen(Screen &screen, int x, int y)
{
    //prints the piece on the screen w/bounding box at x,y
    screen.gotoXY(x,y);
    screen.printChar('#');
    screen.gotoXY(x+1,y+1);
    screen.printChar('#');
    screen.gotoXY(x+2,y+1);
    screen.printChar('#');
    screen.gotoXY(x+3,y);
    screen.printChar('#');
}



