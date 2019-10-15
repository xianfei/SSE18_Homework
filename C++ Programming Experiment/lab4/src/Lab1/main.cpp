#include <graphics.h>
#include "rect.h"
#include "tria.h"
#include "Circle.h"
#include "controlEge.h"
#include "ege_stream.h"

int main() {
  controlEge a{ 960,600 };
  setfont(28,10, "微软雅黑");
  EgeStream::BasicEgeStream cout(550,60,30);
  using std::endl;
  // 圆心，半径，轮廓颜色，填充色，是否填充
  shape* s[5];
  s[0] = new Circle{ point(269, 200), 50, color(GREEN), color(BLUE), true };
  s[1] = new Circle{ point(80, 120), 30, color(254, 26, 89), color(154, 36, 98), false };
  s[2] = new rect{ point(250, 360), point(340, 460), color(154, 98, 253), color(MAGENTA),
          true };
  s[3] = new tria{ point(356, 214), point(520, 215), point(456, 388),color(132, 189, 233), color(CYAN),
          true};
  s[4] = new Circle;
  s[0]->draw();
  s[1]->draw();
  s[2]->draw();
  s[3]->draw();
  *(s[4]) = *(s[1]);
  cout << cout.purple << "复制出来的红色空心圆圆心坐标？" << endl;
  cout << "(" << (*(s[4]))[0] << "," << (*(s[4]))[1] << ")"<<endl;
  cout << cout.purple << "复制出来的红色空心圆和原来的相等吗？" << endl;
  cout << cout.pink << std::boolalpha << ((*(s[1])) == (*(s[4]))) << endl;
  cout << cout.purple << "蓝色的实心圆 > 红色的空心圆？" <<endl;
  cout << cout.pink << std::boolalpha << ((*(s[0])) > (* (s[1]))) << endl;
  cout << cout.purple << "蓝色的实心圆 < 紫色矩形？" << endl;
  cout << cout.orange << "圆面积：" << (*(s[0])).getArea() << "  矩形面积：" << (*(s[2])).getArea() << endl;
  cout << cout.pink << std::boolalpha << ((*(s[0])) < (* (s[2]))) << endl;
  cout << cout.purple << "紫色矩形 > 青色三角形？" << endl;
  cout << cout.orange << "矩形面积："<<(*(s[2])).getArea() << "  三角形面积：" << (*(s[3])).getArea() << endl;
  cout << cout.pink << std::boolalpha << ((*(s[2])) > (*(s[3]))) << endl;
  cout << cout.purple << "下标越界测试：输出(*(s[4]))[8]" << endl;
  try {
    cout << (*(s[4]))[8] << endl;
  }
  catch (std::out_of_range& e) {
    cout << cout.red << "Exception: " << e.what() << endl;
  }
  for (int i = 0; i < 5;i++)delete s[i];
  for (; 1;)getch();

  return 0;
}