#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include <memory>
#include "TextureManager.h"
#include "character.h"
#include "Utils.h"

class FrameWork 
{
protected:
    protected:
    const float m_fps = 60;
    const float m_period = 1000000/m_fps;
    const int m_width = 800;
    const int m_height = 600;
    const char *m_title = "Zombi Shuter";
    
    sf::RenderWindow* m_window;

public:
    FrameWork();
    ~FrameWork();

    bool WindowIsOpened();

    void UpdateEvent();

    void UpdateRender();
};

