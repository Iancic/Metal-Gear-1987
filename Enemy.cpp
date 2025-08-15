#include "precomp.h"
#include "Enemy.h"
#include <iostream>

Enemy::Enemy()
{
	sprite = new Sprite(new Surface("assets/Characters/Soldier.png"), 12);
	alert = new Sprite(new Surface("assets/Characters/alert.png"), 1);

	bbX = 508, bbY = 600, bbSX = 15, bbSY = 15;
	bbOffsetX = (CHARWIDTH / 2);
	bbOffsetY = (CHARHEIGHT / 4) * 3 + 10;

	movementSpeed = patrolSpeed;

	reloadTime = 1.5f, thresholdShoot = 170.f;

	followSpeed = 200.f;
	patrolSpeed = 155.f;

	rayLenght = 800;

	counterSequence = 0;
	elapsedIddle = 0.f;
	counterIddle = 0;
}

void Enemy::Init(float posX, float posY, int instructions, Direction srcSequence[20])
{
	ChangeState(State::PATROL);

	movementSpeed = patrolSpeed;

	maxHitPoints = 2;
	hitPoints = maxHitPoints;

	bbX = posX;
	bbY = posY;

	counterSequence = 0;
	numberOfInstructions = instructions;

	for (int i = 0; i <= instructions; i++)
	{
		directionSequence[i] = srcSequence[i];
	}

	ChangePatrolDirection(directionSequence[counterSequence]);
}

void Enemy::Update(Surface* screen, float deltaTime, MapManager& floor, Player& player)
{
	//Update Main HitBox Position
	hitX = pX;
	hitY = pY;

	if (hitPoints <= 0)
	{
		alive = false;
	}

	//Collision With Tiles
	CheckCollision(floor.maps[floor.rowIndex][floor.columnIndex].boxes[GetTileX()][GetTileY()], deltaTime, player);

	//Fist Collision
	FistCollision(player);

	//For Making the enemy red insinde Draw Actor (Sprite Class)
	gettingDamage = (enemyState == State::HIT);

	previousX = bbX;
	previousY = bbY;

	switch (enemyState)
	{
		case State::HIT:
			HitAnimation(deltaTime);
			break;

		case State::REHIT:
			elapsedFist += deltaTime;
			if (elapsedFist >= 0.6f)
			{
				elapsedFist = 0.f;
				ChangeState(State::FOLLOW);
			}
			break;

		case State::PATROL:
			RayCollision(player, floor);
			DrawRay(screen);

			Movement(deltaTime);
			break;

		case State::IDLE:
			RayCollision(player, floor);
			DrawRay(screen);

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
			break;
	}

	pX = bbX - bbOffsetX;
	pY = bbY - bbOffsetY;

	Render(screen, gettingDamage);
}

void Enemy::Movement(float deltaTime)
{
	switch (enemyDirection)
	{
		case Direction::RIGHT:
			bbX += movementSpeed * deltaTime;
			updateAnimation(deltaTime, rightRun);
			break;
		case Direction::LEFT:
			bbX -= movementSpeed * deltaTime;
			updateAnimation(deltaTime, leftRun);
			break;
		case Direction::UP:
			bbY -= movementSpeed * deltaTime;
			updateAnimation(deltaTime, upRun);
			break;
		case Direction::DOWN:
			bbY += movementSpeed * deltaTime;
			updateAnimation(deltaTime, downRun);
			break;
	}
}

