#include "precomp.h"
#include "game.h"

void Game::Init()
{
	OuterHeaven.InitializeMaps();
	GuardsInit();
}

void Tmpl8::Game::Shutdown()
{

}

void Game::Tick( float deltaTime)
{
	srand(static_cast<unsigned>(time(0)));
	deltaTime /= 1000.f;

	switch (GameState)
	{
	case GameStates::INTRO:
		switch (Intro.currentStage)
		{
		case IntroManager::IntroStage::MSX:
			Intro.MSXAnimation(screen, deltaTime);
			break;
		case IntroManager::IntroStage::KONAMI:
			Intro.KonamiAnimation(screen, deltaTime);
			break;
		case IntroManager::IntroStage::BUAS:
			Intro.BuasAnimation(screen, deltaTime);
			break;
		case IntroManager::IntroStage::TITLESCREEN:
			Intro.TitleScreenAnimation(screen, deltaTime);
			break;
		case IntroManager::IntroStage::SWIM1:
			Audio();
			OuterHeaven.RenderSpecificMap(screen, OuterHeaven.rowStart, OuterHeaven.columnStart);
			Intro.Swim1(screen, deltaTime);
			if (Intro.canRadio)
				UI.calling = true;
			if (Intro.canRadio && UI.calling)
				UI.IntroDisplay(screen, deltaTime);
			break;
		case IntroManager::IntroStage::RADIO:
			Audio();
			UI.calling = false;
			UI.Radio(screen, deltaTime, true);
			break;
		case IntroManager::IntroStage::SWIM2:
			UI.calling = false;
			Audio();
			OuterHeaven.RenderSpecificMap(screen, OuterHeaven.rowStart, OuterHeaven.columnStart);
			Intro.Swim2(screen, deltaTime);
			if (Intro.canStartGame)
				ChangeGameState(GameStates::GAME);
			break;
		}
		break;
	case GameStates::GAME:
		Audio();
		GameLoop(deltaTime);
		UI.MainDisplay(screen, deltaTime, Snake);
		if (OuterHeaven.binoculars)
			ChangeGameState(GameStates::BINOCULARS);
		break;
	case GameStates::RADIO:
		UI.calling = false;
		UI.Radio(screen, deltaTime, false);
		UI.MainDisplay(screen, deltaTime, Snake);
		break;
	case GameStates::BINOCULARS:
		Audio();
		OuterHeaven.RenderBinoculars(screen);
		UI.BinocularsDisplay(screen);
		break;
	case GameStates::INVENTORY:
		Audio();
		UI.InventoryDisplay(screen, deltaTime);
		UI.MainDisplay(screen, deltaTime, Snake);
		break;
	case GameStates::WEAPONS:
		Audio();
		UI.WeaponDisplay(screen, deltaTime);
		UI.MainDisplay(screen, deltaTime, Snake);
		break;
	case GameStates::PLAYERDEATH:
		Audio();
		UI.DeathScreen(screen, deltaTime);
		break;
	}
}

