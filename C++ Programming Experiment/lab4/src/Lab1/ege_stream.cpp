#include "ege_stream.h"
#include <exception>


namespace EgeStream {

EgeStreamStyle::EgeStreamStyle(color_t c) :c_(c) {}

bool EgeStreamStyle::isVaild = false;

color_t EgeStreamStyle::outC=0xffffff;

std::ostream& operator<<(std::ostream& os, EgeStreamStyle s)
{
  s.outC = s.c_;
  s.isVaild = true;
  return os;
}

int EgeStreamBuf::textY = 5;

EgeStreamBuf::EgeStreamBuf(int x, int y,size_t buf_size, int spacing) :
    buf_size_(buf_size),spacing_(spacing),x_(x){
    pbuf_ = new char[buf_size_]; 
    gbuf_ = new char[buf_size_];
    this->textY = y;
    setp(pbuf_, pbuf_ + buf_size_); // set the pointers for output buf
    setg(gbuf_, gbuf_, gbuf_);      // set the pointers for input buf
}

EgeStreamBuf::~EgeStreamBuf() {
    if(pbuf_ != nullptr) {
        delete pbuf_;
        pbuf_ = nullptr;
    }

    if(gbuf_ != nullptr) {
        delete gbuf_;
        gbuf_ = nullptr;
    }
}

// flush the data to the ege
int EgeStreamBuf::sync() {
  color_t tempC;
  if (EgeStreamStyle::isVaild == true) { // set color
     tempC = getcolor();
     setcolor(EgeStreamStyle::outC);
  }
  std::string str;
  for (int i = 0; i < pptr() - pbase(); i++) str.push_back (*(pbase() + i));
  if(str.back()!='\n')str.push_back('\n');
  std::istringstream f(str);
  std::string line;
  while (std::getline(f, line)) {
    outtextxy(x_, textY, line.c_str());
    textY += spacing_;
  }
  if (EgeStreamStyle::isVaild == true) { // recover color
    setcolor(tempC);
    EgeStreamStyle::isVaild = false;
  }
    setp(pbase(), pbase() + buf_size_);
    pbump(0);  // reset the pptr
    return 0;
}

int EgeStreamBuf::overflow(int c) {
    if (-1 == sync()) {
        return traits_type::eof();
    }
    else {
        if (!traits_type::eq_int_type(c, traits_type::eof())) {
            sputc(traits_type::to_char_type(c));
        }

        // return eq_int_type(c, eof()) ? eof():c;
        return traits_type::not_eof(c);
    }
}

int EgeStreamBuf::underflow() {
    // 从键盘输入数据
  int ret = buf_size_;
  std::string str;
  int textX = x_;
  do {
    char a = getch();
    if (a == 8&&!str.empty()) {
      color_t c = getfillcolor();
      setfillcolor(getbkcolor());
      bar(textX - 10, textY + spacing_, textX, textY);// 字间距
      textX -= 10;// 字间距
      str.erase(str.end() - 1);
      setfillcolor(c);
      continue;
    }
    str.push_back(a);
    if (a == 13)break;
    outtextxy(textX, textY, std::string{a}.c_str());
    textX += 10;// 字间距
    
  } while (1);
  textY += spacing_;
      strcpy_s(eback(), buf_size_,str.c_str());
    if (str.size()) {
        setg(eback(), eback(), eback() + ret);
        return traits_type::to_int_type(*gptr());
    } else {
        return traits_type::eof();
    }
    return 1;
}

BasicEgeStream::BasicEgeStream(int x, int y, int spacing,size_t buf_size):
    std::iostream(new EgeStreamBuf(x,y,buf_size,spacing)), buf_size_(buf_size){
}

BasicEgeStream::~BasicEgeStream() {
    delete rdbuf();
}




}  // EgeStream

