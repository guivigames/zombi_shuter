#include <SFML/Graphics.hpp>
#include "character.h"
#include "ZombiArena.h"
#include "TextureManager.h"
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
                arena.width = 500;
                arena.height = 500;
                arena.left = 0;
                arena.top  = 0;

                // pass the vertex array by reference
                // to the creator of the backround
                int tileSize = createBackground(background, arena);

                // Spawn the player.
                player.Spawn(arena, resolution, tileSize);
                
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

            // update the player
            player.update( dtAsSeconds, Mouse::getPosition());

            // Make a note of the playes new position
            Vector2f playerPosition(player.getCenter());

            // make the view centre around he player
            mainView.setCenter(player.getCenter());
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
            // Draw the layer
            window.draw(player.GetSprite());
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
    return 0;
}




