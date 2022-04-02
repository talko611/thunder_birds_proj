#include "Round.h"


void Round::setShips() {
	for (auto& ship : ships) {
		char ch = ship.getShipCharacter();
		for (auto& point : ship.getCurrLoc()) {
			bord[point.getX()][point.getY()] = ch;
		}
	}
}

void Round::init() {
	hideCursor();
	setShips();
	setBlocks();
	renderer.printBord(bord, hight, width);
	renderer.printLegend(lives, time, activeShip);
}

bool Round::isWallAhead(const std::vector<Point> &position) const{
	bool answer = false;
	for (auto& point : position) {
		if (bord[point.getX()][point.getY()] == (char) objectAsciiVal::Wall1 || bord[point.getX()][point.getY()] == (char)objectAsciiVal::Wall2) {
			answer = true;
			break;
		}
	}
	return answer;
}

bool Round::isOtherShipAhead(const std::vector<Point>& position) const{
	bool answer = false;
	for (auto& point : position) {
		if (bord[point.getX()][point.getY()] == ships[!activeShip].getShipCharacter()) {
			answer = true;
			break;
		}
	}
	return answer;
}

bool Round::isValidkey(const char key) const {
	switch (key)
	{
	case (char) ValidKeys::SwitchToBig:
		if (shipFinished[1] == true)
		{
			return false;
		}
		else 
		{
			return true;
		}
	case (char)ValidKeys::SwitchToSmall:
		if (shipFinished[0] == true)
		{
			return false;
		}
		else
		{
			return true;
		}
	case (char)ValidKeys::Up:
		return true;
	case (char)ValidKeys::Down:
		return true;
	case (char)ValidKeys::Left:
		return true;
	case (char)ValidKeys::Right:
		return true;
	default:
		return false;
	}
}

int Round::run() {
	char key = 0;
	Direction dir = Direction::Stop;
	while(true)
	{
		
		do
		{
			moveFallingBlocks();
			if (!isShipDead()) {

				if (_kbhit())
				{
					key = tolower(_getch());
					if (isValidkey(key))
					{
						if (isSwitcherKey(key))
						{
							changeActiveShip(key);
							dir = Direction::Stop;
						}
						else
						{
							dir = (Direction)key;

						}
					}
				}
				playNextMove(dir);
			}
			this->renderer.renderNextMove(ships[activeShip], blocks, numOfBlocks, --time, activeShip, isWin());
			if (time == 0) {
				isLost = true;
			}
			Sleep(100);
		} while (key != (char)ValidKeys::ESC && !isLost && !isWin());

		if (isWin()) {
			renderer.printWinningMessage();
			return 1;
		}
		if (isLost) {
			renderer.printLosingMessage(lives);
			return -1;
		}
		key = 0;
		renderer.printPauseMessage();
		
		while (key != (char)ValidKeys::ESC && key != (char)ValidKeys::EXIT) {
			key = _getch();
			if (key == (char)ValidKeys::ESC) {
				break;
			}
			else if(key == (char)ValidKeys::EXIT){
				return 0;
			}
		}
		renderer.clearRow();
		renderer.printLegend(lives, time, activeShip);
		key = 0;
		dir = Direction::Stop;
	}
}
	

bool Round::isSwitcherKey(const char key)const {
	return key == (char)SwitchKeys::SwitchToBig
		|| key == (char)SwitchKeys::SwitchToSmall;
}

void Round::playNextMove(Direction& dir) {

	if (dir == Direction::Stop) {
		return;
	}

	std::vector<Point> nextMove;
	nextMove = ships[activeShip].getCurrLoc();
	setPointsOfNextMove(dir, nextMove);

	if (isWallAhead(nextMove) || isOtherShipAhead(nextMove)) {
		return;
	}
	else
	{
		Point p;
		if (isBlockAhead(nextMove, p)) {
			Block& saver = findBlock(p);
			int totalWeight = 0;
			if (!saver.getCurrentLocation().empty() && canMoveBlocks(saver, dir, &totalWeight)) {
				moveBlocks(saver, dir);
				moveShip(dir);
			}
			else
			{
				dir = Direction::Stop;
			}
		}
		else if (isExitPointAhead(nextMove)) {
			this->shipFinished[activeShip] = true;
			std::vector<Point>& saver = this->ships[activeShip].getCurrLoc();
			for (auto& point : saver) {
				this->bord[point.getX()][point.getY()] = ' ';
			}
			this->renderer.addPointsToErase(saver);
			dir = Direction::Stop;
			this->activeShip = !activeShip;
		}
		else
		{
			moveShip(dir);
		}
	}
}

