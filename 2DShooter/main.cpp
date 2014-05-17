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

void InitGame();
void GotoTitleScreen(sf::RenderWindow *gameWindow);

using namespace std;

int main()
{
    //================================================================
    // Load Assets
    // Description: loads all necessary assets for the start of the
    // game
    //================================================================
    
	// Create Window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Raging Bullet");
    window.setFramerateLimit(60);

	// Create background sprite and function variables
	BGscroll background;
	int num;
	int random;
	int frames;
	bool bossbool;
	bool boss_set;
	bool bmove;
	bool paused;

    // Load
    sf::Texture stextimage;
    sf::Sprite stext;
    sf::Texture mtextimage;
    sf::Sprite mtext;
    sf::Texture wtextimage;
    sf::Sprite wtext;
    sf::Texture ptextimage;
    sf::Sprite ptext;
	sf::Texture btexture;
	sf::Texture etexture;
	sf::Texture deadtexture;
	sf::Texture bull;
    sf::Sound shoot;
    sf::Sound kill;
    sf::Sound death;
	sf::SoundBuffer sshoot;
	sf::SoundBuffer skill;
	sf::SoundBuffer sdeath;
    // Lifebar
    sf::RectangleShape Lifebar;
    sf::Texture LifebarBGimage;
    sf::Sprite  LifebarBG;
    
    // Create Sprite
	Player sprite;
	//Player * Ptr = &sprite;
	Movement movement;
    
	// Create "enemy" and boss
	std::vector<Enemy> enemies;
	Enemy enemy;
	int numofenemies;
	int enemynumber;
	Enemy boss;
    std::vector<Bullet> Bullets;
	Bullet shot;
    std::vector<Ebullet> enemybullets;
	Ebullet shot2;
    int ebullets;
    bool isNewGame = true;

    srand(time(NULL));
    
    
    //================
    // GameLoop
    //================
    
	while (window.isOpen())
	{
        // resets values for new game
        if (isNewGame)
        {
            num = 0;
            frames = 60;
            bossbool = false;
            boss_set = false;
            bmove = true;
            paused = false;
            
            // Load Text
            stextimage.loadFromFile(resourcePath() + "RBtitle.png");
            stext.setTexture(stextimage);
            stext.setPosition(70,180);
            
            mtextimage.loadFromFile(resourcePath() + "text_entertostart.png");
            mtext.setTexture(mtextimage);
            mtext.setPosition(200,400);

            wtextimage.loadFromFile(resourcePath() + "text_youwon.png");
            wtext.setTexture(wtextimage);
            wtext.setPosition(105,190);
            
            ptextimage.loadFromFile(resourcePath() + "text_pause.png");
            ptext.setTexture(ptextimage);
            ptext.setPosition(225,260);
            
            // Load texture
            btexture.loadFromFile(resourcePath() + "Boss.png");
            etexture.loadFromFile(resourcePath() + "enemy.png");
            deadtexture.loadFromFile(resourcePath() + "deadplayer.png");
            bull.loadFromFile(resourcePath() + "bullet.png");

            // Load sounds
            sdeath.loadFromFile(resourcePath() + "death.wav");
            death.setBuffer(sdeath);
            skill.loadFromFile(resourcePath() + "dyingenemy.wav");
            kill.setBuffer(skill);
            sshoot.loadFromFile(resourcePath() + "shoot.wav");
            shoot.setBuffer(sshoot);
            
            //LifebarBG
            LifebarBGimage.loadFromFile(resourcePath() + "LifebarBG.png");
            LifebarBG.setTexture(LifebarBGimage);
            LifebarBG.setPosition(505,16);
            
            /*
            // FOR windows load
            // Load Text
            stextimage.loadFromFile("RBtitle.png");
            stext.setTexture(stextimage);
            stext.setPosition(70,180);
            
            mtextimage.loadFromFile("text_entertostart.png");
            mtext.setTexture(mtextimage);
            mtext.setPosition(200,400);
            
            mtextimage.loadFromFile("text_entertostart.png");
            wtext.setTexture(wtextimage);
            wtext.setPosition(105,190);
            
            mtextimage.loadFromFile("text_entertostart.png");
            ptext.setTexture(ptextimage);
            ptext.setPosition(225,260);
            
            // Load texture
            btexture.loadFromFile("Boss.png");
            etexture.loadFromFile("enemy.png");
            deadtexture.loadFromFile("deadplayer.png");
            bull.loadFromFile("bullet.png");
             
            // Load sounds
            sdeath.loadFromFile("death.wav");
            death.setBuffer(sdeath);
            skill.loadFromFile("dyingenemy.wav");
            kill.setBuffer(skill);
            sshoot.loadFromFile("shoot.wav");
            shoot.setBuffer(sshoot);
             
            //LifebarBG
            LifebarBGimage.loadFromFile("LifebarBG.png");
            LifebarBG.setTexture(LifebarBGimage);
            LifebarBG.setPosition(500,10);
            */
            
            sprite.Reset();
            enemy.Reset();
            boss.Reset();
            
            numofenemies = 0;
            enemynumber = 20;
            enemy.generate(enemies, enemynumber);
            enemies.clear();
            Bullets.clear();
            enemybullets.clear();
            
            boss.health = 400;
            boss.active = true;
            boss.enemy.setTexture(btexture);
            boss.enemy.setPosition(-800,-800);
            
            // Generate Bullets
            shot.genBullet(Bullets);
            shot2.genBullet(enemybullets);
            ebullets = 0;
            
            // Player Lifebar
            Lifebar.setFillColor(sf::Color(57, 82, 162));
            Lifebar.setPosition(565, 30);
            Lifebar.setSize(sf::Vector2f(sprite.health*sprite.LifebarRatio, sprite.LifebarSize));
            
            GotoTitleScreen(&window);

            isNewGame = false;
        }
        
        //================
        // Event loop
        //================
        sf::Event event;
		while (window.pollEvent(event))
		{
            
			if (event.type == sf::Event::Closed)
            {
				window.close();
            }
            
			if (!bossbool && (event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Num0))
            {
                bossbool = true;
            }
                
            // game genie code: press 0 to spawn boss
            

			// Pause Game
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::P))
			{
				//printf("numofenemies: %i\n", numofenemies);
				//printf("active1: %d\n active2: %d\n active3: %d\n", enemies[numofenemies-3].active, enemies[numofenemies-2].active, enemies[numofenemies-1].active);
				paused = true;
				while (paused == true && window.isOpen())
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
                        if (unpause.type == sf::Event::Closed)
                        {
                            window.close();
                        }
					}

				}
			}

			// Keyboard Movement
			if (event.type == sf::Event::KeyPressed)
			{
				movement.PollKeyboard(sprite);
			}

			// Fire bullets
			if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Space) && (sprite.active == true))
			{
				//if (frames >= 60)
				{
					shoot.play();
					Bullets[num].setpos(Bullets,num,sprite.player.getPosition().x,sprite.player.getPosition().y-12);
					frames = 0;
				}
			}
		} // end event loop
		frames += 1;
        
        //================
        // Spawn Enemies
        //================
		random = std::rand();
		if(1 == (random % 150))
		{
			if(numofenemies <enemynumber) // number of enemies
			{
				enemies[numofenemies].spawn(enemies,numofenemies);
				numofenemies += 1;
				//printf("Spawn enemy # %i\n",numofenemies);
			}
		}
        
		// Fire bullets for active enemies
		for (int i=0;i<numofenemies;i++)
		{
			if (i == random % 50) // number of bullets
			{
				if (enemies[i].active == true)
				{
					//printf("Enemy#%i: fire bullet!\n",i+1);
					enemybullets[i].setpos(enemybullets, ebullets, enemies[i].enemy.getPosition().x,enemies[i].enemy.getPosition().y-18);
				}
			}
		}
        
        //================
        // Spawn Boss
        //================
		if (bossbool == true)
		{
			// Set Position
			if (boss_set == false)
			{
                // clear the screen of all prior enemies
                numofenemies = 0;
                enemynumber = 0;
                ebullets = 0;
                enemy.generate(enemies, enemynumber);
                enemies.clear();
                Bullets.clear();
                enemybullets.clear();
                
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
			if (5 == random % 20)
			{
				if (boss.active == true)
				{
					enemybullets[0].setpos(enemybullets, ebullets, boss.enemy.getPosition().x, boss.enemy.getPosition().y);
				}
			}
			sprite.collision(sprite,boss, Lifebar);
			for (int l=0; l < ebullets; l++)
			{
				sprite.bulletcollision(sprite,enemybullets[l],Lifebar);
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

                            isNewGame = true;
                            
                            break;
						}
					}
					window.clear();
					window.draw(background.bgsprite);
                    window.draw(LifebarBG);
                    window.draw(Lifebar);
					window.draw(sprite.player);
					window.draw(wtext);
					window.display();
				}
			}
		} // end spawn boxx
        
        //================
        // collision &
        // movements
        //================
        
		// Check for collision
		for(int t=0;t<enemynumber;t++)
		{
			sprite.collision(sprite, enemies[t], Lifebar);
		}
		for(int i=0;i<ebullets;i++)
		{
			sprite.bulletcollision(sprite, enemybullets[i], Lifebar);
            
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
		if (!sprite.isdead(sprite,death, Lifebar))
        {
            isNewGame = true;
        }
        
		// Move bullets and reset them once offscreen
		Bullets[num].move(Bullets, num);
		Bullets[num].reset(Bullets, num);
		
		// Move enemy bullets and reset them once offscreen
        if (bossbool)
        {
            enemybullets[ebullets].move(enemybullets, ebullets, -10.5);
        }
        else
        {
            enemybullets[ebullets].move(enemybullets, ebullets);
        }
        
		enemybullets[ebullets].reset(enemybullets, ebullets);
        
        // Enemy movement
        enemies[enemynumber].move(enemies, enemynumber, 0);

		// Background Scroll
		background.Scroll();

        //================
        // Display/Draw
        //================
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
        
        window.draw(LifebarBG);
        window.draw(Lifebar);
		window.draw(sprite.player);
		window.draw(boss.enemy);
		window.display();
        
        if (!sprite.isdead(sprite,death,Lifebar))
        {
            sf::sleep(sf::seconds(1.5f));
        }
	} // end game loop

	return 0;

}