void Enemy::FollowPlayer(Player &player)
{
	float distanceX = ( player.GetPosX() + (player.GetScaleX() / 2) ) - ( GetPosX() + (GetScaleX() / 2) );
	float distanceY = ( player.GetPosY() + (player.GetScaleY() / 2) ) - ( GetPosY() + (GetScaleY() / 2) );

	float distance = float(sqrt(pow(distanceX, 2.0) + pow(distanceY, 2.0)));

	if (distance > thresholdShoot)
	{
		if (!hitWall)
		{
			//Pick Route on Y
			if (abs(distanceY) >= abs(distanceX))
			{
				if (distanceY < 0)
					ChangePatrolDirection(Direction::UP);

				else
					ChangePatrolDirection(Direction::DOWN);
			}

			//Pick Route on X
			else if (abs(distanceX) >= abs(distanceY))
			{
				if (distanceX < 0)
					ChangePatrolDirection(Direction::LEFT);

				else
					ChangePatrolDirection(Direction::RIGHT);
			}
		}
		else
		{
			//Pick Route on Y
			if (abs(distanceY) >= abs(distanceX))
			{
				if (distanceX < 0)
					ChangePatrolDirection(Direction::LEFT);

				else
					ChangePatrolDirection(Direction::RIGHT);
				
			}

			//Pick Route on X
			else if (abs(distanceX) >= abs(distanceY))
			{
				if (distanceY < 0)
					ChangePatrolDirection(Direction::UP);

				else
					ChangePatrolDirection(Direction::DOWN);
			}
		}
	}

	else
		ChangeState(State::SHOOT);
}

//Changes the stop frame 2 times for iddle state.
void Enemy::RotateIddle(float deltaTime)
{
	ChangeState(State::IDLE);
	wallBetween = false;

	elapsed += deltaTime;

	if (elapsed > 0.45f)
	{ 
		elapsed = 0.f;
		counterIddle++;

		int direction = rand() % 4 + 1;

		switch (direction)
		{
		case 1:
			stopAnimation = downRun.x;
			ChangePatrolDirection(Direction::DOWN);
			break;
		case 2:
			stopAnimation = leftRun.x;
			ChangePatrolDirection(Direction::LEFT);
			break;
		case 3:
			stopAnimation = upRun.x;
			ChangePatrolDirection(Direction::UP);
			break;
		case 4:
			stopAnimation = rightRun.x;
			ChangePatrolDirection(Direction::RIGHT);
			break;
		default:
			break;
		}
	}

	if (counterIddle > 3)
	{
		//Reset States and Counters
		rotated = true;
		counterIddle = 0;

		counterSequence++;

		//Execute Sequence Again
		if (counterSequence == numberOfInstructions)
		{
			counterSequence = 0;
		}

		ChangePatrolDirection(directionSequence[counterSequence]);
		ChangeState(State::PATROL);
	}
}

void Enemy::FistCollision(Player& player)
{
	if (player.playerState == Player::States::HIT)
	{
		int fistX = player.fist.pX, fistY = player.fist.pY;
		int fistSX = player.fist.sX, fistSY = player.fist.sY;

		bool collisionX = hitX + hitSX > fistX && fistX + fistSX > hitX;
		bool collisionY = hitY + hitSY > fistY && fistY + fistSY > hitY;

		if (collisionX && collisionY)
		{
			ChangeState(State::HIT);
			runOnce = true;
		}
	}
}

void Enemy::HitAnimation(float deltaTime)
{
	elapsedFist += deltaTime;
	punchSound.play();

	if (runOnce)
	{
		if (elapsedFist >= 0.3f)
		{
			elapsedFist = 0.f;
			ChangeState(State::REHIT);
			runOnce = false;
			Damage(1);
		}
	}
}

//Collision For Movement: Patrol Tiles and Omnidirectional Follow Tiles
void Enemy::CheckCollision(const BoundingBox& boundingbox, float deltaTime, Player &player)
{
	bool collisionX = bbX + bbSX > boundingbox.pX && boundingbox.pX + boundingbox.sX > bbX;
	bool collisionY = bbY + bbSY > boundingbox.pY && boundingbox.pY + boundingbox.sY > bbY;

	if (enemyState == State::PATROL || enemyState == State::IDLE)
	{
		if (collisionX && collisionY && boundingbox.type == BoundingBox::BoxTypes::PATROL && !rotated)
		{
			RotateIddle(deltaTime);
		}

		else if (boundingbox.type != BoundingBox::BoxTypes::PATROL)
		{
			rotated = false;
		}
	}

	else if (enemyState == State::FOLLOW || enemyState == State::SHOOT)
	{
		if (collisionX && collisionY && boundingbox.type == BoundingBox::BoxTypes::WALL)
		{
			hitWall = true;
			bbX = previousX;
			bbY = previousY;
			FollowPlayer(player);
		}

		else if (collisionX && collisionY && (boundingbox.type == BoundingBox::BoxTypes::PATROL || boundingbox.type == BoundingBox::BoxTypes::OMNIDIRECTIONAL))
		{
			FollowPlayer(player);
		}

		else if (collisionX && collisionY && boundingbox.type == BoundingBox::BoxTypes::WALKABLE)
		{
			hitWall = false;
		}
	}
}

