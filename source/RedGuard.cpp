#include "precomp.h"
#include "RedGuard.h"

RedGuard::RedGuard()
{
	sprite = new Sprite(new Surface("assets/Characters/elevatorGuard.png"), 12);
	alert = new Sprite(new Surface("assets/Characters/alert.png"), 1);

	bbX = 508, bbY = 600, bbSX = 15, bbSY = 15;
	bbOffsetX = (CHARWIDTH / 2);
	bbOffsetY = (CHARHEIGHT / 4) * 3 + 10;

	movementSpeed = patrolSpeed;

	maxHitPoints = 5;
	hitPoints = maxHitPoints;

	reloadTime = 1.5f, followSpeed = 130.f, patrolSpeed = 90.f, thresholdShoot = 170.f;

	rayLenght = 800;

	counterSequence = 0;
	elapsedIddle = 0.f;
	counterIddle = 0;
}

void RedGuard::InitRedGuard(float posX, float posY)
{
	ChangeState(State::IDLE);

	bbX = 508, bbY = 600, bbSX = 15, bbSY = 15;
	bbOffsetX = (CHARWIDTH / 2);
	bbOffsetY = (CHARHEIGHT / 4) * 3 + 10;

	bbX = posX;
	bbY = posY;
}

void RedGuard::Update(Surface* screen, float deltaTime, MapManager& floor, Player& player)
{
	//Update Main HitBox Position
	hitX = pX;
	hitY = pY;

	if (hitPoints <= 0)
	{
		alive = false;
	}

	if (player.playerState == Player::States::HIT)
		FistCollision(player);

	//Ray Collision
	RayCollision(player, floor);
	DrawRay(screen);

	//Collision With Tiles
	CheckCollision(floor.maps[floor.rowIndex][floor.columnIndex].boxes[GetTileX()][GetTileY()], deltaTime, player);

	previousX = bbX;
	previousY = bbY;

	//For Making the enemy red insinde Draw Actor (Sprite Class)
	if (enemyState == State::HIT)
	{
		gettingDamage = true;
	}
	else
	{
		gettingDamage = false;
	}

	//Remember Previous State For Hit
	switch (enemyState)
	{
		case State::HIT:
			HitAnimation(deltaTime);
			break;

		case State::PATROL:
			Movement(deltaTime);
			break;

		case State::IDLE:
			sprite->SetFrame(stopAnimation);
			break;

		case State::FOLLOW:
			movementSpeed = followSpeed;
			Movement(deltaTime);
			RenderIcon(screen);
			break;

		case State::SHOOT:
			ChangeState(State::SHOOT);
			RenderIcon(screen);
	}

	pX = bbX - bbOffsetX;
	pY = bbY - bbOffsetY;

	Render(screen, gettingDamage);
}
