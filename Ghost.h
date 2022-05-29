#pragma once
#include "Point.h"
#include "Utils.h"
class Ghost
{
	Point location;
	Direction direction;
	char sign;

public:
	Ghost() = delete;
	Ghost(const Ghost& g) = delete;
	Ghost(const Point& p, Direction dir, char sign): location(p), direction(dir), sign(sign){}
	Ghost(const int x, int y , Direction dir, char sign): location(Point(x,y)),direction(dir), sign(sign){}
	Point getLocation()const { return this->location; }
	void setLocation(const Point& p) { this->location = p; }
	Direction getDirection() const { return this->direction; }
	void setDirection(Direction dir) { this->direction = dir; }
	char getSign() const { return this->sign; }
	virtual bool move(char bord[][width]) = 0;
	virtual bool moveByDir(char bord[][width], Direction dir) = 0;
	virtual void changeDirection() = 0;
	friend ostream& operator<<(ostream& out, const Ghost& g) {
		return out << "Location: " << g.location << endl;

	}

	bool operator==(const Ghost& g) {
		return (this->location == g.location && this->sign == g.sign && this->direction == g.direction);
	}
};

