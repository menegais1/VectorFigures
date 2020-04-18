#ifndef FIGURELISTMANAGER_H
#define FIGURELISTMANAGER_H

#include <vector>
#include "Figure.h"

class FigureListManager
{
public:
    void deleteSelectedFigures();
    Float3 calculateSelectedFiguresCenter();
    void addFigure(Figure *figure);
    void updateSelectedFiguresZIndex(int zIndexModifier);
    void selectFigure(Figure *figure);
    void deselectFigure(Figure *figure);
    void clearSelectedFigures();
    void setDrawBounds(bool drawBounds);
    void translateFigures(Float3 translationAmount);
    void rotateFigures(float angle, Float3 center);
    void rescaleFigures(Float3 scale, Float3 center);
    void setSelectedFiguresColor(Float3 color, bool fillColor);
    Figure *getFirstInteractedFigure(Float2 mousePosition);

private:
    std::vector<Figure *> figures;
    std::vector<Figure *> selectedFigures;
    void updateFigureZIndex(Figure *figure);
    void addFigure(std::vector<Figure *> &figures, Figure *figure);
    bool removeFigure(std::vector<Figure *> &figures, Figure *figure);
};

#endif