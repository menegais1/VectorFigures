#include "Scene.h"
#include "Utilities.h"
#include "Figure.h"
#include "Canvas/gl_canvas2d.h"
#include "Managers/GlobalManager.h"
#include "Label/Label.h"
#include <iostream>
#include <algorithm>

void Scene::mouse(int button, int state, int wheel, int direction, int x, int y)
{
    currentMousePosition = {x, y};
    if (mode == SceneMode::Insert)
    {
        if (leftMouseDown(button, state))
        {
            tmpVertices.push_back({x, y, 0});
        }
    }
    if (mode == SceneMode::Default)
    {
        bool isLeftMouseClicked = leftMouseDown(button, state);
        if (!isLeftMouseClicked)
            return;
        if (multipleSelect)
        {
            multipleSelection(x, y);
        }
        else
        {
            singleSelection(x, y);
        }
    }
    if (mode == SceneMode::Translate)
    {
        Float3 translation = {currentMousePosition.x - lastMousePosition.x, currentMousePosition.y - lastMousePosition.y, 0};
        for (int i = 0; i < selectedFigures.size(); i++)
        {
            selectedFigures[i]->translate(translation);
        }
    }
    lastMousePosition = currentMousePosition;
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
    if (tmpVertices.size() < 2)
        return;
    Float3 backgroundColor = {0.2, 0.2, 0.2};
    Float3 lineColor = {0, 1, 0};
    tmpVertices.push_back(tmpVertices[0]);
    Figure *fig = new Figure(backgroundColor, lineColor, highlightColor, tmpVertices);
    fig->setZIndex(figures.size());
    addFigure(figures, fig);
}

void Scene::addFigure(std::vector<Figure *> &figures, Figure *figure)
{
    if (figures.size() == 0)
    {
        figures.push_back(figure);
    }
    else
    {
        for (int i = 0; i < figures.size(); i++)
        {
            if (figures[i]->getZIndex() <= figure->getZIndex())
            {
                figures.insert(figures.begin() + i, figure);
                break;
            }
        }
    }
}

void Scene::changeFigureZIndex(std::vector<Figure *> &figures, Figure *figure)
{
    auto iterator = std::find(figures.begin(), figures.end(), figure);
    if (iterator != figures.cend())
    {
        int index = std::distance(figures.begin(), iterator);
        if (index + 1 < figures.size() && figures[index + 1]->getZIndex() > figure->getZIndex())
        {
            while (index + 1 < figures.size() && figures[index + 1]->getZIndex() > figure->getZIndex())
            {
                figures[index] = figures[index + 1];
                figures[index + 1] = figure;
                index++;
            }
        }
        else if (index - 1 > -1 && figures[index - 1]->getZIndex() < figure->getZIndex())
        {
            while (index - 1 > -1 && figures[index - 1]->getZIndex() < figure->getZIndex())
            {
                figures[index] = figures[index - 1];
                figures[index - 1] = figure;
                index--;
            }
        }
    }
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
    switch (key)
    {
    case SceneMode::Insert:
        mode = SceneMode::Insert;
        tmpVertices.clear();
        break;
    case SceneMode::Translate:
        lastMode = mode;
        if (mode == SceneMode::Translate)
        {
            mode = SceneMode::Default;
        }
        else
        {
            mode = SceneMode::Translate;
            lastMousePosition = GlobalManager::getInstance()->mousePosition;
        }
    case Key::CTRL:
        multipleSelect = false;
        break;
    case Key::LeftArrow:
        sendToBack();
        break;
    case Key::RightArrow:
        sendToFront();
        break;
    case Key::Enter:
        if (mode == SceneMode::Insert)
        {
            insertNewFigure();
            lastMode = mode;
            mode = SceneMode::Default;
        }
    default:

        break;
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
        text(20, *GlobalManager::getInstance()->screenHeight - 35, "I key: clear points");
        text(20, *GlobalManager::getInstance()->screenHeight - 47, "Enter key: finish insertion");
        break;
    case SceneMode::Translate:
        color(1, 1, 1);
        text(20, *GlobalManager::getInstance()->screenHeight - 10, "Mode: Translation");
        text(20, *GlobalManager::getInstance()->screenHeight - 23, "Move Mouse: Translate selected figures");
        text(20, *GlobalManager::getInstance()->screenHeight - 35, "Any Key: finish translation");
        break;
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
            selectedFigures[i]->setZIndex(selectedFigures[i]->getZIndex() - 10);
            changeFigureZIndex(selectedFigures, selectedFigures[i]);
            changeFigureZIndex(figures, selectedFigures[i]);
        }
    }
}

void Scene::sendToFront()
{
    if (selectedFigures.size() > 0)
    {
        for (int i = 0; i < selectedFigures.size(); i++)
        {
            selectedFigures[i]->setZIndex(selectedFigures[i]->getZIndex() + 10);
            changeFigureZIndex(selectedFigures, selectedFigures[i]);
            changeFigureZIndex(figures, selectedFigures[i]);
        }
    }
}

Scene::Scene()
{
    mode = lastMode = SceneMode::Default;
    highlightColor = {245 / 255.0, 195 / 255.0, 120 / 255.0, 0.6};
}
