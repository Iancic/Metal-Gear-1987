#include "precomp.h"
#include "Mine.h"

Mine::Mine(Player& owner, MapManager& map) :
	playerOwner(owner), mapOwner(map)
{
	strcpy(name, "Mine");
	sprite = new Sprite(new Surface("assets/Items/Mine.png"), 1);
}

void Mine::UpdatePlaceables(Surface* screen, float deltaTime, Enemy* enemy[6])
{
	for (int i = 0; i <= minesCounter; i++)
	{
		//Check if the placeable is in the room where it was initialized.
		if (mapOwner.rowIndex == placeables[i]->floorIndex.x && mapOwner.columnIndex == placeables[i]->floorIndex.y)
			placeables[i]->Update(screen, deltaTime, enemy);
	}
}

void Mine::ShowTextBox(Surface* screen, float deltaTime)
{
	if (pickedUp)
	{
		elapsed += deltaTime;
		textContainer.Render(screen, 650, 50, 335, 50);
		text.Render(screen, 660, 60, name, false, deltaTime);
	}
}

void Mine::ItemBehaviour()
{
	if (minesCounter <= 4)
	{
		//Take player current position and map index for update.
		minesCounter++;
		placeables[minesCounter] = new Placeable(playerOwner.pX + playerOwner.sX / 2 - 32, playerOwner.pY + playerOwner.sY / 2, mapOwner.rowIndex, mapOwner.columnIndex);
	}
}
