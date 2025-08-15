#pragma once

class MovingBox
{

public:

	MovingBox();
	~MovingBox() { };

	float pX, pY, sX, sY;
	Sprite* sprite;

	void Update();
	void Input();

private:

};

