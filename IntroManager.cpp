#include "precomp.h"
#include "game.h"
#include "IntroManager.h"
#include "MapManager.h"

IntroManager::IntroManager()
{
	player.sprite = new Sprite(new Surface("assets/Characters/SolidSnake.png"), 42);

	//Initial Player Swim Positions (700 on X, 670 on Y)
	player.pX = 700;
	player.pY = 670;
}

void IntroManager::MSXAnimation(Surface* screen, float deltaTime)
{
	float incrementMSX = 150;

	//Audio
	//intro.play();

	screen->Clear(0x0112fd);

	if (posXMT1 < posXMT2)
	{
		posXMT1 += incrementMSX * deltaTime;
		posXMT2 -= incrementMSX * deltaTime;
	}

	if (posXMT1 >= posXMT2)
	{
		ChangeStage(deltaTime, IntroStage::KONAMI);
	}

	msx1->DrawScaled(int(posXMT1), int(posYMT1), int(204 * scaleXMT), int(80 * scaleYMT), screen); //Original Size: 204 x 80
	msx2->DrawScaled(int(posXMT2), int(posYMT2), int(204 * scaleXMT), int(80 * scaleYMT), screen); //Original Size: 204 x 80

	screen->Bar(0, 0, 200, SCRHEIGHT - 1, 0x0112fd); //Left Bar
	screen->Bar(SCRWIDTH - 200, 0, SCRWIDTH, SCRHEIGHT - 1, 0x0112fd); //Right Bar
}

void IntroManager::KonamiAnimation(Surface* screen, float deltaTime)
{
	if (posBarY < posYK + 28 * scaleYK)
	{
		posBarY += deltaTime * animationSpeed;
	}

	if (posBarY >= posYK + 28 * scaleYK)
	{
		ChangeStage(deltaTime, IntroStage::BUAS);
	}

	screen->Clear(0xffffff);
	konami->DrawScaled(int(posXK), int(posYK), int(157 * scaleXK), int(28 * scaleYK), screen); //Original Size: 157 x 28
	screen->Bar(int(posBarX), int(posBarY), int(posBarX + 157 * scaleXK), int(SCRHEIGHT - 1), 0xffffff); //Right Bar
}

void IntroManager::TitleScreenAnimation(Surface* screen, float deltaTime)
{
	intro.pause();

	screen->Clear(0x000000);

	elapsed += deltaTime;
	if (elapsed > 0.125f)
	{
		intro2.play();
		increment++;
		elapsed = 0.f;
	}

	if (increment <= 9)
	{
		for (int i = 0; i < increment; i++)
		{
			titleScreen->DrawScaled(int(posXTS), int(posYTS - (70 * i)), int(350 * scaleXTS), int(76 * scaleYMTS), screen); //Original Size: 350 x 76
		}
	}
	else
	{
		intro2.pause();
		screen->Clear(0x000000);
		titleScreen->DrawScaled(int(posXTS), int(600.f - (8 * 70)), int(350 * scaleXTS), int(76 * scaleYMTS), screen); //Original Size: 350 x 76

		Copyright.Render(screen, 350, 300, "Konami 0876", false, deltaTime);
		PlayStart.BreathingRender(screen, 370, 380, "Play Start ", 0xffffff, deltaTime);
	}
}

void IntroManager::BuasAnimation(Surface* screen, float deltaTime)
{
	if (posBarYBuas < posYBuas + 58 * scaleYBuas)
	{
		posBarYBuas += deltaTime * animationSpeed;
	}

	if (posBarYBuas >= posYBuas + 58 * scaleYBuas)
	{
		ChangeStage(deltaTime, IntroStage::TITLESCREEN);
	}

	screen->Clear(0xef7522);
	Buas->DrawScaled(int(posXBuas), int(posYBuas), int(81 * scaleXBuas), int(58 * scaleYBuas), screen); //Original Size: 81 x 58
	screen->Bar(int(posBarXBuas), int(posBarYBuas), int(posBarXBuas + 157 * scaleXBuas), int(SCRHEIGHT - 1), 0xef7522); //Right Bar
}

