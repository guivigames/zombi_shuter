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

    m_player.Update();
}

/// @brief Draw all elements.
void FrameWork::UpdateRender()
{
    m_window->clear();

    m_window->draw( m_player.GetSprite());
    
    m_window->display();
}
