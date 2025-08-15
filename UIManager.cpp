#include "precomp.h"
#include "UIManager.h"

#include <Audio/Sound.hpp>

UIManager::UIManager()
{
	cigar->pickedUp = true;
	inventoryClass->AddCigar(cigar);
}

void UIManager::MainDisplay(Surface* screen, float deltaTime, Player& player)
{
	//Background
	screen->Bar(0, BASESCRHEIGHT, SCRWIDTH, SCRHEIGHT - 1, 0x000000);

	//Weapon Inventory:
	GunContainer.Render(screen, 640, 780, 240, 70);
	if (weaponClass->inventoryItems[weaponClass->selectedIndex] != nullptr)
	{
		weaponClass->inventoryItems[weaponClass->selectedIndex]->RenderInventory(screen, 650, 785);
	}

	//Selected Item
	ItemSlot.Render(screen, 900, 780, 100, 70);
	if (inventoryClass->inventoryItems[inventoryClass->selectedIndex] != nullptr)
	{
		inventoryClass->inventoryItems[inventoryClass->selectedIndex]->RenderInventory(screen, 915, 785);
	}

	//HP
	HealthBar.DynamicRender(screen, player.hitPoints, player.maxHitPoints, 200, 780, 200, 30);

	//Icons
	star->Draw(screen, 200, 820);

	//Life and Class Text
	Life.Render(screen, 60, 780, "Life", false, deltaTime);
	Class.Render(screen, 30, 820, "Class", false, deltaTime);

	//Call Text
	if (calling)
	{
		elapsedBreathing += deltaTime;
		if (elapsedBreathing > 0.6f)
		{
			elapsedBreathing = 0.0f;
			breathing = !breathing;
		}

		if (breathing)
		{
			callingSprite->Draw(screen, 450, 780);
		}
	}
}
void UIManager::BinocularsDisplay(Surface* screen)
{
	screen->Bar(0, BASESCRHEIGHT, SCRWIDTH, SCRHEIGHT - 1, 0x000000);

	binocularGraphic->Draw(screen, SCRWIDTH / 2 - 80, SCRHEIGHT / 2 - 80); //Offset to be centered

	binocularText.Render(screen, 30, 820, "Binocular Mode", false, 0.f);
}

void UIManager::GasRoom(Surface* screen, float deltaTime)
{
	elapsedGas += deltaTime;

	if (elapsedGas < 4.f)
	{
		sleepyContainer.Render(screen, 620, 50, 368, 50);
		sleepyText.Render(screen, 628, 60, "Very Sleepy", false, 0.f);
	}
}

void UIManager::IntroDisplay(Surface* screen, float deltaTime)
{
	//Background
	screen->Bar(0, BASESCRHEIGHT, SCRWIDTH, SCRHEIGHT - 1, 0x000000);

	if (calling)
	{
		elapsedBreathing += deltaTime;
		if (elapsedBreathing > 0.6f)
		{
			elapsedBreathing = 0.0f;
			breathing = !breathing;
		}

		if (breathing)
		{
			callingSprite->Draw(screen, 450, 780);
		}
	}
}

void UIManager::Radio(Surface* screen, float deltaTime, bool intro)
{
	if (charged)
		chargingSound.pause();

	chargerElapsed += deltaTime;

	if (chargerElapsed > 0.01f)
	{
		//Expand Red Charger
		if (!charged)
		{
			chargingSound.play();
			chargerValue += 1;
			chargerElapsed = 0.f;
		}

		//Expand Container
		if (charged && !radioPrepared)
		{
			boxPX -= 1.f * 5;
			boxPY -= 1.f;

			boxSX += 1.f * 25;
			boxSY += 1.f * 5;

			chargerElapsed = 0.f;
		}
	}

	//Charger Expanded
	if (chargerValue >= 100)
	{
		charged = true;
	}

	//Box Expanded
	if (boxSX > 750)
	{
		radioPrepared = true;
	}

	screen->Clear(0x000000);

	radioCharger.DynamicRender(screen, chargerValue, chargerMax, 250, 110, 200, 100);
	transceiver->DrawScaled(190, 100, 576, 288, screen);

	if (charged)
	{
		textBox.Render(screen, boxPX, boxPY, boxSX, boxSY);
	}

	portrait->DrawScaled(780, 160, 140, 140, screen);

	Transceiver.Render(screen, 330, 35, "Transceiver", false, deltaTime);
	if (radioPrepared)
	{
		//Messages
		//Normal Frequency Messages:
		if (!intro)
		{
			Transceiver.Render(screen, 150, 470, messages[currentFrequency], true, deltaTime);

			//Arrow
			elapsedArrow += deltaTime;
			if (elapsedArrow > 0.4f)
			{
				elapsedArrow = 0.0f;
				breathingArrow = !breathingArrow;
			}

			if (breathingArrow)
			{
				arrow->Draw(screen, 850, 638);
			}
		}
		//Intro Messages
		else
		{
			Transceiver.Render(screen, 150, 470, messagesIntro[messageIndexIntro], true, deltaTime);

			//Arrow
			elapsedArrow += deltaTime;
			if (elapsedArrow > 0.4f)
			{
				elapsedArrow = 0.0f;
				breathingArrow = !breathingArrow;
			}

			if (breathingArrow)
			{
				arrow->Draw(screen, 850, 638);
			}
		}
	}

	if (receiveState)
	{
		Receive.Render(screen, 222, 260, "Recv", false, deltaTime);
	}
	else
	{
		Send.Render(screen, 222, 225, "Send", false, deltaTime);
	}

	//Cap The Frequency values
	if (currentFrequency > 99)
	{
		currentFrequency = 99;
	}
	else if (currentFrequency < 0)
	{
		currentFrequency = 0;
	}

	if (currentFrequency >= 10 && digitsFrequency == 1)
	{
		digitsFrequency++;
	}
	else if (currentFrequency < 10 && digitsFrequency == 2)
	{
		digitsFrequency--;
	}

	//Frequency Text
	Frequency.RenderNumbers(screen, 420, 130, 120, 3, 0xff0000);
	screen->Bar(576, 192, 584, 200, 0xff0000);
	FrequencyChanging.RenderNumbers(screen, 560, 130, currentFrequency, digitsFrequency, 0xff0000);
}

