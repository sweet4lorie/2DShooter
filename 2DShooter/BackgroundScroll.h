// ============================================================================
// Name: BackgroundScroll.h
// Date: 5/15/14
// Programmer: Brian C
// Description: Control the scroll movement of the background sprite.
// Details: -
// ============================================================================

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

	BGscroll();

	// Scroll the background sprite
	void Scroll();
	

};