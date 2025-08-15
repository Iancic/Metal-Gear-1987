// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#include "precomp.h"

using namespace Tmpl8;

// constructor
Sprite::Sprite( Surface* surface, unsigned int frameCount ) :
	width( surface->width / frameCount ),
	height( surface->height ),
	numFrames( frameCount ),
	currentFrame( 0 ),
	flags( 0 ),
	start( new unsigned int* [frameCount] ),
	surface( surface )
{
	InitializeStartData();
}

// destructor
Sprite::~Sprite()
{
	delete surface;
	for (unsigned int i = 0; i < numFrames; i++) delete start[i];
	delete start;
}


//Original Table: Earl F. Glynn
//Formulas: https://www.baeldung.com/cs/rgb-color-light-frequency
unsigned int Tmpl8::Sprite::WaveLenghtToHEX(float waveLenght)
{
	float R = 0, G = 0, B = 0;
	int FR = 0, FG = 0, FB = 0;
	float gamma = 0.8, factor = 1;

	//Violet
	if (waveLenght >= 380 && waveLenght < 440)
	{
		R = -(waveLenght - 440) / (440 - 380);
		G = 0;
		B = 1;
	}

	//Blue
	else if (waveLenght >= 440 && waveLenght < 490)
	{
		R = 0;
		G = -(waveLenght - 490) / (490 - 440);
		B = 1;
	}

	//Cyan
	else if (waveLenght >= 490 && waveLenght < 510)
	{
		R = 0;
		G = 1;
		B = -(waveLenght - 510) / (510 - 490);
	}

	///Green
	else if (waveLenght >= 510 && waveLenght < 580)
	{
		R = -(waveLenght - 580) / (580 - 510);
		G = 1;
		B = 0;
	}

	//Yellow
	else if (waveLenght >= 580 && waveLenght < 645)
	{
		R = 1;
		G = -(waveLenght - 645) / (645 - 580);
		B = 0;
	}

	//Orange
	if (waveLenght >= 645 && waveLenght < 780)
	{
		R = 1;
		G = 0;
		B = 0;
	}

	//Factors For End Of Spectrum
	if (waveLenght >= 380 && waveLenght < 420)
	{
		factor = 0.3f + 0.7f * (waveLenght - 380) / (420.0f - 380.0f);
	}
	else if (waveLenght >= 700 && waveLenght < 780)
	{
		factor = 0.3f + 0.7f * (780.0f - waveLenght) / (780.0f - 700.0f);
	}

	FR = int(255 * pow((R * factor), gamma));
	FG = int(255 * pow((G * factor), gamma));
	FB = int(255 * pow((B * factor), gamma));

	//Bit Operations For Hex
	unsigned int combined = (FR << 16) | (FG << 8) | FB;

	return combined;
}

// draw sprite to target surface
void Sprite::Draw( Surface* target, int x, int y)
{
	if (x < -width || x >( target->width + width )) return;
	if (y < -height || y >( target->height + height )) return;
	int x1 = x, x2 = x + width;
	int y1 = y, y2 = y + height;
	uint* src = GetBuffer() + currentFrame * width;
	if (x1 < 0) src += -x1, x1 = 0;
	if (x2 > target->width) x2 = target->width;
	if (y1 < 0) src += -y1 * width * numFrames, y1 = 0;
	if (y2 > target->height) y2 = target->height;
	uint* dest = target->pixels;
	int xs;
	if (x2 > x1 && y2 > y1)
	{
		unsigned int addr = y1 * target->width + x1;
		const int w = x2 - x1;
		const int h = y2 - y1;
		for (int j = 0; j < h; j++)
		{
			const int line = j + (y1 - y);
			const int lsx = start[currentFrame][line] + x;
			xs = (lsx > x1) ? lsx - x1 : 0;
			for (int i = xs; i < w; i++)
			{
				uint c1 = *(src + i);
				if (c1 & 0xffffff) *(dest + addr + i) = c1;

			}
			
			addr += target->width;
			src += width * numFrames;
		}
	}
}

