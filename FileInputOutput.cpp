#include "FileInputOutput.h"

void FileInputOutput::readFilesNamesByMode(GameMode mode) {
	string fileName , fileEnding;
	size_t endingLocation;
	for (const auto& file : fs::directory_iterator(fs::current_path())) {
		fileName = file.path().string();
		endingLocation = fileName.find('.');
		if (endingLocation != string::npos) {
			fileEnding = fileName.substr(endingLocation + 1, fileName.length() - (endingLocation + 1));
		}
		
		

		if (mode == GameMode::regular) {
			if (fileEnding == "screen") {
				this->inputFilesNames.push_back(fileName);
			}
		}
		else  {
			if (fileEnding == "screen")
			{
				this->inputFilesNames.push_back(fileName);
			}
			else if (fileEnding == "steps"){
				this->stepsFilesNames.push_back(fileName);
			}
			else if (fileEnding == "result"){
				this->resultFilesNames.push_back(fileName);
			}
			else if (fileEnding == "deatails") {
				this->lastRecordedFileName = fileName;
			}
		}
	}
}

bool FileInputOutput::isNeedFilesExists(GameMode mode) const {
	if (mode == GameMode::regular || mode == GameMode::record) {
		return !inputFilesNames.empty() ;
	}
	else  {
		return !inputFilesNames.empty() 
			&& (inputFilesNames.size() == stepsFilesNames.size())
			&& (stepsFilesNames.size() == resultFilesNames.size())
			&& !lastRecordedFileName.empty();
	}
}

void FileInputOutput::readScreen(Bord& bord, int screenNum){
	this->inOut1.open(this->inputFilesNames[screenNum], ios_base::in);
	if (!inOut1.good()) {
		throw ios_base::failure("Couldn't open file ");
	}
	string name;
	getline(inOut1, name);
	bord.setName(name);

	int lives;
	inOut1 >> lives;
	bord.setLives(lives);

	int time;
	inOut1 >> time;
	bord.setTime(time);

	char** bordP = bord.getBord();
	string line;
	inOut1.get();
	int counter = 0;
	while (!inOut1.eof()) {
		getline(inOut1, line);
		if (line.size() != width || counter >= hight) {
			throw ios_base::failure("Incorrect file format");
		}
		line.copy(bordP[counter], width);
		counter++;
	}
	inOut1.close();
}

void FileInputOutput::writeWandringGhostMove(const Ghost& g) {
	if (g.getSign() == (char)objectAsciiVal::WandringGhost) {
		string ch = getStringByKey((char)g.getDirection());
		inOut1 << ch << ' ';
	}
}

void FileInputOutput::writeCurrentKey(char key) {
	string chToPrint = getStringByKey(tolower(key));
	inOut1 << endl << chToPrint << endl;
}

string FileInputOutput::getStringByKey(char key) const {
	
	string actionToPrint;
	switch (key)
	{
	case (char)ValidKeys::Down:
		actionToPrint = "Down";
		break;
	case (char)ValidKeys::Up:
		actionToPrint = "Up";
		break;
	case (char)ValidKeys::Left:
		actionToPrint = "Left";
		break;
	case (char)ValidKeys::Right:
		actionToPrint = "Right";
		break;
	case (char)ValidKeys::SwitchToBig:
		actionToPrint = "Big";
		break;
	case (char)ValidKeys::SwitchToSmall:
		actionToPrint = "Small";
		break;
	case (char)ValidKeys::ESC:
		actionToPrint = "ESC";
		break;
	case (char)ValidKeys::EXIT:
		actionToPrint = "Exit";
		break;
	default:
		actionToPrint = "Null";
		break;
	}
	return actionToPrint;

	
}

bool  FileInputOutput::setFilesByMode(GameMode mode) {
	if (mode == GameMode::record) {
		this->inOut1.open(this->stepsFilesNames[this->currentFileNum], ios_base::out);
		this->inOut2.open(this->resultFilesNames[this->currentFileNum], ios_base::out);
	}
	else if (mode == GameMode::loadRun || mode == GameMode::loadSilence) {
		this->inOut1.open(this->stepsFilesNames[this->currentFileNum], ios_base::in);
		this->inOut2.open(this->resultFilesNames[this->currentFileNum], ios_base::in);
	}
	
	return inOut1.good() && inOut2.good();
}

void FileInputOutput::closeAll() {
	inOut1.close();
	inOut2.close();
}

void FileInputOutput::writeResult(int result) {
	string str;
	switch (result)
	{
	case 1:
		str = "win";
		break;
	case -1:
		str = "lost";
		break;
	case 0:
		str = "Exit";
		break;
	default:
		break;
	}
	
	this->inOut2 << str <<  endl;
}

void FileInputOutput::writeTime(int time)
{
	this->inOut2 << time << ' ';
}

int FileInputOutput::getEndRoundTime() 
{
	int res;
	this->inOut2 >> res;
	return res;
}

char FileInputOutput::getNextKeyInput() {
	
	string str;
	this->inOut1 >> str;
	char res = 0;
	if (str == "Up") {
		res = (char)ValidKeys::Up;
	}
	else if (str == "Down") {
		res = (char)ValidKeys::Down;
	}
	else if (str == "Left") {
		res = (char)ValidKeys::Left;
	}
	else if (str == "Right") {
		res = (char)ValidKeys::Right;
	}
	else if (str == "Big") {
		res = (char)ValidKeys::SwitchToBig;
	}
	else if (str == "Small") {
		res = (char)ValidKeys::SwitchToSmall;
	}
	else if (str == "ESC") {
		res = (char)ValidKeys::ESC;
	}
	else if (str == "Exit") {
		res = (char)ValidKeys::EXIT;
	}
	return res;
}

int FileInputOutput::readResult() {
	string str;
	this->inOut2 >> str;

	if (str == "win") {
		return 1;
	}
	else if (str == "lost") {
		return -1;
	}
	else {
		return 0;
	}
}

MenuChoice FileInputOutput::getLastGameMode() {
	this->inOut1.open(lastRecordedFileName, ios_base::in);
	if (!this->inOut1.good()) {
		return MenuChoice::Exit;
	}
	string str;
	int fileNum;
	getline(this->inOut1, str);
	this->inOut1 >> fileNum;
	this->currentFileNum = fileNum;
	this->inOut1.close();
	if (str == "Full Game") {
		return MenuChoice::PlayNewGame;
	}
	return MenuChoice::ChooseAndPlaySingle;
}

bool FileInputOutput::writeGameMode(MenuChoice choice) {
	this->inOut1.open(this->lastRecordedFileName, ios_base::out);
	if (!this->inOut1.good()) {
		return false;
	}
	if (choice == MenuChoice::PlayNewGame) {
		this->inOut1 << "Full Game" << endl <<  this->currentFileNum;
	}
	else {
		this->inOut1 << "Single Game" << endl << this->currentFileNum;
	}
	this->inOut1.close();
	return true;
}

Direction FileInputOutput::readGhostNextDir() {
	string str;
	this->inOut1 >> str;
	if (str == "Up"){
		return Direction::Up;
	}
	else if (str == "Down") {
		return Direction::Down;
	}
	else if (str == "Left") {
		return Direction::Left;
	}
	else if (str == "Right") {
		return Direction::Right;
	}
	else {
		return Direction::Stop;
	}
}


