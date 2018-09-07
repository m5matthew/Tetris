#ifndef WELL_INCLUDED
#define WELL_INCLUDED
#include <vector>
using namespace std;

class Screen;

class Well
{
  public:
    Well(int width, int height);
    void display(Screen& screen, int x, int y);
    void updateScreen(Screen& screen, vector<vector<char> > & board, int x, int y);
    
  private:
    int wellHeight;
    int wellWidth;
    
};

#endif // WELL_INCLUDED
