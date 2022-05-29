#pragma once
#include "Utils.h"
#include "Bord.h"
#include "Renderer.h"
#include "Menu.h"
#include "FileInputOutput.h"
#include "RoundByFile.h"
#include "RoundByUser.h"

class Game
{
	GameMode mode;
	MenuChoice userChoice;
	Bord bord;
	Renderer renderer;
	Menu menu;
	FileInputOutput fileManager;

	void run();
	Round* createRoundByMode();
	bool checkResultVsRecorded(int gameResult) ;
	bool init();

public:
	Game(GameMode mode = GameMode::regular, MenuChoice choice = MenuChoice::PlayNewGame, bool color = true) :
		mode(mode), userChoice(choice), bord(Bord()), renderer(Renderer(color)), menu(Menu()), fileManager(FileInputOutput(mode)) {}
	void start();
};



