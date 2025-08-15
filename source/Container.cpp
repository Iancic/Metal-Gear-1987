#include "precomp.h"
#include "Container.h"

void Container::Render(Surface* screen, float pX, float pY, float widht, float height)
{
	//White Border
	screen->Bar(int(pX), int(pY), int(pX + widht), int(pY + height), 0xffffff);

	//Black Content
	screen->Bar(int(pX + 3), int(pY + 3), int(pX + widht - 3), int(pY + height - 3), 0x000000);
}

void Container::DynamicRender(Surface* screen, int& value, int maxValue, float pX, float pY, float widht, float height)
{
	int increment = int(widht) / maxValue;

	//White Border
	screen->Bar(int(pX), int(pY), int(pX + widht), int(pY + height), 0xffffff);

	//Black Content
	screen->Bar(int(pX + 3), int(pY + 3), int(pX + widht - 3), int(pY + height - 3), 0x000000);

	//Red HealthBar (This Case Scenario)
	screen->Bar(int(pX + 3), int(pY + 3), int(pX + value * increment - 3), int(pY + height - 3), 0xff0000);
}
