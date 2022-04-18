#include "Round.h"

Round::Round(Bord& bord, Renderer& renderer) : renderer(renderer){
	char** pBord = bord.getBord();
	for (int i = 0; i < hight; i++) {
		for (int j = 0; j < width; j++) {
			this->bord[i][j] = pBord[i][j];
		}
	}
	this->lives = bord.getLives();
	this->time = bord.getTime();
}

void Round::readObjectsFromBord()
{
	//To do: error handling - try to read more than on ship and more than one legend point
	bool isSmallShipReaded = false;
	bool isBigShipReaded = false;
	
	for (int i = 0; i < hight; i++) {
		for (int j = 0; j < width; j++) {
			if (!isSmallShipReaded && this->bord[i][j] == (char)objectAsciiVal::SmallShip) {
				ships[0].setLocation(vector<Point> { {i, j}, { i,j + 1 }});
				isSmallShipReaded = true;
			}
				
			else if (!isBigShipReaded && this->bord[i][j] == (char)objectAsciiVal::BigShip) {
				ships[1].setLocation(vector <Point> { {i, j}, { i, j + 1 }, { i + 1, j }, { i + 1, j + 1 }});
				isBigShipReaded = true;
			}

			else if (bord[i][j] >= '1' && bord[i][j] <= '9') {
				vector<Point> temp;
				Point curr(i, j);
				readBlock(temp, curr, bord[i][j]);
				if (!temp.empty()) {
					Block block(temp);
					block.setCharacter(bord[i][j]);
					blocks.push_back(block);
					temp.clear();
				}
			}
			else if (bord[i][j] == '$') {
				this->goats.push_back(Goast(i, j));
			}

			else if (bord[i][j] == '&') {
				renderer.setLegendPosition(i, j);
			}
		}
	}
}

void Round::readBlock(vector<Point>& points, Point& temp, char objectCh) {
	int x = temp.getX();
	int y = temp.getY();

	if (this->bord[x][y] == objectCh && !isPointAlreadyAdded(points, temp) && !isPointBelongToExsistingBlock(temp)) {
		points.push_back(Point(x, y));
		temp.set(x - 1, y);
		readBlock(points, temp, objectCh);
		temp.set(x -1, y + 1);
		readBlock(points, temp, objectCh);
		temp.set(x - 1, y - 1);
		readBlock(points, temp, objectCh);
		temp.set(x, y - 1);
		readBlock(points, temp, objectCh);
		temp.set(x, y + 1);
		readBlock(points, temp, objectCh);
		temp.set(x + 1, y - 1);
		readBlock(points, temp, objectCh);
		temp.set(x + 1, y);
		readBlock(points, temp, objectCh);
		temp.set(x + 1, y + 1);
		readBlock(points, temp, objectCh);
	}
}

bool Round::isPointBelongToExsistingBlock(const Point& p) {
	for (auto& block : this->blocks) {
		for (auto& point : block.getCurrentLocation()) {
			if (point == p) {
				return true;
			}
		}
	}
	return false;
}

bool Round::isPointAlreadyAdded(vector<Point>& points, const Point& p) {
	for (auto& point : points) {
		if (point == p) {
			return true;
		}
	}
	return false;
}

void Round::init() {
	readObjectsFromBord();
	renderer.printBord(this->bord);
	renderer.printLegend(lives, time, activeShip);
}

