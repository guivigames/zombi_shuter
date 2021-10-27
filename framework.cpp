#include "framework.h"


FrameWork::FrameWork()
{
    m_window = new sf::RenderWindow( sf::VideoMode( m_width, m_height), m_title);
}

FrameWork::~FrameWork()
{
    delete m_window;
}


bool FrameWork::WindowIsOpened()
{
    return m_window->isOpen();
}


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
}


void FrameWork::UpdateRender()
{
    m_window->clear();

    m_window->display();
}
