#pragma once
#include "Item.h"
#include "Placeable.h"

#include "MapManager.h"

#include "Enemy.h"
#include "Player.h"


class Mine : public Item
{
public:
	Mine(Player& ownerPlayer, MapManager& map);
	~Mine() { };

	Player& playerOwner;
	MapManager& mapOwner;

	int numberOfMines = 5;
	int minesCounter = -1;
	int minesIndex = 0;

	Placeable* placeables[5] = { nullptr };

	void UpdatePlaceables(Surface* screen, float deltaTime, Enemy* enemy[6]);

	void ShowTextBox(Surface* screen, float deltaTime);

	virtual void ItemBehaviour() override;

private:
};

