#include "controlEge.h"

controlEge::controlEge(int a, int b, color_t color) {
  initgraph(a, b);
  setcolor(color);
}
controlEge::~controlEge() { closegraph(); }
