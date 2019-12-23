//
// Created by xianfei on 2019/12/23.
//

#ifndef EXPERIMENT_7_COMPARE_SORT_HPP
#define EXPERIMENT_7_COMPARE_SORT_HPP

#include <iostream>
#include <random>
#include <chrono>
#include "sort_functions.hpp"

// 创建一个对象用于记录移动次数和比较次数

static int comparedNum = 0, movedNum = 0;

struct IntObj {
    int key;

    bool operator>(const IntObj &d2) {
        ::comparedNum++;
        return this->key > d2.key;
    }

    bool operator<(const IntObj &d2) {
        ::comparedNum++;
        return this->key < d2.key;
    }

    void operator=(const IntObj &d2) {
        ::movedNum++;
        this->key = d2.key;
    }

    IntObj(const IntObj &d2) {
        ::movedNum++;
        this->key = d2.key;
    }

    IntObj(int data = 0) : key(data) {}

    friend std::ostream &operator<<(std::ostream &os, const IntObj &obj) {
        os << obj.key;
        return os;
    }
};

template<typename T>
void sort_output(SList<T> list, void (*fun)(SList<T> &)) {
    using namespace std::chrono;
    comparedNum = movedNum = 0;
    std::cout << "排序前：";
    for (int i = 1; i <= list.length(); i++)std::cout << list.R[i] << ' ';
    auto start = system_clock::now();
    fun(list); // 调用排序函数
    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    std::cout << "\n排序后：";
    for (int i = 1; i <= list.length(); i++)std::cout << list.R[i] << ' ';
    std::cout << '\n' << "共比较了" << comparedNum << "次，移动了" << movedNum << "次，花费了"
              << double(duration.count()) * microseconds::period::num / microseconds::period::den << "秒" << std::endl;
}


#endif //EXPERIMENT_7_COMPARE_SORT_HPP
