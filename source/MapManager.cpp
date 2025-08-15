#pragma once
#include "precomp.h"
#include "game.h"
#include "MapManager.h"
#include "Map.h"

MapManager::MapManager()
{

}

void MapManager::InitializeMaps()
{
	room_4_0.CreateTileSurface(
		"assets/TileMap/OuterHeaven/4_0/4_0.csv",
		"assets/TileMap/OuterHeaven/4_0/4_0_collider.csv");

	room_3_0.CreateTileSurface(
		"assets/TileMap/OuterHeaven/3_0/3_0.csv",
		"assets/TileMap/OuterHeaven/3_0/3_0_collider.csv");

	room_3_1.CreateTileSurface(
		"assets/TileMap/OuterHeaven/3_1/3_1.csv",
		"assets/TileMap/OuterHeaven/3_1/3_1_collider.csv");

	room_3_2.CreateTileSurface(
		"assets/TileMap/OuterHeaven/3_2/3_2.csv",
		"assets/TileMap/OuterHeaven/3_2/3_2_collider.csv");

	room_2_0.CreateTileSurface(
		"assets/TileMap/OuterHeaven/2_0/2_0.csv",
		"assets/TileMap/OuterHeaven/2_0/2_0_collider.csv");

	room_2_1.CreateTileSurface(
		"assets/TileMap/OuterHeaven/2_1/2_1.csv",
		"assets/TileMap/OuterHeaven/2_1/2_1_collider.csv");

	room_1_0.CreateTileSurface(
		"assets/TileMap/OuterHeaven/1_0/1_0.csv",
		"assets/TileMap/OuterHeaven/1_0/1_0_collider.csv");

	room_0_1.CreateTileSurface(
		"assets/TileMap/OuterHeaven/0_1/0_1.csv",
		"assets/TileMap/OuterHeaven/0_1/0_1_collider.csv");

	room_0_0.CreateTileSurface(
		"assets/TileMap/OuterHeaven/0_0/0_0.csv",
		"assets/TileMap/OuterHeaven/0_0/0_0_collider.csv");

	car.CreateTileSurface(
		"assets/TileMap/OuterHeaven/car/car.csv",
		"assets/TileMap/OuterHeaven/car/car_collider.csv");

	elevator.CreateTileSurface(
		"assets/TileMap/OuterHeaven/elevator/elevator.csv",
		"assets/TileMap/OuterHeaven/elevator/elevator_collider.csv");

	room.CreateTileSurface(
		"assets/TileMap/OuterHeaven/room/room.csv",
		"assets/TileMap/OuterHeaven/room/room_collider.csv");

	maps[0][0] = room_0_0;
	maps[0][1] = room_0_1;
	maps[1][0] = room_1_0;
	maps[2][0] = room_2_0;
	maps[2][1] = room_2_1;
	maps[3][0] = room_3_0;
	maps[3][1] = room_3_1;
	maps[3][2] = room_3_2;
	maps[4][0] = room_4_0;
}

void MapManager::RenderMap(Surface* screen)
{
	if (insideCar)
		car.Render(screen);
	else if (insideElevator)
		elevator.Render(screen);
	else if (insideRoom)
		room.Render(screen);
	else if (!insideCar && !insideRoom && !insideElevator)
		maps[rowIndex][columnIndex].Render(screen);
}

void MapManager::RenderSpecificMap(Surface* screen, int row, int column)
{
	maps[row][column].Render(screen);
}	

void MapManager::RenderBinoculars(Surface* screen)
{
	maps[binocularRow][binocularColumn].Render(screen);
}

void MapManager::WestRoom()
{
	columnIndex--;
}

void MapManager::EastRoom()
{
	columnIndex++;
}

void MapManager::SouthRoom()
{
	rowIndex++;
}

void MapManager::NorthRoom()
{
	rowIndex--;
}

void MapManager::WestRoomScope()
{
	if (binocularColumn > 0)
		binocularColumn--;
}

void MapManager::EastRoomScope()
{
	if (binocularColumn < mapColumns[binocularRow] - 1)
		binocularColumn++;
}

void MapManager::SouthRoomScope()
{
	if (binocularRow < maxRows - 1 && mapColumns[binocularRow + 1] > 0)
		binocularRow++;
}

void MapManager::NorthRoomScope()
{
	if (binocularRow > 0)
		binocularRow--;
}
