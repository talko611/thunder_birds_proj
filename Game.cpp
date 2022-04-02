
#include "Game.h"

void Game::startGame(){
    while (lives) {
        Round round(lives, color);
        round.init();
        int res = round.run();
        lives--;
        if (res == 0) {
            break;
        }
        
        Sleep(2000);
        if (res == 1) {
            break;
        }
        clrscr();
    }
}