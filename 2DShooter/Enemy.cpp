#include "Enemy.h"
#include "ResourcePath.hpp"

Enemy::Enemy() //added argument on 5-5
{
	health = 20;
	active = true;
    //spawntime = 0; //added by niyaz on 5-5-14
    spawnpoint = 1;
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
    //spawntime = 0;                                          //added by niyaz on 5-5-14
	int random = std::rand() % 3;
	foes[number].enemy.setPosition(700, random * 200); //changed by niyaz on 5-5-14
    //foes[number].enemy.setPosition(800, (random*150)+150); //changed by niyaz on 5-5-14
                                                           //spawn enemies in the middle, middle of top half or bottom half
}

void Enemy::move(std::vector<Enemy> &Enemies, int number, int movestyle)
{
	
    for(int j=0;j<=number;j++)
	{
		if(Enemies[j].active == true)
		{
			Enemies[j].enemy.move(-.02f,0);
		}
	}
}
/*
void Enemy::move(std::vector<Enemy> &foes, int number, int movestyle)
{
    if (movestyle == 0)
    {
        const float PI = 3.14159265;
        double y = 150*sin((spawntime/1000)*PI); //1000 can be adjusted to increase or decrease vertical movement
                                                 //changing the front number will change the range of movement
        double x = 160*(spawntime/1000); //screen width is 800, enemy will traverse screen in 5 seconds
        foes[number].enemy.setPosition(x,y); //actually change the enemy position
    }
    else if (movestyle == 1)
    {
        const float PI = 3.14159265;
        double d_y = enemy.getPosition().y;
        double y = d_y*((-atan(spawntime/500))+400)*(2/PI); //400 is half the screen width. we want to off-set the movement to the right
                                                          //500 controls how quickly the enemy will move up or down. lower is faster.
        double x = 160*(spawntime/1000); //screen width is 800, enemy will traverse screen in 5 seconds
        foes[number].enemy.setPosition(x,y); //actually change the enemy position
    }
    else //this is the boss
    {
        const float PI = 3.14159265;
        double y, x;
        if (spawntime <= 4000)//if timer is less than or equal to 4000, boss moves forward onto screen.
        {
            y = 400; //boss spawns in center
            x = 35*(spawntime/1000); //very slow, lets say boss takes 4 seconds to move to right third of screen
        }
        else //if timer is greater than 4000, boss moves in an ellipse
        {
            y = 400*sin(spawntime/1000*PI);
            x = 200*cos(spawntime/1000*PI);
        }
        foes[number].enemy.setPosition(x,y); //actually change the enemy position
    }
}
*/
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