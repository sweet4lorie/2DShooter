// ============================================================================
// Name: Player.h
// Date: 5/15/14
// Programmer: Brian C
// Description: Control player collision and death.
// Details: -
// ============================================================================

#pragma once

#include <iostream>
#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Enemy.h"
#include "EnemyBullet.h"

class Player
{
public:
	// player image
	 sf::Sprite player;
	 sf::Texture img;
	 sf::Texture deadimg;
	 // player variables
	int health;
	bool active;
	Player();

	// Handles Player collision
	void collision(Player & character, Enemy & foe);
	void bulletcollision(Player & character, Ebullet &bullet);

	// Handles Player death
	bool isdead(Player &character,sf::Sound &death);
    void Reset();

private:
    
};