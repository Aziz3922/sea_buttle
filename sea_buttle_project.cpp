
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

struct Ship {
    int size;
    int x, y;
    Direction dir;
    int hits = 0;

    bool isSunk() const {
        return hits >= size;
    }
};

struct Board {
    Cell grid[BOARD_SIZE][BOARD_SIZE];
    Ship ships[MAX_SHIPS];
    int shipCount = 0;

    bool canPlaceShip(const Ship& ship) {
        for (int i = 0; i < ship.size; ++i) {
            int nx = ship.x + (ship.dir == HORIZONTAL ? i : 0);
            int ny = ship.y + (ship.dir == VERTICAL ? i : 0);

            if (nx < 0 || ny < 0 || nx >= BOARD_SIZE || ny >= BOARD_SIZE)
                return false;
            if (grid[ny][nx].state != EMPTY)
                return false;
        }
        return true;
    }

};

int main()
{
    
}