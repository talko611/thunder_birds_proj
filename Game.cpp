
#include "Game.h"

void Game::startGame(Bord& bord, Renderer& renderer){
    int lives = bord.getLives();
    while (lives) {
        Round round(bord, renderer);
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