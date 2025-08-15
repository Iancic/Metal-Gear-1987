#pragma once
#include "Enemy.h"

class RedGuard : Enemy
{
public:

	RedGuard();
	~RedGuard() { };

	void InitRedGuard(float posX, float posY);
	virtual void Update(Surface* screen, float deltaTime, MapManager& floor, Player& player) override;

private:
};