int Round::run() {
	char key = 0;
	Direction dir = Direction::Stop;
	while (true)
	{
		do
		{
			moveFallingBlocks();
			moveGoasts();
			if (!isShipDead() && !isLost) {

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
			/*this->renderer.renderNextMove(ships[activeShip], blocks, numOfBlocks, --time, activeShip, isWin());*/
			clrscr();
			renderer.printBord(this->bord);
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
			else if (key == (char)ValidKeys::EXIT) {
				return 0;
			}
		}
		renderer.clearRow();
		renderer.printLegend(lives, time, activeShip);
		key = 0;
		dir = Direction::Stop;
	}
}

vector<Point> Round::getObjectFloatingPoints(const vector<Point>& current, Direction dir) const {
	std::vector<Point> next = current;
	std::vector<Point> result;
	setPointsOfNextMove(dir, next);
	for (const auto& point : next) {
		bool found = false;
		for (const auto& pointOfObject : current) {
			if (pointOfObject == point) {
				found = true;
				break;
			}
		}

		if (found == false) {
			result.push_back(point);
		}
	}

	return result;
}

void Round::moveFallingBlocks() {
	std::vector<Block*> fallingBlocks;
	for (auto& block : blocks) {
		int totalWeight = 0;
		addFallingBlocks(block, fallingBlocks, &totalWeight);
	}
	for (auto& block : fallingBlocks) {
		moveBlock(*block, Direction::Down);
	}
}

bool Round::addFallingBlocks(Block& block, vector<Block*>& fallingBlocks, int* totalWeight)
{
	std::vector<Point> next = getObjectFloatingPoints(block.getCurrentLocation(),Direction::Down);
	int shipIndex;
	Point pointSaver;
	*totalWeight += block.getWeight();

	if (isObjectOutOfBounderies(block.getCurrentLocation())) {
		deleteBlock(block);
		return false;
	}
	if (isShipAhead(next, &shipIndex)) {
		if (this->ships[shipIndex].getWeightCanMove() < *totalWeight) {
			isLost = true;
		}
		return false;
	}
	if (isWallAhead(next)) {
		return false;
	}
	if (isGoastAhead(next, pointSaver)) {
		Goast& goastSaver = findGoast(pointSaver);
		if (!goastSaver.isEmpty()) {
			deleteGoast(goastSaver);
		}
		return true;
	}

	if (isBlockAhead(next, pointSaver)) {
		Block& nextBlock = findBlock(pointSaver);
		if (!nextBlock.isEmpty() && addFallingBlocks(nextBlock, fallingBlocks,totalWeight)) {
			if (isPointUnique(block.getCurrentLocation()[0], fallingBlocks)) {
				fallingBlocks.push_back(&block);
			}
			return true;
		}
		return false;
	}
	if (isPointUnique(block.getCurrentLocation()[0], fallingBlocks)) {
		fallingBlocks.push_back(&block);
	}
	return true;
}

bool Round::isShipAhead(const vector<Point>& position, int* index) const {
	bool answer = false;
	int x, y;
	for (auto& point : position) {
		x = point.getX();
		y = point.getY();
		if (bord[x][y] == (char)objectAsciiVal::BigShip) {
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

bool Round::isWallAhead(const vector<Point>& position) const {
	bool answer = false;
	for (auto& point : position) {
		int x = point.getX();
		int y = point.getY();
		if (bord[x][y] == (char)objectAsciiVal::Wall1 
			|| bord[x][y] == (char)objectAsciiVal::Wall2) {
			answer = true;
			break;
		}
	}
	return answer;
}

bool Round::isBlockAhead(const vector<Point>& position, Point& saver) const {
	bool result = false;
	int x, y;
	for (auto& point : position) {
		x = point.getX();
		y = point.getY();
		if (bord[x][y] >= (char) objectAsciiVal::BlockLowestVal && bord[x][y] <= (char)objectAsciiVal::BlockHighestVal) {
			saver = point;
			result = true;
			break;
		}
	}
	return result;
}

bool Round::isGoastAhead(const vector<Point>& position, Point& saver) const {
	int x, y;
	for (const auto& point : position) {
		x = point.getX();
		y = point.getY();
		if (bord[x][y] == (char)objectAsciiVal::Goast) {
			saver.set(x, y);
			return true;
		}
	}
	return false;
}

Goast& Round::findGoast(const Point& point) {
	for (auto& goast : this->goats) {
		if (point == goast.getLocation()) {
			return goast;
		}
	}
	return Goast();
}

void Round::setPointsOfNextMove(Direction dir, vector<Point>& points) const {
	for (auto& point : points) {
		setPointByDirection(dir, point);
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

void Round::moveGoasts() {
	Direction currDir;
	Point currLoc ,next;
	int x, y;
	for (auto& goast : this->goats) {
		currDir = goast.getDirection();
		currLoc = goast.getLocation();
		next = currLoc;
		setPointByDirection(currDir, next);
		x = next.getX();
		y = next.getY();

		if (bord[x][y] == (char)objectAsciiVal::Wall1 
			|| bord[x][y] == (char)objectAsciiVal::Wall2 
			|| (bord[x][y] >= (char)objectAsciiVal::BlockLowestVal && bord[x][y] <= (char) objectAsciiVal::BlockHighestVal)) {
			goast.changeDirection();
		}
		else if (bord[x][y] == (char)objectAsciiVal::BigShip || bord[x][y] == (char)objectAsciiVal::SmallShip) {
			this->isLost = true;
			break;
		}
		else if (isObjectOutOfBounderies(next)) {
			deleteGoast(goast);
		}
		else {
			renderer.addPointToErase(goast.getLocation());
			goast.move(currDir, this->bord);
			this->renderer.addPointsOfGoast(next);
		}
	}
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

bool Round::isSwitcherKey(const char key)const {
	return key == (char)SwitchKeys::SwitchToBig
		|| key == (char)SwitchKeys::SwitchToSmall;
}

void Round::playNextMove(Direction& dir) {
	if (dir == Direction::Stop) {
		return;
	}

	Point temp;
	vector<Point> nextMove = getObjectFloatingPoints(this->ships[this->activeShip].getCurrLoc(), dir);

	if (isGoastAhead(nextMove, temp)) {
		this->isLost = true;
		return;
	}
	else if (isWallAhead(nextMove) || isOtherShipAhead(nextMove)) {
		return;
	}
	else
	{
		if (isBlockAhead(nextMove, temp)) {
			Block& saver = findBlock(temp);
			int totalWeight = 0;
			if (!saver.isEmpty() && canMoveBlocks(saver, dir, &totalWeight)) {
				/*moveBlocks(saver, dir);
				moveShip(dir);*/
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


Block& Round::findBlock(const Point& pointOfBlock)
{
	for (auto& block : this->blocks) {
		for (auto& point : block.getCurrentLocation()) {
			if (point == pointOfBlock) {
				return block;
			}
		}
	}
	return Block();
}

bool Round::canMoveBlocks(const Block& block, Direction dir, int* totalWeight){
	std::vector<Point> nextMove = getObjectFloatingPoints(block.getCurrentLocation(), dir);
	Point saver;
	*totalWeight += block.getWeight(); // add block's weight;

	if (isWallAhead(nextMove) || isOtherShipAhead(nextMove) || isGoastAhead(nextMove, saver))
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
	vector<Point> temp = block.getCurrentLocation();
	char blockCh = block.getCharacter();
	this->renderer.addPointsToErase(temp);

	for (auto& point : temp) {
		this->bord[point.getX()][point.getY()] = ' ';
	}
	setPointsOfNextMove(dir, temp);//Move block location to the next location according to direction
	block.setLocation(temp);
	for (auto& point : temp) {
		this->bord[point.getX()][point.getY()] = blockCh;
	}
	this->renderer.addPointsOfBlock(temp);
}

bool Round::isPointUnique(const Point& p, std::vector<Block*> fallingBlocks) const {
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

void Round::printObjectDetails() {
	gotoxy(0, 27);
	cout << "Ships" << endl;
	for (auto& ship : this->ships) {
		cout << ship;
	}
	cout << "Blocks" << endl;
	for (auto& block : this->blocks) {
		cout << block;
	}
	cout << endl;
	for (auto& goast : goats) {
		cout << goast;
	}
	cout << endl;
}

bool Round::isObjectOutOfBounderies(const vector<Point>& location) {
	int x, y;
	for (const auto& point : location) {
		x = point.getX();
		y = point.getY();
		if (x <= 0 || x >= (hight - 3)  || y <= 0 || y >= width) { //To do : think of better way to do that
			return true;
		}
	}
	return false;
}

bool Round::isObjectOutOfBounderies(const Point& location) {
	int x, y;
	x = location.getX();
	y = location.getY();

	return (x <= 0 || x >= (hight - 3) || y <= 0 || y >= width);
}

void Round::deleteBlock(const Block& block) {
	this->renderer.addPointsToErase(block.getCurrentLocation());
	for (const auto& point : block.getCurrentLocation()) {
		bord[point.getX()][point.getY()] = ' ';
	}
	remove(this->blocks.begin(), this->blocks.end(), block);
}

void Round::deleteGoast(const Goast& goast) {
	Point temp = goast.getLocation();
	this->renderer.addPointToErase(temp);
	this->bord[temp.getX()][temp.getY()] = ' ';
	renderer.addPointToErase(temp);
	remove(this->goats.begin(), this->goats.end(), goast);
}

