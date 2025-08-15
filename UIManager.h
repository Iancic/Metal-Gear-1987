#pragma once
#include "Container.h"
#include "Text.h"

#include "Player.h"

#include "Inventory.h"

class UIManager
{
public:

	UIManager();
	~UIManager() { };

	//Main Display
	bool calling = false;
	Sprite* star = new Sprite(new Surface("assets/UI/Star.png"), 1);
	Sprite* gunIconEquiped = new Sprite(new Surface("assets/Items/Gun.png"), 1);
	Sprite* callingSprite = new Sprite(new Surface("assets/UI/Call.png"), 1);

	Text Life, Class;
	Container HealthBar, ItemSlot, GunContainer;

	//Radio
	float elapsedBreathing = 0.f;
	bool breathing = true;

	int messageIndex = 80, messageIndexIntro = 0;
	float elapsedArrow = 0.f;
	bool breathingArrow = false, isIntro = true, canEnter = false;

	char* messagesIntro[4] = {
		"This is Big Boss...    Operation Intrude n202.",
		"Infiltrate the enemy   fortress+ Outer Heaven+and destroy Metal Gear+the final weapon!",
		"First+ contact Grey Foxwho's vanished and     learn about Metal Gear.",
		"Call on frequency 01/74from now on.           ...Over"
	};

    bool pressedReceive = false;

    char* messages[99] = {
        "Snake, you're on the move",
        "Otacon on codec standby  ",
        "Meryl watches the field  ",
        "Ocelot lurks in shadows  ",
        "Raiden moves with speed  ",
        "Wolf takes her position  ",
        "Liquid readies to engage ",
        "Snake blends with cover  ",
        "Otacon scans the radar   ",
        "Meryl sets up the guard  ",
        "Ocelot is tracking closely",
        "Raiden defends the path  ",
        "Wolf prowls in darkness  ",
        "Liquid clears the area   ",
        "Snake holds steady       ",
        "Otacon hacks with stealth",
        "Meryl searches weak spots",
        "Ocelot is silent and still",
        "Raiden analyzes the scene",
        "Wolf targets from afar   ",
        "Liquid leaves no trail   ",
        "Snake moves cautiously   ",
        "Otacon preps for data    ",
        "Meryl traces the signal  ",
        "Ocelot rewires systems   ",
        "Raiden on high alert     ",
        "Wolf waits in shadows    ",
        "Liquid makes the call    ",
        "Snake is ready to strike ",
        "Otacon goes undetected   ",
        "Meryl sets checkpoints   ",
        "Ocelot gathers intel     ",
        "Raiden makes his move    ",
        "Wolf fires from cover    ",
        "Liquid sees all exits    ",
        "Snake tracks the signal  ",
        "Otacon runs diagnostics  ",
        "Meryl finds safe routes  ",
        "Ocelot scans for errors  ",
        "Raiden keeps concealed   ",
        "Wolf blends with shadows ",
        "Liquid holds the line    ",
        "Snake guards his cover   ",
        "Otacon reads the logs    ",
        "Meryl tracks intruders   ",
        "Ocelot is on the prowl   ",
        "Raiden scopes the field  ",
        "Wolf takes position now  ",
        "Liquid erases all traces ",
        "Snake prepares the op    ",
        "Otacon adjusts the plan  ",
        "Meryl hides in the dark  ",
        "Ocelot moves like the wind",
        "Raiden seals all paths   ",
        "Wolf waits in silence    ",
        "Liquid clears all data   ",
        "Snake is set to deploy   ",
        "Otacon monitors systems  ",
        "Meryl locks down files   ",
        "Ocelot readies his aim   ",
        "Raiden moves with care   ",
        "Wolf lies in ambush      ",
        "Liquid checks for traces ",
        "Snake scans the horizon  ",
        "Otacon watches quietly   ",
        "Meryl analyzes output    ",
        "Ocelot patrols the area  ",
        "Raiden holds position    ",
        "Wolf guards the escape   ",
        "Liquid patches defenses  ",
        "Snake is ready to move   ",
        "Otacon spots an opening  ",
        "Meryl tightens security  ",
        "Ocelot rewires circuits  ",
        "Raiden holds the line    ",
        "Wolf watches the door    ",
        "Liquid on the final push ",
        "Snake prepares the area  ",
        "Otacon in silent mode    ",
        "Meryl runs recon on path ",
        "Ocelot checks exits      ",
        "Raiden scans perimeter   ",
        "Wolf makes her approach  ",
        "Liquid locks down systems",
        "Snake checks for bugs    ",
        "Otacon secures network   ",
        "Meryl takes high ground  ",
        "Ocelot scopes targets    ",
        "Raiden patches firewall  ",
        "Wolf blends with terrain ",
        "Liquid clears the trail  ",
        "Snake is on recon mode   ",
        "Otacon readies the signal",
        "Meryl holds her position ",
        "Ocelot inspects weapons  ",
        "Raiden updates the route ",
        "Wolf secures the target  ",
        "Liquid on final standby  ",
        "Snake initiates the op   ",
    };

	bool receiveState = true;
	int currentFrequency = 85;
	int digitsFrequency = 1;

	Sprite* transceiver = new Sprite(new Surface("assets/UI/Transceiver.png"), 1);
	Sprite* portrait = new Sprite(new Surface("assets/UI/Portrait.png"), 1);
	Sprite* arrow = new Sprite(new Surface("assets/UI/Arrow.png"), 1);

	Text Transceiver, Dialogue, Frequency, FrequencyChanging, Receive, Send;
	Container radioCharger, textBox;

	int chargerMax = 100, chargerValue = 0;
	float boxPX = SCRWIDTH / 2 - 250, boxPY = SCRHEIGHT / 2 + 50, boxSX = 150, boxSY = 110, chargerElapsed = 0.f;
	bool charged = false, radioPrepared = false;

	Audio::Sound chargingSound{ "assets/audio/radioFrequency.mp3" };

	//Inventory
	Cigar* cigar = new Cigar();

	Inventory* inventoryClass =  new Inventory();
	Inventory* weaponClass = new Inventory();

	float xOffset = 180, yOffset = 150;
	float rowSpacing = 60;
	int rows = 9;
	int maxCapacity = rows;

	Text textItem1, textItem2, textItem3, textItem4, textItem5, textItem6, textItem7, textItem8, textItem9;
	Text inventoryText[9] = { textItem1, textItem2, textItem3, textItem4, textItem5, textItem6, textItem7, textItem8, textItem9 };

	Text InventoryTitle;

	Sprite* select = new Sprite(new Surface("assets/Inventory/selectArrow.png"), 1);
	int selectpX = 0, selectpY = 0;

	//Binocular Screen
	Sprite* binocularGraphic = new Sprite(new Surface("assets/Others/ScopeGraphic.png"), 1);
	Text binocularText;

	//Death Screen
	Text gameOver, continueF5;

	//Gas Room
	float elapsedGas = 0.f;
	Text sleepyText;
	Container sleepyContainer;

	void MainDisplay(Surface* screen, float deltaTime, Player& player);

	void IntroDisplay(Surface* screen, float deltaTime);

	void BinocularsDisplay(Surface* screen);

	void Radio(Surface* screen, float deltaTime, bool isIntro);
	void ResetRadio();

	void InventoryDisplay(Surface* screen, float deltaTime);
	void InventoryInput(int key, int action);

	void WeaponDisplay(Surface* screen, float deltaTime);
	void WeaponDisplayInput(int key, int action);

	void DeathScreen(Surface* screen, float deltaTime);

	void GasRoom(Surface* screen, float deltaTime);

private:
};

