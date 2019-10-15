#include <graphics.h>
#include "rect.h"
#include "tria.h"
#include "Circle.h"
#include "controlEge.h"
#include "file.h"
#include <string>

// by xianfei. 2019/05/27 Last modified.

int main() {
  controlEge egeWindow{};
  mouse_msg msg = {0};
  rect{point(240, 10), point(340, 45)}.draw();
  outtextxy(270, 18, "打开");
  rect{point(380, 10), point(480, 45)}.draw();
  outtextxy(390, 18, "添加图形");
  rect{point(520, 10), point(620, 45)}.draw();
  outtextxy(550, 18, "保存");
  std::string savedStr;
  for (; is_run(); delay_fps(60)) {
    //获取鼠标消息，这个函数会等待，等待到有消息为止
    while (mousemsg()) {
      msg = getmouse();
    }
    if (msg.x < 340 && msg.x > 240 && msg.y < 45 && msg.y > 10 && msg.is_left()) {
      char str[100] = { 0 };
      inputbox_getline("打开", "请输入文件路径",
                       str, sizeof(str) / sizeof(*str));
      std::filesystem::path p{str};
      if (is_regular_file(p))
        readFile(p);
      else
        error(-1,3);
    }
    if (msg.x < 480 && msg.x > 380 && msg.y < 45 && msg.y > 10 &&
        msg.is_left()) {
      std::string s1;
      int n;
      do {
        n = 0;
        char str[100] = { 0 };
        inputbox_getline("创建图形", "请按照使用文档中规定，\n输入正确的参数来创建图形", str,
          sizeof(str) / sizeof(*str));
        s1 += str;
        s1 += "\n";
        for (auto c : s1)  if (c == '\n')++n;//检测换行符个数
      } while (n < 3);
      savedStr += s1;
      s1.erase(s1.end() - 1);//删除最后的一个换行符
      newShape(s1.data());
    }
    // rect{point(520, 10), point(620, 45)}.draw();
    if (msg.x < 620 && msg.x>520 && msg.y < 45 && msg.y > 10 &&
      msg.is_left()) {
      char str[100] = { 0 };
      inputbox_getline("保存", "输入保存路径：", str,
        sizeof(str) / sizeof(*str));
      std::filesystem::path p{ str };
      save(str, savedStr);
    }
  }
  return 0;
}