void Round::setPointByDirection(Direction dir, Point& p) const {
	switch (dir) {
	case Direction::Up:
		p.set(p.getX() - 1, p.getY());
		break;
	case Direction::Down:
		p.set(p.getX() + 1, p.getY());
		break;
	case Direction::Left:
		p.set(p.getX(), p.getY() - 1);
		break;
	case Direction::Right:
		p.set(p.getX(), p.getY() + 1);
		break;
	case Direction::Stop:
		break;
	}
}

void Round::setPointsOfNextMove(Direction dir, std::vector<Point>& points) const {
	for (auto& point : points) {
		setPointByDirection(dir, point);
	}
}

void Round::moveShip(Direction dir) {
	ships[activeShip].move(dir);

	for (auto& point : ships[activeShip].getOldLoc()) {
		bord[point.getX()][point.getY()] = ' ';
	}
	char shipCharacter = ships[activeShip].getShipCharacter();
	for (auto& point : ships[activeShip].getCurrLoc()) {
		bord[point.getX()][point.getY()] = shipCharacter;
	}
	this->renderer.addPointsToErase(ships[activeShip].getOldLoc());
}

void Round::initBlocks() {
	std::vector<Point> points = { {14,36} };
	blocks[0] = Block(points);
	points.clear();
	points.insert(points.begin(), { {4,18}, {5,18} });
	blocks[1] = Block(points);
	points.clear();
	points.insert(points.begin(), { {4,56}, {5,56} });
	blocks[2] = Block(points);
}

void Round::setBlocks() {
	for (auto& block : blocks) {
		for (auto& point : block.getCurrentLocation()) {
			bord[point.getX()][point.getY()] = (char) objectAsciiVal::Block;
		}
	}
}

bool Round::isBlockAhead(const std::vector<Point>& position, Point& saver) const {
	bool result = false;
	for (auto& point : position) {
		if (bord[point.getX()][point.getY()] == (char)objectAsciiVal::Block) {
			saver = point;
			result = true;
			break;
		}
	}
	return result;
}

Block& Round::findBlock(const Point& pointOfBlock)
{
	for (int i = 0; i < this->numOfBlocks; i++) {
		for (auto& point : blocks[i].getCurrentLocation()) {
			if (point == pointOfBlock) {
				return blocks[i];
			}
		}
	}
	return Block();
}

bool Round::canMoveBlocks(const Block& block, Direction dir, int* totalWeight){ // Remove const from hear - not sure is the best sulotion
	std::vector<Point> nextMove = block.getCurrentLocation();
	setPointsOfNextMove(dir, nextMove);
	Point saver;
	*totalWeight += block.getWeight(); // add block's weight;

	if (isWallAhead(nextMove) || isOtherShipAhead(nextMove))
	{
		return false;
	}
	if (isBlockAhead(nextMove, saver)) {
		Block& nextBlock = findBlock(saver);
		return canMoveBlocks(nextBlock, dir, totalWeight);
	}
	return (ships[activeShip].getWeightCanMove() >= *totalWeight);
}


bool Round::isExitPointAhead(const std::vector<Point>& position) const
{
	bool result = false;
	for (auto& point : position) {
		if (bord[point.getX()][point.getY()] == '!') 
		{
			result = true;
		}
	}
	return result;
}

void Round::moveBlocks(Block& block, Direction dir) 
{
	std::vector <Point> next = block.getCurrentLocation();
	setPointsOfNextMove(dir, next);
	Point saver;

	if (isBlockAhead(next, saver)) {
		Block& nextBlock = findBlock(saver);
		moveBlocks(nextBlock, dir);
	}
	moveBlock(block, dir);
}

