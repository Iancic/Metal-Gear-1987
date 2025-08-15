#pragma once
#include "Item.h"
#include "MapManager.h"

class Binoculars : public Item
{
public:
	Binoculars(MapManager& ownerMap);
	~Binoculars() { };

	MapManager& owner;
	
	void ShowTextBox(Surface* screen, float deltaTime);

	virtual void ItemBehaviour() override;

private:
};

