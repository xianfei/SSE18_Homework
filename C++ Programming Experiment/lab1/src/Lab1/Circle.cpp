#include "Circle.h"

void Circle::draw() {
    setcolor(getLineColor());

    if (getIsFilled()) {
      setfillcolor(getFillColor());
      fillellipse(centerPoint.getX(), centerPoint.getY(), r, r);
    } else {
      circle(centerPoint.getX(), centerPoint.getY(), r);
    }
  }


void Circle::setR(int r) { Circle::r = r; }

void Circle::setCenterPoint(point centerPoint) {
    Circle::centerPoint = centerPoint;
  }

int Circle::getR() { return r; }

point Circle::getCenterPoint() { return centerPoint; }
