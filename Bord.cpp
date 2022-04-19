#include "Bord.h"

Bord::Bord()
{
	this->bord = new char* [hight] {};
	for (int i = 0; i < hight; i++)
		bord[i] = new char[width] {};

	this->lives = this->time = 0;
}

Bord::Bord(const Bord& bord) {
	this->bord = bord.bord;
	this->lives = bord.lives;
	this->time = bord.time;
}

Bord::~Bord()
{
	for (int i = 0; i < hight; i++)
		delete[] bord[i];
	delete bord;
}

char** Bord::getBord(){return bord;}

int Bord::getLives() const{return this->lives;}

int Bord::getTime() const{return this->time;}

string Bord::getName() const{return this->name;}

void Bord::setName(string name){this->name = name;}

void Bord::setLives(int lives){this->lives = lives;}

void Bord::setTime(int time){this->time = time;}

ostream& operator<<(ostream& out, const Bord& bord) {
	cout << "Screen Name: " << bord.name << endl;
	cout << "Lives: " << bord.lives << endl;
	cout << "Time: " << bord.time << endl;
	return out;
}

