#pragma once
#include "Item.h"

class GasMask : public Item
{
public:
	GasMask();
	~GasMask() { };

	void ShowTextBox(Surface* screen, float deltaTime);

	virtual void ItemBehaviour() override;

private:
};

