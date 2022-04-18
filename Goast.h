#pragma once
#include "Point.h"
#include "Utils.h"
class Goast
{
	Point position;
	Direction direction = Direction::Down;

public:
	Goast(int x = -1, int y = -1);
	Goast(const Point& p);
	Goast(const Goast& goast);
	void move(Direction dir , char bord[][width]);
	Point getLocation() const;
	Direction getDirection() const;
	void changeDirection();
	void setLocation(int x, int y);
	bool isEmpty() const;
	void operator =(const Goast& goast);
	bool operator ==(const Goast& goast);
	friend ostream& operator <<(ostream& out, const Goast& goast);
};