void UIManager::InventoryDisplay(Surface* screen, float deltaTime)
{
	//Arrow Position
	selectpY = inventoryClass->selectedIndex % rows;

	//Background 
	screen->Clear(0x000000);

	//Display Owned Items in Inventory
	for (int j = 0; j < inventoryClass->currentCapacity; j++)
	{
		if (inventoryClass->inventoryItems[inventoryClass->selectedIndex] != nullptr)
			inventoryClass->inventoryItems[j]->RenderInventory(screen, xOffset, j * rowSpacing + yOffset);

		inventoryText[j].Render(screen, xOffset + 70, j * rowSpacing + yOffset, inventoryClass->inventoryItems[j]->name, false, deltaTime);
	}

	//Display Arrow
	select->Draw(screen, int(xOffset - 70), int(selectpY * rowSpacing + yOffset));

	InventoryTitle.Render(screen, 330, 35, "Equipment Select", false, deltaTime);
}

void UIManager::InventoryInput(int key, int action)
{
	if (action == GLFW_RELEASE)
	{
		switch (key)
		{
		case GLFW_KEY_UP:
			if (inventoryClass->selectedIndex > 0)
			{
				inventoryClass->selectedIndex -= 1;
			}
			break;

		case GLFW_KEY_DOWN:
			if (inventoryClass->selectedIndex < 8 && inventoryClass->selectedIndex < inventoryClass->currentCapacity - 1)
			{
				inventoryClass->selectedIndex += 1;
			}
			break;
		}
	}
}

void UIManager::WeaponDisplay(Surface* screen, float deltaTime)
{
	//Background
	screen->Clear(0x000000);

	if (weaponClass != nullptr)
	{
		//Arrow Position
		selectpY = weaponClass->selectedIndex % rows;

		//Display Owned Items in Inventory
		for (int j = 0; j < weaponClass->currentCapacity; j++)
		{
			if (weaponClass->inventoryItems[weaponClass->selectedIndex] != nullptr)
				weaponClass->inventoryItems[j]->RenderInventory(screen, xOffset, j * rowSpacing + yOffset);

			inventoryText[j].Render(screen, xOffset + 70, j * rowSpacing + yOffset, weaponClass->inventoryItems[j]->name, false, deltaTime);
		}

		//Display Arrow
		select->Draw(screen, int(xOffset - 70), int(selectpY * rowSpacing + yOffset));
	}

	InventoryTitle.Render(screen, 330, 35, "Weapon Select", false, deltaTime);
}

void UIManager::WeaponDisplayInput(int key, int action)
{
	if (action == GLFW_RELEASE)
	{
		switch (key)
		{
		case GLFW_KEY_UP:
			if (weaponClass->selectedIndex > 0)
			{
				weaponClass->selectedIndex -= 1;
			}
			break;

		case GLFW_KEY_DOWN:
			if (weaponClass->selectedIndex < 8 && weaponClass->selectedIndex < weaponClass->currentCapacity - 1)
			{
				weaponClass->selectedIndex += 1;
			}
			break;
		}
	}
}

void UIManager::ResetRadio()
{
	//Reset States
	charged = false;
	radioPrepared = false;

	//Reset Charger
	chargerValue = 0;
	chargerElapsed = 0.f;

	//Reset Box
	boxPX = SCRWIDTH / 2 - 250;
	boxPY = SCRHEIGHT / 2 + 50;
	boxSX = 150;
	boxSY = 110;

	//Reset Box Text
	Transceiver.charCounter = 0;

	Transceiver.isTypingFinished = false;

	for (int i = 0; i <= 99; i ++)
	{
		Transceiver.typed[i] = false;
	}
}

void UIManager::DeathScreen(Surface* screen, float deltaTime)
{
	screen->Clear(0x000000);

	gameOver.Render(screen, 350, 300, "Game Over", false, deltaTime);
	continueF5.Render(screen, 260, 380, "Continue SPACEBAR", false, deltaTime);
}