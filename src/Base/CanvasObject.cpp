#include "CanvasObject.h"
#include "../Managers/GlobalManager.h"
#include "../Utilities.h"
#include <iostream>

void CanvasObject::keyboard(int key)
{
}
void CanvasObject::keyboardUp(int key)
{
}
void CanvasObject::mouse(int button, int state, int wheel, int direction, int x, int y)
{
}
void CanvasObject::render()
{
}

void CanvasObject::setActive(bool isActive)
{
    lastActiveState = this->isActive;
    this->isActive = isActive;
}
bool CanvasObject::getActive()
{
    return this->isActive;
}

bool CanvasObject::checkIfCanExecuteCallback()
{
    if (lastActiveState != isActive)
    {
        bool tmp = lastActiveState;
        lastActiveState = isActive;
        return tmp;
    }
    return this->isActive;
}

CanvasObject::CanvasObject()
{
    objectId = GlobalManager::getInstance()->registerObject(this);
    isActive = true;
    lastActiveState = true;
    position = {0, 0};
    scale = {1, 1};
}
