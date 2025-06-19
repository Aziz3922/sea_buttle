
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

    void placeShip(const Ship& ship) {
        if (!canPlaceShip(ship) || shipCount >= MAX_SHIPS)
            return;

        for (int i = 0; i < ship.size; ++i) {
            int nx = ship.x + (ship.dir == HORIZONTAL ? i : 0);
            int ny = ship.y + (ship.dir == VERTICAL ? i : 0);
            grid[ny][nx].state = SHIP;
        }

        ships[shipCount++] = ship;
    }

    bool isHit(int x, int y) {
        if (grid[y][x].isRevealed)
            return false;

        grid[y][x].isRevealed = true;

        if (grid[y][x].state == SHIP) {
            grid[y][x].state = HIT;
            for (int s = 0; s < shipCount; ++s) {
                Ship& ship = ships[s];
                for (int i = 0; i < ship.size; ++i) {
                    int nx = ship.x + (ship.dir == HORIZONTAL ? i : 0);
                    int ny = ship.y + (ship.dir == VERTICAL ? i : 0);
                    if (nx == x && ny == y) {
                        ship.hits++;
                        break;
                    }
                }
            }
            return true;
        }
        else {
            grid[y][x].state = MISS;
            return false;
        }
    }

    bool allShipsSunk() const {
        for (int i = 0; i < shipCount; ++i) {
            if (!ships[i].isSunk())
                return false;
        }
        return true;
    }

    void display(bool revealShips = false) const {
        cout << "  ";
        for (int x = 0; x < BOARD_SIZE; ++x)
            cout << x << " ";
        cout << "\n";

        for (int y = 0; y < BOARD_SIZE; ++y) {
            cout << y << " ";
            for (int x = 0; x < BOARD_SIZE; ++x) {
                if (!grid[y][x].isRevealed) {
                    if (revealShips && grid[y][x].state == SHIP)
                        cout << "S ";
                    else
                        cout << ". ";
                }
                else if (grid[y][x].state == HIT) {
                    cout << "X ";
                }
                else if (grid[y][x].state == MISS) {
                    cout << "o ";
                }
                else {
                    cout << ". ";
                }
            }
            cout << "\n";
        }
    }

};

int main()
{
    setlocale(LC_ALL, "Russian");

    Board playerBoard, enemyBoard;

    // Расстановка кораблей вручную или случайно
    Ship s1 = { 5, 0, 0, HORIZONTAL };
    Ship s2 = { 4, 2, 2, VERTICAL };
    Ship s3 = { 3, 5, 1, HORIZONTAL };
    Ship s4 = { 3, 7, 6, VERTICAL };
    Ship s5 = { 2, 3, 8, HORIZONTAL };

    playerBoard.placeShip(s1);
    playerBoard.placeShip(s2);
    playerBoard.placeShip(s3);
    playerBoard.placeShip(s4);
    playerBoard.placeShip(s5);

    // Расстановка кораблей противника случайно
    Ship c1 = { 5, rand() % 5, rand() % 10, HORIZONTAL };
    Ship c2 = { 4, rand() % 10, rand() % 6, VERTICAL };
    Ship c3 = { 3, rand() % 7, rand() % 10, HORIZONTAL };
    Ship c4 = { 3, rand() % 10, rand() % 7, VERTICAL };
    Ship c5 = { 2, rand() % 8, rand() % 10, HORIZONTAL };

    enemyBoard.placeShip(c1);
    enemyBoard.placeShip(c2);
    enemyBoard.placeShip(c3);
    enemyBoard.placeShip(c4);
    enemyBoard.placeShip(c5);


    while (!playerBoard.allShipsSunk() && !enemyBoard.allShipsSunk()) {
        int x, y;
        cout << "\nВаше поле:\n";
        playerBoard.display(true);
        cout << "\nПоле врага:\n";
        enemyBoard.display();

        cout << "\nВведите координаты выстрела (x y): ";
        cin >> x >> y;

        if (x < 0 || y < 0 || x >= BOARD_SIZE || y >= BOARD_SIZE) {
            cout << "Неверные координаты. Попробуйте снова.\n";
            continue;
        }

        if (enemyBoard.isHit(x, y))
            cout << "Попадание!\n";
        else
            cout << "Мимо.\n";

        // Простой ход компьютера (рандом)
        do {
            x = rand() % BOARD_SIZE;
            y = rand() % BOARD_SIZE;
        } while (playerBoard.grid[y][x].isRevealed);

        cout << "Компьютер стреляет в (" << x << ", " << y << ")\n";
        if (playerBoard.isHit(x, y))
            cout << "Компьютер попал!\n";
        else
            cout << "Компьютер промахнулся.\n";
    }

}