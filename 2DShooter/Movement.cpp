#include "Movement.h"

void Movement::Keyboard(sf::Keyboard::Key button,Player &player)
{
	if (player.active == true)
	{
		if (button == sf::Keyboard::A)
				{
					if (player.player.getPosition().x >= 0)
						player.player.move(-10, 0);
				}
		if (button == sf::Keyboard::D)
				{
					if (player.player.getPosition().x <= 730)
					player.player.move(10, 0);
				}
		if (button == sf::Keyboard::W)
				{
					if (player.player.getPosition().y >= 0)
					player.player.move(0,-10);
				}
		if (button == sf::Keyboard::S)
				{
					if (player.player.getPosition().y <= 500)
					player.player.move(0,10);
				}
	}
}