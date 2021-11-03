#include "framework.h"

/// @brief 
FrameWork::FrameWork()
{
    m_window = new sf::RenderWindow( sf::VideoMode( m_width, m_height), m_title);

    m_player.SetPosition( sf::Vector2f({ 10.0, 10.0}));
}

/// @brief 
FrameWork::~FrameWork()
{
    delete m_window;
}

/// @brief Return true if the winfow is open.
bool FrameWork::WindowIsOpened()
{
    return m_window->isOpen();
}

/// @brief Poll all the avaiilable eventss  
void FrameWork::UpdateEvent()
{
    sf::Event events;
    while (m_window->pollEvent(events))
    {
        switch (events.type)
        {
        case sf::Event::Closed:
            m_window->close();
            break;

        default:
            break;
        }
    }

    if (m_player.WillUpdate())
    {
        sf::Vector2f player_dir = m_player.GetDirection();
        float alpha = atan2(player_dir.y, player_dir.x)*180/PI;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) alpha-=5;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) alpha+=5;
        
        sf::Vector2f vel = { 0.0, 0.0};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) vel.x+=5;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) vel.x-=5;
        m_player.SetVelocity(vel);

        player_dir.x = cos(alpha*PI/180);
        player_dir.y = sin(alpha*PI/180);
        m_player.SetDirection(player_dir);
    }


    m_player.Update();
}

/// @brief Draw all elements.
void FrameWork::UpdateRender()
{
    m_window->clear();
    m_window->draw( m_player.GetSprite());
    
    m_window->display();
}