void IntroManager::Swim1(Surface* screen, float deltaTime)
{
	player.RenderIntro(screen);
	
	//Left To Middle Swim
	if (player.pX >= 500 && !swimToMiddle)
	{
		player.updateAnimation(deltaTime, swim);
		player.pX = player.pX - swimSpeed * deltaTime;
	}
	else
	{
		player.SetFrame(staticTop);
		swimElapsed += deltaTime;
		if (swimElapsed > 1.f)
		{
			swimElapsed = 0.f;
			swimToMiddle = true;
		}
	}

	//Middle To Box
	if (swimToMiddle)
	{
		if (player.pX >= 200)
		{
			player.updateAnimation(deltaTime, swim);
			player.pX = player.pX - swimSpeed * deltaTime;
		}
		else if (!swimToBox)
		{
			player.updateAnimation(deltaTime, swim);
			swimElapsed += deltaTime;
			if (swimElapsed > 0.5f)
			{
				swimElapsed = 0.f;
				swimToBox = true;
				player.SetFrame(staticTop);
			}
		}
	}

	//Swim To Box
	if (swimToBox)
	{
		if (player.pY >= 600)
		{
			player.updateAnimation(deltaTime, swim);
			player.pY = player.pY - swimSpeed * deltaTime;
		}
		else
		{
			player.SetFrame(staticRight);
			swimElapsed += deltaTime;
			if (swimElapsed > 1.f)
			{
				player.SetFrame(staticRight);
				swimElapsed = 0.f;
				canRadio = true;
			}
		}
	}

	screen->Bar(0, BASESCRHEIGHT, SCRWIDTH, SCRHEIGHT - 1, 0x000000);
}

void IntroManager::Swim2(Surface* screen, float deltaTime)
{
	player.RenderIntro(screen);

	//Walk To Middle
	if (!walkToMiddle)
	{
		if (player.pX <= 500.f)
		{
			player.updateAnimation(deltaTime, walkRight);
			player.pX = player.pX + swimSpeed * deltaTime;
		}
		else
		{
			player.SetFrame(staticTop);
			swimElapsed += deltaTime;
			if (swimElapsed > 1.f)
			{
				swimElapsed = 0.f;
				walkToMiddle = true;
			}
		}
	}
	
	//Swim To Fence
	if (walkToMiddle)
	{
		if (player.pY >= 500.f)
		{
			player.updateAnimation(deltaTime, walkUp);
			player.pY = player.pY - swimSpeed * deltaTime;
		}
		else
		{
			player.SetFrame(staticTop);
			swimElapsed += deltaTime;
			if (swimElapsed > 1.f)
			{
				swimElapsed = 0.f;
				walkToMiddle = false;
				gettingOverFence = true;
			}
		}
	}

	//Get Over Fence
	if (gettingOverFence)
	{
		if (player.pY >= 300.f)
		{
			player.updateAnimation(deltaTime, fence);
			player.pY = player.pY - swimSpeed * deltaTime;
		}
		else
		{
			player.SetFrame(staticTop);
			swimElapsed += deltaTime;
			if (swimElapsed > 0.1f)
			{
				swimElapsed = 0.f;
				gettingOverFence = false;
				canStartGame = true;
				canRadio = false;
			}
		}
	}

	screen->Bar(0, BASESCRHEIGHT, SCRWIDTH, SCRHEIGHT - 1, 0x000000);
}

void IntroManager::SkipText(Surface* screen, float deltaTime, uint c)
{
	SpacebarText.BreathingRender(screen, 260, 820, "SpaceBar To Skip", c, deltaTime);
}

void IntroManager::ChangeStage(float deltaTime, IntroStage whatStage)
{
	elapsedStages += deltaTime;

	if (elapsedStages > 1.f)
	{
		currentStage = whatStage;
		elapsedStages = 0.f;
	}
}
