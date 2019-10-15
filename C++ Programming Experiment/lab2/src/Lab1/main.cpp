#include <graphics.h>
#include "rect.h"
#include "tria.h"
#include "Circle.h"
#include "controlEge.h"


int main() {
  //初始化画图控制类(可传入参数窗口大小，默认640*480)
  controlEge* a = new controlEge{};

  // 颜色类支持接收: 空（默认黑色）、大写颜色（如RED）、RGB参数（如255，165，97）及16进制RGB参数（如0xc0ffee）

  // 圆形类，参数为：圆心，半径，轮廓颜色，填充色，是否填充（后两个参数可不给，即为不填充）
  Circle* c1 = new Circle{point(369, 180), 50, color(GREEN), color(0xffc125), true};
  Circle* c2 = new Circle{point(80, 250), 30, color(254, 26, 89), color(154, 36, 98), false};
  Circle* c3 = new Circle{point(125, 179), 88, color(0xffec8b), color(), false};
  // 绘制圆形
  c1->draw();
  c2->draw();
  c3->draw();
  // 矩形类，参数为：左上顶点，右下顶点，轮廓颜色，填充色，是否填充（后两个参数可不给，即为不填充）
  rect* r1 = new rect{point(250, 360), point(340, 460), color(0xffc1c1), color(MAGENTA),
          true};
  rect* r2 = new rect{point(356, 214), point(456, 388), color(132, 189, 233), color(CYAN),
          false};
  // 绘制矩形
  r1->draw();
  r2->draw();
  // 三角形类，参数为：第一个顶点，第二个顶点，第三个定点，轮廓颜色，填充色，是否填充（后两个参数可不给，即为不填充）
  tria* t1 = new tria{point(450, 100), point(600, 200),point(500,300), color(CYAN), color(0xffc1c1), true};
  t1->draw();
  // 清理对象
  delete c1;
  c1 = nullptr;
  delete c2;
  c2 = nullptr;
  delete c3;
  c3 = nullptr;
  delete r1;
  r1 = nullptr;
  delete r2;
  r2 = nullptr;
  delete t1;
  t1 = nullptr;
  // 暂停
  getch();
  // 删除绘图控制类
  delete a;
  a = nullptr;
  return 0;
}