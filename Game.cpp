#include "Game.h"
#include "Well.h"
#include "UserInterface.h"
#include "Piece.h"
#include <string>
#include <vector>
#include <math.h>
using namespace std;

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;

const int WELL_X = 0;
const int WELL_Y = 0;

const int PROMPT_Y = 20;
const int PROMPT_X = 0;

const int SCORE_X = 16;
const int SCORE_Y = 8;

const int ROWS_LEFT_X = 16;
const int ROWS_LEFT_Y = 9;

const int LEVEL_X = 16;
const int LEVEL_Y = 10;

const int NEXT_PIECE_TITLE_X = 16;
const int NEXT_PIECE_TITLE_Y = 3;

const int NEXT_PIECE_X = 16;
const int NEXT_PIECE_Y = 4;

//===========================================================
//GAME IMPLEMTNATION
//===========================================================
//The code below includes the implementation of my game class//
//This class is in charge of tying all the other classes together//

//Game constructor
Game::Game(int width, int height)
: m_screen(SCREEN_WIDTH, SCREEN_HEIGHT), m_level(1), m_well(width,height),m_board(vector<vector<char> >(width, vector<char>(height,' '))), score(0), rowsDeleted(0)
{
    currentPiece = allocateNewPiece();
    nextPiece = allocateNewPiece();
}

void Game::play()
{
    m_well.display(m_screen, WELL_X, WELL_Y);
    displayStatus();  //  score, rows left, level
    displayPrompt("Press the Enter key to begin playing Chetyris!");
    waitForEnter();  // [in UserInterface.h]

    for(;;)
    {
        if ( ! playOneLevel())
            break;
        displayPrompt("Good job!  Press the Enter key to start next level!");
        waitForEnter();
        m_level++;
    }
    displayPrompt("Game Over!  Press the Enter key to exit!");
    waitForEnter();
}

void Game::displayPrompt(std::string s)     
{
    m_screen.gotoXY(PROMPT_X, PROMPT_Y);
    m_screen.printStringClearLine(s);   // overwrites previous text
    m_screen.refresh();
}

///////////////////////////////////////
///////////displayStatus()/////////////
///////////////////////////////////////
//displays score, rows, & level//
void Game::displayStatus()
{
     //prints 'Score' text
    m_screen.gotoXY(SCORE_X,SCORE_Y);
    m_screen.printString("Score:     "+to_string(score));
    
     //prints 'Rows Left' text
    m_screen.gotoXY(ROWS_LEFT_X, ROWS_LEFT_Y);
    int rowsLeft = max(5*m_level - rowsDeleted,0);                     //calculates rows left
    m_screen.printString("Rows Left: "+to_string(rowsLeft));
    
     //prints 'Level' text
    m_screen.gotoXY(LEVEL_X,LEVEL_Y);
    m_screen.printString("Level:     "+to_string(m_level));
}

///////////////////////////////////////
////////////playOneLevel()/////////////
///////////////////////////////////////
//plays a level in a game//
//returns false if player fails to succeed//
//if it returns true, it will be called again//

bool Game::playOneLevel()
{
    Timer timer;                                                //sets up timer
    double levelTime = max(1000-(100*(m_level-1)), 100);        //calculates time based on level
    
    bool done = false;          //bool that checks if we completed level or not
    bool spacePressed;          //bool that checks if we hit a space bar or not
    bool landed;                //bool that checks if our piece landed
    
     //keep looping until amount of points is scored
    while(!done)
    {
        //checks if piece can be added, adds piece to the board & updates it to the screen
        if(currentPiece->canBeAdded(m_board) == false)
        {
            currentPiece->addToBoard(m_board);
            update();
            break;
        }
        else
            currentPiece->addToBoard(m_board);
        update();
        
        spacePressed = false;
        landed = false;
        while(!landed)
        {
            timer.start(); //restarts timer every time something happens
            
             //player's move
            while(timer.elapsed()<levelTime && !spacePressed)
            {
                char ch; //ch stores what the player presses on the keyboard
                if (getCharIfAny(ch))
                {
                     //if space bar is pressed, spacePressed = true and we skip this loop everytime
                    if(ch == ' ')
                    {
                        spacePressed = true;
                        break;
                    }
                    switch (ch)
                    {
                        //LEFT//
                        case ARROW_LEFT:
                        case 'a':
                            if(currentPiece->moveLeft(m_board)) //moves piece to the left
                                update();
                            break;
                        //RIGHT//
                        case ARROW_RIGHT:
                        case 'd':
                            if(currentPiece->moveRight(m_board)) //moves piece to the right
                                update();
                            break;
                        //DOWN//
                        case ARROW_DOWN:
                        case 's':
                            if(currentPiece->fall(m_board))
                            {
                                update();
                                timer.start(); //restarts timer
                            }
                            break;
                        //UP//
                        //if it can be rotated, rotates piece & updates screen//
                        case ARROW_UP:
                        case 'w':
                            if(currentPiece->rotate(m_board))
                                update();
                            break;
                        //Q//
                        //returns false and exits loop//
                        case  'q':
                        case  'Q':
                            return false;
                            break;
                        default:
                            break;
                    }
                }
            }//time runs out here/players turn ends
            
            //moves the piece down automatically if time runs out & updates
            if(currentPiece->fall(m_board) == false)
                landed = true;
            update();
        }
        
         //makes piece permenant
        currentPiece->makePerm(m_board);
        
         //eliminates complete rows and calculates score
        int numElim = eliminateRows();
        rowsDeleted += numElim;
        if(numElim != 0)
            score += pow(2,numElim-1)*100;
        update();
        
         //deletes currrentpiece & obtain the next piece
        delete currentPiece;
        currentPiece = nextPiece;
        nextPiece = allocateNewPiece();
        
         //if we delete enough rows, move on to the next level
        if(rowsDeleted >= 5*m_level)
        {
            rowsDeleted = 0;    //rowsDeleted is reset
            refreshLevel();
            return true;
        }
        
    }//end of level
    
    return false;
}


