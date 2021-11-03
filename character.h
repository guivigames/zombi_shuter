#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <math.h>

#define PI 3.14159265

class Character
{
protected:
    sf::Vector2f    m_position = { 0.0, 0.0};   // Position of character.
    sf::Vector2f    m_direction = { 1.0, 0.0};  // Direction of character.
    sf::Vector2f    m_velocity = { 0.0, 0.0};   // Velocit of character.
    sf::Sprite      m_walk_sprite;              // Sprites of chracter while walking. 
    sf::Vector2u    m_walk_size;                // Size of the entire texture.
    sf::IntRect     m_walk_frame;               // Rectangle of texture to render.
    id_t            m_walk_frames;              // total number of sprites in texture.
    sf::Sprite      m_run_sprite;               // Sprite for running.
    sf::Clock       m_walk_clock;               // Clock for updating the sprites.
    bool            m_will_update = false;      // Flag to indicate if the player will update.

public:
    Character();
    ~Character();
    //void SetSprite(std::string texture);
    sf::Sprite GetSprite();
    void SetPosition(sf::Vector2f pos);
    sf::Vector2f GetPosition();
    void SetDirection(sf::Vector2f dir);
    sf::Vector2f GetDirection();
    void SetVelocity(sf::Vector2f vel);
    sf::Vector2f GetVelocity();
    void Update();
    bool WillUpdate();
};


