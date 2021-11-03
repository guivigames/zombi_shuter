#include "Utils.h"
#include "TextureManager.h"
#include "framework.h"
#include "character.h"

int main()
{
    srand(time(NULL));

    FrameWork zombi;
    
    while (zombi.WindowIsOpened())
    {
        zombi.UpdateEvent();
        
        zombi.UpdateRender();
    }

    return 1;
}

