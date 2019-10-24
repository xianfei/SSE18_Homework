#include <iostream>
#include <stdexcept>

// 严蔚敏风格代码（手动doge

#define MAXSTRLEN 255 // 可以存储的最大长度
// （原来typedef还可以这么用
typedef unsigned char SString[MAXSTRLEN + 1];

// 重载流输出运算符，愉快的使用std::cout
std::ostream &operator<<(std::ostream &os, const SString &string) {
    // 输出该SString
    for(int i=1;i<=string[0];i++)os << string[i]; // 输出每个字符
    return os;
}

// 输入到SString，以回车结束，返回值为接受的字符数量
int sstringGetline(SString &string) {
    int i = 0;
    for(unsigned char c=0;i<MAXSTRLEN;i++){
        c=getchar();
        if(c=='\n')break;
        string[i + 1]=c;
    }
    string[i+1]=0; // 添加结尾'0'
    string[0] = i; // 设置长度位
    return i;
}

int Index(SString &S, SString &T, int pos = 1) {  // 暴力搜索
    // pos 越界检查
    if (pos < 1 || pos > S[0])
        throw std::out_of_range("argument \"pos\" out of range");
    int i = pos, j = 1;
    while (i <= S[0] && j <= T[0]) {
        if (S[i] == T[j])i++, j++;
        else {
            i = i - j + 2;
            j = 1;
        }
    }
    if (j > T[0]) return i - T[0];
    else return 0;
}

int main() {
    SString str1, str2;
    std::cout << "Please input main string:";
    sstringGetline(str1);
    std::cout << "Please input target string:";
    sstringGetline(str2);
    int result = Index(str1, str2, 1);
    if(result==0)
        std::cout << "Can't found the string \""<< str2 << "\" in \""<< str1 << "\"" << std::endl;
    else
        std::cout << "The string \""<< str2 << "\" in \""<< str1 <<
        "\" first appear at " << result << std::endl;
    return 0;
}