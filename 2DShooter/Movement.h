#pragma once

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Player.h"

typedef sf::Keyboard::Key Key;
typedef sf::Keyboard Keyboard;

class Movement
{
public:
	void PollKeyboard(Player &player);

private:
    bool IsKeyPressed(Key key);
};