void Round::moveBlock(Block& block, Direction dir) {
	std::vector<Point> location = block.getCurrentLocation();
	this->renderer.addPointsToErase(location);
	for (auto& point : location) {
		this->bord[point.getX()][point.getY()] = ' ';
	}
	setPointsOfNextMove(dir, location);//Move block location to the next location according to direction
	block.setCurrentLocation(location);
	for (auto& point : location) {
		this->bord[point.getX()][point.getY()] = (char)objectAsciiVal::Block;
	}
}

void Round:: moveFallingBlocks() {
	std::vector<Block*> fallingBlocks;
	for (auto& block : blocks) {
		isBlockFalling(block, fallingBlocks);
	}
	for (auto& block : fallingBlocks) {
		moveBlock(*block, Direction::Down);
	}
}

bool Round::isBlockFalling(Block& block, std::vector<Block*>& fallingBlocks)
{
	std::vector<Point> next = block.getCurrentLocation();
	setPointsOfNextMove(Direction::Down, next);
	int shipIndex;
	Point saver;

	if (isShipAhead(next, &shipIndex)) {
		if (this->ships[shipIndex].getWeightCanMove() < block.getWeight()) {
			isLost = true;
		}
		return false;
	}
	if (isWallAhead(next)) {
		return false;
	}
	
	if (isBlockAhead(getFloatingPoints(block, Direction::Down), saver)) {
		Block& nextBlock = findBlock(saver);
		if (nextBlock.getCurrentLocation().empty() && isBlockFalling(nextBlock, fallingBlocks)) {
			if (isPointUnique(block.getCurrentLocation()[0], fallingBlocks)) {		
				fallingBlocks.push_back(&block);
			}
			return true;
		}
		return false;
	}
	if(isPointUnique(block.getCurrentLocation()[0], fallingBlocks)) {
		fallingBlocks.push_back(&block);
	}
	return true;
}

std::vector<Point> Round::getFloatingPoints(const Block& block, Direction dir) const {
	std::vector<Point> next = block.getCurrentLocation();
	std::vector<Point> result;
	setPointsOfNextMove(dir, next);
	for (auto& point : next) {
		bool found = false;
		for (auto& pointOfBlock : block.getCurrentLocation()) {
			if (pointOfBlock == point) {
				found = true;
			}
		}

		if (found == false) {
			result.push_back(point);
		}
	}

	return result;
}

bool Round::isShipAhead(const std::vector<Point>& position, int* index) const{
	bool answer = false;
	int x, y;
	for (auto& point : position) {
		x = point.getX();
		y = point.getY();
		if (bord[x][y] == (char) objectAsciiVal::BigShip ) {
			*index = 1;
			answer = true;
			break;
		}
		else if (bord[x][y] == (char)objectAsciiVal::SmallShip) {
			*index = 0;
			answer = true;
			break;
		}
	}
	return answer;
}

bool Round::isPointUnique(const Point& p, std::vector<Block*>& fallingBlocks) const {
	bool answer = true;
	for (auto& block : fallingBlocks) {
		for (auto& point : block->getCurrentLocation()) {
			if (point == p) {
				answer = false;
				break;
			}
		}
	}
	return answer;
}

void Round::changeActiveShip(char key){
	if (key == (char)ValidKeys::SwitchToBig) {
		if (!shipFinished[1]) {
			activeShip = 1;
		}
	}
	else if (!shipFinished[0]) {
		activeShip = 0;
	}
}

bool Round::isWin() const{
	return shipFinished[1] && shipFinished[0];
}

bool Round::isShipDead() 
{
	bool result = false;
	std::vector<Block> blocksOnShip;
	for (const auto& ship : ships) {
		for (const auto& block : blocks) {
			std::vector<Point> below = block.getCurrentLocation();
			setPointsOfNextMove(Direction::Down, below);
			bool answer = false;
			char shipCharacter = ship.getShipCharacter();
			for (const auto& point : below) {
				if (bord[point.getX()][point.getY()] == shipCharacter) {
					answer = true;
				}
			}
			if (answer) {
				blocksOnShip.push_back(block);
			}
		}
		int totalWeight = 0;
		for (const auto& block : blocksOnShip) {
			totalWeight += block.getWeight();
		}
		if (totalWeight > ship.getWeightCanMove()) {
			this->isLost = true;
			result = true;
			break;
		}
	}
	return result;
}

