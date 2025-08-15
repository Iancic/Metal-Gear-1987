#include "precomp.h"
#include "GasMask.h"

GasMask::GasMask()
{
	strcpy(name, "Gas Mask");
	sprite = new Sprite(new Surface("assets/Items/GasMask.png"), 1);
}

void GasMask::ShowTextBox(Surface* screen, float deltaTime)
{
	if (pickedUp)
	{
		elapsed += deltaTime;
		textContainer.Render(screen, 650, 50, 335, 50);
		text.Render(screen, 660, 60, name, false, deltaTime);
	}
}

void GasMask::ItemBehaviour()
{

}
