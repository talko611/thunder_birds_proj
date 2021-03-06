#include "ScreenReader.h"
vector<string>& ScreenReader::getScreenFileNames()
{
	return this->screenFileNames;
}

bool ScreenReader::readScreenFileNames()
{
	string fileName;
	for (auto& file : fs::directory_iterator(fs::current_path())) {
		fileName = file.path().string();
		if (fileName.find("screen") != string::npos) {
			this->screenFileNames.push_back(fileName);
		}
	}

	if (this->screenFileNames.empty()) {
		return false;
	}
	sort(this->screenFileNames.begin(), this->screenFileNames.end());
	return true;
}

void  ScreenReader::readScreen(Bord& bord, int screenNum) const
{
	std::ifstream in(this->screenFileNames[screenNum]);
	if (!in.good()) {
		throw ios_base::failure("Couldn't open file ");
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
	int counter = 0;
	while(!in.eof()) {
		getline(in, line);
		if (line.size() != width || counter >= hight) {
			throw ios_base::failure("Incorrect file format");
		}
		line.copy(bordP[counter], width);
		counter++;
	}
	in.close();
}
