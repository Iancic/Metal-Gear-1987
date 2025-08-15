#include "precomp.h"
#include "game.h"
#include "Player.h"
#include "common.h"

Player::Player()
{
	sprite = new Sprite(new Surface("assets/Characters/SolidSnake.png"), 42);

	bbX = 500, bbY = 300;
	bbOffsetX = CHARWIDTH / 8;
	bbOffsetY = (CHARHEIGHT / 4) * 3;
	bbSX = CHARWIDTH / 4 * 3;
	bbSY = CHARHEIGHT / 4 / 2;

	movementSpeed = 190.f;

	fist.Init(12, int(pX), int(pY), 30, 30);
	leftPunch = 20, rightPunch = 28, upPunch = 24, downPunch = 16;

	maxHitPoints = 100;
	hitPoints = 50;

#ifdef DEBUGMODE
	maxHitPoints = 500;
	hitPoints = 500;
	movementSpeed = 250.f;
#endif

	damageElapsed = 0.f;
}

void Player::Input(int key, int action)
{
	if (action == GLFW_PRESS)
	{
		keyStates[key] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		keyStates[key] = false;
	}
}

//Nick Walton: https://www.youtube.com/watch?v=9pnEBa4cy5w&ab_channel=NickWalton
//Pixel Perfect Collision:
/*
bool Player::PixelPerfectCollision(MovingBox* enemy)
{
	aleft = int(pX);
	aright = aleft + int(sX);
	abot = int(pY);
	atop = abot + int(sY);

	bleft = enemy->pX;
	bright = bleft + enemy->sX;
	bbot = enemy->pY;
	btop = bbot + enemy->sY;

	//Check If Boxes Overlap
	if (aleft > bright || aright < bleft || abot > btop || atop < bbot)
		return false;

	//Bounding Box Of Overlap of the two masks
	left = max(aleft, bleft);
	right = min(aright, bright);
	bottom = max(abot, bbot);
	top = min(atop, btop);

	//Pixel Buffers Of Both
	maskPlayer = sprite->GetBuffer(); //+ currentFrame * CHARWIDTH;
	maskEnemy = enemy->sprite->GetBuffer(); // enemy.currentFrame * CHARWIDTH;

	//Both Overlaping Bounding Boxes are overlaped so we need to see how they are offseted.
	aleft = left - aleft;
	abot = bottom - abot;

	bleft = left - bleft;
	bbot = bottom - bbot;

	for (int j = 0; j < CHARHEIGHT; j++)
	{
		for (int i = 0; i < CHARWIDTH; i++)
		{
			if (maskPlayer[(aleft + i) + (abot + j) * CHARWIDTH] && maskPlayer[(bleft + i) + (bbot + j) * CHARWIDTH])
				return true;
		}
	}

	return false;
}
*/

