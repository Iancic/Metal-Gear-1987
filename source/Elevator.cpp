#include "precomp.h"
#include "Elevator.h"

Elevator::Elevator()
{
	sprite = new Sprite(new Surface("assets/Others/Elevator.png"), 1);
}

void Elevator::Update(Player& player, float deltaTime)
{

	if (player.GetPosX() >= position.x && player.GetPosX() <= position.x + scale.x - 80 && !reachedTop) //When player enters elevator
	{
		player.playerState = Player::States::ELEVATOR; //Fix Player Position
		position.y -= 150.f * deltaTime;
	}

	if (player.GetPosY() < 207.f)
	{
		reachedTop = true;
		player.playerState = Player::States::RUN; //Fix Player Position
	}
}

void Elevator::Render(Surface* screen)
{
	sprite->Draw(screen, int(position.x), int(position.y));

#ifdef DEBUGMODE
	screen->Box(position.x, position.y, position.x + scale.x, position.y + scale.y, 0xffffff);
#endif
}
