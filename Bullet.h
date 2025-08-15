#pragma once
#include "BoundingBox.h"
#include "Enemy.h"

class Bullet
{
public:
	Bullet() { };
	~Bullet() { };

	float speed = 380.f;

	float pX = 100.f, pY = 100.f, sX = 7.f, sY = 7.f; 
	float dirX, dirY;

	bool gotHit = false;
	bool calculated = false;

	double hypotenuse;
	float2 dir;

	float elapsed = 0.f;

	BoundingBox bulletBox;
	Enemy* owner;

	void Init(Enemy* enemy);

	void BulletMovement(float deltaTime, Player& player);

	void CheckPlayerCollision(Player& player, float deltaTime);

	void ResetBullet(float deltaTime, bool boundsCheck);
	void Reload();

	void CheckOverlaping();

	void Render(Surface* screen);
	void Update(Surface* screen, float deltaTime, Player& player, MapManager& floor);

	int GetTileX() { return int(pX) / TILESWIDTH; };
	int GetTileY() { return int(pY) / TILESWIDTH; };

private:
};

