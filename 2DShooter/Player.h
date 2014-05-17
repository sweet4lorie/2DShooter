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
	float health;
	bool active;
	Player();
    
    //handle Lifebar
    int LifebarSize = 20;
    int LifebarRatio = 2;

	// Handles Player collision
	void collision(Player & character, Enemy & foe, sf::RectangleShape &Lifebar);
	void bulletcollision(Player & character, Ebullet &bullet, sf::RectangleShape &Lifebar);

	// Handles Player death
	bool isdead(Player &character,sf::Sound &death, sf::RectangleShape &Lifebar);
    void Reset();

private:
    
};