//TO DO: REFACTOR CHECKS
//Inspiration: https://learnopengl.com/In-Practice/2D-Game/Collisions/Collision-detection
bool Player::CheckCollision(const BoundingBox& boundingbox, MapManager& floor)
{
	bool collisionX = bbX + bbSX >= boundingbox.pX && boundingbox.pX + boundingbox.sX >= bbX;
	bool collisionY = bbY + bbSY >= boundingbox.pY && boundingbox.pY + boundingbox.sY >= bbY;
	
	if (collisionX && collisionY && boundingbox.type == BoundingBox::BoxTypes::WALL)
	{
		return collisionX && collisionY;
	}
	
	//Reset Player Position based on Collider Type
	else if (collisionX && collisionY && boundingbox.type == BoundingBox::BoxTypes::TOPDOOR)
	{
		if (bbY < SCRHEIGHT / 2)
		{
			bbY += SCRHEIGHT - TILESIZE * 8;
			floor.NorthRoom();
		}
		else if (bbY > SCRHEIGHT / 2)
		{
			bbY -= SCRHEIGHT - TILESIZE * 8;
			floor.SouthRoom();
		}

		return false;
	}
	
	else if (collisionX && collisionY && boundingbox.type == BoundingBox::BoxTypes::SIDEDOOR)
	{
		if (bbX < SCRWIDTH / 2)
		{
			bbX += SCRWIDTH - TILESIZE * 4;
			floor.WestRoom();
		}
		else if (bbX > SCRWIDTH / 2)
		{
			bbX -= SCRWIDTH - TILESIZE * 4;
			floor.EastRoom();
		}

		return false;
	}
	
	else if (collisionX && collisionY && boundingbox.type == BoundingBox::BoxTypes::CARDOOR)
	{

		lastX = bbX + 30;
		lastY = bbY + 30;

		bbX += 864.f - bbX - 70;
		bbY += 448.f - bbY;

		floor.currentInside = MapManager::Inside::NORMAL;
		floor.EnterInside();

		return false;
	}

	else if (collisionX && collisionY && boundingbox.type == BoundingBox::BoxTypes::BINOCULARDOOR)
	{

		lastX = bbX + 30;
		lastY = bbY + 30;

		bbX += 864.f - bbX - 70;
		bbY += 448.f - bbY;

		floor.currentInside = MapManager::Inside::BINOCULAR;
		floor.EnterInside();

		return false;
	}

	else if (collisionX && collisionY && boundingbox.type == BoundingBox::BoxTypes::RATIONDOOR)
	{

		lastX = bbX + 30;
		lastY = bbY + 30;

		bbX += 864.f - bbX - 70;
		bbY += 448.f - bbY;

		floor.currentInside = MapManager::Inside::RATION;
		floor.EnterInside();

		return false;
	}

	else if (collisionX && collisionY && boundingbox.type == BoundingBox::BoxTypes::CARDDOOR)
	{

		lastX = bbX + 30;
		lastY = bbY + 30;

		bbX += 864.f - bbX - 70;
		bbY += 448.f - bbY;

		floor.currentInside = MapManager::Inside::CARD;
		floor.EnterInside();

		return false;
	}

	else if (collisionX && collisionY && boundingbox.type == BoundingBox::BoxTypes::GUNDOOR)
	{

		lastX = bbX + 30;
		lastY = bbY + 30;

		bbX += 864.f - bbX - 70;
		bbY += 448.f - bbY;

		floor.currentInside = MapManager::Inside::GUN;
		floor.EnterInside();

		return false;
	}

	else if (collisionX && collisionY && boundingbox.type == BoundingBox::BoxTypes::MINEDOOR)
	{

		lastX = bbX + 30;
		lastY = bbY + 30;

		bbX += 864.f - bbX - 70;
		bbY += 448.f - bbY;

		floor.currentInside = MapManager::Inside::MINE;
		floor.EnterInside();

		return false;
	}
	
	else if (collisionX && collisionY && boundingbox.type == BoundingBox::BoxTypes::CAREXIT)
	{
		floor.ExitInside();

		bbX = lastX;
		bbY = lastY;

		return false;
	}

	else if (collisionX && collisionY && boundingbox.type == BoundingBox::BoxTypes::ELEVATORDOOR)
	{

		lastX = bbX;
		lastY = bbY + 10;

		bbX = 920.f;
		bbY = 718.f;

		floor.EnterElevator();

		return false;
	}

	else if (collisionX && collisionY && boundingbox.type == BoundingBox::BoxTypes::ELEVATOREXIT)
	{
		exitedElevator = true;

		return false;
	}

	else if (collisionX && collisionY && boundingbox.type == BoundingBox::BoxTypes::ROOMDOOR)
	{

		lastX = bbX;
		lastY = bbY + 10;

		bbX = 450.f;
		bbY = 715.f;

		floor.EnterRoom();

		return false;
	}

	else if (collisionX && collisionY && boundingbox.type == BoundingBox::BoxTypes::ROOMEXIT)
	{
		floor.ExitRoom();

		bbX = lastX;
		bbY = lastY;

		return false;
	}

	else
		return false;
}

void Player::AABB(const BoundingBox& boundingbox, MapManager& floor)
{
	if (CheckCollision(boundingbox, floor)) //If actor collides with un-walkable move the bounding box back.
	{
		bbX = previousBBX;
		bbY = previousBBY;
	}
	
	else //If the box is walkable move the player to the box.
	{
		pX = bbX - bbOffsetX;
		pY = bbY - bbOffsetY;
	}
}

