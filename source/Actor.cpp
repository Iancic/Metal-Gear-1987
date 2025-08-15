#pragma once
#include "precomp.h"
#include "game.h"
#include "Actor.h"
#include "common.h"

Actor::Actor() :
	movementSpeed(0),
	bbSX(CHARWIDTH - 20), bbSY(CHARHEIGHT / 4 / 2),
	sX(CHARWIDTH), sY(CHARHEIGHT)
{
}

void Actor::updateAnimation(float deltaTime, const int3& animation)
{
	elapsed += deltaTime * animationSpeed;

	//Considering first frame is static:
	stopAnimation = animation.x;

	if (elapsed >= 1.f)
	{
		elapsed = 0.f;
		counter++;
	}

	//Considering animations are 2 frames:
	if (counter % 2 == 0)
		currentFrame = animation.y;
	else if (counter % 2 == 1)
		currentFrame = animation.z;

	sprite->SetFrame(currentFrame);
}

void Actor::SetFrame(int desiredFrame)
{
	currentFrame = desiredFrame;
	sprite->SetFrame(desiredFrame);
}

void Actor::Render(Surface* screen, bool& damaged)
{
	sprite->DrawActor(screen, int(pX), int(pY), damaged);
#ifdef DEBUGMODE
	//Feet HitBox
	screen->Box(bbX, bbY, bbX + bbSX, bbY + bbSY, 0x0000ff);

	//Main HitBox
	screen->Box(hitX, hitY, hitX + hitSX, hitY + hitSY, 0xffffff);
#endif
}

void Actor::RenderIntro(Surface* screen)
{
	sprite->Draw(screen, int(pX), int(pY));
#ifdef DEBUGMODE
	//Feet HitBox
	screen->Box(bbX, bbY, bbX + bbSX, bbY + bbSY, 0x0000ff);

	//Main HitBox
	screen->Box(hitX, hitY, hitX + hitSX, hitY + hitSY, 0xffffff);
#endif
}
