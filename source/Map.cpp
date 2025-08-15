#include "precomp.h"
#include "game.h"
#include "Map.h"
#include "BoundingBox.h"


Map::Map() :
	containerTile(new Surface(TILESIZE, TILESIZE)),
	tileMap(new Surface("assets/Tilemap/OuterHeaven/OuterHeavenRow.png")),
	finalTileMapSurface(new Surface(SCRWIDTH, SCRHEIGHT))

{
	finalTileMap = new Sprite(finalTileMapSurface, 1);
}

//Inspired from: Geeks for Geeks: https://www.geeksforgeeks.org/c-fopen-function-with-examples/
//Function refferenced from: https://cplusplus.com/reference/cstring/strtok/
// https://cplusplus.com/reference/cstdio/fgets/
void Map::LoadCSV(const char* src, int dest[][TILESWIDTH])
{
	int row = 0, col = 0;

	file = fopen(src, "r");

	while (fgets(s, sizeof(s), file) != NULL && row < TILESHEIGHT)
	{
		col = 0;
		char* token = strtok(s, ",");

		while (token != NULL && col < TILESWIDTH)
		{
			dest[row][col] = atoi(token);
			col++;
			token = strtok(NULL, ",");
		}
		row++;
	}

	fclose(file);
}

void Map::ReturnCollisionInfo(int i, int j)
{
	std::cout << tilemapColliderMatrix[i][j];
}

void Map::CreateTileSurface(const char* loadVisualCSV, const char* loadColliderCSV)
{
	//Turn CSV file into matrix with indexes
	LoadCSV(loadColliderCSV, tilemapColliderMatrix);
	LoadCSV(loadVisualCSV, tilemapMatrix);

	for (int i = 0; i < TILESHEIGHT; i++)
	{
		for (int j = 0; j < TILESWIDTH; j++)
		{
			//Visual
			tilex = (tilemapMatrix[i][j] % TILEMAPLENGHT) * TILESIZE; //Get tile from png surface using index
			tileMap->CopyTo(containerTile, -tilex, 0); //Fill empty tile using index
			containerTile->CopyTo(finalTileMapSurface, j * TILESIZE, i * TILESIZE); //Copy tile to an empty canvas (future background) until full

			//Bounding Boxes
			boxes[j][i].Init(tilemapColliderMatrix[i][j], j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);
		}
	}
}

void Map::Render(Surface* screen)
{
	finalTileMapSurface->CopyTo(screen, 0, 0);
	//finalTileMap->Draw(screen, 0, 0);

#ifdef DEBUGMODE
	for (int i = 0; i < TILESHEIGHT; i++)
	{
		for (int j = 0; j < TILESWIDTH; j++)
		{
			boxes[j][i].Draw(screen);
		}
	}
#endif // DEBUGMODE
}