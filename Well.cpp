#include "Well.h"
#include "UserInterface.h"
#include <vector>
#include <string>
using namespace std;

Well::Well(int width, int height):wellHeight(height), wellWidth(width)
{}

//===========================================================
//DISPLAY FUNCTION
//===========================================================
//This function displays the well//
void Well::display(Screen& screen, int x, int y)
{
    for(int i = x; i <= wellWidth + 1; i++)                         //loops through different locations of the screen based on
    {                                                               //wellWidth and wellHeight
        for(int j = y; j <= wellHeight; j++)
        {
            screen.gotoXY(i,j);
            if(i == 0 || i == wellWidth+1 || j == wellHeight)       //if we are at x=0, x= wellWidth+1, or y=wellHeight, add a @ to
                screen.printChar('@');                              //screen
        }
    }
}

//===========================================================
//UPDATE SCREEN FUNCTION
//===========================================================
//This function refreshes the screen and is used to keep the screen up to date////
//with our 2-D vector of characters//
void Well::updateScreen(Screen & screen, vector<vector<char> > & board, int x, int y)
{
    screen.clear();                                                 //clear screen
    
    for(int i = 0; i<wellWidth; i++)                                //puts everything from our board onto the screen
    {
        for(int j = 0; j<wellHeight; j++)
        {
            screen.gotoXY(x+i+1,y+j);
            if(board[i][j] == '#')
                screen.printChar('#');
            else if(board[i][j] == '$')
                screen.printChar('$');
            if(board[i][j] == '*')
                screen.printChar('*');
        }
    }
    
    display(screen, x, y);                                          //puts the well back on (since we cleared screen)
    screen.refresh();                                               //refreshes the screen
        
    
}