//Check if there are walls between ray and player.
//Check if the ray collides with the player.
void Enemy::RayCollision(Player& player, MapManager& floor)
{
	xRayStart = pX + CHARWIDTH / 2;
	yRayStart = pY + CHARHEIGHT / 2;

	bool collisionX = false, collisionY = false;

	switch (enemyDirection)
	{
		case Direction::DOWN:
			{
			
			for (int i = GetTileY(); i < player.GetTileY(); i++)
			{
				if (floor.maps[floor.rowIndex][floor.columnIndex].boxes[GetTileX()][i].type == 0)
				{
					wallBetween = true;
				}
			}

			
			xRayEnd = xRayStart;
			yRayEnd = yRayStart + rayLenght;

			collisionX = xRayStart >= player.hitX && xRayStart <= player.hitX + player.hitSX;
			collisionY = yRayStart + rayLenght >= player.hitY && yRayStart <= player.hitY + player.hitSY;
			}
			break;

		case Direction::LEFT:
			{
				for (int i = GetTileX(); i > player.GetTileX(); i--)
				{
					if (floor.maps[floor.rowIndex][floor.columnIndex].boxes[i][GetTileY()].type == 0)
					{
						wallBetween = true;
					}
				}

				xRayEnd = xRayStart - rayLenght;
				yRayEnd = yRayStart;

				collisionX = xRayEnd + rayLenght >= player.hitX && xRayEnd <= player.hitX + player.hitSX;
				collisionY = yRayStart >= player.hitY && yRayStart <= player.hitY + player.hitSY;
			}
		break;

		case Direction::UP:
			{
				for (int i = GetTileY(); i > player.GetTileY(); i--)
				{
					if (floor.maps[floor.rowIndex][floor.columnIndex].boxes[GetTileX()][i].type == 0)
					{
						wallBetween = true;
					}
				}

				xRayEnd = xRayStart;
				yRayEnd = yRayStart - rayLenght;

				collisionX = xRayStart >= player.hitX && xRayStart <= player.hitX + player.hitSX;
				collisionY = yRayEnd + rayLenght >= player.hitY && yRayEnd <= player.hitY + player.hitSY;
			}
		break;

		case Direction::RIGHT:
			{
				for (int i = GetTileX(); i < player.GetTileX(); i++)
				{
					if (floor.maps[floor.rowIndex][floor.columnIndex].boxes[i][GetTileY()].type == 0)
					{
						wallBetween = true;
					}
				}

				xRayEnd = xRayStart + rayLenght;
				yRayEnd = yRayStart;

				collisionX = xRayStart + rayLenght >= player.hitX && xRayStart <= player.hitX + player.hitSX;
				collisionY = yRayStart >= player.hitY && yRayStart <= player.hitY + player.hitSY;
			}
		break;
	}

	//Check all conditions: is ray intersecting player? Are there walls between?
	if (collisionX && collisionY && wallBetween == false)
	{
		ChangeState(State::FOLLOW);
	}
}

void Enemy::ChangePatrolDirection(Direction desiredDirection)
{
	enemyDirection = desiredDirection;
}

void Enemy::ChangeState(State desiredState)
{
	enemyState = desiredState;
}

void Enemy::DrawRay(Surface* screen)
{
	//For warning
	Surface* formalPar;
	formalPar = screen;

#ifdef DEBUGMODE
	screen->Line(xRayStart, yRayStart, xRayEnd, yRayEnd, 0xb6ff00);
#endif
}

void Enemy::RenderIcon(Surface* screen)
{
	alert->Draw(screen, int(pX), int(pY - 30));
}