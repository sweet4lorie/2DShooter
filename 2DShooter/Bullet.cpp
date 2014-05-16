// ============================================================================
// Name: Bullet.cpp
// Date: 5/15/14
// Programmer: Brian C
// Description: Control the player bullet movements and collisions. Generate 
// bullets.
// Details: includes the Bullet data structure.
// ============================================================================

#include "Bullet.h"
// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"

void Bullet::genBullet(std::vector<Bullet> &Bullets)
{
	BulletImage.loadFromFile(resourcePath() +  "bullet.png");
    for(int i=0;i<= 200;i++)
	{
		Bullet shell;
		shell.bullets.setTexture(BulletImage);
		//shell.bullets.scale(0.1f,0.1f);
		shell.bullets.setPosition(-40,-40);
		Bullets.push_back(shell);
	}
}

void Bullet::setpos(std::vector<Bullet> &Bullets, int &num, float x, float y)
{
	Bullets[num].bullets.setPosition(x + 70, y + 40);
	Bullets[num].activeB = true;
	num++;
	if(num > 200)
	{
		num = 0;
	}
}
int Bullet::move(std::vector<Bullet> &Bullets,int num) 
{
    //sf::Time dt = sf::Clock::restart();
    
    //Bullets[0].move(2.0 * dt.asSeconds());

	
    for(int j=0;j<=num;j++)
	{
		if(Bullets[j].activeB == true)
		{
			Bullets[j].bullets.move(10.5f,0);
		}
	}
	return num;
}

void Bullet::draw(sf::RenderWindow& window)
{
	window.draw(bullets);
}

void Bullet::reset(std::vector<Bullet> &Bullets, int num)
{
	for(int j=0;j<=num;j++)
	{
		if (Bullets[j].bullets.getPosition().x >= 800)
		{
			Bullets[j].bullets.setPosition(-40,-40);
			Bullets[j].activeB = false;
		}
	}
}
