#pragma once
#include "Item.h"

class Cigar :public Item
{
public:
	Cigar();
	~Cigar() { };

	void ShowTextBox(Surface* screen, float deltaTime);

	virtual void ItemBehaviour() override;

private:
};

