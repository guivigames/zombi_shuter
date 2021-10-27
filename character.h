#pragma once
#include <vector>
#include <SFML/Graphics.hpp>


class Character
{
protected:
    sf::Vector2f    m_position = {0.0, 0.0};
    sf::Vector2f    m_direction = {0.0, 0.0};
    sf::Sprite      m_sprite;   
public:
    sf::Sprite GetSprite()
    {
        return m_sprite;
    };
};


