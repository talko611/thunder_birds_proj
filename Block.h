#pragma once
#include "Utils.h"
#include "Point.h"
#include <iostream>
#include <vector>

class Block
{
	vector<Point> currentLocation;
	int weight = 0;
	char character = -1;
public:
	Block() {};
	Block(const vector<Point>& blockLocation);
	int getWeight() const;
	const vector<Point>& getCurrentLocation() const;
	char getCharacter() const;
	void setLocation(const vector<Point>& location);
	void setCharacter(char ch);
	bool operator==(const Block& block) const;
	void operator= (const Block& block) ;
	friend ostream& operator <<(ostream& out, const Block& block);
};

