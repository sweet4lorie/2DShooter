#include "Movement.h"

void Movement::Keyboard(Player &player)
{
	if (player.active == true)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					if (player.player.getPosition().x >= 0)
						player.player.move(-10, 0);
				}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					if (player.player.getPosition().x <= 730)
					player.player.move(10, 0);
				}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				{
					if (player.player.getPosition().y >= 0)
					player.player.move(0,-10);
				}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					if (player.player.getPosition().y <= 500)
					player.player.move(0,10);
				}
	}
}