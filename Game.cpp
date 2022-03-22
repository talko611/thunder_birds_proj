//
// Created by Tal Koren on 21/03/2022.
//

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
    char shipCh;
    for (int i = 0; i < 2; i++) {
        shipCh = ships[i].getShipCh();
        for (auto& i : ships[i].getCurrLoc()) {
            bord[i.getX()][i.getY()] = shipCh;
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
            if (isKeyValid(key)){
                if (isASwitcherKey(key)) {
                    key == (int) SwitchKeys::SwitchToBig ? acticveShip = 1 : acticveShip = 0;
                    dir = Direction::Stop;
                }
                else {
                    dir = (Direction)key;
                    if (isNextClear(dir)) {
                        ships[acticveShip].moveShip(dir);
                        renderShip();
                    }
                }
            }
            else
            {
                if(isNextClear(dir)) {
                    ships[acticveShip].moveShip(dir);
                    renderShip();
                }
            }
        }
        else
        {
            if (isNextClear(dir)) {
                ships[acticveShip].moveShip(dir);
                renderShip();
            }
        }
        Sleep(500);

    } while ((int) key != 27);
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
    curr = ships[acticveShip].getCurrLoc();

    if (dir != Direction::Stop) {
        bool flag = true;

        for (auto& i : curr) {
            i.movePoint(dir);
        }

        for (auto& i : curr) {
            if (bord[i.getX()][i.getY()] != ' ' 
                && bord[i.getX()][i.getY()] != ships[acticveShip].getShipCh()) {
                flag = false;
                break;
            }
        }
        return flag;
    }
    return false;
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

void Game::renderShip() {
    for (auto& i : ships[acticveShip].getOldLoc()) {
        gotoxy(i.getY(), i.getX());
        std::cout << ' ';
    }
    char ch = ships[acticveShip].getShipCh();
    for (auto& i : ships[acticveShip].getCurrLoc()){
        gotoxy(i.getY(), i.getX());
        std::cout << ch;
    }
}

bool Game::isASwitcherKey(int key) {
    return  key == (int)SwitchKeys::SwitchToBig
            || key == (int)SwitchKeys::SwitchToSmall;
}

