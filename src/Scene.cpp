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
    switch (mode)
    {
    case SceneMode::Insert:
        handleInsertMode(button, state);
        break;
    case SceneMode::Translate:
        handleTranslateMode();
        break;
    case SceneMode::Rotate:
        handleRotateMode();
        break;
    case SceneMode::Scale:
        handleScaleMode();
        break;
    case SceneMode::Default:
        handleDefaultMode(button, state);
        break;
    }
    lastMousePosition = currentMousePosition;
}

void Scene::singleSelection(int x, int y)
{
    if (isMouseInsideObject())
    {
        figureListManager.clearSelectedFigures();
    }
    Figure *fig = figureListManager.getFirstInteractedFigure({x, y});
    if (fig != nullptr)
    {
        figureListManager.clearSelectedFigures();
        figureListManager.selectFigure(fig);
    }
}

void Scene::multipleSelection(int x, int y)
{
    Figure *fig = figureListManager.getFirstInteractedFigure({x, y});
    if (fig != nullptr)
    {
        figureListManager.selectFigure(fig);
    }
    else if (isMouseInsideObject())
    {
        figureListManager.clearSelectedFigures();
    }
}

void Scene::insertNewFigure()
{
    if (tmpVertices.size() < 2)
        return;
    Float3 backgroundColor = {0.2, 0.2, 0.2};
    Float3 lineColor = {0, 1, 0};
    tmpVertices.push_back(tmpVertices[0]);
    Figure *fig = new Figure(backgroundColor, lineColor, highlightColor, tmpVertices);
    fig->setZIndex(0);
    fig->drawBounds = drawBounds;
    figureListManager.addFigure(fig);
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
    handleSceneMode(static_cast<SceneMode>(key));
    handleSceneOperator(static_cast<Operator>(key));
}

void Scene::handleSceneMode(SceneMode sceneMode)
{
    switch (sceneMode)
    {
    case SceneMode::Insert:
        setInsertMode();
        break;
    case SceneMode::Translate:
        setTranslateMode();
        break;
    case SceneMode::Rotate:
        setRotateMode();
        break;
    case SceneMode::Scale:
        setScaleMode();
        break;
    }
}

void Scene::handleSceneOperator(Operator op)
{
    switch (op)
    {
    case Operator::MultipleSelect:
        multipleSelect = false;
        break;
    case Operator::SendToBack:
        sendToBack();
        break;
    case Operator::SendToFront:
        sendToFront();
        break;
    case Operator::InsertPolygon:
        if (mode == SceneMode::Insert)
        {
            insertNewFigure();
            lastMode = mode;
            mode = SceneMode::Default;
        }
        break;
    case Operator::FixY:
        fixatedAxis = {0, 1};
        break;
    case Operator::FixX:
        fixatedAxis = {1, 0};
        break;
    case Operator::RenderBounds:
        drawBounds = !drawBounds;
        drawPolygonBounds();
        break;
    case Operator::DeleteSelected:
        figureListManager.deleteSelectedFigures();
        break;
    case Operator::SelectFillColor:
        selectFillColor();
        break;
    case Operator::SelectLineColor:
        selectLineColor();
        break;
    default:
        break;
    }
}

void Scene::drawPolygonBounds()
{
    figureListManager.setDrawBounds(drawBounds);
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
        if (selectingFillColor)
            text(20, *GlobalManager::getInstance()->screenHeight - 23, "Selecting Fill Color");
        if (selectingLineColor)
            text(20, *GlobalManager::getInstance()->screenHeight - 23, "Selecting Line Color");
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
    figureListManager.updateSelectedFiguresZIndex(-10);
}

void Scene::sendToFront()
{
    figureListManager.updateSelectedFiguresZIndex(10);
}

