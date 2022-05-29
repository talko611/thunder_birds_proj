#include "Game.h"

void Game::start() {
	hideCursor();
	if (init()) {
		while (this->userChoice != MenuChoice::Exit) {
			clrscr();
			run();
			this->userChoice = MenuChoice::Exit;
			if (mode == GameMode::record || mode == GameMode::regular) {
				this->userChoice = menu.getUserChoice(this->bord, this->fileManager, this->renderer);
				if (this->mode == GameMode::record && userChoice != MenuChoice::Exit) {
					this->fileManager.writeGameMode(this->userChoice);
				}
			}
		}
	}
	else {
		cout << "Somthing went Wrong! Could not start game\n";
		Sleep(2000);
	}
	clrscr();
	mode == GameMode::loadSilence ? cout << ' ' : cout << "Goodbye!";//To do- write better
}

bool Game::init() {
	if (this->fileManager.isNeedFilesExists(this->mode)) {
		if (this->mode == GameMode::regular || this->mode == GameMode::record) {
			this->userChoice = menu.getUserChoice(this->bord, this->fileManager, this->renderer);
			if (this->mode == GameMode::record) {
				this->fileManager.writeGameMode(this->userChoice);
			}
		}
		else {
			this->userChoice = this->fileManager.getLastGameMode();
			this->fileManager.readScreen(bord, this->fileManager.getCurrentFileNum());
		}
		if (!fileManager.setFilesByMode(this->mode)) {
			this->userChoice = MenuChoice::Exit;
		}
		return true;
	}
	return false;
}

void Game::run() 
{
	int res = 0;
	int maxStages = this->fileManager.getMaxStages();
	int currentStage = this->fileManager.getCurrentFileNum();
	Round* round = createRoundByMode();
	bool silenceCheck = false;
	if (round) {
		while (true)
		{
			if (!round->init()) {
				this->userChoice == MenuChoice::ChooseAndPlaySingle ?
					this->userChoice = MenuChoice::ChooseAndPlaySingle : this->userChoice = MenuChoice::Exit;
				cout << "Somthing went Wrong! Could not start game\n";
				break;
			}
			res = round->run();
			if (this->mode == GameMode::record) {
				this->fileManager.writeResult(res);
			}
			
			if (this->mode == GameMode::loadSilence || this->mode == GameMode::loadRun) {
				silenceCheck = checkResultVsRecorded(res);
				if (this->mode == GameMode::loadSilence && !silenceCheck ) {
					cout << "Test faild!";
					break;
				}
			}
			clrscr();
			if (res == 1) {
				if (this->userChoice == MenuChoice::PlayNewGame && currentStage < maxStages - 1) {
					this->fileManager.closeAll();
					this->fileManager.setCurrentFileNum(++currentStage);
					this->fileManager.readScreen(this->bord, currentStage);
					round->setRound(bord);
					this->fileManager.setFilesByMode(this->mode);
				}
				else {
					if (this->mode == GameMode::loadSilence) {
						silenceCheck ? cout << "Test passed!" : cout << "Test faild";
						cout << "\nPress any key to continue...";
						getch();
						break;
					}
					cout << "Congratulations You Won!";
					Sleep(2000);
					break;
				}
			}
			else if (res == -1) {
				int lives = this->bord.getLives();
				--lives;
				if (lives == 0) {
					if (this->mode == GameMode::loadSilence) {
						silenceCheck ? cout << "Test passed!" : cout << "Test faild";
						cout << "\nPress any key to continue...";
						getch();
						break;
					}
					cout << "You Lost :(";
					Sleep(2000);
					break;
				}
				this->bord.setLives(lives);
				round->setRound(this->bord);
			}
			else {
				
				if (this->mode == GameMode::loadSilence) {
					silenceCheck ? cout << "Test passed!" : cout << "Test faild";
					cout << "\nPress any key to continue...";
					getch();
				}
				break;
			}
		}
		clrscr();
	}
	else {
		this->userChoice == MenuChoice::Exit;
		cout << "Somthing went Wrong! Could not start game\n";
		Sleep(2000);
	}
	this->fileManager.closeAll();
	delete round;
}

Round* Game::createRoundByMode() {
	if (mode == GameMode::regular || mode == GameMode::record) {
		return new RoundByUser(this->bord, this->renderer, this->fileManager, this->mode);
	}
	else if (mode == GameMode::loadRun) {
		return  new RoundByFile(this->bord, this->renderer, this->fileManager, this->mode);
	}
	else {
		return  new RoundByFile(this->bord, this->renderer, this->fileManager, this->mode, 0);
	}
	return nullptr;
}

bool Game::checkResultVsRecorded(int gameResult) {
	int recordedRes;
	recordedRes = this->fileManager.readResult();
	return recordedRes == gameResult;
}
