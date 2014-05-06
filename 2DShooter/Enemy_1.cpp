#include "Enemy.h"
// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"

Enemy::Enemy()
{
	health = 20;
	active = true;

}
void Enemy::generate(std::vector<Enemy> &foes, int number)
{
	imgenemy.loadFromFile(resourcePath() + "enemy.png");
	for(int i=0;i<= number;i++)
	{
		Enemy create;
		create.enemy.setTexture(imgenemy);
		//create.enemy.scale(.3f,.3f);
		create.enemy.setPosition(-500,300);
		foes.push_back(create);
	}
}

void Enemy::spawn(std::vector<Enemy> &foes, int number)
{
	active = true;
	int random = std::rand() % 3;
	foes[number].enemy.setPosition(700, random * 200);
}

void Enemy::collision(Enemy &foe, Bullet &shot)
{
	// Bounding box
	sf::FloatRect bulletbox = shot.bullets.getGlobalBounds();
	sf::FloatRect enemybox = foe.enemy.getGlobalBounds();

	// Check collision                 
	if(bulletbox.intersects(enemybox))
	{
		foe.health -= 10;
		shot.bullets.setPosition(-40,-40);
		shot.activeB = false;
	}
}

void Enemy::isdead(Enemy &foe,sf::Sound &death)
{
	if (foe.health <= 0)
	{
		if (active == true)
		{
			death.play();
		}
		active = false;
		foe.enemy.setPosition(-900, -100);
	}
}