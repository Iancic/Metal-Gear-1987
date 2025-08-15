#include "precomp.h"
#include "Ration.h"

Ration::Ration(Player& ownerPlayer) : owner(ownerPlayer)
{
	strcpy(name, "Ration");
	sprite = new Sprite(new Surface("assets/Items/Ration.png"), 1);
}

void Ration::ShowTextBox(Surface* screen, float deltaTime)
{
	if (pickedUp)
	{
		elapsed += deltaTime;
		textContainer.Render(screen, 650, 50, 335, 50);
		text.Render(screen, 660, 60, name, false, deltaTime);
	}
}

void Ration::ItemBehaviour()
{
	if (owner.hitPoints <= 90)
		owner.hitPoints += 10;
}