///////////////////////////////////////
////////allocateNewPiece()/////////////
///////////////////////////////////////
//creates a new, random piece and returns its address//
//dont forget to delete the newly allocated storage!//
Piece* Game::allocateNewPiece()
{
    Piece* newPiece;
    switch (chooseRandomPieceType())
    {
        case PIECE_I:
            newPiece = new iPiece();
            break;
        case PIECE_L:
            newPiece = new lPiece();
            break;
        case PIECE_J:
            newPiece = new jPiece();
            break;
        case PIECE_T:
            newPiece = new tPiece();
            break;
        case PIECE_O:
            newPiece = new oPiece();
            break;
        case PIECE_S:
            newPiece = new sPiece();
            break;
        case PIECE_Z:
            newPiece = new zPiece();
            break;
        case PIECE_VAPOR:
            newPiece = new vaporBomb();
            break;
        case PIECE_FOAM:
            newPiece = new foamBomb();
            break;
        case PIECE_CRAZY:
            newPiece = new crazyShape();
            break;
        default:
            newPiece = new iPiece();
            break;
    }
    
    return newPiece;
}

///////////////////////////////////////
///////////////Destructor//////////////
///////////////////////////////////////
//delete currentPiece and nextPiece//
Game::~Game()
{
    delete currentPiece;
    delete nextPiece;
}

///////////////////////////////////////
///////////////update()//////////////
///////////////////////////////////////
//keeps game updated//
//clears, updates, & refreshes screen
void Game::update()
{
    m_well.updateScreen(m_screen, m_board, WELL_X, WELL_Y);   //copies whatevers on board onto screen
    displayStatus(); //puts well back on the screen(which was deleted in the previous function
    
    m_screen.gotoXY(NEXT_PIECE_TITLE_X, NEXT_PIECE_TITLE_Y);  //    //prints 'Next Piece' text
    m_screen.printString("Next Piece:");
    
    nextPiece->printToScreen(m_screen, NEXT_PIECE_X, NEXT_PIECE_Y);
}

///////////////////////////////////////
//////////eliminateRows()//////////////
///////////////////////////////////////
//eliminates completed rows//
//does not change screen//
int Game::eliminateRows()
{
    int total = 0;
    int numElim = 0;
    
    //loop through(keeping the rows as the outer loop)
    for(int j = 0; j<m_board[0].size(); j++)
    {
        for(int i = 0; i<m_board.size(); i++)
        {
            if(m_board[i][j]=='$' || m_board[i][j] == '*')          //count number of $ and * in the row
                total++;
        }
        if(total == m_board.size())                                 //if they fill up the row, we call shiftRows and increment num elim
        {
            shiftRows(j);
            numElim++;
        }
        total = 0;
    }
    return numElim; 
    
}

///////////////////////////////////////
//////////////shiftRows()//////////////
///////////////////////////////////////
//shifts rows down & replaces row at y=0 with an empty row//
void Game::shiftRows(int rowToElim)
{
    //loops through starting at y=rowToElim
    for(int j = rowToElim; j>=0; j--)
    {
        for(int i = 0; i<m_board.size(); i++)
        {
            if(j == 0)                              //empty the last row
                m_board[i][j] = ' ';
            else
                m_board[i][j] = m_board[i][j-1];    //every other row gets the value of the row above it
        }
    }
}

///////////////////////////////////////
//////////////refreshLevel()///////////
///////////////////////////////////////
//wipes to board//
void Game::refreshLevel()
{
    for(int i = 0; i< m_board.size(); i++)
    {
        for(int j = 0; j < m_board[0].size(); j++)
        {
            m_board[i][j] = ' ';    //sets all elements of board to empty space
        }
    }
}
