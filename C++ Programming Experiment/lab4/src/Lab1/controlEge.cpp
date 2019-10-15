#include "controlEge.h"

controlEge::controlEge(int a, int b, color_t color) {
  initgraph(a, b);
  setcolor(color);
  setbkcolor(0xe6f0f9);
  setcaption("C++ สตั้หฤ by xianfei");
}
controlEge::~controlEge() { closegraph(); }
