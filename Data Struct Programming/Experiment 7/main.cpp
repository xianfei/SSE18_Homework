#include <iostream>
#include <random>
#include "sort_functions.hpp"

// 创建一个对象用于记录移动次数和比较次数
struct IntObj {
    int key;
    int comparedNum = 0, movedNum = 0;
    bool operator>(IntObj &d2) {
        comparedNum++;
        return this->key > d2.key;
    }
    bool operator<(IntObj &d2) {
        comparedNum++;
        return this->key < d2.key;
    }
    void operator=(IntObj &d2) {
        movedNum++;
        this->key = d2.key;
    }
    IntObj(int data = 0) : key(data) {}
    friend std::ostream &operator<<(std::ostream &os, const IntObj &obj) {
        os <<  obj.key;
        return os;
    }
};

template<typename T>
void sort_output(SList<T> list, void (*fun)(SList<T>&)){
    std::cout << "排序前：";
    for (int i = 1; i <= list.length(); i++)std::cout << list.R[i] << ' ';
    fun(list); // 调用排序函数
    std::cout << "\n排序后：";
    for (int i = 1; i <= list.length(); i++)std::cout << list.R[i] << ' ';
    int comparedSum=0,movedSum=0;
    for (int i = 0; i <= list.length(); i++){
        comparedSum+=list.R[i].comparedNum;
        movedSum+=list.R[i].movedNum;
    }
    std::cout << '\n' << "共比较了" << comparedSum << "次，移动了" << movedSum << "次" << std::endl;
}

int main() {
    // 创建随机数生成器
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(1, 10000);
    SList<IntObj> list;
    // 填充100个随机数
    std::cout << "在1-10000范围随机填充100个数\n";
    for (int i = 0; i < 10; ++i) list.R.emplace_back(uniform_dist(e1));

    std::cout << "\n插入排序：\n";
    sort_output(list,InsertSort);

    std::cout << "\n冒泡排序：\n";
    sort_output(list,BubbleSort);

    std::cout << "\n快速排序：\n";
    sort_output(list,QuickSort);

    return 0;
}