void Tmpl8::Game::KeyDown(int key)
{
	switch (GameState)
	{
	case GameStates::GAME:
		if (key == GLFW_KEY_R)
		{
			ChangeGameState(GameStates::RADIO);
		}
		else if (key == GLFW_KEY_I)
		{
			ChangeGameState(GameStates::INVENTORY);
		}
		else if (key == GLFW_KEY_O)
		{
			ChangeGameState(GameStates::WEAPONS);
		}
		else if (key == GLFW_KEY_H)
		{
			UI.inventoryClass->UseItem();
		}
		else if (key == GLFW_KEY_G)
		{
			UI.weaponClass->UseItem();
		}
		Snake.Input(key, GLFW_PRESS);
		break;
	case GameStates::RADIO:
		if (key == GLFW_KEY_R)
		{
			ChangeGameState(GameStates::GAME);
			UI.calling = false;
			UI.ResetRadio();
		}
		if (key == GLFW_KEY_SPACE)
		{
			if (UI.receiveState)
				UI.receiveState = false;
			else
				UI.receiveState = true;
		}
		if (key == GLFW_KEY_UP)
		{
			UI.ResetRadio();

			UI.currentFrequency++;
		}
		else if (key == GLFW_KEY_DOWN)
		{
			UI.ResetRadio();

			UI.currentFrequency--;
		}
		break;
	case GameStates::INVENTORY:
		if (key == GLFW_KEY_I)
		{
			ChangeGameState(GameStates::GAME);
		}
		break;
	case GameStates::BINOCULARS:
		if (key == GLFW_KEY_H)
		{
			OuterHeaven.binoculars = false;
			ChangeGameState(GameStates::GAME);
		}
		else if (key == GLFW_KEY_UP)
		{
			OuterHeaven.NorthRoomScope();
		}
		else if (key == GLFW_KEY_DOWN)
		{
			OuterHeaven.SouthRoomScope();
		}
		else if (key == GLFW_KEY_LEFT)
		{
			OuterHeaven.WestRoomScope();
		}
		else if (key == GLFW_KEY_RIGHT)
		{
			OuterHeaven.EastRoomScope();
		}
		break;
	case GameStates::WEAPONS:
		if (key == GLFW_KEY_O)
		{
			ChangeGameState(GameStates::GAME);
		}
		break;
	case GameStates::PLAYERDEATH:
		if (key == GLFW_KEY_SPACE)
		{
			//Map Reset
			OuterHeaven.rowIndex = 4;
			OuterHeaven.columnIndex = 0;
			OuterHeaven.insideElevator = false;

			//Player Reset
			Snake.hasAccesCard = false;
			Snake.hitPoints = Snake.maxHitPoints;
			Snake.exitedElevator = false;
			Snake.alive = true;
			mine->minesCounter = -1;
			Snake.bbX = 500;
			Snake.bbY = 300;
			Snake.keyStates[GLFW_KEY_D] = false;
			Snake.stopAnimation = 0;

			//Inventory Reset
			UI.inventoryClass->currentCapacity = 0;
			UI.inventoryClass->stackCounter = 0;
			UI.inventoryClass->selectedIndex = 0;
			//UI.inventoryClass->inventoryItems[9] = { nullptr };

			UI.weaponClass->currentCapacity = 0;
			UI.weaponClass->stackCounter = 0;
			UI.weaponClass->selectedIndex = 0;
			//UI.weaponClass->inventoryItems[9] = { nullptr };

			//Music Reset
			loseSound.pause();
			isAlerted = false;

			Snake.canPlay = false;

			ChangeGameState(GameStates::GAME);
		}
		break;
	}
}

void Tmpl8::Game::KeyUp(int key)
{
	switch (GameState)
	{
	case GameStates::INTRO:
		if (key == GLFW_KEY_SPACE)
		{
			if (Intro.currentStage == IntroManager::IntroStage::TITLESCREEN)
			{
				Intro.currentStage = IntroManager::IntroStage::SWIM1;
			}
			else if (Intro.currentStage == IntroManager::IntroStage::SWIM1 && Intro.canRadio)
			{
				Intro.currentStage = IntroManager::IntroStage::RADIO;
			}
			else if (Intro.currentStage == IntroManager::IntroStage::RADIO)
			{
				if (UI.messageIndexIntro < 3 && UI.Transceiver.isTypingFinished)
				{
					UI.messageIndexIntro++;
					UI.Transceiver.isTypingFinished = false;

					//Reset Box Text
					UI.Transceiver.charCounter = 0;

					for (int i = 0; i <= 99; i++)
					{
						UI.Transceiver.typed[i] = false;
					}
				}
				else if (UI.messageIndexIntro == 3 && UI.Transceiver.isTypingFinished)
				{
					UI.calling = true;
					Intro.currentStage = IntroManager::IntroStage::SWIM2;
				}
			}
		}
		break;
	case GameStates::GAME:
		Snake.Input(key, GLFW_RELEASE);
		break;
	case GameStates::RADIO:
		Snake.Input(key, GLFW_RELEASE);
		break;
	case GameStates::INVENTORY:
		UI.InventoryInput(key, GLFW_RELEASE);
		Snake.Input(key, GLFW_RELEASE);
		break;
	case GameStates::WEAPONS:
		UI.WeaponDisplayInput(key, GLFW_RELEASE);
		Snake.Input(key, GLFW_RELEASE);
		break;
	}
}

void Tmpl8::Game::ChangeGameState(GameStates whatState)
{
	GameState = whatState;
}

