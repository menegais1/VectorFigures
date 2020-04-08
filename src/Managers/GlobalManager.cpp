
#include <vector>
#include "../Base/CanvasObject.h"
#include "GlobalManager.h"
#include <iostream>

GlobalManager::GlobalManager()
{
}
GlobalManager *GlobalManager::getInstance()
{
    static GlobalManager *instance = new GlobalManager();
    return instance;
}

void GlobalManager::keyboard(int key)
{

    for (int i = 0; i < objects.size(); i++)
    {
        if (!objects[i]->checkIfCanExecuteCallback())
            continue;
        objects[i]->keyboard(key);
    }
}
void GlobalManager::keyboardUp(int key)
{
    for (int i = 0; i < objects.size(); i++)
    {
        if (!objects[i]->checkIfCanExecuteCallback())
            continue;
        objects[i]->keyboardUp(key);
    }
}
void GlobalManager::mouse(int button, int state, int wheel, int direction, int x, int y)
{
    for (int i = 0; i < objects.size(); i++)
    {
        if (!objects[i]->checkIfCanExecuteCallback())
            continue;
        objects[i]->mouse(button, state, wheel, direction, x, y);
    }
}
void GlobalManager::render()
{
    for (int i = 0; i < GlobalManager::objects.size(); i++)
    {
        if (!objects[i]->checkIfCanExecuteCallback())
            continue;
        objects[i]->render();
    }
}
int GlobalManager::registerObject(CanvasObject *object)
{
    objects.push_back(object);
    return objects.size() - 1;
}
CanvasObject *GlobalManager::unregisterObject(int objectId)
{
    CanvasObject *object = objects[objectId];
    objects.erase(objects.begin() + objectId);
    return object;
}
