#pragma once
#include "Point.h"
#include "Utils.h"
class Goast
{
	Point position;
	Direction direction = Direction::Down;

public:
	Goast() {};
	Goast(int x, int y);
	Goast(const Point& p);
	Goast(const Goast& goast);
	void move(Direction dir);
	Point getLocation() const;
	void setLocation(int x, int y);
	void operator =(const Goast& goast);
	bool operator ==(const Goast& goast);
	friend ostream& operator <<(ostream& out, const Goast& goast);
};

