#include "precomp.h"
#include "Binoculars.h"

Binoculars::Binoculars(MapManager& ownerMap) : owner(ownerMap)
{
	strcpy(name, "Scope");
	sprite = new Sprite(new Surface("assets/Items/Binoculars.png"), 1);
}

void Binoculars::ShowTextBox(Surface* screen, float deltaTime)
{
	if (pickedUp)
	{
		elapsed += deltaTime;
		textContainer.Render(screen, 650, 50, 335, 50);
		text.Render(screen, 660, 60, name, false, deltaTime);
	}
}

void Binoculars::ItemBehaviour()
{
	owner.binoculars = true;
}
