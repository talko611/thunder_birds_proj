#include "Block.h"

Block::Block(const vector<Point>& blockLocation) : currentLocation(blockLocation) {
	this->weight = blockLocation.size();
}

int Block::getWeight() const { return weight; }

vector<Point> Block::getCurrentLocation() const { return currentLocation; }

vector<Point> Block::getOldLocation() const { return oldLocation; };

void Block::setLocation(const vector<Point>& location) { this->currentLocation = location;}

char Block::getCharacter() const { return this->character; }

void Block::setCharacter(char ch) { this->character = ch; }

bool Block::isEmpty() const { return this->currentLocation.empty(); }

bool Block::operator==(const Block& block) const {
	return this->currentLocation == block.currentLocation;
}

void Block::operator=(const Block& block)  {
	this->currentLocation = block.currentLocation;
	this->character = block.character;
	this->weight = block.weight;
}

ostream& operator <<(ostream& out, const Block& block) {
	out << "Block location: ";
	for (auto& point : block.currentLocation) {
		cout << point << " ";
	}
	return out << endl << "Weight: " << block.weight << std::endl << "Character: " << block.character << endl;;
	
}