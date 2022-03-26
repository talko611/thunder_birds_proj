
#include "Game.h"

void Game::initBord() {
    for (int i = 0; i < Hight; i++) {
        for (int j = 0; j < Width; j++) {
            if (i == 0 || i == Hight - 1) {
                bord[i][j] = '-';
            }
            else if (j == 0 || j == Width - 1) {
                bord[i][j] = '|';
            }
            else
            {
                bord[i][j] = ' ';
            }
        }
    }
}

void Game::printBord() {
    for (int i = 0; i < Hight; i++) {
        for (int j = 0; j < Width; j++) {
            std::cout << bord[i][j];
        }
        std::cout << std::endl;
    }
}

void Game::initGame() {
    hideCursor();
    initBord();
    setShip();
    printBord();
}

void Game::setShip() {
    for (auto& ship : ships) {
        char ch = ship.getShipCharacter();
        for (auto& point : ship.getCurrLoc()) {
            bord[point.getX()][point.getY()] = ch;
        }
    }
}

void Game::run() {
    char key = 0;
    Direction dir = Direction::Stop;

    do
    {
        if (_kbhit()) {
            key = tolower(_getch());
            if (isKeyValid(key)) {
                if (isASwitcherKey(key)) {
                    key == (int)SwitchKeys::SwitchToBig ? activeShip = 1 : activeShip = 0;
                    dir = Direction::Stop;
                }
                else {
                    dir = (Direction)key;
                    if (isNextClear(dir)) {
                        ships[activeShip].move(dir);
                        renderShip();
                    }
                }
            }
            else
            {
                if (isNextClear(dir)) {
                    ships[activeShip].move(dir);
                    renderShip();
                }
            }
        }
        else
        {
            if (isNextClear(dir)) {
                ships[activeShip].move(dir);
                renderShip();
            }
        }
        Sleep(500);

    } while ((int)key != 27);
    clrscr();
}

bool Game::isKeyValid(int key) {
    return key == (int)Direction::Down
        || key == (int)Direction::Up
        || key == (int)Direction::Left
        || key == (int)Direction::Right
        || key == (int)SwitchKeys::SwitchToBig
        || key == (int)SwitchKeys::SwitchToSmall;
}

bool Game::isNextClear(Direction dir) {
    std::vector<Point> curr;
    curr = ships[activeShip].getCurrLoc();
    bool flag = true;

    for (auto& i : curr) {
        setPointByDirection(dir, i);
    }

    for (auto& i : curr) {
        if (bord[i.getX()][i.getY()] != ' '  && bord[i.getX()][i.getY()] != ships[activeShip].getShipCharacter()) {
            flag = false;
            break;
        }
    }
    return flag;
}

void Game::printWithNums() { //Test func
    for (int i = 0; i < Hight; ++i) {
        for (int j = 0; j < Width; ++j) {
            if (bord[i][j] == ' ')
            {
                std::cout << 0;
            }
            else if (bord[i][j] == '-') {
                std::cout << 1;
            }
            else if (bord[i][j] == '|') {
                std::cout << 2;
            }
            else if (bord[i][j] == '@') {
                std::cout << 3;
            }

        }
        std::cout << std::endl;
    }

}

void Game::setPointByDirection(Direction dir, Point& p) {
    switch (dir) {
    case Direction::Up:
        p.set(p.getX() - 1, p.getY());
        break;
    case Direction::Down:
        p.set(p.getX() + 1, p.getY());
        break;
    case Direction::Left:
        p.set(p.getX(), p.getY() - 1);
        break;
    case Direction::Right:
        p.set(p.getX(), p.getY() + 1);
        break;
    case Direction::Stop:
        break;
    }
}

bool Game::isASwitcherKey(int key) {
    return  key == (int)SwitchKeys::SwitchToBig
        || key == (int)SwitchKeys::SwitchToSmall;
}

void Game::renderShip() {
    for (auto& i : ships[activeShip].getOldLoc()) {
        gotoxy(i.getY(), i.getX());
        std::cout << ' ';
    }
    char ch = ships[activeShip].getShipCharacter();
    for (auto& i : ships[activeShip].getCurrLoc()) {
        gotoxy(i.getY(), i.getX());
        std::cout << ch;
    }
}


