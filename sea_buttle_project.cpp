
#include <iostream>
using namespace std;

const int BOARD_SIZE = 10;
const int MAX_SHIPS = 5;

enum CellState {
    EMPTY,
    SHIP,
    HIT,
    MISS
};

enum Direction {
    HORIZONTAL,
    VERTICAL
};

struct Cell {
    CellState state = EMPTY;
    bool isRevealed = false;
};



int main()
{
    
}