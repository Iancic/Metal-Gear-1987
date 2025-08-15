#pragma once
#include "Item.h"
#include "Binoculars.h"
#include "AccesCard.h"
#include "GasMask.h"
#include "Cigar.h"
#include "Gun.h"
#include "Item.h"
#include "Ration.h"
#include "Mine.h"

class Inventory
{
public:

	Inventory();
	~Inventory() { };

	int currentCapacity = 0;
	int stackCounter = 0;

	int selectedIndex = 0;

	//Store pointers to Items to preserve polymorphism.
	Item* inventoryItems[9] = { nullptr };

	void AddCigar(Cigar* item);
	void AddBinoculars(Binoculars* item);
	void AddRation(Ration* item);
	void AddGun(Gun* item);
	void AddGasMask(GasMask* item);
	void AddAccesCard(AccesCard* item);
	void AddMine(Mine* item);

	void UseItem();

private:
};

