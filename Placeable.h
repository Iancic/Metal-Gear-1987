#pragma once
#include "Enemy.h"

class Placeable
{
public:
	Placeable(float positionX, float positionY, int row, int column);
	~Placeable() { };

	float2 scale = { 60.f, 60.f };
	float2 position;

	int2 floorIndex;
		
	Sprite* sprite = nullptr;
	Sprite* explosion = nullptr;

	int explosionCounter = 0;
	float elapsed = 0.f;

	bool triggered = false, exploding = false;

	void Update(Surface* screen, float deltaTime, Enemy* enemy[6]);
	void Render(Surface* screen);

	void CheckEnemyCollision(Enemy* enemy[6]);

private:

};

