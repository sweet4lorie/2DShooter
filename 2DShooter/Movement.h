#pragma once

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Player.h"

class Movement
{
public:
	void Keyboard(sf::Keyboard::Key button,Player &player);

private:
};