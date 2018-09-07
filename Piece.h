#ifndef PIECE_INCLUDED
#define PIECE_INCLUDED
#include "UserInterface.h"
#include <vector>
using namespace std;

enum PieceType {
    PIECE_I, PIECE_L, PIECE_J, PIECE_T, PIECE_O, PIECE_S, PIECE_Z,
    PIECE_VAPOR, PIECE_FOAM, PIECE_CRAZY, NUM_PIECE_TYPES
};

PieceType chooseRandomPieceType();

//===========================================================
//PIECE DECLARATION(BASE CLASS)(ABSTRACT CLASS)
//===========================================================
class Piece{
public:
    Piece();
    virtual bool canBeAdded(vector<vector<char> > & board) = 0;      //checks if it can be added to board
    virtual bool addToBoard(vector<vector<char> > & board) = 0;      //adds piece to board based on its current bounding box x&y
    virtual bool removeFromBoard(vector<vector<char> > & board) = 0; //removes piece from board based on its bounding box x&y
    virtual bool fall(vector<vector<char> > & board) = 0;            //moves piece down, returns false if not able to move
    virtual bool moveLeft(vector<vector<char> > & board) = 0;        //moves piece to left, returns false if not able to move
    virtual bool moveRight(vector<vector<char> > & board) = 0;       //moves piece to right, return false if not able to move
    virtual bool rotate(vector<vector<char> > & board) = 0;          //rotates piece & changes orientation
    virtual void makePerm(vector<vector<char> > & board) = 0;        //makes piece permenenant
    virtual void printToScreen(Screen & screen, int x, int y) = 0;       //prints the piece based off of x & y
    virtual ~Piece(){}
    
 
    
     //setter/getter methods for our piece private variables
    int getBoxX();
    int getBoxY();
    int getOrient();
    void setBoxX(int value);
    void setBoxY(int value);
    void incrementOrient();    //used to change orientation of piece
    
private:
    int x;              //bounding box x value
    int y;              //bounding box y value
    int orientation;    //keeps track of orientation of piece
};

//===========================================================
//VAPOR BOMB DECLARATION
//===========================================================
class vaporBomb: public Piece
{
public:
    vaporBomb();
    virtual bool canBeAdded(vector<vector<char> > & board);
    virtual bool addToBoard(vector<vector<char> > & board);
    virtual bool removeFromBoard(vector<vector<char> > & board);
    virtual bool fall(vector<vector<char> > & board);
    virtual bool moveLeft(vector<vector<char> > & board);
    virtual bool moveRight(vector<vector<char> > & board);
    virtual bool rotate(vector<vector<char> > & board);
    virtual void makePerm(vector<vector<char> > & board);
    virtual void printToScreen(Screen & screen, int x, int y);

private:
    void explode(vector<vector<char> > & board);
};

//===========================================================
//FOAM BOMB DECLARATION
//===========================================================
class foamBomb:public Piece
{
public:
    foamBomb();
    virtual bool canBeAdded(vector<vector<char> > & board);
    virtual bool addToBoard(vector<vector<char> > & board);
    virtual bool removeFromBoard(vector<vector<char> > & board);
    virtual bool fall(vector<vector<char> > & board);
    virtual bool moveLeft(vector<vector<char> > & board);
    virtual bool moveRight(vector<vector<char> > & board);
    virtual bool rotate(vector<vector<char> > & board);
    virtual void makePerm(vector<vector<char> > & board);
    virtual void printToScreen(Screen & screen, int x, int y);
    
private:
    void puff(vector<vector<char> > & board, int x, int y);
};

//===========================================================
//CRAZY SHAPE DECLARATION
//===========================================================
class crazyShape:public Piece
{
public:
    crazyShape();
    virtual bool canBeAdded(vector<vector<char> > & board);
    virtual bool addToBoard(vector<vector<char> > & board);
    virtual bool removeFromBoard(vector<vector<char> > & board);
    virtual bool fall(vector<vector<char> > & board);
    virtual bool moveLeft(vector<vector<char> > & board);
    virtual bool moveRight(vector<vector<char> > & board);
    virtual bool rotate(vector<vector<char> > & board);
    virtual void makePerm(vector<vector<char> > & board);
    virtual void printToScreen(Screen & screen, int x, int y);
};

