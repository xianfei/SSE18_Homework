#pragma once
#include <graphics.h>
#include "color.h"

class shape {
protected:
  color* lineColor = nullptr;
  color* fillColor = nullptr;
  bool isFilled;
  
 public:
  shape(color lineColor, color fillColor, bool isFilled);

  shape();

  shape(const shape& s);

  virtual ~shape();

  virtual shape& operator=(shape&)=0;

  virtual int& operator[](int) = 0;

  virtual double getArea() = 0;

  bool operator>(shape&);

  bool operator>=(shape&);

  bool operator<(shape&);

  bool operator<=(shape&);

  virtual bool operator==(shape&) { return false; }

  bool getIsFilled();

  color_t getLineColor();

  color_t getFillColor();

  void setLineColor(color lineColor);

  void setFillColor(color fillColor);

  void setIsFilled(bool isFilled);

  virtual void draw() = 0;
};
