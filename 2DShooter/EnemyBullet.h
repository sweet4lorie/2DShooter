// ============================================================================
// Name: EnemyBullet.h
// Date: 5/15/14
// Programmer: Brian C
// Description: Create and position enemy bullets. Controls bullet movement and
// collision.
// Details: -
// ============================================================================

#pragma once

#include <iostream>
#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Ebullet
{
public:
		bool activeB;
		sf::Sprite bullets;
		sf::Texture BulletImage;

		// Generate enemy bullets
		void genBullet(std::vector<Ebullet> &bulls);

		// Position and move enemy bullets
		void setpos(std::vector<Ebullet> &bulls,int &num, float x, float y);
		int move(std::vector<Ebullet> &bulls, int num, float speed = -5.25f);
		
		void draw(sf::RenderWindow &window);
		void reset(std::vector<Ebullet> &bulls, int num);

private:
		
};