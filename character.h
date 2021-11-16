#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <math.h>

#define PI 3.14159265

class Character
{
protected:
    const float START_SPEED = 200;
    const float START_HEALTH = 100;
    float           m_Speed;
    sf::Vector2f    m_position = { 0.0, 0.0};   // Position of character.
    sf::Vector2f    m_direction = { 1.0, 0.0};  // Direction of character.
    sf::Vector2f    m_velocity = { 0.0, 0.0};   // Velocit of character.
    sf::Vector2f    m_resolution;               // Screen resolution.
    //sf::Sprite      m_walk_sprite;              // Sprites of chracter while walking. 
    //sf::Vector2u    m_walk_size;                // Size of the entire texture.
    //sf::IntRect     m_walk_frame;               // Rectangle of texture to render.
    //id_t            m_walk_frames;              // total number of sprites in texture.
    sf::Sprite      m_Sprite;              // Sprites of chracter
    sf::IntRect     m_Arena;                    // Size of the current arena.
    int             m_TileSize;                 // How big is each tile in the arena.
    int             m_Health;
    int             m_MaxHealth;
    sf::Sprite      m_run_sprite;               // Sprite for running.
    sf::Clock       m_walk_clock;               // Clock for updating the sprites.
    bool            m_will_update = false;      // Flag to indicate if the player will update.
    bool            m_UpPressed = false;        // Flag to indicate if the up button is pressed.
    bool            m_DownPressed = false;
    bool            m_LeftPressed = false;
    bool            m_RightPressed = false;
    sf::Time        m_LastHit;

public:
    Character();
    ~Character();
    void Spawn(sf::IntRect arena, sf::Vector2f resolution, int tileSize);
    void resetPlayerState();
    bool hit(sf::Time timeHit);
    sf::Time getLastHitTime();
    sf::FloatRect getPosition();
    sf::Vector2f getCenter();
    float getRotation();
    sf::Sprite getSprite();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void stopLeft();
    void stopRight();
    void stopUp();
    void stopDown();
    void update(float elapsedTime, sf::Vector2i mousePosition);
    void upgradeSpeed();
    void upgradeHealth();
    void increaseHealthLevel(int amount);
    int getHealth();
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


