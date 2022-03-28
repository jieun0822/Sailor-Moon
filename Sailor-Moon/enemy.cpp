#include "framework.h"
#include "enemy.h"

enemy::enemy()
{
}

enemy::~enemy()
{
}

HRESULT enemy::init()
{
   

    return S_OK;
}

HRESULT enemy::init(const char* imageName, POINT position)
{
    
 


    _count = 0;
    _currentFrameX = 0;
    _currentFrameY = 0;


    _fireCount = 0;
    _rndfireCount = RND->getFromIntTo(1, 1000);

    _image = IMAGE->findImage(imageName);
    _rc = RectMakeCenter(position.x, position.y, _image->getFrameWidth(), _image->getFrameHeight());

    return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
  
    

    animation();
}

void enemy::render()
{
    draw();
}

void enemy::draw()
{
    
  

    _image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
}

void enemy::animation()
{
 
   
}

