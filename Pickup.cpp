#include "Pickup.h"
#include "TextureManager.h"
#include <iostream>

Pickup::Pickup(int type)
{
    m_Type = type;
    if (m_Type == 1)
    {
        m_Sprite = sf::Sprite(TheTextureManager::Instance()->GetTexture("assets/health_pickup.png"));
        m_Value = HEALTH_START_VALUE;
    }    
    else
    {
        m_Sprite = sf::Sprite(TheTextureManager::Instance()->GetTexture("assets/ammo_pickup.png"));
        m_Value = AMMO_START_VALUE;
    }
    m_Sprite.setOrigin(25, 25);
    m_secondsToLive = START_SECONDS_TO_LIVE;
    m_secondsToWait = START_WAIT_TIME;
}

void Pickup::setArena(sf::IntRect arena)
{
    m_Arena.left = arena.left;
    m_Arena.top = arena.top;
    m_Arena.width = arena.width;
    m_Arena.height = arena.height;

    spawn();
}

void Pickup::spawn()
{
    srand((int)time(0) / m_Type);
    int x = (rand()% m_Arena.width);
    srand((int)time(0) * m_Type);
    int y = (rand()% m_Arena.height);
    m_Spawned = true;
    m_Sprite.setPosition(x, y);
    std::cout << "Spawn pickup at: X = " << x << " Y = " << y << std::endl;
}

sf::FloatRect Pickup::getPosition()
{
    return m_Sprite.getGlobalBounds();
}

sf::Sprite Pickup::getSprite()
{
    return m_Sprite;
}

bool Pickup::isSpawned()
{
    return m_Spawned;
}

int Pickup::gotIt()
{
    m_Spawned = false;
    m_secondsSinceDeSpawn = 0;
    return m_Value;
}

void Pickup::update(float elapsedTime)
{
    if (m_Spawned)
    {
        m_secondsSinceSpawn += elapsedTime;
    }
    else 
    {
        m_secondsSinceDeSpawn += elapsedTime;
    }

    if (m_secondsSinceSpawn > m_secondsToLive && m_Spawned)
    {
        m_Spawned = false;
        m_secondsSinceDeSpawn = 0;
    }

    if(m_secondsSinceDeSpawn > m_secondsToWait && !m_Spawned)
    {
        spawn();
    }
}

void Pickup::upgrade()
{
    if (m_Type == 1)
    {
        m_Value += (HEALTH_START_VALUE * 0.5);
    }
    else m_Value += (AMMO_START_VALUE * 0.5);

    m_secondsToLive += START_SECONDS_TO_LIVE / 10;
    m_secondsToWait += START_WAIT_TIME / 10;
}

