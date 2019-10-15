#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <graphics.h>

//  Version 0.4 By Xianfei (王衔飞) SSE of BUPT  2019.5
// 
//  参考资料： 

//  https://zh.cppreference.com/w/cpp/io/basic_ostream/operator_ltlt2
//  C++ 之定制输入输出流 http://kaiyuan.me/2017/06/22/custom-streambuf/

namespace EgeStream {

// for control the style of output stream


struct EgeStreamStyle {
    color_t c_;
    //color_t unchanged_c_;
    static color_t outC;
    static bool isVaild;
  EgeStreamStyle(color_t c);
  friend std::ostream& operator<<(std::ostream& os, EgeStreamStyle s);
};

// a simple stream buf for ege output stream
class EgeStreamBuf : public std::streambuf {
public:
    EgeStreamBuf(int x, int y,size_t buf_size, int spacing);
    ~EgeStreamBuf();

    int underflow();
    int overflow(int c);
    int sync();

private:
    const size_t buf_size_;
    int spacing_;
    char* pbuf_;
    char* gbuf_;
    int x_;
    static int textY;
};


class BasicEgeStream : public std::iostream {
public:
    BasicEgeStream(int x=5,int y=5, int spacing = 25,size_t buf_size = 100);
    ~BasicEgeStream();
    EgeStreamStyle red{ 0xff0000 };
    EgeStreamStyle blue{ 0x2cb6f0 };
    EgeStreamStyle white{ 0xffffff };
    EgeStreamStyle pink{ 0xf859ab };
    EgeStreamStyle orange{ 0xfd9940 };
    EgeStreamStyle yellow{ 0xfde540 };
    EgeStreamStyle green{ 0x6dec4b };
    EgeStreamStyle purple{ 0xa24bec };
private:
    const size_t buf_size_;
};

}  
