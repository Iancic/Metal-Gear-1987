#include "precomp.h"
#include "game.h"
#include "BoundingBox.h"

void::BoundingBox::Draw(Surface* screen)
{ 
	if (type == 6 || type == 7)
		screen->Bar(pX, pY, pX + sX-1, pY + sY-1, colour);
	if (type != 1)
		screen->Box(pX, pY, pX + sX, pY + sY, colour);
}

void BoundingBox::Update(int positionX, int positionY)
{
	pX = positionX;
	pY = positionY;
}

void::BoundingBox::Init(int typeFromMatrix, int positionX, int positionY, int scaleX, int scaleY)
{
	pX = positionX;
	pY = positionY;
	sX = scaleX;
	sY = scaleY;
	
	type = typeFromMatrix;

	//to do: complete with enum
	switch (type)
	{	
		case WALL:
			SetColour(0xff0000);
			break;
		case TOPDOOR:
			SetColour(0xffff00);
			break;
		case SIDEDOOR:
			SetColour(0xffff00);
			break;
		case CARDOOR:
			SetColour(0xffa500);
			break;
		case CAREXIT:
			SetColour(0xa020f0);
			break;
		case PATROL:
			SetColour(0xffffff);
			break;
		case OMNIDIRECTIONAL:
			SetColour(0xffffff);
			break;
		case ROOMDOOR:
			SetColour(0xd77bba);
			break;
		case ROOMEXIT:
			SetColour(0xff00af);
			break;
		case ELEVATORDOOR:
			SetColour(0x524b24);
			break;
		case ELEVATOREXIT:
			SetColour(0xd4db43);
			break;
		default:
			break;
	}

}

void BoundingBox::SetColour(uint c)
{
	colour = c;
}
