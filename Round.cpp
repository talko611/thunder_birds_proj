#include "Round.h"

Round::Round(Bord& bord, Renderer& renderer, int lives) : renderer(renderer) {
	char** pBord = bord.getBord();
	for (int i = 0; i < hight; i++) {
		for (int j = 0; j < width; j++) {
			this->bord[i][j] = pBord[i][j];
		}
	}
	this->lives = lives;
	this->time = bord.getTime();
}

bool Round::readObjectsFromBord()
{
	int smallShipPointCounter = 0, bigShipPointCounter = 0, exitPointCounter = 0;
	bool exitPointReaded = false;
	for (int i = 0; i < hight; i++) {
		for (int j = 0; j < width; j++) {
			if (this->bord[i][j] == (char)objectAsciiVal::SmallShip) {
				if (smallShipPointCounter < (int)ShipSize::Small) {
					this->ships[0].setPointOfLocation({ i,j });
					smallShipPointCounter++;
				}
				else {
					return false;
				}
			}

			else if (this->bord[i][j] == (char)objectAsciiVal::BigShip) {
				if (bigShipPointCounter < (int)ShipSize::Big) {
					this->ships[1].setPointOfLocation({ i,j });
					bigShipPointCounter++;
				}
				else {
					return false;
				}
			}

			else if (bord[i][j] >= (char)objectAsciiVal::BlockLowestVal && bord[i][j] <= (char)objectAsciiVal::BlockHighestVal) {
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
			else if (bord[i][j] == (char)objectAsciiVal::Goast) {
				this->goats.push_back(Goast(i, j));
			}
			else if (bord[i][j] == (char) objectAsciiVal::ExitPoint){
				exitPointCounter++;
				if (exitPointCounter > 1) {
					exitPointReaded = true;
				}
			}
			else if (bord[i][j] == '&') {
				renderer.setLegendPosition(i, j);
			}
		}
	}
	if (exitPointReaded) {
		return true;
	}
	return false;
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

bool Round::init() {
	if (!readObjectsFromBord()) {
		return false;
	}
	renderer.printBord(this->bord);
	renderer.printLegend(lives, time, activeShip);
	return true;
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
			if (!isLost) {
				if (_kbhit())
				{
					key = tolower(_getch());
					if (isValidkey(key))
					{
						if (isSwitcherKey(key))
						{
							if (changeActiveShip(key)) {
								dir = Direction::Stop;
							}
						}
						else
						{
							dir = (Direction)key;
						}
					}
				}
				playNextMove(dir);
			}
			this->renderer.renderNextMove(--time, activeShip, this->blocks);
			if (time == 0) {
				isLost = true;
			}
			Sleep(300);
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
	if (isWallAhead(next)) {
		return false;
	}
	if (isGoastAhead(next, pointSaver)) {
		Goast* goastSaver = findGoast(pointSaver);
		if (goastSaver) {
			deleteGoast(*goastSaver);
		}
		return true;
	}

	if (isBlockAhead(next, pointSaver)) {
		Block* nextBlock = findBlock(pointSaver);
		if (nextBlock && addFallingBlocks(*nextBlock, fallingBlocks,totalWeight)) {
			if (isPointUnique(block.getCurrentLocation()[0], fallingBlocks)) {
				fallingBlocks.push_back(&block);
			}
			return true;
		}
		return false;
	}
	if (isShipAhead(next, &shipIndex)) {
		if (shipIndex == 2) {
			if (this->ships[1].getWeightCanMove() < *totalWeight) {
				isLost = true;
			}
		}
		else if (this->ships[shipIndex].getWeightCanMove() < *totalWeight) {
			isLost = true;
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
	bool bigShip = false, smallShip = false;
	for (auto& point : position) {
		x = point.getX();
		y = point.getY();
		if (bord[x][y] == (char)objectAsciiVal::BigShip) {
			bigShip = true;
		}
		else if (bord[x][y] == (char)objectAsciiVal::SmallShip) {
			smallShip = true;
		}
	}
	if (bigShip && smallShip) {
		answer = true;
		*index = 2;
	}
	else if (bigShip) {
		answer = true;
		*index = 1;
	}
	else if (smallShip) {
		answer = true;
		*index = 0;
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

Goast* Round::findGoast(const Point& point) {
	for (auto& goast : this->goats) {
		if (point == goast.getLocation()) {
			return &goast;
		}
	}
	return nullptr;
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
	if (isObjectOutOfBounderies(this->ships[this->activeShip].getCurrLoc())) {
		this->isLost = true;
		return;
	}
	Point temp;
	vector<Point> nextMove = getObjectFloatingPoints(this->ships[this->activeShip].getCurrLoc(), dir);
	vector<Point> above = getObjectFloatingPoints(this->ships[this->activeShip].getCurrLoc(), Direction::Up);

	
	if (isGoastAhead(nextMove, temp)) {
		this->isLost = true;
		return;
	}
	else if (isWallAhead(nextMove) || isOtherShipAhead(nextMove)) {
		return;
	}
	else if (isBlockAhead(nextMove, temp)) {
		Block* saver = findBlock(temp);
		int totalWeight = 0;
		if (saver && canMoveBlocks(*saver, dir, &totalWeight)) {
			curryBlocks(above, dir);
			pushBlocks(*saver, dir);
			moveShip(dir);
		}
		else
		{
			dir = Direction::Stop;
		}
	}
	else if (isExitPointAhead(nextMove)) {
			this->shipFinished[activeShip] = true;
			std::vector<Point> saver = this->ships[activeShip].getCurrLoc();
			for (auto& point : saver) {
				this->bord[point.getX()][point.getY()] = ' ';
			}
			this->renderer.addPointsToErase(saver);
			dir = Direction::Stop;
			this->activeShip = !activeShip;
	}
	else
	{
		curryBlocks(above, dir);
		moveShip(dir);
	}
}

void Round::moveShip(Direction dir) {
	
	vector<Point> temp = ships[activeShip].getCurrLoc();
	for (auto& point : temp) {
		bord[point.getX()][point.getY()] = ' ';
	}
	this->renderer.addPointsToErase(temp);
	ships[activeShip].move(dir);
	temp = ships[activeShip].getCurrLoc();

	char shipCharacter = ships[activeShip].getShipCharacter();
	for (auto& point : temp) {
		bord[point.getX()][point.getY()] = shipCharacter;
	}
	this->renderer.addPointsOfShip(temp);
}

Block* Round::findBlock(const Point& pointOfBlock)
{
	for (auto& block : this->blocks) {
		for (auto& point : block.getCurrentLocation()) {
			if (point == pointOfBlock) {
				return &block;
			}
		}
	}
	return nullptr;
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
		Block* nextBlock = findBlock(saver);
		return canMoveBlocks(*nextBlock, dir, totalWeight);
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

void Round::pushBlocks(Block& block, Direction dir) 
{
	std::vector <Point> next = getObjectFloatingPoints(block.getCurrentLocation(),dir);
	Point saver;

	if (isBlockAhead(next, saver)) {
		Block* nextBlock = findBlock(saver);
		pushBlocks(*nextBlock, dir);
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

bool Round::changeActiveShip(char key){
	bool res = false;
	if (key == (char)ValidKeys::SwitchToBig) {
		if (!shipFinished[1] && this->activeShip == 0) {
			activeShip = 1;
			res = true;
		}
	}
	else if (!shipFinished[0] && this->activeShip == 1) {
		activeShip = 0;
		res = true;
	}
	return res;
}

bool Round::isWin() const{
	return shipFinished[1] && shipFinished[0];
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
	this->blocks.erase(remove(this->blocks.begin(), this->blocks.end(), block), this->blocks.end());
}

void Round::deleteGoast(const Goast& goast) {
	Point temp = goast.getLocation();
	this->renderer.addPointToErase(temp);
	this->bord[temp.getX()][temp.getY()] = ' ';
	renderer.addPointToErase(temp);
	this->goats.erase(remove(this->goats.begin(), this->goats.end(), goast), this->goats.end());
}

void Round::curryBlocks(vector<Point>& position, Direction dir) {
	if (dir == Direction::Down || dir == Direction::Up) {
		return;
	}
	Point temp;
	if (isBlockAhead(position, temp)) {
		vector<Block*> blocksToCurry;
		Block* tempBlock = findBlock(temp);
		if (tempBlock) {
			int totalWeight = 0;
			getBlockToCurry(blocksToCurry, *tempBlock, &totalWeight);

			for (auto& block : blocksToCurry) {
				totalWeight = 0;
				if (canMoveBlocks(*block, dir, &totalWeight)) {
					pushBlocks(*block, dir);
				}
			}
		}
	}
}

void Round::getBlockToCurry(vector<Block*>& blocks, Block& first, int* totalWeight) {
	Point temp;
	vector <Point> tempLocation = getObjectFloatingPoints(first.getCurrentLocation(), Direction::Up);
	blocks.push_back(&first);
	*totalWeight += first.getWeight();

	if (isBlockAhead(tempLocation, temp)) {
		Block* tempBlock = findBlock(temp);
		getBlockToCurry(blocks, *tempBlock, totalWeight);
	}
}

