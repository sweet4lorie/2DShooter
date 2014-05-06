#include "BackgroundScroll.h"
// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"

BGscroll::BGscroll()
{
	bgX = bgsprite.getPosition().x;
	bgimg.loadFromFile(resourcePath() + "background.png");
	bgsprite.setTexture(bgimg);
	bgsprite.setScale(3.0f,3.0f);
	bgsprite.setPosition(0,0);
}

void BGscroll::Scroll()
{
	if (bgX > -400)
	{
		bgX -= 0.007f;
	}
	else
	{
		bgX = 0;
	}
	bgsprite.setPosition(bgX,0);
}