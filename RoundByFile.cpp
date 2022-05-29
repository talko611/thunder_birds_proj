#include "RoundByFile.h"
int RoundByFile::run() {
	Direction dir = Direction::Stop;
	GameMode mode = getMode();
	FileInputOutput& fileManeger = getFileManeger();
	Renderer& renderer = getRenderer();
	int lives = getLives();
	int time = getTime();
	int endTime = fileManeger.getEndRoundTime();
	int sleepTime = getSleepTime();
	char key = fileManeger.getNextKeyInput();
	const auto p1 = chrono::system_clock::now();
	

	while (true)
	{
		while (key != (char)ValidKeys::ESC && !getIsLost() && !isWin()) {
			moveFallingBlocks();
			moveGoasts();
			key = fileManeger.getNextKeyInput();
			if (isValidkey(key))
			{
				if (isSwitcherKey(key))
				{
					if (changeActiveShip(key)) {
						dir = Direction::Stop;
					}
				}
				else
				{
					dir = (Direction)key;
				}
			}
			playNextMove(dir, key);
			--time;
			if (mode == GameMode::loadRun) {
				renderer.renderNextMove(time, getActiveShip(), getBlocks());
				Sleep(sleepTime);
			}
			if (time == 0) {
				setIsLost(true);
			}
		}

		if (isWin()) {
			if (mode == GameMode::loadRun) {
				renderer.clearRow();
			}
			
			resetObjects();
			return 1;
		}
		if (getIsLost()) {
			if (mode == GameMode::loadRun) {
				renderer.printLosingMessage(lives);
			}
			resetObjects();
			return -1;
		}
		key = fileManeger.getNextKeyInput();
		if (mode == GameMode::loadRun) {
			renderer.printPauseMessage();
			Sleep(3000);
		}
		
		while (key != (char)ValidKeys::ESC && key != (char)ValidKeys::EXIT) {
			key = fileManeger.getNextKeyInput();
			if (key == (char)ValidKeys::ESC) {
				break;
			}
			else if (key == (char)ValidKeys::EXIT) {
				return 0;
			}
		}
		if (mode == GameMode::loadRun) {
			renderer.clearRow();
			renderer.printLegend(lives, time, getActiveShip());
		}
		key = fileManeger.getNextKeyInput();
		dir = Direction::Stop;
	}
}
