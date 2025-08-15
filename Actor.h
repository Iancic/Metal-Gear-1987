#pragma once
#include "BoundingBox.h"
#include "MapManager.h"
#include "common.h"

class Actor
{
public:

	Actor();
	~Actor() { };

	Sprite* sprite;

	//Game Logic
	float movementSpeed;
	int hitPoints, maxHitPoints;
	bool alive = true;

	//Animation Frame
	int currentFrame;

	//Sprite Position and Scale
	float pX, pY, sX, sY;

	//Feet HitBox
	float bbX, bbY, bbSX, bbSY;

	//Main HitBox
	float hitX = pX, hitY = pY, hitSX = CHARWIDTH, hitSY = CHARHEIGHT;

	//Animations:
	float animationSpeed = 4.1f, elapsed = 0;
	int counter = 1, stopAnimation = 0;

	void updateAnimation(float deltaTime, const int3& animation);
	void SetFrame(int desiredFrame);

	void Damage(int hits) { hitPoints -= hits; };

	void Render(Surface* screen, bool& damaged);
	void RenderIntro(Surface* screen);

	float GetPosX() const { return bbX; };
	float GetPosY() const { return bbY; };
	float GetScaleX() const { return sX; };
	float GetScaleY() const { return sY; };

private:
};
