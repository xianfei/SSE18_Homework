#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <fstream>

std::string inputStr;// 输入字符串
int index_;// 输入符号读入字符的位置
int line = 1;// 行数
int id_word_num = 0;// id个数
int ch_num = 0;// 字符个数
int num_word_num = 0;// 数字个数
int keyword_num = 0;// 关键字个数
int bound_word_num = 0;// 边界符号个数
int operater_word_num = 0;// 操作数个数
char character;// 最新读入的字符
std::string token;// 已读入的字符
std::map<std::string, int> id;// 标识符集
// 语言保留关键字表
std::string keyWords[64] = {
        "auto", "double", "int", "struct", "break", "else", "long", "switch", "case", "enum", "register", "typedef",
        "char", "extern", "return", "union", "const", "float", "short", "unsigned", "continue", "for", "signed", "void",
        "default", "goto", "sizeof", "volatile", "do", "if", "while", "static", "extend", "read", "write", "bool",
        "catch", "class", "delete", "false", "true", "friend", "inline", "new", "private", "protected", "public",
        "this", "try", "using", "virtual", "include"
};
// 分界符表
std::string boundaries[200] = {
        "{", "}", "[", "]", ";", ",", ".", "(", ")", ":", "/*", "#", "*/", "//", "\"", "'"
};
// 运算符表
std::string operators[300] = {
        "+", "-", "*", "/", "%", ">", "<", ">=", "<=", "==", "-=", "+=", "*=", "/=", "!=", "=", "%=", "&", "&&", "|",
        "||", "!", "++", "--", "~", "<<", ">>", "?"
};

struct WordInfo {
    int type_id_ = 0; // 分类 -1为标识符  -2为数值 0-63存储保留字 64-127存储分界符  128-255存储运算符 -3为错误
    int index = 0; // 如果是标识符则存储标识符下标
    std::string value = "-"; // 存储字符串

    WordInfo(int c, int i, std::string v) {
        type_id_ = c;
        index = i;
        value = move(v);
    }
};


void getChar() {// 读取单个字符
    character = inputStr[index_++];
}

void get_not_blank_char() {// 读入非空白字符串
    while (character == ' ' || character == '\t') {
        getChar();
    }
}

void concat() {// 连接字符串
    token = token + character;
}

bool is_letter() {// 判断是否字母
    if ((character >= 'A' && character <= 'Z') || (character >= 'a' && character <= 'z'))
        return true;
    return false;
}

bool is_digit() {// 判断是否数字
    if (character >= '0' && character <= '9')
        return true;
    return false;
}

void retract() {// 回退
    character = ' ';
    index_--;
}

int keyword_map() {// 匹配保留字符
    for (int i = 0; i < 55; i++)
        if (keyWords[i] == (token))
            return i;
    return -1;
}

int id_map() {  // 对符号表进行查找  有则返回之前的，没有则创建新的
    if (id.count(token) == 1)
        return id[token];
    else {
        id[token] = (id.size() + 1);
        return id[token];
    }
}

// 连接数字
bool continue_int_map() {
    if (is_digit()) {
        concat();
        ch_num++;
        getChar();
        while (is_digit()) {
            concat();
            ch_num++;
            getChar();
        }
        retract();
        return true;
    } else {
        retract();
        return false;
    }
}

// 错误处理
WordInfo error() {
    std::cerr << "位于第" << line << "行 字符串\"" << token << "\"无法解析" << std::endl;
    return WordInfo(-3, line, "-");
}

// 处理科学计数法
WordInfo integer_after_E_map() {
    concat();
    ch_num++;
    getChar();
    if (character == '+' || character == '-') {
        concat();
        ch_num++;
        getChar();
    }

    if (continue_int_map()) {
        return WordInfo(-2, -1, token);
    } else {
        return error();
    }

}

// 跳转到下一个该字符，用于处理注释等
void jump(char s) {
    while (true) {
        if (character == s) {
            if (s == '\n')
                line++;
            else
                ch_num++;
            return;
        } else if (character == '\n')
            line++;
        else {
            ch_num++;
        }
        getChar();
    }
}


