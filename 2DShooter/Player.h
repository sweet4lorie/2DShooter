#pragma once

#include <iostream>
#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Enemy.h"
#include "Enemyfire.h"

class Player
{
public:
	 sf::Sprite player;
	 sf::Texture img;
	 sf::Texture deadimg;
	int health;
	bool active;
	Player();
	void collision(Player & character, Enemy & foe);
	void bulletcollision(Player & character, Ebullet &bullet);
	bool isdead(Player &character,sf::Sound &death);

private:

};