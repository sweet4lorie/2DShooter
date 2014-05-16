// ============================================================================
// Name: Bullet.h
// Date: 5/15/14
// Programmer: Brian C
// Description: Control the player bullet movements and collisions. Generate 
// and spawn bullets.
// Details: -
// ============================================================================

#pragma once

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Bullet
{
public:
		bool activeB;
		sf::Sprite bullets;
		sf::Texture BulletImage;

		// Create bullet sprites
		void genBullet(std::vector<Bullet> &Bullets);

		// Set bullet position
		void setpos(std::vector<Bullet> &Bullets,int &num, float x, float y);

		// Move bullets
		int move(std::vector<Bullet> &Bullets, int num);
		void draw(sf::RenderWindow &window);
		void reset(std::vector<Bullet> &Bullets, int num);

private:
		
};