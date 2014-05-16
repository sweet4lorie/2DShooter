#pragma once

#include <iostream>
#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>  
#include <SFML/Window.hpp>
#include <SFML\System\Clock.hpp>//added by niyaz on 5-16-14
#include <math.h>//added by niyaz on 5-16-14
#include <random>
#include <time.h>
#include <math.h> //added by niyaz on 5-5-14
#include "Bullet.h"


//#include "Player.h"

class Enemy
{
public:
	sf::Sprite enemy;
	sf::Texture imgenemy;
	int health;
	bool active;
    int spawnpoint;
    sf::Clock spawntime; //added by niyaz on 5-5-14
    double s_x,s_y; //added by niyaz
    double p_x,p_y; //player location at spawn
    
	Enemy();
	void generate(std::vector<Enemy> &foes, int number);
	void spawn(std::vector<Enemy> &foes, int number);
	void collision(Enemy &foe, Bullet &shot);
	void isdead(Enemy &foe,sf::Sound &death);
    void move(std::vector<Enemy> &foes, int number, int movestyle);
    void Reset();
    
private:

};