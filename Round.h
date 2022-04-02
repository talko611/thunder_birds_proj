#pragma once
#include "Ship.h"
#include "Utils.h"
#include "Block.h"
#include "Renderer.h"
#include <conio.h>

enum class ValidKeys { Up = 119, Down = 120, Right = 100, Left = 97, SwitchToSmall = 115, SwitchToBig = 98, ESC = 27, EXIT = 57 };
enum class SwitchKeys { SwitchToSmall = 115, SwitchToBig = 98 };

class Round
{
	Ship ships[2] = { {{4,1} ,ShipSize::Small, '@' , 2}, {{1,1}, ShipSize::Big, '#' , 6} };
	constexpr static int numOfBlocks = 3;
	Block blocks[numOfBlocks];
	int activeShip = 0;
	int time = 300;
	int lives;
	bool shipFinished[2] = { false, false };
	bool isLost = false;
	Renderer renderer;
	char bord[hight][width] = { 
								"|----------------------------------------------------------------------------|\0",
								"|    |            |||||||||||||||||||||||||||||||||||||||                    |\0",
								"|    |            |||||||||||||||||||||||||||||||||||||||                    |\0",
								"|    |            |||||||||||||||||||||||||||||||||||||||                    |\0",
								"|    |                                                                       |\0",
								"|    |                                                                       |\0",
								"|    |            |||||||||||||||||||||||||||||||||||||||                    |\0",
								"|    |                              |                                        |\0",
								"|    |                              |                                        |\0",
								"|    |                              |                   |                    |\0",
								"|    |                              |                   |                    |\0",
								"|    |                              |                   |                    |\0",
								"|    |                              |                   |                    |\0",	
								"|    |                              |                   |                    |\0",
								"|    |                                                  |                    |\0",
								"|    |                              |                   |                    |\0",
								"|    |                              |                   |                    |\0",
								"|    |                              |                   |                    |\0",
								"|    |                              |                   |                    |\0",
								"|    |                              |                   |                    |\0",
								"|                                   |                   |                    |\0",
								"|                                   |                   |                    |\0",
								"----------------------------------------------------------------------!!!!----\0",};
	
	void setShips(); //set ships on bord in initialization
	bool isWallAhead(const std::vector<Point>& position) const;
	bool isOtherShipAhead(const std::vector<Point>& position) const; //checks if the non active ship is in the way.
	bool isShipAhead(const std::vector<Point>& position, int* index) const; //check if a ship is on the way and rerutrn which ship in index;
	bool isValidkey(const char key) const;
	bool isSwitcherKey(const char key)const;
	void playNextMove(Direction& dir);//Checks if next move is vallid and if yes plays it.
	void setPointByDirection(Direction dir, Point& p) const;
	void setPointsOfNextMove(Direction dir, std::vector<Point>& points) const;
	void moveShip(Direction dir);
	void initBlocks();
	void setBlocks();//set block on bord in initialization
	bool isBlockAhead(const std::vector<Point>& position , Point& saver) const;
	Block& findBlock(const Point& point);
	bool canMoveBlocks(const Block& block, Direction dir, int* totalWeight);
	bool isExitPointAhead(const std::vector<Point>& position) const;
	void moveBlocks(Block& block, Direction dir);
	void moveFallingBlocks();
	bool isBlockFalling(Block& block, std::vector<Block*>& fallingBlocks);
	bool isPointUnique(const Point& p, std::vector<Block*>& fallingBlocks) const;
	std::vector<Point> getFloatingPoints(const Block& block, Direction dir) const;
	void changeActiveShip(char key);
	bool isWin()const;
	bool isShipDead();
	void Round::moveBlock(Block& block, Direction dir);
public:
	Round(int _lives, bool color) : lives(_lives), renderer(Renderer(color)) { 
		initBlocks(); }
	void init();
	int run();
	
};