WordInfo Analyzer() {// 词法分析程序
    token = "";
    getChar();
    get_not_blank_char();
    std::string val;
    int num = -1;
    switch (character) {
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
        case 'g':
        case 'h':
        case 'i':
        case 'j':
        case 'k':
        case 'l':
        case 'm':
        case 'n':
        case 'o':
        case 'p':
        case 'q':
        case 'r':
        case 's':
        case 't':
        case 'u':
        case 'v':
        case 'w':
        case 'x':
        case 'y':
        case 'z':
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
        case 'G':
        case 'H':
        case 'I':
        case 'J':
        case 'K':
        case 'L':
        case 'M':
        case 'N':
        case 'O':
        case 'P':
        case 'Q':
        case 'R':
        case 'S':
        case 'T':
        case 'U':
        case 'V':
        case 'W':
        case 'X':
        case 'Y':
        case 'Z':
            while (is_letter() || is_digit()) {// 为字母或数字
                concat();
                ch_num++;
                getChar();
            }
            retract();
            num = keyword_map();
            if (num != -1) {
                return WordInfo(num, 0, "-");
            } else {
                val = token;
                return WordInfo(-1, id_map(), val);
            }
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            while (is_digit()) {
                concat();
                ch_num++;
                getChar();
            }
            // 处理小数点
            if (character == '.') {
                concat();
                ch_num++;
                getChar();

                if (!continue_int_map()) {
                    return error();
                }
                getChar();
            }
            // 处理科学计数法
            if (character == 'E') {
                return integer_after_E_map();
            } else {
                retract();
                return WordInfo(-2, -1, token);
            }

        case '{':
            ch_num++;
            return WordInfo(64, -1, "-");
        case '}':
            ch_num++;
            return WordInfo(65, -1, "-");
        case '[':
            ch_num++;
            return WordInfo(66, -1, "-");
        case ']':
            ch_num++;
            return WordInfo(67, -1, "-");
        case ';':
            ch_num++;
            return WordInfo(68, -1, "-");
        case ',':
            ch_num++;
            return WordInfo(69, -1, "-");
        case '.':
            ch_num++;
            return WordInfo(70, -1, "-");
        case '(':
            ch_num++;
            return WordInfo(71, -1, "-");
        case ')':
            ch_num++;
            return WordInfo(72, -1, "-");
        case ':':
            ch_num++;
            return WordInfo(73, -1, "-");
        case '/':
            ch_num++;
            getChar();
            if (character == '*') {
                ch_num++;
                getChar();
                jump('*');
                getChar();
                while (character != '/') {
                    jump('*');
                    getChar();
                }
                ch_num++;
                return WordInfo(74, -1, "-");
            } else if (character == '=') {
                ch_num++;
                return WordInfo(141, -1, "-");
            } else if (character == '/') {
                ch_num++;
                getChar();
                jump('\n');
                return WordInfo(77, -1, "-");
            } else {
                retract();
                return WordInfo(131, -1, "-");
            }
        case '#':
            ch_num++;
            return WordInfo(75, -1, "-");
        case '"':
            ch_num++;
            return WordInfo(78, -1, "-");
        case '\'':
            ch_num++;
            return WordInfo(79, -1, "-");
        case '*':
            ch_num++;
            getChar();
            if (character == '/') {
                ch_num++;
                return WordInfo(76, -1, "-");
            } else if (character == '=') {
                ch_num++;
                return WordInfo(140, -1, "-");
            } else {
                retract();
                return WordInfo(130, -1, "-");
            }
        case '+':
            ch_num++;
            getChar();
            if (character == '=') {
                ch_num++;
                return WordInfo(139, -1, "-");
            } else if (character == '+') {
                ch_num++;
                return WordInfo(150, -1, "-");
            } else {
                retract();
                return WordInfo(128, -1, "-");
            }
        case '-':
            ch_num++;
            getChar();
            if (character == '=') {
                ch_num++;
                return WordInfo(138, -1, "-");
            } else if (character == '-') {
                ch_num++;
                return WordInfo(151, -1, "-");
            } else {
                retract();
                return WordInfo(129, -1, "-");
            }
        case '%':
            ch_num++;
            getChar();
            if (character == '=') {
                ch_num++;
                return WordInfo(144, -1, "-");
            } else {
                retract();
                return WordInfo(132, -1, "-");
            }
        case '>':
            ch_num++;
            getChar();
            if (character == '=') {
                ch_num++;
                return WordInfo(135, -1, "GE");
            } else if (character == '>') {
                ch_num++;
                return WordInfo(154, -1, "-");
            } else {
                retract();
                return WordInfo(133, -1, "GT");
            }
        case '<':
            ch_num++;
            getChar();
            if (character == '=') {
                ch_num++;
                return WordInfo(136, -1, "LE");
            } else if (character == '<') {
                ch_num++;
                return WordInfo(153, -1, "-");
            } else {
                retract();
                return WordInfo(134, -1, "LT");
            }
        case '=':
            ch_num++;
            getChar();
            if (character == '=') {
                ch_num++;
                return WordInfo(137, -1, "EQ");
            } else {
                retract();
                return WordInfo(143, -1, "assign-op");
            }
        case '!':
            ch_num++;
            getChar();
            if (character == '=') {
                ch_num++;
                return WordInfo(142, -1, "NE");
            } else {
                retract();
                return WordInfo(149, -1, "-");
            }
        case '&':
            ch_num++;
            getChar();
            if (character == '&') {
                ch_num++;
                return WordInfo(146, -1, "-");
            } else {
                retract();
                return WordInfo(145, -1, "-");
            }
        case '|':
            ch_num++;
            getChar();
            if (character == '|') {
                ch_num++;
                return WordInfo(148, -1, "-");
            } else {
                retract();
                return WordInfo(147, -1, "-");
            }
        case '~':
            ch_num++;
            return WordInfo(152, -1, "-");
        case '?':
            ch_num++;
            return WordInfo(155, -1, "-");
        case '@':
            return WordInfo(-3, -1, "-");
        case '\n':
            line++;
            return WordInfo(-3, -1, "-");

        default:
            concat();
            ch_num++;
            return error();
    }
}

