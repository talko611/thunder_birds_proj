#include "RoundByUser.h"

int RoundByUser::run() {
	char key = 0;
	Direction dir = Direction::Stop;
	GameMode mode = getMode();
	FileInputOutput& recorder = getFileManeger();
	Renderer& renderer = getRenderer();
	int lives = getLives();
	int time = getTime();
	int sleepTime = getSleepTime();
	if (mode == GameMode::record) {
		recorder.writeCurrentKey(key);
	}

	while (true)
	{
		do
		{
			moveFallingBlocks();
			moveGoasts();
			if (!getIsLost()) {
				if (_kbhit())
				{
					key = tolower(_getch());

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
				}
				if (mode == GameMode::record) {
					recorder.writeCurrentKey(key);
				}
				playNextMove(dir, key);
			}
			renderer.renderNextMove(--time, getActiveShip(), getBlocks());
			if (time == 0) {
				setIsLost(true);
			}
			Sleep(sleepTime);
		} while (key != (char)ValidKeys::ESC && !getIsLost() && !isWin());

		

		if (isWin()) {
			if (mode == GameMode::record) {
				recorder.writeTime(time);
			}
			renderer.clearRow();
			resetObjects();
			return 1;
		}
		if (getIsLost()) {
			if (mode == GameMode::record) {
				recorder.writeTime(time);
			}
			renderer.printLosingMessage(lives);
			resetObjects();
			return -1;
		}
		key = 0;
		if (mode == GameMode::record) {
			recorder.writeCurrentKey(key);
		}
		renderer.printPauseMessage();

		while (key != (char)ValidKeys::ESC && key != (char)ValidKeys::EXIT) {
			key = tolower( _getch());
			if (mode == GameMode::record) {
				recorder.writeCurrentKey(key);
			}
			if (key == (char)ValidKeys::ESC) {
				break;
			}
			else if (key == (char)ValidKeys::EXIT) {
				if (mode == GameMode::record) {
					recorder.writeTime(time);
				}
				resetObjects();
				return 0;
			}
		}
		renderer.clearRow();
		renderer.printLegend(lives, time, getActiveShip());
		key = 0;
		if (mode == GameMode::record) {
			recorder.writeCurrentKey(key);
		}
		dir = Direction::Stop;
	}
}
