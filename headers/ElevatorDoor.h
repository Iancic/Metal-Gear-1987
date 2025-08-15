#pragma once
#include "Door.h"
class ElevatorDoor : public Door
{
public:

	ElevatorDoor(float posX, float posY);
	~ElevatorDoor() { };

	int door2Counter;

	virtual void PlayAnimation(Surface* screen, float deltaTime) override;

	virtual void CheckCollision(Player& player) override;

private:

};

