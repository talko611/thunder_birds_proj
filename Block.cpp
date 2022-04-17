#include "Block.h"

Block::Block(const vector<Point>& blockLocation) : currentLocation(blockLocation) {
	this->weight = blockLocation.size();
}

int Block::getWeight() const { return weight; }

vector<Point> Block::getCurrentLocation() const { return currentLocation; }

vector<Point> Block::getOldLocation() const { return oldLocation; };

void Block::setLocation(const vector<Point>& location) { this->currentLocation = location;}

ostream& operator <<(std::ostream& out, const Block& block) {
	out << "Block location: ";
	for (auto& point : block.currentLocation) {
		std::cout << point << " ";
	}
	out << std::endl << "Weight: " << block.weight << std::endl;
	return out;
}