#include "precomp.h"
#include "AccesCard.h"

AccesCard::AccesCard(Player& ownerPlayer) : owner(ownerPlayer)
{
	strcpy(name, "Acces Card");
	sprite = new Sprite(new Surface("assets/Items/AccesCard.png"), 1);
}

void AccesCard::ShowTextBox(Surface* screen, float deltaTime)
{
	if (pickedUp)
	{
		elapsed += deltaTime;
		textContainer.Render(screen, 650, 50, 335, 50);
		text.Render(screen, 660, 60, name, false, deltaTime);
	}
}

void AccesCard::ItemBehaviour()
{
	owner.hasAccesCard = true;
}
