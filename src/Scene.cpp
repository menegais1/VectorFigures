#include "Scene.h"
#include "Utilities.h"
#include "Figure.h"
#include "Canvas/gl_canvas2d.h"
#include "Managers/GlobalManager.h"
#include "Label/Label.h"
#include <iostream>
void Scene::mouse(int button, int state, int wheel, int direction, int x, int y)
{
    if (mode == SceneMode::Insert)
    {
        if (leftMouseClicked(button, state))
        {
            tmpVertices.push_back({x, y, 0});
            std::cout << "insert" << std::endl;
        }
    }
    if (mode == SceneMode::Default)
    {
        if (leftMouseClicked(button, state))
        {
            for (int i = 0; i < figures.size(); i++)
            {
                figures[i]->isSelected = false;
            }
            for (int i = 0; i < figures.size(); i++)
            {
                if (isPointInsidePolygon({x, y, 0}, figures[i]->vertices, figures[i]->vertices.size()))
                {
                    figures[i]->isSelected = true;
                    return;
                }
            }
        }
    }
    if (lastMode == SceneMode::Insert)
    {
        insertNewFigure();
        lastMode = SceneMode::Default;
    }
}

void Scene::insertNewFigure()
{
    Figure *fig = new Figure();
    fig->backgroundColor = {0.2, 0.2, 0.2};
    fig->lineColor = {0, 1, 0};
    fig->vertices = tmpVertices;
    fig->highlightColor = this->highlightColor;
    figures.push_back(fig);
    std::cout << "new figure" << std::endl;
}

void Scene::keyboardUp(int key)
{

    if (key == SceneMode::Insert)
    {
        mode = SceneMode::Insert;
        tmpVertices.clear();
    }
    else
    {
        lastMode = mode;
        mode = SceneMode::Default;
    }
}

void Scene::render()
{
    if (tmpVertices.size() > 0 && mode == SceneMode::Insert)
        renderPolygonInsertion();

    renderCurrentMode();
}
void Scene::renderPolygonInsertion()
{
    int size = tmpVertices.size();
    for (int i = 0; i < size; i++)
    {
        color(1, 1, 1);
        circle(tmpVertices[i].x, tmpVertices[i].y, 3, 10);
    }
    for (int i = 0; i < size - 1; i++)
    {
        color(1, 0, 0);
        line(tmpVertices[i].x, tmpVertices[i].y, tmpVertices[i + 1].x, tmpVertices[i + 1].y);
    }
    line(tmpVertices[size - 1].x, tmpVertices[size - 1].y, tmpVertices[0].x, tmpVertices[0].y);
}

void Scene::renderCurrentMode()
{

    switch (mode)
    {
    case SceneMode::Default:
        color(1, 1, 1);
        text(20, *GlobalManager::getInstance()->screenHeight - 10, "Mode: Default");
        break;
    case SceneMode::Insert:
        color(1, 1, 1);
        text(20, *GlobalManager::getInstance()->screenHeight - 10, "Mode: Insert");
        text(20, *GlobalManager::getInstance()->screenHeight - 23, "Left mouse: Insert point");
        text(20, *GlobalManager::getInstance()->screenHeight - 35, "Any Key: finish insertion");
    default:
        break;
    }
}

Scene::Scene()
{
    mode = lastMode = SceneMode::Default;
    highlightColor = {245 / 255.0, 195 / 255.0, 120 / 255.0, 0.6};
}
