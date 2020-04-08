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
    CanvasObject *unregisterObject(int objectId);
    static GlobalManager* getInstance();

private:
    static GlobalManager *instance;
    std::vector<CanvasObject *> objects;
    GlobalManager();
};

#endif
