#include "precomp.h"
#include "Inventory.h"

Inventory::Inventory()
{
}

void Inventory::AddCigar(Cigar* item)
{
	if (item != nullptr)
	{
		if (item->pickedUp && !item->addedToInventory)
		{
			item->addedToInventory = true;
			currentCapacity++;
			inventoryItems[stackCounter] = item;
			stackCounter++;
		}
	}
}

void Inventory::AddBinoculars(Binoculars* item)
{
	if (item != nullptr)
	{
		if (item->pickedUp && !item->addedToInventory)
		{
			item->addedToInventory = true;
			currentCapacity++;
			inventoryItems[stackCounter] = item;
			stackCounter++;
		}
	}
}

void Inventory::AddRation(Ration* item)
{
	if (item != nullptr)
	{
		if (item->pickedUp && !item->addedToInventory)
		{
			item->addedToInventory = true;
			currentCapacity++;
			inventoryItems[stackCounter] = item;
			stackCounter++;
		}
	}
}

void Inventory::AddGun(Gun* item)
{
	if (item != nullptr)
	{
		if (item->pickedUp && !item->addedToInventory)
		{
			item->addedToInventory = true;
			currentCapacity++;
			inventoryItems[stackCounter] = item;
			stackCounter++;
		}
	}
}

void Inventory::AddGasMask(GasMask* item)
{
	if (item != nullptr)
	{
		if (item->pickedUp && !item->addedToInventory)
		{
			item->addedToInventory = true;
			currentCapacity++;
			inventoryItems[stackCounter] = item;
			stackCounter++;
		}
	}
}

void Inventory::AddAccesCard(AccesCard* item)
{
	if (item != nullptr)
	{
		if (item->pickedUp && !item->addedToInventory)
		{
			item->addedToInventory = true;
			currentCapacity++;
			inventoryItems[stackCounter] = item;
			stackCounter++;
		}
	}
}

void Inventory::AddMine(Mine* item)
{
	if (item != nullptr)
	{
		if (item->pickedUp && !item->addedToInventory)
		{
			item->addedToInventory = true;
			currentCapacity++;
			inventoryItems[stackCounter] = item;
			stackCounter++;
		}
	}
}

void Inventory::UseItem()
{
	if (inventoryItems[selectedIndex] != nullptr) {
		inventoryItems[selectedIndex]->ItemBehaviour();
	}
}
