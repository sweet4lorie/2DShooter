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
#include "EnemyBullet.h"
#include "Movement.h"
#include "BackgroundScroll.h"
#include <time.h>
#include "ResourcePath.hpp"

using namespace std;

int main()
{
	// Create Window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Sample Window");
    window.setFramerateLimit(60);

	// Create background sprite and function variables
	BGscroll background;
	int num = 0;
	srand(time(NULL));
	int random;
	int frames = 60;
	bool bossbool = false;
	bool boss_set = false;
	bool bmove = true;
	bool paused = false;
	bool start = true;

	// Load text
	sf::Font fonty;
	fonty.loadFromFile(resourcePath() + "Verdana.ttf");
	
    sf::Texture stextimage;
    sf::Sprite stext;
	stextimage.loadFromFile(resourcePath() + "RBtitle.png");
    stext.setTexture(stextimage);
    stext.setPosition(70,180);

    sf::Texture mtextimage;
    sf::Sprite mtext;
	mtextimage.loadFromFile(resourcePath() + "text_entertostart.png");
    mtext.setTexture(mtextimage);
    mtext.setPosition(200,400);
    

	sf::Text wtext;
	wtext.setFont(fonty);
	wtext.setString("CONGRATULATIONS!!");
	wtext.setCharacterSize(46);
	wtext.setStyle(sf::Text::Bold);
	wtext.setColor(sf::Color::Red);
	wtext.setPosition(310,280);

	sf::Text ptext;
	ptext.setFont(fonty);
	ptext.setString("PAUSED");
	ptext.setCharacterSize(46);
	ptext.setStyle(sf::Text::Bold);
	ptext.setColor(sf::Color::Green);
	ptext.setPosition(310,280);

	// Load texture
	sf::Texture btexture;
	btexture.loadFromFile(resourcePath() + "Boss.png");
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

	sdeath.loadFromFile("death.wma");
	death.setBuffer(sdeath);
	skill.loadFromFile("dyingenemy.wma");
	kill.setBuffer(skill);
	sshoot.loadFromFile("shoot.wma");
	shoot.setBuffer(sshoot);
	

	// Create Sprite
	Player sprite;
	//Player * Ptr = &sprite;
	Movement movement;

	// Create "enemy" and boss
	std::vector<Enemy> enemies;
	Enemy enemy;
	int numofenemies = 0;
	int enemynumber = 20;
	enemy.generate(enemies, enemynumber);

	Enemy boss;
	boss.health = 400;
	boss.active = true;
	boss.enemy.setTexture(btexture);
	boss.enemy.setPosition(-800,-800);

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
		if (start)//beginning of start menu Eric 5/6
                {
                        sf::Event event;
                        while (window.pollEvent(event))
                        {
                                if (event.type == sf::Event::Closed)
                                        window.close();
 
                                // Detect enter press
                                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
                                {
                                        start = false;
                                        //place player in starting position, or move ship to the right for N frames. frames += 1; not included
                                }
                        }
						window.clear();
						window.draw(background.bgsprite);
						window.draw(stext);
						window.draw(mtext);
						window.display();
                        //afterwards, move player to the right for N frames, or place in playing field
                }//end of start menu Eric 5/6
		else
		{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			// Pause Game
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::P))
			{
				//printf("numofenemies: %i\n", numofenemies);
				//printf("active1: %d\n active2: %d\n active3: %d\n", enemies[numofenemies-3].active, enemies[numofenemies-2].active, enemies[numofenemies-1].active);
				paused = true;
				while (paused == true)
				{
					window.draw(ptext);
					window.display();
					sf::Event unpause;
					while (window.pollEvent(unpause))
					{
						if ((unpause.type == sf::Event::KeyPressed) && (unpause.key.code == sf::Keyboard::P))
						{
							paused = false;
						}
					}

				}
			}

			// Keyboard Movement
			if (event.type == sf::Event::KeyPressed)
			{
				movement.Keyboard(sprite);
			}

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
		if(1 == (random % 6000))
		{
			if(numofenemies <enemynumber)
			{
				enemies[numofenemies].spawn(enemies,numofenemies);
				numofenemies += 1;
				//printf("Spawn enemy # %i\n",numofenemies);
			}
		}

		// Fire bullets for active enemies
		for (int i=0;i<numofenemies;i++)
		{
			if (i == random % 1000)
			{
				if (enemies[i].active == true)
				{
					//printf("Enemy#%i: fire bullet!\n",i+1);
					enemybullets[i].setpos(enemybullets, ebullets, enemies[i].enemy.getPosition().x,enemies[i].enemy.getPosition().y);
				}
			}
		}

		// Spawn Boss
		if (bossbool == true)
		{
			// Set Position
			if (boss_set == false)
			{
				boss.enemy.setPosition(650,300);
				boss_set = true;
			}
			if (boss.enemy.getPosition().x >= 600)
			{
				boss.enemy.move(-1,0);
			}
			else
			{
				// Move boss
				if ((boss.enemy.getPosition().y <= 450) && (bmove == true))
				{
						//printf("Up\n");
						boss.enemy.move(0,-1);
						if (boss.enemy.getPosition().y == 50)
							bmove = false;
				}
				if ((boss.enemy.getPosition().y >= 50) && (bmove == false))
				{
					//printf("Down\n");
					boss.enemy.move(0,1);
					if (boss.enemy.getPosition().y == 450)
						bmove = true;
				}
			}
			if (5 == random % 90)
			{
				if (boss.active == true)
				{
					enemybullets[0].setpos(enemybullets, ebullets, boss.enemy.getPosition().x, boss.enemy.getPosition().y);
				}
			}
			sprite.collision(sprite,boss);
			for (int l=0; l < ebullets; l++)
			{
				sprite.bulletcollision(sprite,enemybullets[l]);
			}
			for (int t=0; t<num; t++)
			{
				boss.collision(boss,Bullets[t]);
			}
			boss.isdead(boss,kill);
			if (boss.active == false)
			{
				bool win = true;
				while (win == true)
				{
					sf::Event gamewon;
					while (window.pollEvent(gamewon))
					{
						if ((gamewon.type == sf::Event::KeyPressed) && (gamewon.key.code == sf::Keyboard::Return))
						{
							win = false;
							window.close();
						}
					}
					window.clear();
					window.draw(background.bgsprite);
					window.draw(sprite.player);
					window.draw(wtext);
					window.display();
				}
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
		if (numofenemies == enemynumber)
		{
			if ((enemies[numofenemies-3].active == false) && (enemies[numofenemies-2].active == false) && (enemies[numofenemies-1].active == false))
			{
				bossbool = true;
			}
		}

		// Check if player life is 0
		sprite.isdead(sprite,death);

		// Move bullets and reset them once offscreen
		Bullets[num].move(Bullets, num);
		Bullets[num].reset(Bullets, num);
		
		// Move enemy bullets and reset them once offscreen
		enemybullets[ebullets].move(enemybullets, ebullets);
		enemybullets[ebullets].reset(enemybullets, ebullets);
        
        // Enemy movement
        enemies[enemynumber].move(enemies, enemynumber, 0);

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
		window.draw(boss.enemy);
		window.display();
	}
	}
	return 0;

}