#pragma once
#include "Player.h"

class Elevator
{

public:

	Elevator();
	~Elevator() { };

	Sprite* sprite;

	float2 scale = { 128.f, 208.f };
	float2 position = { 365.f, 560.f };

	bool reachedTop = false;

	void Update(Player& player, float deltaTime);
	void Render(Surface* screen);

private:

};

