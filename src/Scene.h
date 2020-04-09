#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "Figure.h"

enum SceneMode
{
    Insert = 'i',
    Translate = 't',
    Scale = 's',
    Rotate = 'r',
    Default = 0
};

class Scene : public CanvasObject
{
public:
    std::vector<Figure *> figures;
    void mouse(int button, int state, int wheel, int direction, int x, int y) override;
    void keyboardUp(int key) override;
    void render() override;
    Scene();

private:
    std::vector<Float3> tmpVertices;
    int mode;
    int lastMode;

    void renderPolygonInsertion();
    void renderCurrentMode();
};

#endif