void Tmpl8::Sprite::DrawFont(Surface* target, int x, int y, uint c)
{
	if (x < -width || x >(target->width + width)) return;
	if (y < -height || y >(target->height + height)) return;
	int x1 = x, x2 = x + width;
	int y1 = y, y2 = y + height;
	uint* src = GetBuffer() + currentFrame * width;
	if (x1 < 0) src += -x1, x1 = 0;
	if (x2 > target->width) x2 = target->width;
	if (y1 < 0) src += -y1 * width * numFrames, y1 = 0;
	if (y2 > target->height) y2 = target->height;
	uint* dest = target->pixels;
	int xs;
	if (x2 > x1 && y2 > y1)
	{
		unsigned int addr = y1 * target->width + x1;
		const int w = x2 - x1;
		const int h = y2 - y1;
		for (int j = 0; j < h; j++)
		{
			const int line = j + (y1 - y);
			const int lsx = start[currentFrame][line] + x;
			xs = (lsx > x1) ? lsx - x1 : 0;
			for (int i = xs; i < w; i++)
			{
				uint c1 = *(src + i);
				if (c1 == 0xffffff) c1 = c;
				if (c1 & 0xffffff) *(dest + addr + i) = c1;

			}

			addr += target->width;
			src += width * numFrames;
		}
	}
}

// draw scaled sprite
void Sprite::DrawScaled( int x1, int y1, int w, int h, Surface* target )
{
	if (width == 0 || height == 0) return;
	for (int x = 0; x < w; x++) for (int y = 0; y < h; y++)
	{
		int u = (int)((float)x * ((float)width / (float)w));
		int v = (int)((float)y * ((float)height / (float)h));
		uint color = GetBuffer()[u + v * width * numFrames];
		//Color Pallete Changer
		if (color == 0x214942) color = 0xFFC0CB;
		if (color & 0xffffff) target->pixels[x1 + x + ((y1 + y) * target->width)] = color;
	}
}

void Sprite::DrawActor(Surface* target, int x, int y, bool& damaged)
{
	if (x < -width || x >(target->width + width)) return;
	if (y < -height || y >(target->height + height)) return;
	int x1 = x, x2 = x + width;
	int y1 = y, y2 = y + height;
	uint* src = GetBuffer() + currentFrame * width;
	if (x1 < 0) src += -x1, x1 = 0;
	if (x2 > target->width) x2 = target->width;
	if (y1 < 0) src += -y1 * width * numFrames, y1 = 0;
	if (y2 > target->height) y2 = target->height;
	uint* dest = target->pixels;
	int xs;
	if (x2 > x1 && y2 > y1)
	{
		unsigned int addr = y1 * target->width + x1;
		const int w = x2 - x1;
		const int h = y2 - y1;
		for (int j = 0; j < h; j++)
		{
			const int line = j + (y1 - y);
			const int lsx = start[currentFrame][line] + x;
			xs = (lsx > x1) ? lsx - x1 : 0;
			for (int i = xs; i < w; i++)
			{
				uint c1 = *(src + i);

				//Change Colours When Damaged
				if (damaged)
				{ 
					if (c1 == 0x010101) c1 = 0x990000;  // Bright dark red
					if (c1 == 0x214942) c1 = 0xDD3333;  // Strong red
					if (c1 == 0x06926B) c1 = 0xDD5555;  // Redder and strong
					if (c1 == 0x6b6e6b) c1 = 0xFF4444;  // Bright vivid red
					// Adjust for skin tone (assuming skin tone like tan or peach)
					if (c1 == 0xD2B48C) c1 = 0xFF3333;  // Strong red tone
					if (c1 == 0x414841) c1 = 0xb22222;
					if (c1 == 0x8b6d41) c1 = 0xdc143c;
				}

				if (c1 & 0xffffff) *(dest + addr + i) = c1;

			}

			addr += target->width;
			src += width * numFrames;
		}
	}
}

// prepare sprite outline data for faster rendering
void Sprite::InitializeStartData()
{
	for (unsigned int f = 0; f < numFrames; ++f)
	{
		start[f] = new unsigned int[height];
		for (int y = 0; y < height; ++y)
		{
			start[f][y] = width;
			uint* addr = GetBuffer() + f * width + y * width * numFrames;
			for (int x = 0; x < width; ++x) if (addr[x])
			{
				start[f][y] = x;
				break;
			}
		}
	}
}