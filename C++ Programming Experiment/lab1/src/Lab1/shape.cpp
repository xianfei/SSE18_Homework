#include "shape.h"


shape::shape(color lineColor, color fillColor, bool isFilled)
    : lineColor(lineColor), fillColor(fillColor), isFilled(isFilled) {}

bool shape::getIsFilled() { return isFilled; }

color_t shape::getLineColor() { return lineColor.getC(); }

color_t shape::getFillColor() { return fillColor.getC(); }

void shape::setLineColor(color lineColor) { shape::lineColor = lineColor; }

void shape::setFillColor(color fillColor) { shape::fillColor = fillColor; }

void shape::setIsFilled(bool isFilled) { shape::isFilled = isFilled; }

