#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "../Figure/Figure.h"
#include "../Vectors/Float3.h"
#include "../Vectors/Float4.h"
#include "../Figure/FigureListManager.h"
#include "../ColorPicker/ColorPickerPanel.h"

enum Operator {
    InsertPolygon = 13,
    SendToBack = 200,
    SendToFront = 202,
    MultipleSelect = 214,
    FixX = 'x',
    FixY = 'y',
    RenderBounds = 'b',
    DeleteSelected = 127,
    SelectFillColor = 'f',
    SelectLineColor = 'l',
    LoadFile = 'o',
    SaveFile = 'p'
};

enum FigureType {
    Polygon = '0',
    Circle = '1',
    Triangle = '3',
    Square = '4',
    Pentagon = '5',
    Hexagon = '6',
    Heptagon = '7',
    Octagon = '8',
    Nonagon = '9'
};

enum SceneMode {
    Insert = 'i',
    Translate = 't',
    Scale = 's',
    Rotate = 'r',
    Default = 0
};

class Scene : public CanvasObject {
public:
    void mouse(int button, int state, int wheel, int direction, int x, int y) override;

    void keyboardUp(int key) override;

    void keyboard(int key) override;

    void render() override;

    bool pointIntersectsObject(Float3 point) override;

    Scene();

private:
    FigureListManager figureListManager;
    std::vector<Float3> tmpVertices;
    int mode;
    bool multipleSelect;
    bool drawBounds;
    Float4 highlightColor;
    Float2 lastMousePosition;
    Float3 selectionCenter;
    Float2 currentMousePosition;
    Float2 fixatedAxis;
    ColorPickerPanel *colorPickerPanel;
    Button *selectFillColorButton;
    Button *selectLineColorButton;
    bool selectingFillColor;
    bool selectingLineColor;
    FigureType insertionType;

    void renderPolygonInsertion();

    void renderCurrentMode();

    void insertNewFigure();

    void singleSelection(int x, int y);

    void multipleSelection(int x, int y);

    void sendToBack();

    void sendToFront();

    void selectFillColor();

    void selectLineColor();

    void drawPolygonBounds();

    void handleSceneMode(SceneMode sceneMode);

    void handleSceneOperator(Operator op);

    void handleFigureTypeSelection(FigureType type);

    //Scene Mode handle
    void setInsertMode();

    void setTranslateMode();

    void setScaleMode();

    void setRotateMode();

    void setDefaultMode();

    void handleInsertMode(int button, int state);

    void handleTranslateMode();

    void handleScaleMode();

    void handleRotateMode();

    void handleDefaultMode(int button, int state);
    //Components
    void ignoreUpperCaseChar(int &key);
};

#endif
