#pragma once
class Container
{
public:
	Container() { };
	~Container() { };

	//float pX, pY;
	//float widht, height;

	float borderOffset = 3.f;

	void Render(Surface* screen, float pX, float pY, float widht, float height);
	void DynamicRender(Surface* screen, int& value, int maxValue, float pX, float pY, float widht, float height);

private:
};

