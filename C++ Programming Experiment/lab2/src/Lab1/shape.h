#pragma once
#include <graphics.h>
#include "color.h"

class shape {
  color* lineColor = nullptr;
  color* fillColor = nullptr;
  bool isFilled;
  
 public:
  shape(color lineColor, color fillColor, bool isFilled);

  shape() = default;

  shape(const shape& s);

  ~shape();

  bool getIsFilled();

  color_t getLineColor();

  color_t getFillColor();

  void setLineColor(color lineColor);

  void setFillColor(color fillColor);

  void setIsFilled(bool isFilled);

  virtual void draw() = 0;
};
