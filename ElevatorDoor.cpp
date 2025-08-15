#include "precomp.h"
#include "ElevatorDoor.h"

ElevatorDoor::ElevatorDoor(float posX, float posY)
{
	pX = posX, pY = posY, sX = TILESIZE * 5, sY = TILESIZE * 4;
	bbPX = posX, bbPY = posY, bbSX = 0, bbSY = sY;

	door2Counter = int(pX) + TILESIZE * 2;

	sprite = new Sprite(new Surface("assets/Others/ElevatorDoor.png"), 1);
}

void ElevatorDoor::PlayAnimation(Surface* screen, float deltaTime)
{
	int doorSlide = 150 * int(deltaTime);

	if (door2Counter > pX)
	{
		door2Counter -= doorSlide;
	}

	if (bbSX < sX - TILESIZE)
	{
		bbSX += doorSlide;
	}
	

	screen->Bar(int(pX + TILESIZE * 2), int(bbPY), int(pX + bbSX), int(bbPY + bbSY), 0x000000); //Right Bar
	screen->Bar(int(door2Counter), int(bbPY), int(pX + TILESIZE * 2), int(bbPY + bbSY), 0x000000); //Left Bar
}

void ElevatorDoor::CheckCollision(Player& player)
{
	bool collisionX = player.bbX + player.bbSX >= pX && pX + sX >= player.bbX;
	bool collisionY = player.bbY + player.bbSY >= pY && pY + sY >= player.bbY;

	if (collisionX && collisionY)
	{
		animating = true;
	}
}
