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

		void genBullet(std::vector<Bullet> &Bullets);
		void setpos(std::vector<Bullet> &Bullets,int &num, float x, float y);
		int move(std::vector<Bullet> &Bullets, int num);
		void draw(sf::RenderWindow &window);
		void reset(std::vector<Bullet> &Bullets, int num);

private:
		
};