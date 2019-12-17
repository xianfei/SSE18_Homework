//
// Created by xianfei on 2019/12/17.
//

#ifndef EXPERIMENT_7_SORT_FUNCTIONS_HPP
#define EXPERIMENT_7_SORT_FUNCTIONS_HPP

#include <vector>
#include <iostream>

template<typename T>
struct SList {
    std::vector<T> R{0};
    int length() { return R.size() - 1; }
};

template<typename T>
void InsertSort(SList<T> &L) {
    for (int i = 2; i <= L.length(); i++)
        if (L.R[i] < L.R[i - 1]){
            L.R[0] = L.R[i];
            int j;
            for (j = i - 1; L.R[0] < L.R[j]; j--)
                L.R[j + 1] = L.R[j]; //从当前要插入的 元素的前一个元素开始，如果比哨兵小就记录后移
            L.R[j + 1] = L.R[0]; //比较结束，将待插元素插入到正确位置
        }
}

template<typename T>
void BubbleSort(SList<T> &L) { // 将a中整数序列重新排列成自小至大有序的整数序列(起泡排序)
    bool change = true;//是否有交换的标志
    for (int i = L.length(); i > 1 && change; --i){ //控制最后一个每趟比较的元素
        change = false;//一趟交换前把交换标志清0
        for (int j = 0; j < i; ++j)//从第0个元素开始一趟交换
            if (L.R[j] > L.R[j + 1]) {
                L.R[0] = L.R[j];
                L.R[j] = L.R[j + 1];
                L.R[j + 1] = L.R[0];
                change = true;
            }
    }
}

template<typename T>
void QuickSort(SList<T> &L) {

}

#endif //EXPERIMENT_7_SORT_FUNCTIONS_HPP
