#pragma once
#include "Ship.h"
#include "Utils.h"
#include "Block.h"
#include "Renderer.h"
#include "Bord.h"
#include "Goast.h"
#include <conio.h>
#include <vector>

using namespace std;

enum class ValidKeys { Up = 119, Down = 120, Right = 100, Left = 97, SwitchToSmall = 115, SwitchToBig = 98, ESC = 27, EXIT = 57 };
enum class SwitchKeys { SwitchToSmall = 115, SwitchToBig = 98 };

class Round
{
	char bord[hight][width];
	Ship ships[2] = { Ship(ShipSize::Small, '@', 2) , Ship(ShipSize::Big, '#', 6) };
	vector<Block> blocks;
	vector<Goast> goats;
	int activeShip = 0;
	int time;
	int lives;
	Renderer& renderer;
	bool shipFinished[2] = { false, false };
	bool isLost = false;
	
	void readObjectsFromBord();
	void readBlock(vector<Point>& points, Point& temp, char objectCh);
	bool isPointBelongToExsistingBlock(const Point& p);
	bool isPointAlreadyAdded(vector<Point>& points, const Point& p);
	void printObjectDetails();//Test func
	vector<Point> getObjectFloatingPoints(const vector<Point>& current, Direction dir) const;// Return the only the new points that the object steps on in next move
	void setPointsOfNextMove(Direction dir, vector<Point>& points) const;
	void setPointByDirection(Direction dir, Point& p) const;
	bool isShipAhead(const vector<Point>& position, int* index) const; //check if a ship is on the way and rerutrn which ship in index;
	bool isWallAhead(const vector<Point>& position) const;
	bool isBlockAhead(const vector<Point>& position, Point& saver) const;
	bool isGoastAhead(const vector<Point>& position, Point& saver) const;
	Goast& findGoast(const Point& point);
	Block& findBlock(const Point& point);
	bool isPointUnique(const Point& p, std::vector<Block*> fallingBlocks) const;
	void moveFallingBlocks();
	bool addFallingBlocks(Block& block, vector<Block*>& fallingBlocks, int* totalWeight);
	void moveBlock(Block& block, Direction dir);
	void moveGoasts();
	bool isValidkey(const char key) const;
	bool isSwitcherKey(const char key)const;
	bool isOtherShipAhead(const std::vector<Point>& position) const; //checks if the non active ship is in the way.
	bool canMoveBlocks(const Block& block, Direction dir, int* totalWeight);
	bool isObjectOutOfBounderies(const vector<Point>& location);
	bool isObjectOutOfBounderies(const Point& location);
	void deleteBlock(const Block& block);
	void deleteGoast(const Goast& goast);
	
	void playNextMove(Direction& dir);//Checks if next move is vallid and if yes plays it.
	
	
	void moveShip(Direction dir);
	
	
	
	bool isExitPointAhead(const std::vector<Point>& position) const;
	void moveBlocks(Block& block, Direction dir);
	
	
	
	
	void changeActiveShip(char key);
	bool isWin()const;
	bool isShipDead();
	
public:
	Round(Bord& bord, Renderer& renderer);
	void init();
	int run();
	
};