void Tmpl8::Game::GameLoop(float deltaTime)
{
	//Win Condition
	if(Snake.exitedElevator)
		ChangeGameState(GameStates::PLAYERDEATH);

	Audio();

	//Tilemap
	OuterHeaven.RenderMap(screen);

	if (!Snake.alive)
		ChangeGameState(GameStates::PLAYERDEATH);

	//Room Changed 
	if (OuterHeaven.rowIndex != previousRowIndex || OuterHeaven.columnIndex != previousColumnIndex)
	{
		hasRoomChanged = true;
		previousRowIndex = OuterHeaven.rowIndex;
		previousColumnIndex = OuterHeaven.columnIndex;
	}
	else
		hasRoomChanged = false;

	if (hasRoomChanged)
		RoomReset();

	//Scenes (Enemies, Items & Doors)
	if (!OuterHeaven.insideCar && !OuterHeaven.insideRoom && !OuterHeaven.insideElevator)
	{
		//Row 3
		if (OuterHeaven.rowIndex == 3)
		{
			if (OuterHeaven.columnIndex == 1)
			{
				//Trigger Both Enemies To Follow
				if (Enemy_3_1_A->enemyState == Enemy::State::FOLLOW || Enemy_3_1_B->enemyState == Enemy::State::FOLLOW)
				{
					Enemy_3_1_A->ChangeState(Enemy::State::FOLLOW);
					Enemy_3_1_B->ChangeState(Enemy::State::FOLLOW);
					isAlerted = true;
				}

				if (Enemy_3_1_A->alive)
				{
					Enemy_3_1_A->Update(screen, deltaTime, OuterHeaven, Snake);
					Bullet_3_1_A.Update(screen, deltaTime, Snake, OuterHeaven);
				}

				if (Enemy_3_1_B->alive)
				{
					Enemy_3_1_B->Update(screen, deltaTime, OuterHeaven, Snake);
					Bullet_3_1_B.Update(screen, deltaTime, Snake, OuterHeaven);
				}
			}

			else if (OuterHeaven.columnIndex == 2)
			{
				roomDoor->Update(screen, deltaTime, Snake);
			}
		}

		//Row 2
		else if (OuterHeaven.rowIndex == 2)
		{
			if (OuterHeaven.columnIndex == 0)
			{
				//Trigger Both Enemies To Follow
				if (Enemy_2_0_A->enemyState == Enemy::State::FOLLOW || Enemy_2_0_B->enemyState == Enemy::State::FOLLOW)
				{
					Enemy_2_0_A->ChangeState(Enemy::State::FOLLOW);
					Enemy_2_0_B->ChangeState(Enemy::State::FOLLOW);
					isAlerted = true;
				}

				if (Enemy_2_0_A->alive)
				{
					Enemy_2_0_A->Update(screen, deltaTime, OuterHeaven, Snake);
					Bullet_2_0_A.Update(screen, deltaTime, Snake, OuterHeaven);
				}

				if (Enemy_2_0_B->alive)
				{
					Enemy_2_0_B->Update(screen, deltaTime, OuterHeaven, Snake);
					Bullet_2_0_B.Update(screen, deltaTime, Snake, OuterHeaven);
				}
			}
		}

		//Row 1
		else if (OuterHeaven.rowIndex == 1)
		{
			if (OuterHeaven.columnIndex == 0)
			{
				//Trigger Both Enemies To Follow
				if (Enemy_1_0_A->enemyState == Enemy::State::FOLLOW || Enemy_1_0_B->enemyState == Enemy::State::FOLLOW)
				{
					Enemy_1_0_A->ChangeState(Enemy::State::FOLLOW);
					Enemy_1_0_B->ChangeState(Enemy::State::FOLLOW);
					isAlerted = true;
				}

				if (Enemy_1_0_A->alive)
				{
					Enemy_1_0_A->Update(screen, deltaTime, OuterHeaven, Snake);
					Bullet_1_0_A.Update(screen, deltaTime, Snake, OuterHeaven);
				}

				if (Enemy_1_0_B->alive)
				{
					Enemy_1_0_B->Update(screen, deltaTime, OuterHeaven, Snake);
					Bullet_1_0_B.Update(screen, deltaTime, Snake, OuterHeaven);
				}
			}
		}

		//Row 0
		else if (OuterHeaven.rowIndex == 0)
		{
			if (OuterHeaven.columnIndex == 0)
			{
				elevatorDoor->Update(screen, deltaTime, Snake);
			}
		}
	}

	//Gas Mask Room
	if (OuterHeaven.insideRoom)
	{
		UI.GasRoom(screen, deltaTime);
		Guard_C.Update(screen, deltaTime);
		UI.inventoryClass->AddGasMask(gasmask);
		gasmask->Update(screen, deltaTime, 256, 5, Snake);
	}

	//Jeep 
	else if (OuterHeaven.insideCar)
	{
		switch (OuterHeaven.currentInside)
		{
		case MapManager::Inside::BINOCULAR:
			UI.inventoryClass->AddBinoculars(binoculars);
			binoculars->Update(screen, deltaTime, SCRWIDTH / 2, SCRHEIGHT / 2, Snake);
			break;
		case MapManager::Inside::RATION:
			UI.inventoryClass->AddRation(ration);
			ration->Update(screen, deltaTime, SCRWIDTH / 2, SCRHEIGHT / 2, Snake);
			break;
		case MapManager::Inside::CARD:
			UI.inventoryClass->AddAccesCard(card);
			card->Update(screen, deltaTime, SCRWIDTH / 2, SCRHEIGHT / 2, Snake);
			break;
		case MapManager::Inside::GUN:
			UI.weaponClass->AddGun(gun);
			gun->Update(screen, deltaTime, SCRWIDTH / 2, SCRHEIGHT / 2, Snake);
			break;
		case MapManager::Inside::MINE:
			UI.weaponClass->AddMine(mine);
			mine->Update(screen, deltaTime, SCRWIDTH / 2, SCRHEIGHT / 2, Snake);
			break;
		}
	}

	//Elevator
	if (OuterHeaven.insideElevator)
	{
		elevatorObject->Update(Snake, deltaTime);
		elevatorObject->Render(screen);
	}

	//Mines
	mine->UpdatePlaceables(screen, deltaTime, enemies);

	//Player
	//if (Snake.PixelPerfectCollision(box))
		//std::cout << "there is collision";

	if (OuterHeaven.insideElevator && Snake.playerState != Player::States::ELEVATOR && !elevatorObject->reachedTop)
	{
		Snake.bbY = 718.f;
	}

	if (OuterHeaven.insideElevator && Snake.playerState != Player::States::ELEVATOR && elevatorObject->reachedTop)
	{
		Snake.bbY = 207.f;
	}

	Snake.Update(deltaTime, OuterHeaven);
	Snake.Render(screen, Snake.gettingDamage);
}

