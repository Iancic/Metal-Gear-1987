// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#pragma once

namespace Tmpl8
{

// basic sprite class
class Sprite
{
public:

	int counter = 1;
	float elapsed = 0;
	int wave = 380;
	bool ascending = true, descending = false;

	// structors
	Sprite( Surface* surface, unsigned int frameCount );
	~Sprite();
	// methods
	unsigned int WaveLenghtToHEX( float wave );
	void Draw( Surface* target, int x, int y );
	void DrawFont(Surface* target, int x, int y, uint c);
	void DrawScaled( int x, int y, int width, int height, Surface* target );
	void DrawActor(Surface* target, int x, int y, bool& damaged );
	void SetFlags( unsigned int f ) { flags = f; }
	void SetFrame( unsigned int i ) { currentFrame = i; }
	unsigned int GetFlags() const { return flags; }
	int GetWidth() { return width; }
	int GetHeight() { return height; }
	uint* GetBuffer() { return surface->pixels; }
	unsigned int Frames() { return numFrames; }
	Surface* GetSurface() { return surface; }
	void InitializeStartData();
private:
	// attributes
	uint originalColors[16];
	uint gameboyColors[16];
	int width, height;
	unsigned int numFrames;
	unsigned int currentFrame;
	unsigned int flags;
	unsigned int** start;
	Surface* surface;
};

}