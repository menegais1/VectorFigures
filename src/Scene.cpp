#include "Scene.h"
#include "Utilities.h"
#include "Figure.h"
#include "Canvas/gl_canvas2d.h"
#include "Managers/GlobalManager.h"
#include "Label/Label.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include "Vectors/Float2.h"
#include "Vectors/Float3.h"
#include "Vectors/Float4.h"

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
            selectedFigures[i]->translate({translation.x * fixatedAxis.x, translation.y * fixatedAxis.y, translation.z});
        }
    }

    if (mode == SceneMode::Scale)
    {
        Float3 scale1 = {currentMousePosition.x - selectionCenter.x, currentMousePosition.y - selectionCenter.y, 0};
        Float3 scale2 = {lastMousePosition.x - selectionCenter.x, lastMousePosition.y - selectionCenter.y, 0};

        float scale = scale1.length() - scale2.length();
        for (int i = 0; i < selectedFigures.size(); i++)
        {
            selectedFigures[i]->rescale({scale / 100 * fixatedAxis.x, scale / 100 * fixatedAxis.y, 0}, selectionCenter);
        }
    }

    if (mode == SceneMode::Rotate)
    {
        Float2 vector1 = {currentMousePosition.x - selectionCenter.x, currentMousePosition.y - selectionCenter.y};
        Float2 vector2 = {lastMousePosition.x - selectionCenter.x, lastMousePosition.y - selectionCenter.y};
        float length = vector1.length();
        vector1 = {vector1.x / length, vector1.y / length};
        length = vector2.length();
        vector2 = {vector2.x / length, vector2.y / length};
        float direction = vector1.x * vector2.y - vector1.y * vector2.x;
        direction = direction > 0 ? -1 : 1;
        std::cout << vector1.x << " " << vector1.y << std::endl;
        std::cout << vector2.x << " " << vector2.y << std::endl;
        float dot = vector1.x * vector2.x + vector1.y * vector2.y;
        dot = dot > 1 ? 1 : dot;
        float angle = std::acos(dot);
        for (int i = 0; i < selectedFigures.size(); i++)
        {
            selectedFigures[i]->rotate(angle * direction, selectionCenter);
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
            fixatedAxis = {1, 1};
        }
        break;
    case SceneMode::Rotate:
        lastMode = mode;
        if (mode == SceneMode::Rotate)
        {
            mode = SceneMode::Default;
        }
        else
        {
            mode = SceneMode::Rotate;
            calculateSelectedFiguresCenter();
        }
        break;
    case SceneMode::Scale:
        lastMode = mode;
        if (mode == SceneMode::Scale)
        {
            mode = SceneMode::Default;
        }
        else
        {
            mode = SceneMode::Scale;
            lastMousePosition = GlobalManager::getInstance()->mousePosition;
            calculateSelectedFiguresCenter();
            fixatedAxis = {1, 1};
        }
        break;
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
        break;
    case Key::y:
        fixatedAxis = {0, 1};
        break;
    case Key::x:
        fixatedAxis = {1, 0};
        break;
    case Key::b:
        drawPolygonBounds();
    default:

        break;
    }
}

void Scene::drawPolygonBounds()
{
    for (int i = 0; i < figures.size(); i++)
    {
        figures[i]->drawBounds = !figures[i]->drawBounds;
    }
}

void Scene::calculateSelectedFiguresCenter()
{
    Float3 mean = {0, 0, 0};
    int size = selectedFigures.size();
    for (int i = 0; i < size; i++)
    {
        mean.x += selectedFigures[i]->getCenter().x;
        mean.y += selectedFigures[i]->getCenter().y;
        mean.z += selectedFigures[i]->getCenter().z;
    }

    selectionCenter = {mean.x / size, mean.y / size, mean.z / size};
}

void Scene::render()
{
    color(1, 1, 1, 1);
    if (tmpVertices.size() > 0 && mode == SceneMode::Insert)
        renderPolygonInsertion();

    renderCurrentMode();

    if (mode == SceneMode::Rotate || mode == SceneMode::Scale)
    {
        line(selectionCenter.x, selectionCenter.y, currentMousePosition.x, currentMousePosition.y);
    }
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
        text(20, *GlobalManager::getInstance()->screenHeight - 35, "T Key: finish translation");
        text(20, *GlobalManager::getInstance()->screenHeight - 47, "X Key: Fixate x axis");
        text(20, *GlobalManager::getInstance()->screenHeight - 59, "Y Key: Fixate y axis");
        break;
    case SceneMode::Rotate:
        color(1, 1, 1);
        text(20, *GlobalManager::getInstance()->screenHeight - 10, "Mode: Rotation");
        text(20, *GlobalManager::getInstance()->screenHeight - 23, "Move Mouse: Rotate selected figures");
        text(20, *GlobalManager::getInstance()->screenHeight - 35, "R Key: finish rotation");
        break;
    case SceneMode::Scale:
        color(1, 1, 1);
        text(20, *GlobalManager::getInstance()->screenHeight - 10, "Mode: Scaling");
        text(20, *GlobalManager::getInstance()->screenHeight - 23, "Move Mouse: Scale selected figures");
        text(20, *GlobalManager::getInstance()->screenHeight - 35, "S Key: finish scaling");
        text(20, *GlobalManager::getInstance()->screenHeight - 47, "X Key: Fixate x axis");
        text(20, *GlobalManager::getInstance()->screenHeight - 59, "Y Key: Fixate y axis");
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
    setZIndex(100);
}
