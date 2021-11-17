#pragma once 
#include <SFML/Graphics.hpp>


class Zombie
{
private:
    // How fast is each zombie type
    const float BLOAT_SPEED = 40;
    const float CHASER_SPEED = 80;
    const float CRAWLER_SPEED = 20;

    // How touph is each zombie type
    const float BLOATED_HEALTH = 5;
    const float CHASER_HEALTH = 1;
    const float CRAWLER_HEALTH = 3;

    // Make each zombie vary its speed slightly 
    const int MAX_VARRIANCE = 30;
    const int OFFSET = 101 - MAX_VARRIANCE;
    // Were is this zombie
    sf::Vector2f m_Position;
    // A Sprite for the zombie
    sf::Sprite m_Sprite;
    // How fast can this one run/crawl
    float m_Speed;
    // How much health does this one has
    float m_Health;
    // is it still alive
    bool m_Alive;
public:
    // Handle when a bullet hits a zombie
    bool hit();

    // Find out if the zombie is alive
    bool isAlive();

    // Spawn a new zombie
    void spawn(float startX, float startY, int type, int seed);

    // return a rectangle that is the position in the world
    sf::FloatRect getPosition();

    // return the sprite
    sf::Sprite getSprite();

    //Update the zombie each frame
    void update(float elapsedTime, sf::Vector2f playerLocation);
};

