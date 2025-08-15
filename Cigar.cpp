#include "precomp.h"
#include "Cigar.h"

Cigar::Cigar()
{
	strcpy(name, "Cigar");
	sprite = new Sprite(new Surface("assets/Items/Cigar.png"), 1);
}

void Cigar::ShowTextBox(Surface* screen, float deltaTime)
{
	if (pickedUp)
	{
		elapsed += deltaTime;
		textContainer.Render(screen, 650, 50, 335, 50);
		text.Render(screen, 660, 60, name, false, deltaTime);
	}
}

void Cigar::ItemBehaviour()
{
	std::cout << "Cigar does this";
}
