#pragma once

#include <iostream>
#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>  
#include <SFML/Window.hpp>
#include <random>
#include "Bullet.h"

class Enemy
{
public:
	sf::Sprite enemy;
	sf::Texture imgenemy;
	int health;
	bool active;
	Enemy();
	void generate(std::vector<Enemy> &foes, int number);
	void spawn(std::vector<Enemy> &foes, int number);
	void collision(Enemy &foe, Bullet &shot);
	void isdead(Enemy &foe,sf::Sound &death);

private:

};