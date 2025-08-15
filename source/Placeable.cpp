#include "precomp.h"
#include "Placeable.h"

Placeable::Placeable(float positionX, float positionY, int row, int column)
{
	sprite = new Sprite(new Surface("assets/Items/Placeable.png"), 1);
	explosion = new Sprite(new Surface("assets/Items/Explosion.png"), 4);
	explosion->SetFrame(3);

	floorIndex.x = row;
	floorIndex.y = column;

	position.x = positionX;
	position.y = positionY;
}

void Placeable::Update(Surface* screen, float deltaTime, Enemy* enemy[6])
{
	if (!triggered)
	{
		Render(screen);
		CheckEnemyCollision(enemy);
	}

	if (exploding)
	{
		//Counter
		elapsed += deltaTime;
		if (elapsed >= 0.1f)
		{
			elapsed = 0.f;
			explosionCounter++;
		}

		//Animation
		if (explosionCounter <= 3)
		{
			explosion->SetFrame(explosionCounter);
			explosion->Draw(screen, int(position.x - 32), int(position.y - 32));
		}
		else
		{
			triggered = true;
			exploding = false;
		}
	}
}

void Placeable::CheckEnemyCollision(Enemy* enemy[6])
{
	for (int i = 0; i < 5; i ++)
	{
		bool collisionX = position.x + scale.x >= enemy[i]->bbX && enemy[i]->bbX + enemy[i]->bbSX >= position.x;
		bool collisionY = position.y + scale.y >= enemy[i]->bbY && enemy[i]->bbY + enemy[i]->bbSY >= position.y;

		if (collisionX && collisionY)
		{
			enemy[i]->alive = false;
			exploding = true;
		}
	}
}

void Placeable::Render(Surface* screen)
{
	sprite->Draw(screen, int(position.x), int(position.y));

#ifdef DEBUGMODE
	screen->Box(position.x, position.y, position.x + scale.x, position.y + scale.y, 0xffffff);
#endif
}
