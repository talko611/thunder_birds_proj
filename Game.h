#pragma once
#include "Utils.h"
#include "Round.h"


class Game {
    int lives = 3;
    bool color;

public:
    Game(bool _color): color(_color){}
    void startGame();
};


