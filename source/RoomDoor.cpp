#include "precomp.h"
#include "RoomDoor.h"

RoomDoor::RoomDoor(float posX, float posY)
{
	pX = posX, pY = posY, sX = TILESIZE * 4, sY = TILESIZE * 4;
	bbPX = posX, bbPY = posY, bbSX = 0, bbSY = sY;

	sprite = new Sprite(new Surface("assets/Others/Door.png"), 1);
}