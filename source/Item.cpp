#include "precomp.h"
#include "game.h"
#include "Item.h"

Item::Item()
{
	sprite = new Sprite(new Surface("assets/Items/Cigar.png"), 1);
}

void Item::Update(Surface* screen, float deltaTime, float posX, float posY, Player& player)
{
	pX = posX;
	pY = posY;
	Render(screen, deltaTime);
	CheckCollision(player);
}

//If picked up render text box for a second. If not render item.
void Item::Render(Surface* screen, float deltaTime)
{
	if (!pickedUp)
	{
		sprite->DrawScaled(int(pX), int(pY), int(sX), int(sY), screen);

#ifdef DEBUGMODE
		screen->Box(pX, pY, pX + sX, pY + sY, 0xffffff);
#endif
	}
	else if (elapsed < 1.f && pickedUp)
		ShowTextBox(screen, deltaTime);

}

void Item::RenderInventory(Surface* screen, float posX, float posY)
{
	sprite->DrawScaled(int(posX), int(posY), int(sX), int(sY), screen);
}

void Item::CheckCollision(Player& player)
{
	bool collisionX = pX + sX >= player.hitX && player.hitX + player.hitSX >= pX;
	bool collisionY = pY + sY >= player.hitY && player.hitY + player.hitSY >= pY;

	if (collisionX && collisionY)
	{
		pickedUp = true;
	}
}

void Item::ShowTextBox(Surface* screen, float deltaTime)
{
	if (pickedUp)
	{
		elapsed += deltaTime;
		textContainer.Render(screen, 300, 300, 60, 60);
		text.Render(screen, 300, 300, name, false, deltaTime);
	}
}

void Item::ItemBehaviour()
{
	std::cout << "Item does this";
}

char* Item::GetName()
{
	return name;
}
