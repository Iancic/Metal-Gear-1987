#pragma once
#include "Item.h"

class AccesCard : public Item
{
public:
	AccesCard(Player& ownerPlayer);
	~AccesCard() { };

	Player& owner;

	void ShowTextBox(Surface* screen, float deltaTime);

	virtual void ItemBehaviour() override;

private:
};

