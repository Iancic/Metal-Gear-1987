#pragma once
#include <Audio/Sound.hpp>

class Text
{
public:

	Text();
	~Text() { };

	//float pX, pY;
	//uint c;

	int charCounter = 0, maxChar;
	float elapsed = 0.f;
	bool typed[100] = { 0 };

	Sprite* fontLetters;
	Sprite* fontNumbers;

	int frames = 58;
	int framesNumbers = 10;

	bool breathing = false;
	bool isTypingFinished = false;

	//TO DO: Update so the Text class uses both in one file.
	int asciiStart = 32; //Characters available are those that start at SPACE (32 in ASCII) and end at Z (132)
	int asciiStartNumbers = 48; //48->58, 0->9:

	//Audio
	Audio::Sound type{ "assets/audio/radioType.mp3" };

	void Render(Surface* screen, float pX, float pY, char string[], bool animated, float deltaTime);
	void BreathingRender(Surface* screen, float pX, float pY, char string[], uint c, float deltaTime);

	void RenderNumbers(Surface* screen, float posX, float posY, int number, int digits, uint colour);

private:
};

