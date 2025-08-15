#pragma once

//Game States
//#define FULLSCREEN
//#define DEBUGMODE

//32x24 tiles: Metal Gear Resolution in Tiles
constexpr int TILESWIDTH = 32;
constexpr int TILESHEIGHT = 24;

//Considering a 32x32 tile: Resolution In Pixels -> 1024x768
constexpr int TILESIZE = 32;

constexpr int BASESCRWIDTH = TILESIZE * TILESWIDTH;
constexpr int BASESCRHEIGHT = TILESIZE * TILESHEIGHT;
constexpr int SCRWIDTH = BASESCRWIDTH;
constexpr int SCRHEIGHT = BASESCRHEIGHT + 100;

//Tilemap Lenght In Tiles
constexpr int TILEMAPLENGHT = 435;

//Character size
constexpr int CHARHEIGHT = TILESIZE * 4;
constexpr int CHARWIDTH = TILESIZE * 2;

//constants
constexpr float PI = 3.14159265358979323846264f;
constexpr float INVPI = 0.31830988618379067153777f;
constexpr float INV2PI = 0.15915494309189533576888f;
constexpr float TWOPI = 6.28318530717958647692528f;
constexpr float SQRT_PI_INV = 0.56418958355f;
constexpr float LARGE_FLOAT = 1e34f;


