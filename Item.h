#pragma once
#include "Player.h"
#include "Text.h"
#include "Container.h"
#include <iostream>

class Item
{
public:

	Item();
	//Item(MapManager& owner) { };
	//Item(Player& owner) { };
	~Item() { };

	Sprite* sprite = nullptr;

	int quantity = 0;

	bool equiped = false;

	float pX = 500.f, pY = 500.f, sX = 60.f, sY = 60.f;

	char name[20] = "Default";

	bool pickedUp = false;
	bool addedToInventory = false;
	float elapsed = 0.f;

	Text text;
	Container textContainer;

	void Update(Surface* screen, float deltaTime, float posX, float posY, Player& player);
	void Render(Surface* screen, float deltaTime);

	void RenderInventory(Surface* screen, float pX, float pY);

	void CheckCollision(Player& player);

	virtual void ShowTextBox(Surface* screen, float deltaTime);
	virtual void ItemBehaviour();

	char* GetName();

private:
};