void Player::Update(float deltaTime, MapManager& floor)
{
	if (hitPoints <= 0)
	{
		playerState = States::DEAD;
	}

	//For Making the player red insinde Draw Actor (Sprite Class)
	if (gettingDamage)
	{
		damageElapsed += deltaTime;
		if (damageElapsed >= 0.4f)
		{
			gettingDamage = false;
			damageElapsed = 0.f;
		}
	}

	//Update Main HitBox Position
	hitX = pX;
	hitY = pY;

	for (int i = GetTileX() - 1; i < GetTileCornerX() + 1; i++)
	{
		for (int j = GetTileY() - 1; j < GetTileCornerY() + 1; j++)
		{
			if (floor.insideCar)
				AABB(floor.car.boxes[i][j], floor);

			else if (floor.insideElevator)
				AABB(floor.elevator.boxes[i][j], floor);

			else if (floor.insideRoom)
				AABB(floor.room.boxes[i][j], floor);

			else if (!floor.insideCar && !floor.insideRoom && !floor.insideElevator)
				AABB(floor.maps[floor.rowIndex][floor.columnIndex].boxes[i][j], floor);
		}
	}

	//Reset Position: Wall Collision
	previousBBX = bbX;
	previousBBY = bbY;

	switch (playerState)
	{
	case States::RUN:
		if (keyStates[GLFW_KEY_W])
		{
			lastKey = GLFW_KEY_W;
			updateAnimation(deltaTime, upRun);
			bbY -= movementSpeed * deltaTime;
		}
		else if (keyStates[GLFW_KEY_S])
		{
			lastKey = GLFW_KEY_S;
			updateAnimation(deltaTime, downRun);
			bbY += movementSpeed * deltaTime;
		}
		else if (keyStates[GLFW_KEY_A])
		{
			lastKey = GLFW_KEY_A;
			updateAnimation(deltaTime, leftRun);
			bbX -= movementSpeed * deltaTime;
		}
		else if (keyStates[GLFW_KEY_D])
		{
			lastKey = GLFW_KEY_D;
			updateAnimation(deltaTime, rightRun);
			bbX += movementSpeed * deltaTime;
		}

		//Stop Frame:
		else if (!keyStates[GLFW_KEY_W] && !keyStates[GLFW_KEY_S] && !keyStates[GLFW_KEY_D] && !keyStates[GLFW_KEY_A])
		{
			sprite->SetFrame(stopAnimation);
		}
		break;
	case States::DEAD:
		canPlay = true;
		animationElapsed += deltaTime;
		if (animationElapsed >= 0.3f)
		{
			animationElapsed = 0.f;
			deathFrame++;
		}

		if (deathFrame <= 5)
			sprite->SetFrame(death[deathFrame]);
		else
			alive = false;
		break;
	case States::HIT:
		break;
	case States::ELEVATOR:
		sprite->SetFrame(9);
		bbY -= 150.f * deltaTime;
		break;
	}
	
	//Punching Input:
	if (keyStates[GLFW_KEY_F] && playerState != States::DEAD)
	{
		Punch();
	}
	else if (!keyStates[GLFW_KEY_F])
	{
		playerState = States::RUN;
	}

}

void Player::Punch()
{
	playerState = States::HIT;

	if (lastKey == GLFW_KEY_A)
	{
		fistX = (pX + CHARWIDTH / 2) - fist.sX / 2 - fistOffset;
		fistY = (pY + CHARHEIGHT / 2) - fist.sY / 2;
		SetFrame(leftPunch);
	}

	else if (lastKey == GLFW_KEY_D)
	{
		lastKey = 0;
		fistX = (pX + CHARWIDTH / 2) - fist.sX / 2 + fistOffset;
		fistY = (pY + CHARHEIGHT / 2) - fist.sY / 2;
		SetFrame(rightPunch);
	}

	else if (lastKey == GLFW_KEY_W)
	{
		fistX = (pX + CHARWIDTH / 2) - fist.sX / 2;
		fistY = (pY + CHARHEIGHT / 2) - fist.sY / 2 - fistOffset;
		SetFrame(upPunch);
	}

	else if (lastKey == GLFW_KEY_S)
	{
		fistX = (pX + CHARWIDTH / 2) - fist.sX / 2;
		fistY = (pY + CHARHEIGHT / 2) - fist.sY / 2 + fistOffset;
		SetFrame(downPunch);
	}

	fist.Update(int(fistX), int(fistY));
}