void Tmpl8::Game::RoomReset()
{
	if (OuterHeaven.rowIndex == 3 && OuterHeaven.columnIndex == 0)
	{
		UI.calling = true;
	}
	else
	{
		//Reset Call UI
		UI.calling = false;
	}

	isAlerted = false;

	EnemyInit();
}

void Tmpl8::Game::EnemyInit()
{
	Enemy_2_0_A->alive = true;
	Enemy_2_0_B->alive = true;
	Enemy_2_0_A->Init(360.f, 380.f, 8, sequence_2_0_A);
	Enemy_2_0_B->Init(700.f, 120.f, 2, sequence_2_0_B);
	Bullet_2_0_A.Init(Enemy_2_0_A);
	Bullet_2_0_B.Init(Enemy_2_0_B);

	Enemy_3_1_A->alive = true;
	Enemy_3_1_B->alive = true;
	Enemy_3_1_A->Init(580.f, 510.f, 4, sequence_3_1_A);
	Enemy_3_1_B->Init(639.f, 510.f, 4, sequence_3_1_B);
	Bullet_3_1_A.Init(Enemy_3_1_A);
	Bullet_3_1_B.Init(Enemy_3_1_B);

	Enemy_1_0_A->alive = true;
	Enemy_1_0_B->alive = true;
	Enemy_1_0_A->Init(650.f, 250.f, 2, sequence_1_0_A);
	Enemy_1_0_B->Init(650.f, 475.f, 2, sequence_1_0_B);
	Bullet_1_0_A.Init(Enemy_1_0_A);
	Bullet_1_0_B.Init(Enemy_1_0_B);
}

void Tmpl8::Game::GuardsInit()
{
	Guard_C.InitGasGuard(620.f, 350.f);
}

void Tmpl8::Game::Audio()
{
#ifdef DEBUGMODE
	return;
#endif

	if (GameState == GameStates::GAME || GameState == GameStates::INTRO || GameState == GameStates::END)
	{
		if (!Snake.canPlay) //Player is not dead.
		{
			if (isAlerted)
			{
				if (!alertMusic.isPlaying())
				{
					alertedSound.play();
				}

				alertMusic.play();

				normalMusic.replay();
				normalMusic.pause();
			}
			else
			{
				normalMusic.play();

				alertMusic.replay();
				alertMusic.pause();
			}
		}
		else
		{
			alertMusic.pause();
			loseSound.play();
		}
	}

	if (UI.calling)
		callingSound.play();
	else
		callingSound.pause();
}
