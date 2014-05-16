#include "Enemy.h"
//#include "ResourcePath.hpp"

Enemy::Enemy() //added argument on 5-5
{
	Reset();
}
void Enemy::generate(std::vector<Enemy> &foes, int number)
{
	//imgenemy.loadFromFile(resourcePath() + "enemy.png");
    imgenemy.loadFromFile("enemy.png");
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
    //spawntime = 0;                                          //added by niyaz on 5-5-14
    int random = std::rand() % 3;
	//foes[number].enemy.setPosition(700, random * 200); //changed by niyaz on 5-5-14
    double sx,sy;
    sx = 700;
    sy = (random*150)+150;
    printf("%lf\n",sy);
    s_x = sx;
    s_y = sy;
    foes[number].enemy.setPosition(sx, sy); //changed by niyaz on 5-5-14
                                                           //spawn enemies in the middle, middle of top half or bottom half
}

void Enemy::move(std::vector<Enemy> &Enemies, int number, int movestyle)
{
    double x = 0.0;
    double y = 0.0;
    double pi = 3.14159;
	y = 75*sin(spawntime.getElapsedTime().asSeconds()*pi);
    x = (700-(spawntime.getElapsedTime().asSeconds()*32));
    //printf("%lf\n",s_y);
    for(int j=0;j<=number;j++)
	{
		if(Enemies[j].active == true)
		{
			//Enemies[j].enemy.move(-1.0f,0);
            Enemies[j].enemy.setPosition(x,y);
            if (j == 1)
            {
                printf("%1.5lf,%1.5lf:%1.5lf,%1.5lf\n",x,y,s_x,s_y);
            }
		}
	}
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

void Enemy::Reset()
{
    health = 20;
	active = true;
    spawnpoint = 1;
    spawntime.restart();
}