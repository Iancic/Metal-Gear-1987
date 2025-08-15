#include "precomp.h"
#include "Bullet.h"
#include <cmath>
#include <iostream>

void Bullet::Init(Enemy* enemy)
{
	owner = enemy;
}

void Bullet::BulletMovement(float deltaTime, Player& player)
{
	if (!calculated)
	{
		calculated = true;
		dir = { (player.GetPosX() - pX) , (player.GetPosY() - pY) };
		hypotenuse = sqrt( pow((player.GetPosX() - pX), 2) + pow((player.GetPosY() - pY), 2) );
	}

	pX += speed * deltaTime * (dir.x / float(hypotenuse));
	pY += speed * deltaTime * (dir.y / float(hypotenuse));

	//Using tmpl8 normalize 
	/*
	float2 dir = { (player.GetPosX() - pX) , (player.GetPosY() - pY) };
	dir = normalize(dir);

	pX += speed * deltaTime * dir.x;
	pY += speed * deltaTime * dir.y;
	*/
}

void Bullet::Reload()
{
	pX = owner->pX + CHARWIDTH / 2;
	pY = owner->pY + CHARHEIGHT / 2;
}

void Bullet::CheckOverlaping()
{
	
}

void Bullet::ResetBullet(float deltaTime, bool boundsCheck)
{
	//You check if you reset the bullet after a bound check or not because you don't want to wait after the bullet exits the screen 
	//(out of bounds surface tmpl8 error)
	if (boundsCheck)
	{
		Reload();
		calculated = false;
		owner->ChangeState(Enemy::State::FOLLOW);
	}
	else
	{
		elapsed += deltaTime;
		if (elapsed >= owner->reloadTime)
		{
			elapsed = 0.f;
			Reload();
			calculated = false;
			owner->ChangeState(Enemy::State::FOLLOW);
		}
	}
}

void Bullet::Render(Surface* screen)
{
	screen->Bar(int(pX), int(pY), int(pX) + int(sX), int(pY) + int(sY), 0xffffff);
}

void Bullet::Update(Surface* screen, float deltaTime, Player& player, MapManager& floor)
{
	//Check For Player Hit
	CheckPlayerCollision(player, deltaTime);

	if (owner->enemyState == Enemy::State::SHOOT)
	{
		Render(screen);
		BulletMovement(deltaTime, player);

		if (floor.maps[floor.rowIndex][floor.columnIndex].boxes[GetTileX()][GetTileY()].type == BoundingBox::BoxTypes::WALL)
		{
			ResetBullet(deltaTime, false);
		}
	}
	else
	{
		Reload();
	}

	//If Bullet Go Out Of Bounds
	if ((pX + sX > SCRWIDTH || pX < 0) || (pY + sY > SCRHEIGHT || pY < 0))
	{
		ResetBullet(deltaTime, true);
	}
}

void Bullet::CheckPlayerCollision(Player& player, float deltaTime)
{
	bool collisionX = pX + sX >= player.hitX && player.hitX + player.hitSX >= pX;
	bool collisionY = pY + sY >= player.hitY && player.hitY + player.hitSY >= pY;

	if (collisionX && collisionY && gotHit == false)
	{
		gotHit = true;
		player.gettingDamage = true;
		player.Damage(10);
		ResetBullet(deltaTime, false);
	}

	//Avoids hitting the player multiple times
	else if (!(collisionX && collisionY))
	{
		gotHit = false;
	}

}
