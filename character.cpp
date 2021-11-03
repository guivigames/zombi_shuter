#include "character.h"
#include "TextureManager.h"


/// @brief
Character::Character()
{
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

/// @brief
sf::Sprite Character::GetSprite()
{
    return m_walk_sprite;
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