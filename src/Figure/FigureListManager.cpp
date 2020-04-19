
#include <vector>
#include <iostream>
#include <algorithm>
#include "Figure/Figure.h"
#include "FigureListManager.h"

void FigureListManager::deleteSelectedFigures() {
    if (selectedFigures.size() == 0)
        return;
    for (int i = 0; i < selectedFigures.size(); i++) {
        Figure *fig = selectedFigures[i];
        removeFigure(figures, fig);
        delete fig;
    }

    selectedFigures.clear();
    std::cout << figures.size() << std::endl;
}

void FigureListManager::clearSelectedFigures() {
    for (int i = 0; i < selectedFigures.size(); i++) {
        selectedFigures[i]->isSelected = false;
    }
    selectedFigures.clear();
}

void FigureListManager::addFigure(Figure *figure) {
    addFigure(figures, figure);
}

Float3 FigureListManager::calculateSelectedFiguresCenter() {
    Float3 mean = {0, 0, 0};
    int size = selectedFigures.size();
    for (int i = 0; i < size; i++) {
        mean.x += selectedFigures[i]->getCenter().x;
        mean.y += selectedFigures[i]->getCenter().y;
        mean.z += selectedFigures[i]->getCenter().z;
    }

    return {mean.x / size, mean.y / size, mean.z / size};
}

void FigureListManager::updateSelectedFiguresZIndex(int zIndexModifier) {
    for (int i = 0; i < selectedFigures.size(); i++) {
        selectedFigures[i]->setZIndex(selectedFigures[i]->getZIndex() + zIndexModifier);
        updateFigureZIndex(selectedFigures[i]);
    }
}

void FigureListManager::updateFigureZIndex(Figure *figure) {
    if (figure->isSelected) {
        removeFigure(selectedFigures, figure);
        addFigure(selectedFigures, figure);
    }

    removeFigure(figures, figure);
    addFigure(figures, figure);
}

void FigureListManager::selectFigure(Figure *figure) {
    figure->isSelected = true;
    addFigure(selectedFigures, figure);
}

void FigureListManager::deselectFigure(Figure *figure) {
    figure->isSelected = false;
    removeFigure(selectedFigures, figure);
}

Figure *FigureListManager::getFirstInteractedFigure(Float2 mousePosition) {
    int size = figures.size();
    for (int i = 0; i < size; i++) {
        Figure *fig = figures[i];
        if (isPointInsidePolygon(mousePosition, fig->vertices, fig->vertices.size() - 1)) {
            return fig;
        }
    }

    return nullptr;
}

void FigureListManager::setDrawBounds(bool drawBounds) {
    for (int i = 0; i < figures.size(); i++) {
        figures[i]->drawBounds = drawBounds;
    }
}

void FigureListManager::addFigure(std::vector<Figure *> &figures, Figure *figure) {
    int size = figures.size();
    if (size == 0) {
        figures.push_back(figure);
    } else {
        for (int i = 0; i < size; i++) {
            if (figures[i]->getZIndex() <= figure->getZIndex()) {
                figures.insert(figures.begin() + i, figure);
                break;
            }
        }
        if (size == figures.size())
            figures.push_back(figure);
    }
}

bool FigureListManager::removeFigure(std::vector<Figure *> &figures, Figure *figure) {
    auto iterator = std::find(figures.begin(), figures.end(), figure);
    if (iterator != figures.cend()) {
        figures.erase(iterator);
        return true;
    }
    return false;
}

void FigureListManager::translateFigures(Float3 translationAmount) {

    for (int i = 0; i < selectedFigures.size(); i++) {
        selectedFigures[i]->translate({translationAmount.x, translationAmount.y, translationAmount.z});
    }
}

void FigureListManager::rotateFigures(float angle, Float3 center) {
    for (int i = 0; i < selectedFigures.size(); i++) {
        selectedFigures[i]->rotate(angle, center);
    }
}

void FigureListManager::rescaleFigures(Float3 scale, Float3 center) {
    for (int i = 0; i < selectedFigures.size(); i++) {
        selectedFigures[i]->rescale({scale.x, scale.y, scale.z}, center);
    }
}

void FigureListManager::setSelectedFiguresColor(Float3 color, bool fillColor) {
    for (int i = 0; i < selectedFigures.size(); i++) {
        if (fillColor)
            selectedFigures[i]->backgroundColor = color;
        else
            selectedFigures[i]->lineColor = color;
    }
}
