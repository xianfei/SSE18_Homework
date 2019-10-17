#include <iostream>
#include <stdexcept>

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

bool isMatched(const char *str) {
    Stack<char> s;
    for (; *str; str++) {
        switch (*str) {
            case '(':
            case '[':
                s.push(*str);
                break;
            case ')':
                if (s.pop() != '(')return false;
                break;
            case ']':
                if (s.pop() != '[')return false;
                break;
            default:
                throw std::logic_error("illegal expression");
        }
    }
    return s.isEmpty();
}

int main() {
    try {
        std::cout << std::boolalpha << "([]()) :" << isMatched("([]())") << std::endl;
        std::cout << std::boolalpha << "[()] :" << isMatched("[()]") << std::endl;
        std::cout << std::boolalpha << "[()](( :" << isMatched("[()]((") << std::endl;
        std::cout << std::boolalpha << "(]()) :" << isMatched("(]())") << std::endl;
        std::cout << std::boolalpha << "empty string :" << isMatched("") << std::endl;
        std::cout << std::boolalpha << "({-}) :" << isMatched("({-})") << std::endl;
    } catch (std::exception &e) { std::cout << e.what(); }
    return 0;
}