Scene::Scene()
{
    mode = lastMode = SceneMode::Default;
    highlightColor = {245 / 255.0, 195 / 255.0, 120 / 255.0, 0.8};
    setZIndex(100);
    drawBounds = false;
    colorPickerPanel = new ColorPickerPanel({10, 10, 0}, {250, 250, 0}, {0.3, 0.3, 0.3});
    colorPickerPanel->setActive(false);
    selectFillColorButton = new Button({10, 10, 0}, {120, 30, 0}, {1, 1, 1}, "Fill Color", {0, 0, 0});
    selectFillColorButton->addListener([this] {
        selectFillColor();
    });
    selectLineColorButton = new Button({132, 10, 0}, {120, 30, 0}, {1, 1, 1}, "Line Color", {0, 0, 0});
    selectLineColorButton->addListener([this] {
        selectLineColor();
    });
    colorPickerPanel->addOnValueChangedListener([this](Float3 color) {
        this->figureListManager.setSelectedFiguresColor(color, this->selectingFillColor);
    });
    colorPickerPanel->addOnActivateListener([this](bool isActive) {
        if (!isActive)
        {
            this->selectingLineColor = false;
            this->selectingFillColor = false;
        }
    });
    this->scale = Float3(*GlobalManager::getInstance()->screenWidth, *GlobalManager::getInstance()->screenHeight, 0);
    this->setZIndex(-1);
}

void Scene::selectFillColor()
{
    this->selectingFillColor = true;
    this->selectingLineColor = false;
    this->colorPickerPanel->setActive(true);
}

void Scene::selectLineColor()
{
    this->selectingLineColor = true;
    this->selectingFillColor = false;
    this->colorPickerPanel->setActive(true);
}

void Scene::setInsertMode()
{
    lastMode = mode;
    mode = SceneMode::Insert;
    tmpVertices.clear();
}

void Scene::setTranslateMode()
{
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
}

void Scene::setScaleMode()
{
    lastMode = mode;
    if (mode == SceneMode::Scale)
    {
        mode = SceneMode::Default;
    }
    else
    {
        mode = SceneMode::Scale;
        lastMousePosition = GlobalManager::getInstance()->mousePosition;
        selectionCenter = figureListManager.calculateSelectedFiguresCenter();
        fixatedAxis = {1, 1};
    }
}
void Scene::setRotateMode()
{
    lastMode = mode;
    if (mode == SceneMode::Rotate)
    {
        mode = SceneMode::Default;
    }
    else
    {
        mode = SceneMode::Rotate;
        selectionCenter = figureListManager.calculateSelectedFiguresCenter();
    }
}
void Scene::setDefaultMode()
{
}

void Scene::handleInsertMode(int button, int state)
{
    if (leftMouseDown(button, state))
    {
        tmpVertices.push_back({currentMousePosition.x, currentMousePosition.y, 0});
    }
}
void Scene::handleTranslateMode()
{
    Float3 translation = {currentMousePosition.x - lastMousePosition.x, currentMousePosition.y - lastMousePosition.y, 0};
    figureListManager.translateFigures({translation.x * fixatedAxis.x, translation.y * fixatedAxis.y, 0});
}
void Scene::handleScaleMode()
{
    Float3 scale1 = {currentMousePosition.x - selectionCenter.x, currentMousePosition.y - selectionCenter.y, 0};
    Float3 scale2 = {lastMousePosition.x - selectionCenter.x, lastMousePosition.y - selectionCenter.y, 0};

    float scale = scale1.length() - scale2.length();
    figureListManager.rescaleFigures({scale / 100 * fixatedAxis.x, scale / 100 * fixatedAxis.y, 0}, selectionCenter);
}
void Scene::handleRotateMode()
{
    Float2 vector1 = {currentMousePosition.x - selectionCenter.x, currentMousePosition.y - selectionCenter.y};
    Float2 vector2 = {lastMousePosition.x - selectionCenter.x, lastMousePosition.y - selectionCenter.y};
    float length = vector1.length();
    vector1 = {vector1.x / length, vector1.y / length};
    length = vector2.length();
    vector2 = {vector2.x / length, vector2.y / length};
    float direction = vector1.x * vector2.y - vector1.y * vector2.x;
    direction = direction > 0 ? -1 : 1;
    float dot = vector1.x * vector2.x + vector1.y * vector2.y;
    dot = dot > 1 ? 1 : dot;
    float angle = std::acos(dot);
    figureListManager.rotateFigures(angle * direction, selectionCenter);
}
void Scene::handleDefaultMode(int button, int state)
{
    bool isLeftMouseClicked = leftMouseDown(button, state);
    if (!isLeftMouseClicked)
        return;
    if (multipleSelect)
    {
        multipleSelection(currentMousePosition.x, currentMousePosition.y);
    }
    else
    {
        singleSelection(currentMousePosition.x, currentMousePosition.y);
    }
}

bool Scene::pointIntersectsObject(Float3 point)
{
    return true;
}
