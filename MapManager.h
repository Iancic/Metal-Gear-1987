#pragma once
#include "Map.h"
#include "iostream"

class MapManager
{
public:

	MapManager();
	~MapManager() { };

	const int maxRows = 5;
	int mapColumns[5] = {2, 1, 2, 3, 1}; //Numbers of columns per row.

	Map maps[5][3];
	Map room_4_0, room_3_0, room_3_1, room_3_2, room_2_0, room_2_1, room_1_0, room_0_0, room_0_1;
	Map car, elevator, room;

	enum class Inside {
		NORMAL,
		BINOCULAR,
		RATION,
		CARD,
		GUN,
		MINE
	};

	Inside currentInside;

	bool insideCar = false, insideElevator = false, insideRoom = false;

	bool binoculars = false;

	int rowStart = 4, columnStart = 0;  //Starting Room
	int rowIndex = rowStart, columnIndex = columnStart;
	int binocularRow = rowStart, binocularColumn = columnStart;

	void InitializeMaps();
	void RenderMap(Surface* screen);
	void RenderSpecificMap(Surface* screen, int row, int column);
	void RenderBinoculars(Surface* screen);

	void WestRoom();
	void EastRoom();
	void SouthRoom();
	void NorthRoom();

	void WestRoomScope();
	void EastRoomScope();
	void SouthRoomScope();
	void NorthRoomScope();

	void EnterInside() { insideCar = true; };
	void ExitInside() { insideCar = false; };

	void EnterElevator() { insideElevator = true; };
	void ExitElevator() { insideElevator = false; };

	void EnterRoom() { insideRoom = true; };
	void ExitRoom() { insideRoom = false; };

private:
};

