#pragma once
#include "Utils.h"
#include "Ship.h"
#include <conio.h>


class Game {
    constexpr static int Hight = 25;
    constexpr static int Width = 80;
    char bord[Hight][Width];
    Ship ships[2] = { {Point(1,1), ShipSize::Small, '@' }, {Point(3,1), ShipSize::Big, '#' } };
    int activeShip = 0;


    void initBord();
    void printBord();
    void setShip();
    static bool isKeyValid(int key);
    static void setPointByDirection(Direction dir, Point& p);
    bool isASwitcherKey(int key);
    void renderShip();



public:
    void initGame();
    void run();
    bool isNextClear(Direction dir);
    void printWithNums(); //Test func
    char getPointOnBord(int x, int y) { //Test func
        return bord[x][y];
    }
};


