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
	Block(const std::vector<Point> &blockLocation) : currentLocation(blockLocation) {
		this->weight = blockLocation.size();
	}

	int getWeight() const { return weight; }
	std::vector<Point> getCurrentLocation() const{ return currentLocation; }
	std::vector<Point> getOldLocation() const{ return oldLocation; }
	void setCurrentLocation(const std::vector<Point>& points) {currentLocation = points;}

	friend std::ostream& operator <<(std::ostream& out, const Block& block) {
		std::cout << "Block location: ";
		for (auto& point : block.currentLocation) {
			std::cout << point << " ";
		}
		std::cout << std::endl <<"Weight: " << block.weight << std::endl;
		return out;
	}
};

