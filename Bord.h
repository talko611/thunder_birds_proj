#pragma once
#include <string>
#include "Utils.h"

class Bord
{
	constexpr static int hight = 25, width = 80;
	char** bord;
	string name;
	int lives;
	int time;
	
public:
	Bord();
	~Bord();
	char** getBord();
	int getLives() const;
	int getTime() const;
	string getName() const;
	int getbordHight() const;
	int getbordWidth() const;
	void setName(string name);
	void setLives(int lives);
	void setTime(int time);

	friend ostream& operator<<(ostream& out, const Bord& bord) {
		cout << "Screen Name: " << bord.name << endl;
		cout << "Lives: " <<bord.lives << endl;
		cout << "Time: " << bord.time << endl;
		return out;
	}
};

