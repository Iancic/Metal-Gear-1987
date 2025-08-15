#pragma once
#include <Audio/Sound.hpp>

#include "BoundingBox.h"
#include "MapManager.h"
#include "Map.h"

#include "IntroManager.h"
#include "UIManager.h"

#include "Actor.h"
#include "Player.h"
#include "Enemy.h"
#include "RedGuard.h"
#include "GasGuard.h"
#include "Bullet.h"

#include "Door.h"
#include "ElevatorDoor.h"
#include "RoomDoor.h"
#include "Elevator.h"

#include <iostream>
#include <windows.h>

namespace Tmpl8
{

class Game : public TheApp 
{
public:

	int2 mousePos;

	enum class GameStates {
		INTRO,
		GAME,
		RADIO,
		INVENTORY,
		BINOCULARS,
		WEAPONS,
		END,
		PLAYERDEATH
	};

	GameStates GameState = GameStates::INTRO;

	void Init();
	void Tick( float deltaTime );
	void Shutdown();
	void MouseUp( int ) {}
	void MouseDown( int ) {}
	void MouseMove( int x, int y ) { mousePos.x = x, mousePos.y = y; }
	void MouseWheel( float ) {}
	void KeyUp(int);
	void KeyDown(int);
	void ChangeGameState(GameStates whatState);
	void GameLoop(float deltaTime);
	void RoomReset();
	void EnemyInit();
	void GuardsInit();
	void Audio();

	//Managers
	MapManager OuterHeaven;
	IntroManager Intro;
	UIManager UI;

	//Room Reset
	bool hasRoomChanged = false;
	int previousRowIndex = -1, previousColumnIndex = -1;

	//Testing Moving Box
	MovingBox* box = new MovingBox();

	Player Snake;

	//Enemies
	Enemy* Enemy_3_1_A = new Enemy();
	Enemy* Enemy_3_1_B = new Enemy();
	Enemy* Enemy_2_0_A = new Enemy();
	Enemy* Enemy_2_0_B = new Enemy();
	Enemy* Enemy_1_0_A = new Enemy();
	Enemy* Enemy_1_0_B = new Enemy();
	Enemy* enemies[6] = { Enemy_3_1_A, Enemy_3_1_B, Enemy_2_0_A, Enemy_2_0_B, Enemy_1_0_A, Enemy_1_0_B };//List With All Items for checking with mines

	GasGuard Guard_C;

	//1_0 Enemies
	Enemy::Direction sequence_1_0_A[2] = { Enemy::Direction::LEFT, Enemy::Direction::RIGHT };
	Enemy::Direction sequence_1_0_B[2] = { Enemy::Direction::LEFT, Enemy::Direction::RIGHT };

	//2_0 Enemies
	Enemy::Direction sequence_2_0_A[8] = { Enemy::Direction::UP, Enemy::Direction::LEFT, Enemy::Direction::DOWN,
										Enemy::Direction::RIGHT, Enemy::Direction::UP, Enemy::Direction::LEFT,
										Enemy::Direction::DOWN, Enemy::Direction::LEFT };
	Enemy::Direction sequence_2_0_B[2] = { Enemy::Direction::LEFT, Enemy::Direction::RIGHT };

	//3_1 Enemies
	Enemy::Direction sequence_3_1_A[4] = { Enemy::Direction::UP, Enemy::Direction::LEFT, Enemy::Direction::DOWN, Enemy::Direction::RIGHT };
	Enemy::Direction sequence_3_1_B[4] = { Enemy::Direction::UP, Enemy::Direction::RIGHT, Enemy::Direction::DOWN, Enemy::Direction::LEFT };

	//Bullets
	Bullet Bullet_3_1_A, Bullet_3_1_B, Bullet_2_0_A, Bullet_2_0_B, Bullet_1_0_A, Bullet_1_0_B, Bullet_G_A, Bullet_G_B;

	//Items
	Binoculars* binoculars =  new Binoculars(OuterHeaven);
	AccesCard* card = new AccesCard(Snake);
	Ration* ration = new Ration(Snake);
	GasMask* gasmask = new GasMask();
	Gun* gun = new Gun();
	Mine* mine = new Mine(Snake, OuterHeaven);
	 
	//Doors
	ElevatorDoor* elevatorDoor = new ElevatorDoor(384, 0);
	Door* roomDoor = new RoomDoor(288, 256);

	//Elevator Door
	Elevator* elevatorObject = new Elevator();

	//Audio
	bool isAlerted = false, alertSound = false;
	Audio::Sound alertedSound{ "assets/audio/alerted.mp3" };
	Audio::Sound alertMusic{ "assets/audio/bgm_alert.mp3" };
	Audio::Sound normalMusic{ "assets/audio/bgm_normal.mp3" };
	Audio::Sound callingSound{ "assets/audio/call.mp3" };
	Audio::Sound loseSound{ "assets/audio/lose.mp3" };
};

} 