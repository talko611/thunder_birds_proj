//
// Created by Tal Koren on 21/03/2022.
//

#pragma once
#include <conio.h>
#include "Utils.h"
#include "Ship.h"


class Game {
    constexpr static int Hight = 25;
    constexpr static int Width = 80;
    char bord[Hight][Width];
    Ship ships[2] = { {{1,1}, ShipSize::Small, '@'}, {{3,1}, ShipSize::Big, '#'} };
    int acticveShip = 0; //qustion how do i init all those fileds in a constructor


    void initBord();
    void printBord();
    void setShip();
    static bool isKeyValid(int key);
    bool isNextClear(Direction dir);
    void renderShip();
    bool isASwitcherKey(int key);


public:
    void initGame();
    void run();
    void printWithNums(); //Test func
    char getPointOnBord(int x, int y) { //Test func
        return bord[x][y];
    }
};


