#pragma once
#include "Item.h"

class Ration : public Item
{
public:
	Ration(Player& ownerPlayer);
	~Ration() { };

	Player& owner;

	void ShowTextBox(Surface* screen, float deltaTime) override;
	void ItemBehaviour() override;

private:
};

