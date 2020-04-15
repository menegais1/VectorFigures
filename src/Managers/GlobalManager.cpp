
#include <vector>
#include "../Base/CanvasObject.h"
#include "GlobalManager.h"
#include <iostream>
#include <algorithm>
#include <chrono>
using namespace std::chrono;

GlobalManager::GlobalManager()
{
    screenWidth = new int();
    screenHeight = new int();
    *screenWidth = 600;
    *screenHeight = 600;
}
GlobalManager *GlobalManager::getInstance()
{
    static GlobalManager *instance = new GlobalManager();
    return instance;
}

void GlobalManager::keyboard(int key)
{

    for (int i = GlobalManager::objects.size() - 1; i >= 0; i--)
    {
        if (!objects[i]->checkIfCanExecuteCallback())
            continue;
        objects[i]->keyboard(key);
    }
}
void GlobalManager::keyboardUp(int key)
{
    for (int i = GlobalManager::objects.size() - 1; i >= 0; i--)
    {
        if (!objects[i]->checkIfCanExecuteCallback())
            continue;
        objects[i]->keyboardUp(key);
    }
}
void GlobalManager::mouse(int button, int state, int wheel, int direction, int x, int y)
{
    mousePosition = {x, y};
    for (int i = GlobalManager::objects.size() - 1; i >= 0; i--)
    {
        if (!objects[i]->checkIfCanExecuteCallback())
            continue;
        objects[i]->mouse(button, state, wheel, direction, x, y);
    }
}
void GlobalManager::render()
{
    for (int i = GlobalManager::objects.size() - 1; i >= 0; i--)
    {
        if (!objects[i]->checkIfCanExecuteCallback())
            continue;
        objects[i]->render();
    }
}
int GlobalManager::registerObject(CanvasObject *object)
{
    addObjectToList(object);
    return objectIdCounter++;
}

void GlobalManager::addObjectToList(CanvasObject *object)
{
    int size = objects.size();
    if (size == 0)
    {
        objects.push_back(object);
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            if (objects[i]->getZIndex() <= object->getZIndex())
            {
                objects.insert(objects.begin() + i, object);
                break;
            }
        }
        if (size == objects.size())
            objects.push_back(object);
    }
}
void GlobalManager::changeObjectZIndex(CanvasObject *object)
{
    auto iterator = std::find(objects.begin(), objects.end(), object);
    if (iterator != objects.cend())
    {
        objects.erase(iterator);
        addObjectToList(object);
    }
}

CanvasObject *GlobalManager::unregisterObject(CanvasObject *object)
{
    auto iterator = std::find(objects.begin(), objects.end(), object);
    objects.erase(iterator);
    return object;
}