//===========================================================
//I-PIECE DECLARATION
//===========================================================
class iPiece: public Piece
{
public:
    iPiece();
    virtual bool canBeAdded(vector<vector<char> > & board);
    virtual bool addToBoard(vector<vector<char> > & board);
    virtual bool removeFromBoard(vector<vector<char> > & board);
    virtual bool fall(vector<vector<char> > & board);
    virtual bool moveLeft(vector<vector<char> > & board);
    virtual bool moveRight(vector<vector<char> > & board);
    virtual bool rotate(vector<vector<char> > & board);
    virtual void makePerm(vector<vector<char> > & board);
    virtual void printToScreen(Screen & screen, int x, int y);
};

//===========================================================
//O-PIECE DECLARATION
//===========================================================
class oPiece: public Piece
{
public:
    oPiece();
    virtual bool canBeAdded(vector<vector<char> > & board);
    virtual bool addToBoard(vector<vector<char> > & board);
    virtual bool removeFromBoard(vector<vector<char> > & board);
    virtual bool fall(vector<vector<char> > & board);
    virtual bool moveLeft(vector<vector<char> > & board);
    virtual bool moveRight(vector<vector<char> > & board);
    virtual bool rotate(vector<vector<char> > & board);
    virtual void makePerm(vector<vector<char> > & board);
    virtual void printToScreen(Screen & screen, int x, int y);
};

//===========================================================
//T-PIECE DECLARATION
//===========================================================
class tPiece: public Piece
{
public:
    tPiece();
    virtual bool canBeAdded(vector<vector<char> > & board);
    virtual bool addToBoard(vector<vector<char> > & board);
    virtual bool removeFromBoard(vector<vector<char> > & board);
    virtual bool fall(vector<vector<char> > & board);
    virtual bool moveLeft(vector<vector<char> > & board);
    virtual bool moveRight(vector<vector<char> > & board);
    virtual bool rotate(vector<vector<char> > & board);
    virtual void makePerm(vector<vector<char> > & board);
    virtual void printToScreen(Screen & screen, int x, int y);
};

//===========================================================
//L-PIECE DECLARATION
//===========================================================
class lPiece: public Piece
{
public:
    lPiece();
    virtual bool canBeAdded(vector<vector<char> > & board);
    virtual bool addToBoard(vector<vector<char> > & board);
    virtual bool removeFromBoard(vector<vector<char> > & board);
    virtual bool fall(vector<vector<char> > & board);
    virtual bool moveLeft(vector<vector<char> > & board);
    virtual bool moveRight(vector<vector<char> > & board);
    virtual bool rotate(vector<vector<char> > & board);
    virtual void makePerm(vector<vector<char> > & board);
    virtual void printToScreen(Screen & screen, int x, int y);
};

//===========================================================
//J-PIECE DECLARATION
//===========================================================
class jPiece: public Piece
{
public:
    jPiece();
    virtual bool canBeAdded(vector<vector<char> > & board);
    virtual bool addToBoard(vector<vector<char> > & board);
    virtual bool removeFromBoard(vector<vector<char> > & board);
    virtual bool fall(vector<vector<char> > & board);
    virtual bool moveLeft(vector<vector<char> > & board);
    virtual bool moveRight(vector<vector<char> > & board);
    virtual bool rotate(vector<vector<char> > & board);
    virtual void makePerm(vector<vector<char> > & board);
    virtual void printToScreen(Screen & screen, int x, int y);
};

//===========================================================
//S-PIECE DECLARATION
//===========================================================
class sPiece: public Piece
{
public:
    sPiece();
    virtual bool canBeAdded(vector<vector<char> > & board);
    virtual bool addToBoard(vector<vector<char> > & board);
    virtual bool removeFromBoard(vector<vector<char> > & board);
    virtual bool fall(vector<vector<char> > & board);
    virtual bool moveLeft(vector<vector<char> > & board);
    virtual bool moveRight(vector<vector<char> > & board);
    virtual bool rotate(vector<vector<char> > & board);
    virtual void makePerm(vector<vector<char> > & board);
    virtual void printToScreen(Screen & screen, int x, int y);
};

//===========================================================
//Z-PIECE DECLARATION
//===========================================================
class zPiece: public Piece
{
public:
    zPiece();
    virtual bool canBeAdded(vector<vector<char> > & board);
    virtual bool addToBoard(vector<vector<char> > & board);
    virtual bool removeFromBoard(vector<vector<char> > & board);
    virtual bool fall(vector<vector<char> > & board);
    virtual bool moveLeft(vector<vector<char> > & board);
    virtual bool moveRight(vector<vector<char> > & board);
    virtual bool rotate(vector<vector<char> > & board);
    virtual void makePerm(vector<vector<char> > & board);
    virtual void printToScreen(Screen & screen, int x, int y);
};



#endif // PIECE_INCLUDED
