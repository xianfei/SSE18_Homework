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

    T &operator[](int index) {
        return R[index + 1];
    }
};

template<typename T>
void InsertSort(SList<T> &L) {
    for (int i = 2; i <= L.length(); i++)
        if (L.R[i] < L.R[i - 1]) {
            L.R[0] = L.R[i];
            int j;
            for (j = i - 1; L.R[0] < L.R[j]; j--)
                L.R[j + 1] = L.R[j]; //从当前要插入的 元素的前一个元素开始，如果比哨兵小就记录后移
            L.R[j + 1] = L.R[0]; //比较结束，将待插元素插入到正确位置
        }
}

template<typename T>
void ShellSort(SList<T> &L) {
    // 2^k+1
    int k = log2(L.length());
    for (int n = k; n > 0; n--) {
        int dk = pow(2, n) - 1;
        for (int i = dk + 1; i <= L.length(); i++)
            if (L.R[i] < L.R[i - dk]) {
                L.R[0] = L.R[i];
                int j;
                for (j = i - dk; j > 0 && L.R[0] < L.R[j]; j -= dk)
                    L.R[j + dk] = L.R[j]; //从当前要插入的 元素的前一个元素开始，如果比哨兵小就记录后移
                L.R[j + dk] = L.R[0]; //比较结束，将待插元素插入到正确位置
            }
    }
//    for(int i=L.length();i>0;i/=3)ShellSort_(L,i);
}

template<typename T>
void BubbleSort(SList<T> &L) { // 将a中整数序列重新排列成自小至大有序的整数序列(起泡排序)
    bool change = true;//是否有交换的标志
    for (int i = L.length(); i > 1 && change; --i) { //控制最后一个每趟比较的元素
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

namespace innerFunction { // 快速排序调用的内部函数
    template<typename T>
    inline int Partition(SList<T> &L, int low, int high) {
        L.R[0] = L.R[low];
        auto pivotkey = L.R[low]; // pivot
        while (low < high) {
            while (low < high && !(L.R[high] < pivotkey))
                --high; // From right to left
            L.R[low] = L.R[high];
            while (low < high && !(L.R[low] > pivotkey))
                ++low; // From left to right
            L.R[high] = L.R[low];
        }
        L.R[low] = L.R[0];
        return low;
    }// Partition

    template<typename T>
    inline void QSort(SList<T> &L, int s, int t) { // Quick sort R[s..t]
        if (s < t) {
            // length is more then 1
            int pivotloc = Partition(L, s, t);
            // first time partitioning R[s..t]
            QSort(L, s, pivotloc - 1);
            // For low sequence sorting，pivotloc is pivot position
            QSort(L, pivotloc + 1, t); // Quick sort high sequence
        }
    } // QSort
}

template<typename T>
void QuickSort(SList<T> &L) {
    innerFunction::QSort(L, 1, L.length());
}

template<typename T>
void SelectionSort(SList<T> &L) {
    for (int i = 1; i <= L.length(); i++) {
        int minEle = i;
        for (int j = i; j <= L.length(); j++)if (L.R[j] < L.R[minEle])minEle = j;
        T temp = L.R[i];
        L.R[i] = L.R[minEle];
        L.R[minEle] = temp;
    }
}

namespace innerFunction { // 堆排序调用的内部函数
    template<typename T>
    inline void HeapAdjust(SList<T> &H, int s, int m) { //已知H.r[s..m]中除H.r[s]外均满足堆定义,
        // 本函数将H.r[s..m]调整为大顶堆.
        auto rc = H.R[s];
        for (int j = 2 * s; j <= m; j *= 2) { //沿key较大的子结点向下筛选
            if (j < m && !(H.R[j] > H.R[j + 1]))
                j++; //j为key较大的记录的下标
            if (!(rc < H.R[j])) break;
            H.R[s] = H.R[j];
            s = j;
        }
        H.R[s] = rc;
    }
}

template<typename T>
void HeapSort(SList<T> &H) {
    for (int i = H.length() / 2; i > 0; i--)
        innerFunction::HeapAdjust(H, i, H.length()); //把H.r[1..H.length]建成最大堆
    for (int i = H.length(); i > 1; i--) {
        auto temp = H.R[1];
        H.R[1] = H.R[i];
        H.R[i] = temp;
        innerFunction::HeapAdjust(H, 1, i - 1);
    }
}

namespace innerFunction {
    template<typename T>
    void merge(SList<T> &a, int lo, int mid, int hi, SList<T> &aux) {
        int i = lo, j = mid + 1;
        for (int k = lo; k <= hi; k++) {
            aux.R[k] = a.R[k];
        }
        for (int k = lo; k <= hi; k++) {
            if (i > mid) { a.R[k] = aux.R[j++]; }
            else if (j > hi) { a.R[k] = aux.R[i++]; }
            else if (aux.R[j] < aux.R[i]) { a.R[k] = aux.R[j++]; }
            else { a.R[k] = aux.R[i++]; }
        }
    }

    template<typename T>
    void mergesort(SList<T> &a, int lo, int hi, SList<T> &newList) {
        if (lo >= hi) return;
        int mid = lo + (hi - lo) / 2;
        mergesort(a, lo, mid, newList);
        mergesort(a, mid + 1, hi, newList);
        merge(a, lo, mid, hi, newList);
    }

}


template<typename T>
void MergeSort(SList<T> &a) {
    SList<T> newList = a;
    innerFunction::mergesort(a, 0, a.length(), newList);
}


#endif //EXPERIMENT_7_SORT_FUNCTIONS_HPP
