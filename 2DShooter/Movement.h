// ============================================================================
// Name: Movement.h
// Date: 5/15/14
// Programmer: Brian C
// Description: Control player movement.
// Details: -
// ============================================================================

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
	// Checks player movement against WASD
	void PollKeyboard(Player &player);

private:
    bool IsKeyPressed(Key key);
};