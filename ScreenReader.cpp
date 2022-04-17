#include "ScreenReader.h"
vector<string>& ScreenReader::getScreenFileNames()
{
	return this->screenFileNames;
}

void ScreenReader::readScreenFileNames()
{
	string fileName;
	for (auto& file : fs::directory_iterator(fs::current_path())) {
		fileName = file.path().string();
		if (fileName.find("screen") != string::npos) {
			this->screenFileNames.push_back(fileName);
		}
	}

	if (this->screenFileNames.empty()) {
		//To do : Handle Error
	}
	sort(this->screenFileNames.begin(), this->screenFileNames.end());
}

void  ScreenReader::readScreen(Bord& bord, int screenNum) const
{
	std::ifstream in(this->screenFileNames[screenNum]);
	if (!in.good()) {
		//Todo : handle error
	}
	string name;
	getline(in, name);
	bord.setName(name);

	int lives;
	in >> lives;
	bord.setLives(lives);

	int time;
	in >> time;
	bord.setTime(time);

	char** bordP = bord.getBord();
	string line;
	in.get();
	for (int i = 0; i < hight; i++) {
		getline(in, line);
		line.copy(bordP[i], width);//Check if there is a better way
	}

	in.close();
}
