///Manager responsible for forwarding the GLUT callbacks
///To every CanvasObject instantiated, every object has a uniqueId given
///in the beggining of its lifetime

#ifndef GLOBAL_MANAGER_H
#define GLOBAL_MANAGER_H

#include <vector>

#include "../Base/CanvasObject.h"
class GlobalManager
{
public:
    void keyboard(int key);
    void keyboardUp(int key);
    void mouse(int button, int state, int wheel, int direction, int x, int y);
    void render();
    int registerObject(CanvasObject *object);
    bool isMouseInsideObject(CanvasObject *object);
    CanvasObject *unregisterObject(CanvasObject *object);
    void changeObjectZIndex(CanvasObject *object);
    static GlobalManager *getInstance();
    int *screenWidth;
    int *screenHeight;
    Float2 mousePosition;

private:
    int objectIdCounter;
    static GlobalManager *instance;
    //The order of the objects is descending, so what will be rendered first is last 
    std::vector<CanvasObject *> objects;
    GlobalManager();
    void addObjectToList(CanvasObject *object);
};

#endif
