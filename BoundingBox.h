#pragma once
#include "common.h"


class BoundingBox
{
public:

	uint colour = 0xffffff;

	int type;
	int pX, pY, sX, sY;

	void Draw(Surface* screen);
	void Update(int positionX, int positionY);
	void Init(int typeFromMatrix, int positionX, int positionY, int scaleX, int scaleY);
	void SetColour(uint c);

	enum BoxTypes
	{
		WALL, //RED
		WALKABLE, //GREEN
		TOPDOOR, //YELLOW
		SIDEDOOR, //BLUE
		CARDOOR, //ORANGE 
		CAREXIT, //PURPLE
		PATROL, //WHITE
		OMNIDIRECTIONAL, //WHITE
		ROOMDOOR, //LIGHT PINK
		ROOMEXIT, //NEON PINK
		ELEVATORDOOR, //DARK GREEN
		ELEVATOREXIT, //DARK YELLOW
		RATIONDOOR,
		BINOCULARDOOR,
		CARDDOOR,
		GUNDOOR,
		MINEDOOR
	};

private:
};
