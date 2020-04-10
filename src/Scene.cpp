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
        }
    }
    if (mode == SceneMode::Default)
    {
        if (leftMouseClicked(button, state) && !multipleSelect)
        {
            singleSelection(x, y);
        }
        else if (leftMouseClicked(button, state) && multipleSelect)
        {
            multipleSelection(x, y);
        }
    }
}

void Scene::singleSelection(int x, int y)
{
    selectedFigures.clear();
    for (int i = 0; i < figures.size(); i++)
    {
        figures[i]->isSelected = false;
    }
    for (int i = 0; i < figures.size(); i++)
    {
        std::cout << figures[i] << std::endl;
        if (isPointInsidePolygon({x, y, 0}, figures[i]->vertices, figures[i]->vertices.size() - 1))
        {
            figures[i]->isSelected = true;
            selectedFigures.push_back(figures[i]);
            return;
        }
    }
}

void Scene::multipleSelection(int x, int y)
{
    bool someFigureWasClicked = false;
    for (int i = 0; i < figures.size(); i++)
    {
        if (isPointInsidePolygon({x, y, 0}, figures[i]->vertices, figures[i]->vertices.size() - 1))
        {
            figures[i]->isSelected = true;
            selectedFigures.push_back(figures[i]);
            someFigureWasClicked = true;
        }
    }
    if (!someFigureWasClicked)
        selectedFigures.clear();
}

void Scene::insertNewFigure()
{
    Figure *fig = new Figure();
    fig->backgroundColor = {0.2, 0.2, 0.2};
    fig->lineColor = {0, 1, 0};
    std::cout << "insert vertices" << std::endl;
    tmpVertices.push_back(tmpVertices[0]);
    fig->vertices = tmpVertices;
    std::cout << "end insert vertices" << std::endl;
    fig->highlightColor = this->highlightColor;
    fig->setZIndex(figures.size());
    figures.push_back(fig);
}

void Scene::keyboard(int key)
{
    if (mode == SceneMode::Default && key == 214)
    {
        multipleSelect = true;
    }
}

void Scene::keyboardUp(int key)
{
    std::cout << key << std::endl;
    if (key == SceneMode::Insert)
    {
        mode = SceneMode::Insert;
        tmpVertices.clear();
    }
    else
    {
        lastMode = mode;
        mode = SceneMode::Default;
        if (lastMode == SceneMode::Insert)
        {
            insertNewFigure();
            lastMode = SceneMode::Default;
        }
    }

    if (key == 214)
    {
        multipleSelect = false;
    }

    if (key == 200)
        sendToBack();
    if (key == 202)
        sendToFront();
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

void Scene::sendToBack()
{
    if (selectedFigures.size() > 0)
    {
        for (int i = 0; i < selectedFigures.size(); i++)
        {
            selectedFigures[i]->setZIndex(selectedFigures[i]->getZIndex() - 1);
        }
    }
}

void Scene::sendToFront()
{
    if (selectedFigures.size() > 0)
    {
        for (int i = 0; i < selectedFigures.size(); i++)
        {
            selectedFigures[i]->setZIndex(selectedFigures[i]->getZIndex() + 1);
        }
    }
}

Scene::Scene()
{
    mode = lastMode = SceneMode::Default;
    highlightColor = {245 / 255.0, 195 / 255.0, 120 / 255.0, 0.6};
}
