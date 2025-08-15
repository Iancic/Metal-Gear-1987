#pragma once

class Map
{
public:

	Map();

	char s[20000] { };
	FILE* file { };

	Surface* tileMap;
	Surface* finalTileMapSurface;
	Surface* containerTile;

	Sprite* finalTileMap = nullptr;

	BoundingBox boxes[32][24];

	int tilex = 0;

	int tilemapMatrix[TILESHEIGHT][TILESWIDTH] { };
	int tilemapColliderMatrix[TILESHEIGHT][TILESWIDTH] { };

	void LoadCSV(const char* src, int dest[][TILESWIDTH]);
	void CreateTileSurface(const char* loadVisualCSV, const char* loadColliderCSV);
	void Render(Surface* screen);

	void ReturnCollisionInfo(int i, int j);

private:
};
