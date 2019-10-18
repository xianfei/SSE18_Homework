#include <iostream>
#include <stdexcept>
#include <sstream>

template<class T>
struct Stack {
    const int DEFAULT_SIZE = 10;
    T *array = (T *) malloc(DEFAULT_SIZE * sizeof(T));
    int size = 0;
    int capacity = DEFAULT_SIZE;

    T getTop() {
        if (size == 0)throw std::out_of_range("stack is empty");
        return array[size - 1];
    }

    void push(const T &num) {
        if (size >= capacity - 1) {
            array = (T *) realloc(array, 2 * capacity * sizeof(T));
            if (!array)throw std::overflow_error("stack overflow");
            capacity *= 2;
        }
        array[size++] = num;
    }

    T pop() {
        if (size == 0)throw std::out_of_range("stack is empty");
        return array[--size];
    }

    bool isEmpty() { return size == 0; }
};

int calcPostfix(const char* string){
    Stack<int> stack;
    std::stringstream sstr(string);
    std::string str;
    try {
        while (!sstr.eof()) {
            sstr >> str;
            int op1 = 0, op2 = 0;
            if (str[0] <= '0' || str[0] >= '9') {// 如果不是数字
                op2 = stack.pop();
                op1 = stack.pop();
                switch (str[0]) {
                    case '+':
                        stack.push(op1 + op2);
                        break;
                    case '-':
                        stack.push(op1 - op2);
                        break;
                    case '*':
                        stack.push(op1 * op2);
                        break;
                    case '/':
                        stack.push(op1 / op2);
                        break;
                    default:
                        throw std::exception();
                }
            } else {// 如果是数字
                stack.push(std::atoi(str.data())); // 转换为数字压入栈
            }
        }
        if (stack.size == 1)return stack.pop();
        else throw std::exception();
    }catch(std::exception &e){
        throw std::logic_error(std::string("illegal expression: ") + string);
    }
    return 0;
}

int main() {
    try {
        std::cout << calcPostfix("35 45 6 + -") << std::endl;
        std::cout << calcPostfix("1 4 * 2 /") << std::endl;
        std::cout << calcPostfix("1 - 4 * 2 / +") << std::endl;
    }catch(std::exception &e){
        std::cerr << e.what() << std::endl;
    }
    return 0;
}