#include "precomp.h"
#include "Gun.h"

Gun::Gun()
{
	sX = 86, sY = 60;
	strcpy(name, "Gun");
	sprite = new Sprite(new Surface("assets/Items/Gun.png"), 1);
}

void Gun::ShowTextBox(Surface* screen, float deltaTime)
{
	if (pickedUp)
	{
		elapsed += deltaTime;
		textContainer.Render(screen, 650, 50, 335, 50);
		text.Render(screen, 660, 60, name, false, deltaTime);
	}
}

void Gun::ItemBehaviour()
{
	std::cout << "Gun does this";
}
