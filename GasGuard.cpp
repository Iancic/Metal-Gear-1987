#include "precomp.h"
#include "GasGuard.h"

GasGuard::GasGuard()
{
	sprite = new Sprite(new Surface("assets/Characters/gasGuard.png"), 12);
	snore = new Sprite(new Surface("assets/Characters/Snore.png"), 3);

	bbX = 508, bbY = 600, bbSX = 15, bbSY = 15;
	bbOffsetX = (CHARWIDTH / 2);
	bbOffsetY = (CHARHEIGHT / 4) * 3 + 10;

	movementSpeed = patrolSpeed;

	maxHitPoints = 5;
	hitPoints = maxHitPoints;

	reloadTime = 1.5f, followSpeed = 130.f, patrolSpeed = 90.f, thresholdShoot = 170.f;

	rayLenght = 800;

	counterSequence = 0;
	elapsedIddle = 0.f;
	counterIddle = 0;
	counter = 0;
}

void GasGuard::InitGasGuard(float posX, float posY)
{
	ChangeState(State::IDLE);

	bbX = 508, bbY = 600, bbSX = 15, bbSY = 15;
	bbOffsetX = (CHARWIDTH / 2);
	bbOffsetY = (CHARHEIGHT / 4) * 3 + 10;

	bbX = posX;
	bbY = posY;
}

void GasGuard::Update(Surface* screen, float deltaTime)
{
	elapsedSnore += deltaTime;

	if (elapsedSnore >= 1.f)
	{
		counterSnore++;

		if (counterSnore == 3)
			counterSnore = 0;
	}

	snore->SetFrame(counterSnore);
	snore->Draw(screen, int(pX - 60), int(pY - 60));

	//Update Main HitBox Position
	hitX = pX;
	hitY = pY;

	previousX = bbX;
	previousY = bbY;

	sprite->SetFrame(stopAnimation);

	pX = bbX - bbOffsetX;
	pY = bbY - bbOffsetY;

	Render(screen, gettingDamage);
}
