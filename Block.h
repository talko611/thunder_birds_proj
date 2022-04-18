#pragma once
#include "Utils.h"
#include "Point.h"
#include <iostream>
#include <vector>

class Block
{
	std::vector<Point> currentLocation ,oldLocation;
	int weight;
	char character;
public:
	Block() {};
	Block(const vector<Point>& blockLocation);
	int getWeight() const;
	std::vector<Point> getCurrentLocation() const;
	std::vector<Point> getOldLocation() const;
	bool isEmpty() const;
	void setLocation(const vector<Point>& location);
	char getCharacter() const;
	void setCharacter(char ch);
	bool operator==(const Block& block) const;
	void operator= (const Block& block) ;
	friend ostream& operator <<(std::ostream& out, const Block& block);
};

