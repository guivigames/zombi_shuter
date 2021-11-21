#include <SFML/Graphics.hpp>
#include "character.h"
#include "ZombiArena.h"
#include "TextureManager.h"
#include "Bullet.h"
#include "Pickup.h"
#include <iostream>


using namespace sf;

int main()
{

#pragma region Initialization
    // The game will always be in one of four states
    enum class State { PAUSED, LEVELING_UP, GAME_OVER, PLAYING };
    // Start with the GAME_OVER state;
    State state = State::GAME_OVER;

    // Get the screen resolution and
    // create an SFML window.
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    RenderWindow window( VideoMode(resolution.x, resolution.y),
                        "Zombi Arena", Style::Fullscreen);

    // Create a an SFML View for the main action
    View mainView(sf::FloatRect(0,0, resolution.x, resolution.y));

    // Here is our clock for timing everything
    Clock clock;

    // How long has the PLAYING state been active
    Time gameTimeTotal;

    // Where is the moise in
    // relation to world coordinates
    Vector2f mouseWorldPosition;

    // Where is hte mouse in 
    // relation to screen coordinates
    Vector2i mouseScreenPosition;
    
    //Create an instance of the Player class
    Character player;

    // The boundaries of the arena
    IntRect arena;

    // CreateThe background.
    VertexArray background;
    // Load the texture for our baclground vertex array.
    Texture textureBackground;
    textureBackground = TheTextureManager::Instance()->GetTexture("assets/background_sheet.png");

    // Prepare for a horde of zombies
    int numZombies;
    int numZombiesAlive;
    Zombie* zombies = nullptr;

    // Bullets
    Bullet bullets[100];
    int currentBullet = 0;
    int bulletsSpare = 24;
    int bulletsInClip = 6;
    int clipSize = 6;
    float fireRate = 1;
    Time lastPressed;

    // Replace mouse with cross
    window.setMouseCursorVisible(true);
    sf::Sprite spriteCrosshair;
    spriteCrosshair.setTexture(TextureManager::Instance()->GetTexture("assets/crosshair.png"));
    spriteCrosshair.setOrigin(25, 25);

    Pickup healthPickup(1);
    Pickup ammoPickup(2);

    // Game data
    int score = 0;
    int hiScore = 0;

#pragma endregion Initialization

    // The main game loop
    while (window.isOpen())
    {
        /*
        ************
        Handle input
        ************
        */
        // Handle events by polling
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyPressed)
            {
                // Pause a game while playing
                if (event.key.code == Keyboard::Return && state == State::PLAYING)
                {
                    state = State::PAUSED;
                } 
                // Restart while paused
                else if (event.key.code == Keyboard::Return && state == State::PAUSED)
                {
                    state = State::PLAYING;
                }

                // Start a new game while in GAME_OVER state
                else if ( event.key.code == Keyboard::Return && state == State::GAME_OVER)
                {
                    state = State::LEVELING_UP;
                }

                if (state == State::PLAYING)
                {
                    if (event.key.code == sf::Keyboard::R)
                    {
                        if (bulletsSpare >= clipSize)
                        {
                            bulletsInClip  = clipSize;
                            bulletsSpare -= clipSize;
                        }
                        else if (bulletsSpare > 0)
                        {
                            bulletsInClip = bulletsSpare;
                            bulletsSpare = 0;
                        } 
                        else {

                        }
                    }

                }
            }
        }// End event polling

        // Handle the player quiting
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        // Handle WASD while playing
        if (state == State::PLAYING)
        {
            // Handle the pressin and releasing if the WASD keys
            if (Keyboard::isKeyPressed(Keyboard::W))
            {
                player.moveUp();
            }
            else {
                player.stopUp();
            }
            if (Keyboard::isKeyPressed(Keyboard::A))
            {
                player.moveLeft();
            }
            else {
                player.stopLeft();
            }
            if (Keyboard::isKeyPressed(Keyboard::S))
            {
                player.moveDown();
            }
            else {
                player.stopDown();
            }
            if (Keyboard::isKeyPressed(Keyboard::D))
            {
                player.moveRight();
            }
            else {
                player.stopRight();
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (gameTimeTotal.asMilliseconds()
                    -lastPressed.asMilliseconds()
                    > 1000 / fireRate && bulletsInClip > 0)
                    {
                        bullets[currentBullet].shoot(
                            player.getCenter().x, player.getCenter().y,
                            mouseWorldPosition.x, mouseWorldPosition.y);
                        currentBullet++;
                        if (currentBullet > 99)
                            currentBullet = 0;
                        lastPressed = gameTimeTotal;
                        bulletsInClip--;
                    }
            }
        } // End WASD 

        // Handle leveling up
        if (state == State::LEVELING_UP)
        {
            if (event.key.code == Keyboard::Num1)
                state = State::PLAYING;
            if (event.key.code == Keyboard::Num2)
                state = State::PLAYING;
            if (event.key.code == Keyboard::Num3)
                state = State::PLAYING;
            if (event.key.code == Keyboard::Num4)
                state = State::PLAYING;
            if (event.key.code == Keyboard::Num5)
                state = State::PLAYING;
            if (event.key.code == Keyboard::Num6)
                state = State::PLAYING;
            if (state == State::PLAYING)
            {
                // prepare the level
                // we will modify the next two lines later
                arena.width = 1000;
                arena.height = 1000;
                arena.left = 0;
                arena.top  = 0;

                // pass the vertex array by reference
                // to the creator of the backround
                int tileSize = createBackground(background, arena);

                // Spawn the player.
                player.Spawn(arena, resolution, tileSize);
                
                healthPickup.setArena(arena);
                ammoPickup.setArena(arena);

                // Create a horde of zombies
                numZombies = 20;
                // Delete the previously allocated memory if it exist
                delete[] zombies;
                zombies = createHorde(numZombies, arena);
                numZombiesAlive = numZombies;

                // Reset the clock so there isn't a frame jump
                clock.restart();
            }
        } // End levelingup
        
        /*
        ****************
        Update the frame
        ****************
        */
        if (state == State::PLAYING)
       {
           // update the delta time
           Time dt = clock.restart();
           gameTimeTotal += dt;

           // Make a decimal fraction of 1 from the delta time
            float dtAsSeconds = dt.asSeconds();

            // Where is the mouse pinter
            mouseScreenPosition = Mouse::getPosition();

            // Convert mouse positionto world coordinates of mainView
            mouseWorldPosition = window.mapPixelToCoords(
                Mouse::getPosition(), mainView);
            
            spriteCrosshair.setPosition(mouseWorldPosition);

            // update the player
            player.update( dtAsSeconds, Mouse::getPosition());

            // Make a note of the playes new position
            Vector2f playerPosition(player.getCenter());

            // make the view centre around he player
            mainView.setCenter(player.getCenter());

            // update the living zombies
            for (int i = 0; i < numZombies; i++)
            {
                if (zombies[i].isAlive())
                {
                    //std::cout << "Update Zombe " << i << std::endl;
                    zombies[i].update( dt.asSeconds(), playerPosition);
                }
            }
            
            // update all bullets.
            for (int i = 0; i < 100; i++)
            {
                bullets[i].update(dtAsSeconds);
            }

            // Update the pickups
            healthPickup.update(dtAsSeconds);
            ammoPickup.update(dtAsSeconds);

            // Collition detection.
            // Check if zombie has been shot.
            for (int i = 0; i < 100; i++)
            {
                for (int j = 0; j < numZombies; j++)
                {
                    if (bullets[i].isInFlight() && zombies[j].isAlive())
                    {
                        if (bullets[i].getPosition().intersects( zombies[j].getPosition()))
                        {
                            bullets[i].stop();
                            // regster the hit and see if it was killed
                            if (zombies[j].hit())
                            {
                                score += 10;
                                if (score >= hiScore)
                                    hiScore = score;
                                numZombiesAlive--;
                                if (numZombiesAlive == 0)
                                    state = State::LEVELING_UP;
                            }
                        }
                    }
                }
            }

            // Have the zombies touch the player.
            for (int i = 0; i < numZombies; i++)
            {
                if( player.getPosition().intersects( zombies[i].getPosition()) && zombies[i].isAlive())
                {
                    if (player.hit(gameTimeTotal))
                    {

                    }

                    if (player.getHealth() <= 0)
                        state = State::GAME_OVER;
                }
            }

            // Has the player touch a puckup.
            if( player.getPosition().intersects(healthPickup.getPosition()) && healthPickup.isSpawned())
            {
                player.increaseHealthLevel(healthPickup.gotIt());
            }
            if( player.getPosition().intersects( ammoPickup.getPosition()) && ammoPickup.isSpawned())
            {
                bulletsSpare += ammoPickup.gotIt();
            }

       }// Endupdat the escene.
        
        /*
        **************
        DRAW THE SCENE
        **************
        */
       if (state == State::PLAYING)
       {
            window.clear();

            // Set the mainView to be displayed in the window
            // and draw everything related to it
            window.setView(mainView);

            // draw the background
            window.draw( background, &textureBackground);

            // Draw the zombies
            for (int i = 0; i < numZombies; i++)
            {
                window.draw(zombies[i].getSprite());
                
            }

            for (int i = 0; i < 100; i++)
            {
                if (bullets[i].isInFlight())
                    window.draw(bullets[i].getShape());
            }

            // Draw the layer
            window.draw(player.GetSprite());

            if (ammoPickup.isSpawned())
                window.draw(ammoPickup.getSprite());
            if (healthPickup.isSpawned())
                window.draw(healthPickup.getSprite());

            window.draw(spriteCrosshair);
       }

       if (state == State::LEVELING_UP)
       {

       }

       if (state == State::PAUSED)
       {

       }

       if (state == State::GAME_OVER)
       {

       }

       window.display();

    }// End game

    delete[] zombies;
    return 0;
}




