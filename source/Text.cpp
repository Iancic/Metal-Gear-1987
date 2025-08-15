#include "precomp.h"
#include "Text.h"
#include <iostream>

Text::Text()
{
	fontLetters = new Sprite(new Surface("assets/UI/Font/Font.png"), frames);
	fontNumbers = new Sprite(new Surface("assets/UI/Font/Numbers.png"), framesNumbers);
}

//Usable Characters Start at index 32 (Space) in the ASCII table up until Z.
void Text::Render(Surface* screen, float pX, float pY, char string[], bool animated, float deltaTime)
{
	if (!animated)
	{
		for (int chr = 0; chr < strlen(string); chr++)
		{
			int charIndex = (int(string[chr]) % asciiStart) + (int(string[chr]) / asciiStart * asciiStart);
			int desiredFrame;

			if (charIndex < 64)
			{
				desiredFrame = charIndex % asciiStart;
			}
			else
			{
				desiredFrame = (charIndex % asciiStart) + asciiStart - 1;
			}

			fontLetters->SetFrame(desiredFrame);
			fontLetters->Draw(screen, int(pX + 32 * chr), int(pY));
		}
	}

	else
	{
		elapsed += deltaTime;
		
		if (!isTypingFinished)
		{
		
			if (elapsed > 0.07f && charCounter <= strlen(string))
			{
				typed[charCounter] = true;
				charCounter++;
				type.play();
				elapsed = 0.f;
			}

			if (charCounter > strlen(string))
			{
				isTypingFinished = true;
				type.pause();
			}
		}

		for (int chr = 0; chr < strlen(string); chr++)
		{
			int charIndex = (int(string[chr]) % asciiStart) + (int(string[chr]) / asciiStart * asciiStart);
			int desiredFrame;

			if (charIndex < 64)
			{
				desiredFrame = charIndex % asciiStart;
			}
			else
			{
				desiredFrame = (charIndex % asciiStart) + asciiStart - 1;
			}

			fontLetters->SetFrame(desiredFrame);

			//Text Wraping: 23 characters per line
			if (typed[chr])
			{
				if (chr >= 23)
				{
					fontLetters->Draw(screen, int(pX + 32 * (chr % 23)), int(pY + chr / 23 * 40));
				}
				else
				{
					fontLetters->Draw(screen, int(pX + 32 * chr), int(pY + chr / 23 * 40));
				}
			}
		}
	}

}

void Text::BreathingRender(Surface* screen, float pX, float pY, char string[], uint c, float deltaTime)
{
	elapsed += deltaTime;
	if (elapsed > 0.6f)
	{
		elapsed = 0.0f;
		breathing = !breathing;
	}

	if (breathing)
	{
		for (int chr = 0; chr < strlen(string); chr++)
		{
			int charIndex = (int(string[chr]) % asciiStart) + (int(string[chr]) / asciiStart * asciiStart);
			int desiredFrame;

			if (charIndex < 64)
			{
				desiredFrame = charIndex % asciiStart;
			}
			else
			{
				desiredFrame = (charIndex % asciiStart) + asciiStart - 1;
			}

			fontLetters->SetFrame(desiredFrame);
			fontLetters->DrawFont(screen, int(pX + 32 * chr), int(pY), c);
		}
	}
}

void Text::RenderNumbers(Surface* screen, float posX, float posY, int number, int digits, uint colour)
{
	int numberContainer = number;

	for (int chr = digits; chr > 0; chr--)
	{
		fontNumbers->SetFrame(numberContainer % 10);
		if (digits == 1)
			fontNumbers->DrawFont(screen, int(posX + 35 * 2), int(posY), colour);
		else 
		fontNumbers->DrawFont(screen, int(posX + 35 * chr), int(posY), colour);

		numberContainer = numberContainer / 10;
	}
	
	if (digits == 1)
	{
		fontNumbers->SetFrame(0);
		fontNumbers->DrawFont(screen, int(posX + 35), int(posY), colour);
	}
}
