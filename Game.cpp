
#include "Game.h"

bool Game::startGame(Bord& bord, Renderer& renderer){
    int lives = bord.getLives();
    while (lives) {
        Round round(bord, renderer, lives);
        if (!round.init()) {
            return false;
        }
        int res = round.run();
        if (res == 0) {
            break;
        }
        
        Sleep(2000);
        if (res == 1) {
            break;
        }
        --lives;
        clrscr();
    }
    return true;
}