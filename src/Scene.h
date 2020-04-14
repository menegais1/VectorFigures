#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "Figure.h"
#include "Label/Label.h"

enum Key
{
    Enter = 13,
    LeftArrow = 200,
    RightArrow = 202,
    CTRL = 214
};

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
    std::vector<Figure *> selectedFigures;
    void mouse(int button, int state, int wheel, int direction, int x, int y) override;
    void keyboardUp(int key) override;
    void keyboard(int key) override;
    void render() override;
    Scene();

private:
    std::vector<Float3> tmpVertices;
    Float4 highlightColor;
    int mode;
    int lastMode;
    Float2 lastMousePosition;
    Float3 rotationCenter;
    Float2 currentMousePosition;
    bool multipleSelect;
    void renderPolygonInsertion();
    void renderCurrentMode();
    void insertNewFigure();
    void singleSelection(int x, int y);
    void multipleSelection(int x, int y);
    void sendToBack();
    void sendToFront();
    void calculateSelectedFiguresCenter();
    void addFigure(std::vector<Figure *> &figures, Figure *figure);
    void changeFigureZIndex(std::vector<Figure *> &figures, Figure *figure);
    //Components
};

#endif
