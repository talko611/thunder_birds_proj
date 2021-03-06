#pragma once
#include "Ship.h"
#include "Utils.h"
#include "Block.h"
#include "Renderer.h"
#include "Bord.h"
#include "Ghost.h"
#include "HorizontalGhost.h"
#include "VerticalGhost.h"
#include "WanderingGhost.h"
#include "FileInputOutput.h"
#include <conio.h>
#include <vector>

using namespace std;


enum class SwitchKeys { SwitchToSmall = 115, SwitchToBig = 98 };

class Round
{
	char bord[hight][width];
	Ship ships[2] = { Ship(ShipSize::Small, '@', 3) , Ship(ShipSize::Big, '#', 6) };
	vector<Block> blocks;
	vector<Ghost*> ghosts;
	int activeShip = 0;
	int time;
	int lives;
	size_t sleepTime;
	Renderer& renderer;
	bool shipFinished[2] = { false, false };
	bool isLost = false;
	FileInputOutput& fileManeger;
	GameMode mode;

protected:
	bool readObjectsFromBord();
	void readBlock(vector<Point>& points, Point& temp, char objectCh);
	bool isPointBelongToExsistingBlock(const Point& p);
	bool isPointAlreadyAdded(vector<Point>& points, const Point& p);
	void printObjectDetails();//Test func
	vector<Point> getObjectFloatingPoints(const vector<Point>& current, Direction dir) const;// Return the only the new points that the object steps on in next move
	void setPointsOfNextMove(Direction dir, vector<Point>& points) const;
	bool isShipAhead(const vector<Point>& position, int* index) const; //check if a ship is on the way and rerutrn which ship in index;
	bool isShipAhead(const Point& p);
	bool isWallAhead(const vector<Point>& position) const;
	bool isBlockAhead(const vector<Point>& position, Point& saver) const;
	bool isGhostAhead(const vector<Point>& position, Point& saver) const;
	Ghost* findGhost(const Point& point);
	Block* findBlock(const Point& point);
	bool isPointUnique(const Point& p, std::vector<Block*> fallingBlocks) const;
	void moveFallingBlocks();
	bool addFallingBlocks(Block& block, vector<Block*>& fallingBlocks, int* totalWeight);
	void moveBlock(Block& block, Direction dir);
	bool isValidkey(const char key) const;
	bool isSwitcherKey(const char key)const;
	bool isOtherShipAhead(const std::vector<Point>& position) const; //checks if the non active ship is in the way.
	bool canMoveBlocks(const Block& block, Direction dir, int* totalWeight);
	bool isObjectOutOfBounderies(const vector<Point>& location);
	bool isObjectOutOfBounderies(const Point& location);
	void deleteBlock(const Block& block);
	void deleteGhost(Ghost* goast);
	void playNextMove(Direction& dir, char& key);//Checks if next move is vallid and if yes plays it.
	void curryBlocks(vector<Point>& position, Direction dir);
	void getBlockToCurry(vector<Block*>& blocks, Block& first, int* totalWeight);
	void moveShip(Direction dir);
	bool isExitPointAhead(const std::vector<Point>& position) const;
	void pushBlocks(Block& block, Direction dir);
	bool changeActiveShip(char key);
	bool isWin()const;
	void resetObjects();
	void moveGoasts();
	
public:
	Round(Bord& bord, Renderer& renderer, FileInputOutput& fileManeger,GameMode mode, size_t sleepTime = 300 );
	~Round();
	Round(const Round& round) = delete;
	void operator=(const Round& round) = delete;
	void setRound(Bord& bord);
	bool init();
	GameMode getMode() const { return this->mode; }
	FileInputOutput& getFileManeger() { return this->fileManeger; }
	Renderer& getRenderer() { return this->renderer; }
	bool getIsLost() { return this->isLost; }
	void setIsLost(bool val) { this->isLost = val; }
	int getLives() { return this->lives; }
	int getTime() { return this->time; }
	int getActiveShip() { return this->activeShip; }
	size_t getSleepTime() { return this->sleepTime; }
	vector<Block>& getBlocks() { return this->blocks; }
	virtual int run() = 0;
};

