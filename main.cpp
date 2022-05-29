#include <iostream>
#include "Game.h"

GameMode setGameMode(const vector<string>& programArg);
vector<string> getProgramArg(int argc, char* argv[]);

int main(int argc, char* argv[]) {
	try {
		vector<string>& proArg = getProgramArg(argc, argv);
		GameMode mode = setGameMode(proArg);
		Game game(mode);
		game.start();
	}
	catch(exception& e){
		cout << e.what();
	}
}

vector<string> getProgramArg(int argc, char* argv[]) {
	vector<string> arguments;
	arguments.reserve(2);
	for (int i = 1; i < argc; ++i) {
		arguments.push_back(argv[i]);
	}
	return arguments;
}

GameMode setGameMode(const vector<string>& programArg) {
	if (programArg.empty()) {
		return GameMode::regular;
	}
	else if (programArg[0].find("save") != string::npos) {
		return GameMode::record;
	}
	else if (programArg[0].find("load") != string::npos ) {
		if (programArg.size() == 2) {
			if (programArg[1].find("silent") != string::npos) {
				return GameMode::loadSilence;
			}
			else {
				return GameMode::loadRun;
			}
		}
		else {
			return GameMode::loadRun;
		}
	}
	else {
		throw invalid_argument("Unknown command ");
	}
}