#include "controlEge.h"

controlEge::controlEge(int a, int b, color_t color) {
  initgraph(a, b);
  setcolor(color);
  setcaption("C++ Lab03           by xianfei 2019.5");
}
controlEge::~controlEge() { closegraph(); }
