#pragma once

#include "Actor.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

class ActorPool
{

public:

	ActorPool();
	~ActorPool() { };

	const int totalActors = 1;
	Actor* pool[1] = { };

	//Player
	Player* Snake = nullptr;

	//Enemies
	Enemy* Enemy_2_0_A = nullptr;
	Enemy* Enemy_2_0_B = nullptr;

	Enemy* Enemy_3_1_A = nullptr;
	Enemy* Enemy_3_1_B = nullptr;

	Enemy* Enemy_1_0_A = nullptr;
	Enemy* Enemy_1_0_B = nullptr;

	Enemy* Enemy_0_0_A = nullptr;
	Enemy* Enemy_0_0_B = nullptr;

	Enemy* Enemy_2_1_Jeep = nullptr;

	Enemy* Enemy_0_1_A = nullptr;
	Enemy* Enemy_0_1_B = nullptr;
	Enemy* Enemy_0_1_C = nullptr;
	Enemy* Enemy_0_1_D = nullptr;

	void Init();

	void Update();

private:

};

