#include "CanvasObject.h"
#include "../Managers/GlobalManager.h"
#include "../Utilities.h"
#include <iostream>
#include "../Vectors/Float3.h"

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

void CanvasObject::setZIndex(int zIndex)
{
    this->zIndex = zIndex;
    GlobalManager::getInstance()->changeObjectZIndex(this);
}

int CanvasObject::getZIndex()
{
    return zIndex;
}

CanvasObject::CanvasObject()
{
    objectId = GlobalManager::getInstance()->registerObject(this);
    isActive = true;
    lastActiveState = true;
    position = {0, 0, 0};
    scale = {1, 1, 1};
    zIndex = 0;
}

CanvasObject::~CanvasObject()
{
    GlobalManager::getInstance()->unregisterObject(this);
}

bool CanvasObject::isMouseInsideObject()
{
    GlobalManager::getInstance()->isMouseInsideObject(this);
}

void CanvasObject::translate(Float3 translationAmount)
{
    position = position + translationAmount;
}
void CanvasObject::rotate(float, Float3)
{
}
void CanvasObject::rescale(Float3, Float3)
{
}
