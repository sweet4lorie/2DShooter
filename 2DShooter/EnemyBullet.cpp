// ============================================================================
// Name: EnemyBullet.cpp
// Date: 5/15/14
// Programmer: Brian C
// Description: Create and position enemy bullets. Controls bullet movement and
// collision.
// Details: includes the Ebullet data structure.
// ============================================================================

#include "EnemyBullet.h"
// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"

void Ebullet::genBullet(std::vector<Ebullet> &bulls)
{
	BulletImage.loadFromFile(resourcePath() + "enemybullet.png");
    for(int i=0;i<= 80;i++)
	{
		Ebullet shell;
		shell.bullets.setTexture(BulletImage);
		//shell.bullets.scale(0.1f,0.1f);
		shell.bullets.setPosition(-40,-40);
		bulls.push_back(shell);
	}
}

void Ebullet::setpos(std::vector<Ebullet> &bulls, int &num, float x, float y)
{
	bulls[num].bullets.setPosition(x - 30, y + 40);
	bulls[num].activeB = true;
	num++;
	if(num > 80)
	{
		num = 0;
	}
}
int Ebullet::move(std::vector<Ebullet> &bulls,int num, float speed)
{ 
	
    for(int j=0;j<=num;j++)
	{
		if(bulls[j].activeB == true)
		{
			bulls[j].bullets.move(speed,0);
		}
	}
	return num;
}

void Ebullet::draw(sf::RenderWindow& window)
{
	window.draw(bullets);
}

void Ebullet::reset(std::vector<Ebullet> &bulls, int num)
{
	for(int j=0;j<=num;j++)
	{
		if (bulls[j].bullets.getPosition().x <= 0)
		{
			bulls[j].bullets.setPosition(-40,-40);
			bulls[j].activeB = false;
		}
	}
}