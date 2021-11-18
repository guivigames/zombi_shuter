#include "Zombie.h"
#include "TextureManager.h"
#include <cstdlib>
#include <ctime>
#include <math.h>

using namespace std;

void Zombie::spawn(float startX, float startY, int type, int seed)
{
    switch (type)
    {
    case 0:
        m_Sprite = sf::Sprite(TextureManager::Instance()->GetTexture("assets/bloater.png"));
        m_Speed = BLOAT_SPEED;
        m_Health = BLOATED_HEALTH;
        break;
    case 1:
        m_Sprite = sf::Sprite(TextureManager::Instance()->GetTexture("assets/chaser.png"));
        m_Speed = CHASER_SPEED;
        m_Health = CHASER_HEALTH;
        break;
    case 2:
        m_Sprite = sf::Sprite(TextureManager::Instance()->GetTexture("assets/crwler.png"));
        m_Speed = CRAWLER_SPEED;
        m_Health = CRAWLER_HEALTH;
        break;
    }

    // mofity the speed to make every zombie unique
    srand((int) time(0) * seed);
    // Somewhere between 80 adn 100
    float modifier = (rand() % MAX_VARRIANCE) + OFFSET;
    // Express this as a fraction of 1
    modifier /= 100;
    m_Speed *= modifier;
    // Initialize its location
    m_Position.x = startX;
    m_Position.y = startY;
    // Set its origin to its center
    m_Sprite.setOrigin(25, 25);
    // Se its position 
    m_Sprite.setPosition( m_Position);
    m_Alive = true;
}

bool Zombie::hit()
{
    m_Health--;
    if (m_Health < 0)
    {
        // dead
        m_Alive = false;
        m_Sprite.setTexture(TextureManager::Instance()->GetTexture("assets/blood.png"));
        return true;
    }
    return false;
}

bool Zombie::isAlive()
{
    return m_Alive;
}

sf::FloatRect Zombie::getPosition()
{
    return m_Sprite.getGlobalBounds();
}

sf::Sprite Zombie::getSprite()
{
    return m_Sprite;
}

void Zombie::update(float elapsedTime, sf::Vector2f playerLocation)
{
    float playerX = playerLocation.x;
    float playerY = playerLocation.y;

    // Update the zombie position variable
    if (playerX > m_Position.x)
    {
        m_Position.x = m_Position.x + m_Speed * elapsedTime;
    }
    if (playerY > m_Position.y)
    {
        m_Position.y = m_Position.y + m_Speed * elapsedTime;
    }
    if (playerX < m_Position.x)
    {
        m_Position.x = m_Position.x - m_Speed * elapsedTime;
    }
    if (playerY < m_Position.y)
    {
        m_Position.y = m_Position.y - m_Speed * elapsedTime;
    }
    // Move the sprite
    m_Sprite.setPosition(m_Position);

    // Face the sprite in the current direction 
    float angle = (atan2(playerY - m_Position.y, playerX - m_Position.x) * 180) / 3.1415;
    m_Sprite.setRotation( angle);
}