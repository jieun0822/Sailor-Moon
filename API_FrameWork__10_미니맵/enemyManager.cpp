#include "framework.h"
#include "enemyManager.h"

enemyManager::enemyManager()
{
}

enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init()
{
    this->setMinion();


    return S_OK;
}

void enemyManager::release()
{
  
}

void enemyManager::update()
{
    _viMinion = _vMinion.begin();
    for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
    {
        (*_viMinion)->update();
    }
  
    collision();
  
}
void enemyManager::render()
{
    _viMinion = _vMinion.begin();
    for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
    {
        (*_viMinion)->render();
    }
    
}

void enemyManager::setMinion()
{
   
        
    
}


void enemyManager::removeMinion(int arrNum)
{
    _vMinion.erase(_vMinion.begin() + arrNum);
}

void enemyManager::collision()
{
    
}
