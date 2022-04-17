#pragma once
#include "Utils.h"
#include "Point.h"
#include <iostream>
#include <vector>

class Block
{
	std::vector<Point> currentLocation ,oldLocation;
	int weight;
public:
	Block() {};
	Block(const vector<Point>& blockLocation);
	int getWeight() const;
	std::vector<Point> getCurrentLocation() const;
	std::vector<Point> getOldLocation() const;
	void setLocation(const vector<Point>& location);
	friend ostream& operator <<(std::ostream& out, const Block& block);
};

