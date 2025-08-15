#include "precomp.h"
#include "Door.h"

void Door::Render(Surface* screen)
{
	sprite->Draw(screen, int(pX), int(pY));
#ifdef DEBUGMODE
	screen->Box(bbPX, bbPY, bbPX + sX, bbPY + bbSY, 0xffffff);
#endif
}

void Door::CheckCollision(Player& player)
{
	bool collisionX = player.bbX + player.bbSX >= pX && pX + sX >= player.bbX;
	bool collisionY = player.bbY + player.bbSY >= pY && pY + sY >= player.bbY;

	if (collisionX && collisionY && player.hasAccesCard)
	{
		animating = true;
	}
	else if (collisionX && collisionY && !player.hasAccesCard)
	{
		player.bbX = player.previousBBX;
		player.bbY = player.previousBBY;
	}
	else //If the box is walkable move the player to the box.
	{
		player.pX = player.bbX - player.bbOffsetX;
		player.pY = player.bbY - player.bbOffsetY;
	}
}

void Door::Update(Surface* screen, float deltaTime, Player& player)
{
	Render(screen);

	if (animating)
		PlayAnimation(screen, deltaTime);

	CheckCollision(player);
}

void Door::PlayAnimation(Surface* screen, float deltaTime)
{
	if (bbSX < sX)
	{
		bbSX += 150 * deltaTime;
	}

	screen->Bar(int(bbPX), int(bbPY), int(bbPX + bbSX), int(bbPY + bbSY), 0x000000); //Right Bar
}
