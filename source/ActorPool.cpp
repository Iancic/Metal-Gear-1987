#include "precomp.h"
#include "ActorPool.h"

ActorPool::ActorPool()
{
	Snake = new Player();

	Enemy_2_0_A = new Enemy();
	Enemy_2_0_B = new Enemy();
}

void ActorPool::Init()
{
	pool[0] = Snake;

	//2_0 Entities
	pool[1] = Enemy_2_0_A;
	pool[2] = Enemy_2_0_B;

	Enemy::Direction sequence_Enemy_2_0_A[8] = { Enemy::Direction::UP, Enemy::Direction::LEFT, Enemy::Direction::DOWN,
										Enemy::Direction::RIGHT, Enemy::Direction::UP, Enemy::Direction::LEFT,
										Enemy::Direction::DOWN, Enemy::Direction::LEFT };
	Enemy::Direction sequence_Enemy_2_0_B[2] = { Enemy::Direction::LEFT,
										Enemy::Direction::RIGHT };

	Enemy_2_0_A->Init(360, 380, 8, sequence_Enemy_2_0_A);
	Enemy_2_0_B->Init(700, 120, 2, sequence_Enemy_2_0_B);
}

void ActorPool::Update()
{
	for (Actor* actor : pool)
	{
		if (actor->alive)
		{
			//actor->Update(screen, deltaTime, floor);
		}
	}
}
