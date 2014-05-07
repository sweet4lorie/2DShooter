#pragma once

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class BGscroll
{
public:

	float bgX; 
	sf::Texture bgimg;
	sf::Sprite bgsprite;
	void Scroll();
	BGscroll();

};