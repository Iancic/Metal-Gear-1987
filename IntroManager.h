#pragma once
#include "Text.h"
#include "Actor.h"
#include <Audio/Sound.hpp>

class IntroManager
{
public:
	IntroManager();
	~IntroManager() { };

	//Swim
	int3 swim = { 0, 40, 41 };
	int3 fence = { 0, 12, 13 };
	int3 walkRight = { 0, 39, 35 };
	int3 walkUp = { 0, 38, 34 };

	float swimElapsed = 0.f;
	float swimSpeed = 120.f;
	Actor player;

	int staticTop = 38, staticRight = 39;

	//Swim 1
	bool swimToMiddle = false, swimToBox = false, canRadio = false;

	//Swim2
	bool walkToMiddle = false, gettingOverFence = false, canStartGame = false;

	Sprite* sprite;

	float animationSpeed = 170.f;
	float stopDuration = 0.8f;
	float elapsedStages = 0.f;

	Text SpacebarText;

	Audio::Sound intro{ "assets/audio/intro.mp3" };
	Audio::Sound intro2{ "assets/audio/intro2.mp3" };

	//MSX
	float scaleXMT = 3, scaleYMT = 3;
	float posXMT1 = -200.f, posYMT1 = 120.f;
	float posXMT2 = 600.f, posYMT2 = 120.f;
	Sprite* msx1 = new Sprite(new Surface("assets/UI/Intro/MSX1.png"), 1);
	Sprite* msx2 = new Sprite(new Surface("assets/UI/Intro/MSX2.png"), 1);

	//KONAMI
	int scaleXK = 5, scaleYK = 5;
	float posXK = 130.f, posYK = 210.f;
	float posBarX = posXK, posBarY = posYK;
	Sprite* konami = new Sprite(new Surface("assets/UI/Intro/Konami.png"), 1);

	//Metal Gear Title
	int scaleXTS = 2, scaleYMTS = 2;
	float posXTS = 140.f, posYTS = 600.f;
	float targetPosXTS = 120.f, targetPosYTS = 150.f;
	bool init = false;
	float elapsed = 0.f;
	float increment = 1;
	Sprite* titleScreen = new Sprite(new Surface("assets/UI/Intro/TitleScreen.png"), 1);
	Text PlayStart, Copyright, Date;

	//Buas
	int scaleXBuas = 6, scaleYBuas = 6;
	float posXBuas = 270.f, posYBuas = 210.f;
	float posBarXBuas = posXBuas, posBarYBuas = posYBuas;
	Sprite* Buas = new Sprite(new Surface("assets/UI/Intro/BUas.png"), 1);

	enum class IntroStage {
		MSX,
		KONAMI,
		BUAS,
		TITLESCREEN,
		SWIM1,
		RADIO,
		SWIM2
	};

	IntroStage currentStage = IntroStage::MSX;

	void MSXAnimation(Surface* screen, float deltaTime);
	void KonamiAnimation(Surface* screen, float deltaTime);
	void TitleScreenAnimation(Surface* screen, float deltaTime);
	void BuasAnimation(Surface* screen, float deltaTime);
	void Swim1(Surface* screen, float deltaTime);
	void Swim2(Surface* screen, float deltaTime);

	void SkipText(Surface* screen, float deltaTime, uint c);
	void ChangeStage(float deltaTime, IntroStage whatStage);

private:
};

