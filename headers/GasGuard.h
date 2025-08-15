#pragma once
#include "Enemy.h"

class GasGuard : public Enemy
{
public:

	GasGuard();
	~GasGuard() { };

	float elapsedSnore = 0.f;
	int counterSnore = 0;
	Sprite* snore;

	void InitGasGuard(float pX, float pY);
	void Update(Surface* screen, float deltaTime);

private:
};

