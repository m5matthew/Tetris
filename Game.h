#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Well.h"
#include "Piece.h"
#include "UserInterface.h"
#include <vector>
#include <string>
using namespace std;
// [Add other #include directives as necessary.]

class Game
{
  public:
    Game(int width, int height);
    void play();
    bool playOneLevel();
    void displayPrompt(std::string s);
    void displayStatus();
    ~Game();
    //void displayNext();     //displays next piece

  private:
    
    Piece* allocateNewPiece();      //creates a new, random piece and returns its address
    void update();
    int eliminateRows();            //returns score from rows eliminated
    void shiftRows(int rowToElim);  //shifts rows down starting from rowToElim
    void refreshLevel();            //clears board
    
    
    Well    m_well;
    Screen  m_screen;
    int     m_level;
    int     score;
    int     rowsDeleted;
    
    vector<vector<char> > m_board;
    Piece* currentPiece;
    Piece* nextPiece;
    
    
};

#endif // GAME_INCLUDED
