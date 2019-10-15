#include "rect.h"

rect::rect(point upPoint, point downPoint, color lineColor, color fillColor,
     bool isFilled)
    : shape(lineColor, fillColor, isFilled),
      upPoint(upPoint),
      downPoint(downPoint) {}

rect::rect(point upPoint, point downPoint, color lineColor)
    : shape(lineColor, CYAN, false), upPoint(upPoint), downPoint(downPoint) {}

void rect::draw() {
  setcolor(getLineColor());

  if (!getIsFilled()) {
    setfillcolor(getFillColor());
    rectangle(upPoint.getX(), upPoint.getY(), downPoint.getX(),
              downPoint.getY());
  } else {
    setfillcolor(getLineColor());
    bar(upPoint.getX(), upPoint.getY(), downPoint.getX(), downPoint.getY());
  }
}

void rect::setUpPoint(point upPoint) { rect::upPoint = upPoint; }

void rect::setDownPoint(point downPoint) { rect::downPoint = downPoint; }

point rect::getUpPoint() { return upPoint; }

point rect::getDownPoint() { return downPoint; }