// ============================================================================
// Name: ReStart Game/GotoTitleScreen
// Date: 5/16/14
// Programmer: Emily Chiang
// Description: Resets and reloads assets for new game
// Details: -
// ============================================================================

void GotoTitleScreen(sf::RenderWindow *gameWindow)
{
    bool isTitleScreenFinished = false;
    BGscroll background;
    sf::Event event;
    sf::Texture stextimage;
    sf::Sprite stext;
    sf::Texture mtextimage;
    sf::Sprite mtext;
    
    
    stextimage.loadFromFile(resourcePath() + "RBtitle.png");
    //stextimage.loadFromFile("RBtitle.png");

    stext.setTexture(stextimage);
    stext.setPosition(70,180);
    
	mtextimage.loadFromFile(resourcePath() + "text_entertostart.png");
    //mtextimage.loadFromFile("text_entertostart.png");
    mtext.setTexture(mtextimage);
    mtext.setPosition(200,400);

    gameWindow->clear();
    gameWindow->draw(background.bgsprite);
    gameWindow->draw(stext);
    gameWindow->draw(mtext);
    gameWindow->display();
    
    while (!isTitleScreenFinished && gameWindow->isOpen())
	{
        while (gameWindow->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                gameWindow->close();
            }
            
            // Detect enter press
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
            {
                isTitleScreenFinished = !isTitleScreenFinished;
                
                break;
            }
        }

    } 
}