#include "BackgroundScroll.h"
// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"

BGscroll::BGscroll()
{
	bgX = bgsprite.getPosition().x;
	bgimg.loadFromFile(resourcePath() + "background.png");
	bgsprite.setTexture(bgimg);
	bgsprite.setScale(1.0f,1.0f);
	bgsprite.setPosition(0,0);
}

void BGscroll::Scroll()
{
	if (bgX > -800)
	{
		bgX -= 1.0f;
	}
	else
	{
		bgX = 0;
	}
	bgsprite.setPosition(bgX,0);
}