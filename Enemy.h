#pragma once
#include "Actor.h"
#include "Player.h"
#include <Audio/Sound.hpp>

class Enemy : public Actor
{
public:

	Enemy();
	~Enemy() { };

	//Animations:
	const int3 downRun = { 0, 1, 2 },
		leftRun = { 3, 4, 5 },
		upRun = { 6, 7, 8 },
		rightRun = { 9, 10, 11 };

	int2 directions[4] = { int2{0, 1}, int2{0, -1}, int2{1, 0}, int2{-1, 0} };

	enum class State { IDLE, PATROL, FOLLOW, SHOOT, HIT, REHIT };
	enum class Direction { DOWN, LEFT, UP, RIGHT };

	Sprite* alert;

	Audio::Sound punchSound{ "assets/audio/punchHit.mp3" };

	State enemyState = State::PATROL;

	//Patrol:
	Direction directionSequence[20];
	Direction enemyDirection;
	int numberOfInstructions, counterSequence = 0;

	//Patrol & Iddle Rotating:
	bool rotated = false;
	float elapsedIddle = 0.f;
	int counterIddle = 0;

	//Raycasting:
	bool wallBetween = false;
	float rayLenght = 800, xRayStart, yRayStart, xRayEnd, yRayEnd;

	//Follow & Shooting State:
	float followSpeed;
	float patrolSpeed;
	float thresholdShoot;
	float reloadTime;

	//Fist Collision
	State previousState;
	float elapsedFist = 0.f;
	float previousFistY;
	bool gettingDamage = false, runOnce = false; //Flag for Actor

	//Collision:
	bool hitWall = false;
	float previousX, previousY;
	int bbOffsetY, bbOffsetX;

	void Init(float pX, float pY, int instructions, Direction directionSequence[20]);
	virtual void Update(Surface* screen, float deltaTime, MapManager& floor, Player& player);

	void Movement(float deltaTime);
	void RotateIddle(float deltaTime);
	void FollowPlayer(Player& player);

	void FistCollision(Player& player);
	void HitAnimation(float deltaTime);

	void CheckCollision(const BoundingBox& boundingbox, float deltaTime, Player& player);
	void RayCollision(Player& player, MapManager& floor);

	void ChangeState(State desiredState);
	void ChangePatrolDirection(Direction desiredDirection);

	void DrawRay(Surface* screen);
	void RenderIcon(Surface* screen);

	int GetTileX() { return int(bbX) / TILESWIDTH; };
	int GetTileY() { return int(bbY) / TILESWIDTH; };

private:
};

