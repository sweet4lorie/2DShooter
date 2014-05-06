// ============================================================================
// Name: Main.cpp
// Date: 4/18/14
// Programmer: Brian C
// Description: Basic movement on player controlled sprite and collision detec
// tion. WASD movement loading an image sprite.
// Details: -
// ============================================================================


#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Enemyfire.h"
#include "Movement.h"
#include "BackgroundScroll.h"
#include <time.h>
// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"

using namespace std;

int main()
{
	// Create Window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Sample Window");

	// Create background sprite
	BGscroll background;
	int num = 0;
	srand(time(NULL));
	int random;
	int frames = 400;

	// Load texture
	sf::Texture etexture;
	etexture.loadFromFile(resourcePath() + "enemy.png");
	sf::Texture deadtexture;
	deadtexture.loadFromFile(resourcePath() + "deadplayer.png");
	sf::Texture bull;
	bull.loadFromFile(resourcePath() + "bullet.png");

	// Load sounds
	
	sf::SoundBuffer sshoot;
	sf::Sound shoot;
	sf::SoundBuffer skill;
	sf::Sound kill;
	sf::SoundBuffer sdeath;
	sf::Sound death;

	sdeath.loadFromFile(resourcePath() + "death.wma");
	death.setBuffer(sdeath);
	skill.loadFromFile(resourcePath() + "dyingenemy.wma");
	kill.setBuffer(skill);
	sshoot.loadFromFile(resourcePath() + "shoot.wma");
	shoot.setBuffer(sshoot);
	

	// Create Sprite
	Player sprite;
	//Player * Ptr = &sprite;
	Movement movement;

	// Create "enemy"
	std::vector<Enemy> enemies;
	Enemy enemy;
	int numofenemies = 0;
	int enemynumber = 20;
	enemy.generate(enemies, enemynumber);

	// Generate Bullets
	std::vector<Bullet> Bullets;
	Bullet shot;
	shot.genBullet(Bullets);
	std::vector<Ebullet> enemybullets;
	Ebullet shot2;
	shot2.genBullet(enemybullets);
	int ebullets = 0;

	while (window.isOpen())
	{
		

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			// Keyboard Movement
			if (event.type == sf::Event::KeyPressed)
			{
				movement.Keyboard(event.key.code, sprite);
			}
            cout << sf::Event::KeyPressed;

			// Fire bullets
			if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Space) && (sprite.active == true))
			{
				if (frames >= 400)
				{
					shoot.play();
					Bullets[num].setpos(Bullets,num,sprite.player.getPosition().x,sprite.player.getPosition().y);
					frames = 0;
				}
			}
		}
		frames += 1;

		// Spawn enemy
		random = std::rand();
		if(1 == (random % 3000))
		{
			if(numofenemies <enemynumber)
			{
				enemies[numofenemies].spawn(enemies,numofenemies);
				numofenemies += 1;
				printf("Spawn enemy # %i\n",numofenemies);
			}
		}
		for (int i=0;i<numofenemies;i++)
		{
			if (i == random % 900)
			{
				if (enemies[i].active == true)
					enemybullets[i].setpos(enemybullets, ebullets, enemies[i].enemy.getPosition().x,enemies[i].enemy.getPosition().y);
			}
		}
		// Check for collision
		for(int t=0;t<enemynumber;t++)
		{
			sprite.collision(sprite, enemies[t]);
		}
		for(int i=0;i<ebullets;i++)
		{
			sprite.bulletcollision(sprite, enemybullets[i]);
		}
		for(int t=0;t<=num;t++)
		{
			for (int j=0;j<enemynumber;j++)
				enemies[j].collision(enemies[j],Bullets[t]);
		}

		// Check if enemies are dead
		for(int t=0;t<=enemynumber;t++)
		{
			enemies[t].isdead(enemies[t],kill);
		}

		// Check if player life is 0
		sprite.isdead(sprite,death);

		// Move bullets and reset them once offscreen
		Bullets[num].move(Bullets, num);
		Bullets[num].reset(Bullets, num);
		
		// Move enemy bullets and reset them once offscreen
		enemybullets[ebullets].move(enemybullets, ebullets);
		enemybullets[ebullets].reset(enemybullets, ebullets);

		// Background Scroll
		background.Scroll();

		// Display
		window.clear();
		window.draw(background.bgsprite);
		for (int k=0;k < ebullets; k++)
		{
			enemybullets[k].draw(window);
		}
		for (int j=0;j < num;j++)
		{
			Bullets[j].draw(window);
		}
		for (int t=0;t<enemynumber;t++)
		{
			if (enemy.active == true)
				window.draw(enemies[t].enemy);
		}
		window.draw(sprite.player);
		window.display();
	}
	return 0;

}