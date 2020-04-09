#include "Scene.h"
#include "Utilities.h"
#include "Figure.h"
#include "Canvas/gl_canvas2d.h"
#include <iostream>
void Scene::mouse(int button, int state, int wheel, int direction, int x, int y)
{
    if (mode == 1)
    {
        if (button == MouseButton::Left && state == MouseState::Down)
        {
            tmpVertices.push_back({x, y, 0});
            std::cout << "insert" << std::endl;
        }
    }
    else if (mode != 1 && lastMode == 1)
    {
        Figure *fig = new Figure();
        fig->backgroundColor = {1, 1, 1};
        fig->lineColor = {0, 0, 0};
        fig->vertices = tmpVertices;
        figures.push_back(fig);
        lastMode = 0;
        std::cout << "new figure" << std::endl;
    }
}
void Scene::keyboardUp(int key)
{

    if (key == 'i')
    {
        mode = 1;
        tmpVertices.clear();
    }
    else
    {
        lastMode = mode;
        mode = 0;
    }
}

void Scene::render()
{
    if (tmpVertices.size() <= 0)
        return;
    for (int i = 0; i < tmpVertices.size(); i++)
    {
        color(1, 0, 0);
        point(tmpVertices[i].x, tmpVertices[i].y);
    }
}

Scene::Scene()
{
    mode = lastMode = 0;
}
