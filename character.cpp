#include "character.h"
#include "TextureManager.h"


/// @brief
Character::Character()
{
    m_Speed     = START_SPEED;
    m_Health    = START_HEALTH;
    m_MaxHealth = START_HEALTH;

    sf::Texture texture  = TheTextureManager::Instance()->GetTexture("assets/player_walk_strip6.png");
    m_walk_frames = 6;
    m_walk_size = texture.getSize();
    m_walk_frame.left = 0;
    m_walk_frame.top = 0;
    m_walk_frame.width = m_walk_size.x / m_walk_frames;
    m_walk_frame.height = m_walk_size.y;
    m_walk_sprite.setTexture(TheTextureManager::Instance()->GetTexture("assets/player_walk_strip6.png"));
    m_walk_sprite.setTextureRect(m_walk_frame);
    m_walk_sprite.setOrigin( sf::Vector2f((m_walk_frame.width-m_walk_frame.left)/2, (m_walk_frame.height-m_walk_frame.top)/2));
}

/// @brief
Character::~Character()
{

}

void Character::Spawn(sf::IntRect arena, sf::Vector2f resolution, int tileSize)
{
    m_position.x = arena.width/2;
    m_position.y = arena.height/2;
    m_Arena = arena;

    m_TileSize = tileSize;

    m_resolution = resolution;
}

void Character::resetPlayerState()
{
    m_Speed = START_SPEED;
    m_Health = START_HEALTH;
    m_MaxHealth = START_HEALTH;
}

sf::Time Character::getLastHitTime()
{
    return m_LastHit;
}

bool Character::hit(sf::Time timeHit)
{
    if (timeHit.asMilliseconds() - m_LastHit.asMilliseconds() > 200)
    {
        m_LastHit = timeHit;
        m_Health -= 10;
        return true;
    }
    else return false;
}

sf::FloatRect Character::getPosition()
{
    return m_walk_sprite.getGlobalBounds();
}

sf::Vector2f Character::getCenter()
{
    return m_position;
}

float Character::getRotation()
{
    return m_walk_sprite.getRotation();
}

/// @brief
sf::Sprite Character::GetSprite()
{
    return m_walk_sprite;
}

int Character::getHealth()
{
    return m_Health;
}

void Character::moveLeft()
{
    m_LeftPressed = true;
}

void Character::moveRight()
{
    m_RightPressed = true;
}

void Character::moveUp()
{
    m_UpPressed = true;
}

void Character::moveDown()
{
    m_DownPressed = true;
}

void Character::stopLeft()
{
    m_LeftPressed = false;
}

void Character::stopRight()
{
    m_RightPressed = false;
}

void Character::stopUp()
{
    m_UpPressed = false;
}

void Character::stopDown()
{
    m_DownPressed = false;
}

void Character::update( float elapsedTime, sf::Vector2f mousePosition)
{
    if(m_UpPressed)
    {
        m_position.y -= m_Speed * elapsedTime;
    }

    if(m_DownPressed)
    {
        m_position.y += m_Speed * elapsedTime;
    }

    if(m_LeftPressed)
    {
        m_position.x -= m_Speed * elapsedTime;
    }

    if(m_RightPressed)
    {
        m_position.x += m_Speed * elapsedTime;
    }

    m_walk_sprite.setPosition(m_position);

    if (m_position.x > m_Arena.width - m_TileSize)
        m_position.x = m_Arena.width - m_TileSize;

    if (m_position.x < m_Arena.width + m_TileSize)
        m_position.x = m_Arena.width + m_TileSize;
    
    if (m_position.y > m_Arena.height - m_TileSize)
        m_position.y = m_Arena.height - m_TileSize;
    
    if (m_position.y < m_Arena.height + m_TileSize)
        m_position.y = m_Arena.height + m_TileSize;


    float angle = (atan2(   mousePosition.y - m_resolution.y / 2, 
                            mousePosition.x - m_resolution.x / 2) * 180) / 3.1415;
    m_walk_sprite.setRotation(angle);
}

void Character::upgradeSpeed()
{
    m_Speed += (START_SPEED * 0.2);
}

void Character::upgradeHealth()
{
    m_MaxHealth += (START_HEALTH * 0.2);
}

void Character::increaseHealthLevel(int amount)
{
    m_Health+=amount;
    if (m_Health > m_MaxHealth)
        m_Health = m_MaxHealth;
}

/// @brief
sf::Vector2f Character::GetPosition()
{
    return m_position;
}

/// @brief
void Character::SetPosition(sf::Vector2f pos)
{
    m_position = pos;
}

/// @brief
void Character::SetDirection(sf::Vector2f dir)
{
    m_direction = dir;
}

/// @brief
sf::Vector2f Character::GetDirection()
{
    return m_direction;
}

/// @brief
void Character::SetVelocity(sf::Vector2f vel)
{
    m_velocity = vel;
}

/// @brief
sf::Vector2f Character::GetVelocity()
{
    return m_velocity;
}

/// @brief
void Character::Update()
{
    if (m_will_update)
    {
        float alpha = atan2(m_direction.y, m_direction.x)*180/PI;
        if (m_velocity.x != 0){
            m_walk_frame.left += m_walk_frame.width;
            if ( static_cast<unsigned int>( m_walk_frame.left) >= m_walk_size.x)
                m_walk_frame.left = 0;
            else if (static_cast<unsigned int>( m_walk_frame.left) < 0)
                m_walk_frame.left = m_walk_size.x-m_walk_frame.width;

            m_position.x = m_position.x + (m_direction.x * m_velocity.x);
            m_position.y = m_position.y + (m_direction.y * m_velocity.x);
        }
        m_walk_sprite.setTextureRect(m_walk_frame);
        m_walk_sprite.setRotation(alpha);
        m_walk_sprite.setPosition(m_position);
        m_will_update = false;
    }
}

/// @brief Checks if the charcter should update.
bool Character::WillUpdate()
{
    if (m_walk_clock.getElapsedTime().asSeconds() > 0.1f)
    {
        m_will_update = true;
        m_walk_clock.restart();
    }
    return m_will_update;
}

