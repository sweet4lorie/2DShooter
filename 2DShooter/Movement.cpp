#include "Movement.h"


void Movement::PollKeyboard(Player &player)
{
    Keyboard keyboard;
    
    
	if (player.active)
	{
		if (IsKeyPressed(keyboard.A) || IsKeyPressed(keyboard.Left))
        {
            if (player.player.getPosition().x >= 0)
            {
                player.player.move(-10, 0);
            }
        }
		
        if (IsKeyPressed(keyboard.D) || IsKeyPressed(keyboard.Right))
        {
            if (player.player.getPosition().x <= 730)
            {
                player.player.move(10, 0);
            }
        }
        
		if (IsKeyPressed(keyboard.W) || IsKeyPressed(keyboard.Up))
        {
            if (player.player.getPosition().y >= 0)
            {
                player.player.move(0,-10);
            }
        }
            
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            if (player.player.getPosition().y <= 500)
            {
                player.player.move(0,10);
            }
        }
	}
}


// private helpers
bool Movement::IsKeyPressed(Key key)
{
    return Keyboard::isKeyPressed(key);
}