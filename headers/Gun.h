#pragma once
#include "Item.h"

class Gun : public Item
{
public:
	Gun();
	~Gun() { };

	void ShowTextBox(Surface* screen, float deltaTime);

	virtual void ItemBehaviour() override;

private:
};

