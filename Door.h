#pragma once
#include "Player.h"

class Door
{
public:

	Door() { };
	~Door() { };

	Sprite* sprite = nullptr;

	float pX, pY, sX, sY;
	float bbPX, bbPY, bbSX, bbSY;
	float doorSX;

	bool animating = false;

	void Update(Surface* screen, float deltaTime, Player& player);
	
	void Render(Surface* screen);

	virtual void CheckCollision(Player& player);

	virtual void PlayAnimation(Surface* screen, float deltaTime);

private:
};