int main() {
    std::cout << "请输入文件路径" << std::endl;
    std::string path;
    std::cin >> path;
    std::ifstream file(path);
    if (!file.good()) {
        std::cerr << "文件无法打开！";
        return 0;
    }
    inputStr = std::string((std::istreambuf_iterator<char>(file)),
                      std::istreambuf_iterator<char>());
    // 删除'\r'解决文件换行符同时出现\n\r的问题
    inputStr.erase(std::remove(inputStr.begin(), inputStr.end(), '\r'), inputStr.end());
    id.clear();
    index_ = 0;
    character = ' ';
    token = "";

    WordInfo word = WordInfo(0, 0, "-");
    // 循环进行词法分析直到识别所有单词符号
    std::cout << std::string(12,'-') << "识别结果" <<  std::string(12,'-') << std::endl;
    while (index_ < inputStr.length()) {
        word = Analyzer();
        if (word.type_id_ == -2) {
            // 数值
            num_word_num++;
            std::cout.setf(std::ios::left);
            std::cout.width(15);
            std::cout << word.value << "\t<num , " << word.value << ">" << std::endl;
        } else if (word.type_id_ == -1) {
            // 标识符
            id_word_num++;
            std::cout.setf(std::ios::left);
            std::cout.width(15);
            std::cout << word.value << "\t<id , " << word.index << ">" << std::endl;
        } else if (word.type_id_ >= 0 && word.type_id_ <= 63) {
            // 关键字
            keyword_num++;
            std::cout.setf(std::ios::left);
            std::cout.width(15);
            std::cout << keyWords[word.type_id_] << "\t<" << keyWords[word.type_id_] << " , " << word.value << ">" << std::endl;
        } else if (word.type_id_ >= 64 && word.type_id_ <= 127) {
            // 边界
            bound_word_num++;
            std::cout.setf(std::ios::left);
            std::cout.width(15);
            std::cout << boundaries[word.type_id_ - 64] << "\t<" << boundaries[word.type_id_ - 64] << " , " << word.value << ">"
                 << std::endl;
            if (word.type_id_ == 74) { // 处理 /* */
                bound_word_num++;
                std::cout.setf(std::ios::left);
                std::cout.width(15);
                std::cout << boundaries[76 - 64] << "\t<" << boundaries[76 - 64] << " , " << word.value << ">" << std::endl;

            }
        } else if (word.type_id_ >= 128 && word.type_id_ <= 255) {
            // 操作符
            operater_word_num++;
            std::cout.setf(std::ios::left);
            std::cout.width(15);
            if (word.value == "-")
                std::cout << operators[word.type_id_ - 128] << "\t<" << operators[word.type_id_ - 128] << " , " << word.value
                     << ">"
                     << std::endl;
            else if (word.value == "assign-op")
                std::cout << operators[word.type_id_ - 128] << "\t<assign-op , ->" << std::endl;
            else
                std::cout << operators[word.type_id_ - 128] << "\t<relop , " << word.value << ">" << std::endl;
        } else if (word.type_id_ == -3) {

        }
    }
    std::cout << "\n总行数：\t" << (line - 1) << "\t字符总数：\t" << ch_num << std::endl;
    std::cout << "\n各类单词个数：";
    std::cout << "id数量:\t" << id_word_num << std::endl;
    std::cout << "数字数量:\t" << num_word_num << std::endl;
    std::cout << "关键字数量:\t" << keyword_num << std::endl;
    std::cout << "分隔符数量:\t" << bound_word_num << std::endl;
    std::cout << "操作符数量:\t" << operater_word_num << std::endl;
    return 0;
}
