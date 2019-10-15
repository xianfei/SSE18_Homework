#include "file.h"

void error(int line = 0, int errorCode = 0) {
  static int textY = 5;
  setcolor(0xff0000);
  std::string s1{};
  if (line >= 0) s1 += "第" + std::to_string(line + 1) + "行 ";
  switch (errorCode) {
  case 1:
    s1 += "缺少参数";
    break;
  case 2:
    s1 += "非法图形代码";
    break;
  case 3:
    s1 += "文件不存在";
    break;
  }
  outtextxy(5, textY, s1.data());
  textY += 25;
}

int readFile(const std::filesystem::path& p) {
  std::ifstream in(p);
  if (in.fail()) return 1;
  int i = 1, whereN[100] = { 0 };
  // 记录所有换行符所在的文件位置号
  while (!in.eof()) if (in.get() == '\n') whereN[i++] = in.tellg();
  int maxI = i;
  in.close();
  in.open(p);
  // 尝试绘图 3n行为图形代码  3n+1行为几何属性参数  3n+2行为颜色属性参数
  for (i = 0; !in.eof() && i < maxI; i += 3) {
    int data[11] = { 0 };
    //读取图形类型
    in.seekg(whereN[i], std::ios_base::beg);
    in >> data[0];
    if ((data[0] < 1) || (data[0] > 3)) {
      error(i, 2);
      continue;
    }
    //读取几何参数
    in.seekg(whereN[i + 1], std::ios_base::beg);
    switch (data[0]) {
    case 1:  //圆形
      in >> data[1] >> data[2] >> data[3];
      break;
    case 2:  //三角形
      in >> data[1] >> data[2] >> data[3] >> data[4] >> data[5] >> data[6];
      break;
    case 3:  //矩形
      in >> data[1] >> data[2] >> data[3] >> data[4];
      break;
    }
    if (in.tellg() > whereN[i + 2]) {
      error(i + 1, 1);
      continue;
    }
    // 读取颜色及是否填充
    in.seekg(whereN[i + 2], std::ios_base::beg);
    in >> data[7] >> data[8] >> data[9] >> data[10];
    if ((in.tellg() > whereN[i + 3]) && !in.eof()) {
      error(i + 2, 1);
      //continue;
    }
    //绘图
    switch (data[0]) {
    case 1:  //圆形
      Circle{ point(data[1], data[2]), data[3], color{data[7], data[8], data[9]} ,
                 color{data[7], data[8], data[9]},static_cast<bool>(data[10]) }.draw();
      break;
    case 2:  //三角形
      tria{ point(data[1], data[2]), point(data[3], data[4]),
               point(data[5], data[6]), color{data[7], data[8], data[9]},
          color{data[7], data[8], data[9]}, static_cast<bool>(data[10]) }
      .draw();
      break;
    case 3:  //矩形
      rect{
          point(data[1], data[2]), point(data[3], data[4]),
               color{data[7], data[8], data[9]},
               color{data[7], data[8], data[9]}, static_cast<bool>(data[10]) }
      .draw();
      break;
    }
  }
  return 0;
}

int newShape(char* s) {
  std::stringstream in;
  in << s;
  if (in.fail()) return 1;
  int i = 1, whereN[100] = { 0 };
  // 记录所有换=行符所在的文件位置号
  for (int j = 0; s[j]; j++) {
    if (s[j] == '\n') whereN[i++] = j;
  }
  int maxI = i;
  in << s;
  // 尝试绘图 3n行为图形代码  3n+1行为几何属性参数  3n+2行为颜色属性参数
  for (i = 0; !in.eof() && i < maxI; i += 3) {
    int data[11] = { 0 };
    //读取图形类型
    in.seekg(whereN[i], std::ios_base::beg);
    in >> data[0];
    if ((data[0] < 1) || (data[0] > 3)) {
      error(i, 2);
      continue;
    }
    //读取几何参数
    in.seekg(whereN[i + 1], std::ios_base::beg);
    switch (data[0]) {
    case 1:  //圆形
      in >> data[1] >> data[2] >> data[3];
      break;
    case 2:  //三角形
      in >> data[1] >> data[2] >> data[3] >> data[4] >> data[5] >> data[6];
      break;
    case 3:  //矩形
      in >> data[1] >> data[2] >> data[3] >> data[4];
      break;
    }
    if (in.tellg() > whereN[i + 2]) {
      error(i + 1, 1);
      continue;
    }
    // 读取颜色及是否填充
    in.seekg(whereN[i + 2], std::ios_base::beg);
    in >> data[7] >> data[8] >> data[9] >> data[10];
    /*if ((in.tellg() > whereN[i + 3]) && !in.eof()) {
      error(i + 2, 1);
      // continue;
    }*/
    //绘图
    switch (data[0]) {
    case 1:  //圆形
      Circle{ point(data[1], data[2]), data[3],
             color{data[7], data[8], data[9]},
             color{data[7], data[8], data[9]}, static_cast<bool>(data[10]) }
      .draw();
      break;
    case 2:  //三角形
      tria{ point(data[1], data[2]),          point(data[3], data[4]),
           point(data[5], data[6]),          color{data[7], data[8], data[9]},
           color{data[7], data[8], data[9]}, static_cast<bool>(data[10]) }
      .draw();
      break;
    case 3:  //矩形
      rect{ point(data[1], data[2]), point(data[3], data[4]),
           color{data[7], data[8], data[9]}, color{data[7], data[8], data[9]},
           static_cast<bool>(data[10]) }
      .draw();
      break;
    }
  }
  return 0;
}

void save(const std::filesystem::path & p, std::string & str) {
  std::ofstream out(p);
  str.erase(str.end() - 1);//删除最后的一个换行符
  out << str;
}
