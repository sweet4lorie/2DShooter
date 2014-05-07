#include "Player.h"
// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"

Player::Player()
{
	Reset();
}

void Player::collision(Player & character, Enemy & foe)
{
	// Bounding box
	sf::FloatRect boundbox = character.player.getGlobalBounds();
	sf::FloatRect enemybox = foe.enemy.getGlobalBounds();

	// Check collision
	if(boundbox.intersects(enemybox))
	{
			character.health = character.health - 30;
			foe.health = foe.health - 20;
	}
}

void Player::bulletcollision(Player & character, Ebullet &bullet)
{
	// Bounding box
	sf::FloatRect boundbox = character.player.getGlobalBounds();
	sf::FloatRect bulletbox = bullet.bullets.getGlobalBounds();

	// Check collision
	if(boundbox.intersects(bulletbox))
	{
			character.health = character.health - 10;
			bullet.bullets.setPosition(-40,-40);
			bullet.activeB = false;
	}
}

bool Player::isdead(Player &character,sf::Sound &death)
{
	deadimg.loadFromFile(resourcePath() + "deadplayer.png");
	if(character.health <= 0)
	{
		if(character.active == true)
		{
			death.play();
		}
		character.player.setTexture(deadimg);
		character.active = false;
	}

	return character.active;
}

void Player::Reset()
{
	health = 100;
	active = true;
    
	img.loadFromFile(resourcePath() + "image.png");
	player.setTexture(img);
	player.setPosition(80,200);
}