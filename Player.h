#pragma once
#include "Actor.h"
#include "MovingBox.h"

class Player : public Actor
{
public:

	Player();
	~Player() { };

	const int3 downRun = { 0, 1, 2 },
			leftRun = { 3, 4, 5 },
			upRun = { 6, 7, 8 },
			rightRun = { 9, 10, 11 };

	float animationElapsed;

	bool keyStates[348];

	const int death[6] = { 3, 0, 9, 6, 14, 15 };

	int deathFrame;
	bool canPlay = false;

	enum class States {RUN, HIT, DEAD, ELEVATOR};

	States playerState = States::RUN;

	int leftPunch, rightPunch, upPunch, downPunch;
	int fistOffset = 60;
	float fistX = pX, fistY = pY, elapsedFist = 0.f;;
	BoundingBox fist;
	int lastKey;

	bool hasAccesCard = false;
	bool exitedElevator = false;

	//Collisions:
	int bbOffsetY, bbOffsetX;
	float previousBBX, previousBBY; //For Red Boxes
	float lastX, lastY; //For Inside & Outside

	bool gettingDamage = false;
	float damageElapsed;

	bool CheckCollision(const BoundingBox& boundingbox, MapManager& floor);
	void AABB(const BoundingBox& boundingbox, MapManager& floor);

	void Punch();

	int aleft, aright, abot, atop;
	int bleft, bright, bbot, btop;

	int cols, rows;

	int left, right, bottom, top;

	uint* maskPlayer;
	uint* maskEnemy;
	//bool PixelPerfectCollision(MovingBox* enemy);

	void Input(int key, int action);
	void Update(float deltaTime, MapManager& floor);

	int GetTileX() const { return int(bbX) / TILESWIDTH; };
	int GetTileY() const { return int(bbY) / TILESWIDTH; };

	int GetTileCornerX() const { return int(bbX + bbSX) / TILESWIDTH; };
	int GetTileCornerY() const { return int(bbY + bbSY) / TILESWIDTH; };

private:
};