//
// Created by 86130 on 2023/12/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 交换数组中两个元素的值
void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

// 打印数组
void printArray(int arr[], int n) {
  for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

// 直接插入排序
void insertionSort(int arr[], int n, int *compCount, int *moveCount) {
  for (int i = 1; i < n; i++) {
    int key = arr[i];
    int j = i - 1;
    (*compCount)++;
    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      (*moveCount) += 3; // 移动次数包括交换3次
      j--;
    }
    arr[j + 1] = key;
  }
}

// 希尔排序
void shellSort(int arr[], int n, int *compCount, int *moveCount) {
  for (int gap = n / 2; gap > 0; gap /= 2) {
    for (int i = gap; i < n; i++) {
      int temp = arr[i];
      int j = i;
      (*compCount)++;
      while (j >= gap && arr[j - gap] > temp) {
        arr[j] = arr[j - gap];
        (*moveCount)++;
        j -= gap;
      }
      arr[j] = temp;
      (*moveCount)++;
    }
  }
}

// 冒泡排序
void bubbleSort(int arr[], int n, int *compCount, int *moveCount) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      (*compCount)++;
      if (arr[j] > arr[j + 1]) {
        swap(&arr[j], &arr[j + 1]);
        (*moveCount) += 3; // 移动次数包括交换3次
      }
    }
  }
}

// 快速排序
void quickSort(int arr[], int low, int high, int *compCount, int *moveCount) {
  if (low < high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
      (*compCount)++;
      if (arr[j] < pivot) {
        i++;
        swap(&arr[i], &arr[j]);
        (*moveCount) += 3;
      }
    }
    swap(&arr[i + 1], &arr[high]);
    (*moveCount) += 3;

    int partitionIndex = i + 1;
    quickSort(arr, low, partitionIndex - 1, compCount, moveCount);
    quickSort(arr, partitionIndex + 1, high, compCount, moveCount);
  }
}

// 简单选择排序
void selectionSort(int arr[], int n, int *compCount, int *moveCount) {
  for (int i = 0; i < n - 1; i++) {
    int minIndex = i;
    for (int j = i + 1; j < n; j++) {
      (*compCount)++;
      if (arr[j] < arr[minIndex]) {
        minIndex = j;
      }
    }
    swap(&arr[minIndex], &arr[i]);
    (*moveCount) += 3; // 移动次数包括交换3次
  }
}

// 堆排序
void heapify(int arr[], int n, int i, int *compCount, int *moveCount) {
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  (*compCount)++;
  if (left < n && arr[left] > arr[largest]) {
    largest = left;
  }

  (*compCount)++;
  if (right < n && arr[right] > arr[largest]) {
    largest = right;
  }

  if (largest != i) {
    swap(&arr[i], &arr[largest]);
    (*moveCount) += 3;
    heapify(arr, n, largest, compCount, moveCount);
  }
}

void heapSort(int arr[], int n, int *compCount, int *moveCount) {
  for (int i = n / 2 - 1; i >= 0; i--) {
    heapify(arr, n, i, compCount, moveCount);
  }

  for (int i = n - 1; i > 0; i--) {
    swap(&arr[0], &arr[i]);
    (*moveCount) += 3;
    heapify(arr, i, 0, compCount, moveCount);
  }
}

// 归并排序
void merge(int arr[], int l, int m, int r, int *compCount, int *moveCount) {
  int n1 = m - l + 1;
  int n2 = r - m;

  int L[n1], R[n2];

  for (int i = 0; i < n1; i++) {
    L[i] = arr[l + i];
  }
  for (int j = 0; j < n2; j++) {
    R[j] = arr[m + 1 + j];
  }

  int i = 0, j = 0, k = l;

  while (i < n1 && j < n2) {
    (*compCount)++;
    if (L[i] <= R[j]) {
      arr[k] = L[i];
      (*moveCount)++;
      i++;
    } else {
      arr[k] = R[j];
      (*moveCount)++;
      j++;
    }
    k++;
  }

  while (i < n1) {
    arr[k] = L[i];
    (*moveCount)++;
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = R[j];
    (*moveCount)++;
    j++;
    k++;
  }
}

void mergeSort(int arr[], int l, int r, int *compCount, int *moveCount) {
  if (l < r) {
    int m = l + (r - l) / 2;

    mergeSort(arr, l, m, compCount, moveCount);
    mergeSort(arr, m + 1, r, compCount, moveCount);

    merge(arr, l, m, r, compCount, moveCount);
  }
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// ...（前面的代码不变）

int main() {
  srand(time(NULL));

  int n = 100; // 表长
  int dataSets = 5; // 数据组数

  for (int i = 0; i < dataSets; i++) {
    int arr[n];
    for (int j = 0; j < n; j++) {
      arr[j] = rand() % 1000; // 生成0到999的随机数
    }

    int compCount, moveCount;

    // 测试并比较每个排序算法
    printf("数据集 %d:\n", i + 1);

    // 复制数组到临时数组
    int tempArr[n];
    memcpy(tempArr, arr, n * sizeof(int));

    // 插入排序
    compCount = 0;
    moveCount = 0;
    insertionSort(tempArr, n, &compCount, &moveCount);
    printf("插入排序: 比较次数：%d，移动次数：%d\n", compCount, moveCount);

    // 复制数组到临时数组
    memcpy(tempArr, arr, n * sizeof(int));

    // 希尔排序
    compCount = 0;
    moveCount = 0;
    shellSort(tempArr, n, &compCount, &moveCount);
    printf("希尔排序: 比较次数：%d，移动次数：%d\n", compCount, moveCount);

    // 复制数组到临时数组
    memcpy(tempArr, arr, n * sizeof(int));

    // 冒泡排序
    compCount = 0;
    moveCount = 0;
    bubbleSort(tempArr, n, &compCount, &moveCount);
    printf("冒泡排序: 比较次数：%d，移动次数：%d\n", compCount, moveCount);

    // 复制数组到临时数组
    memcpy(tempArr, arr, n * sizeof(int));

    // 快速排序
    compCount = 0;
    moveCount = 0;
    quickSort(tempArr, 0, n - 1, &compCount, &moveCount);
    printf("快速排序: 比较次数：%d，移动次数：%d\n", compCount, moveCount);

    // 复制数组到临时数组
    memcpy(tempArr, arr, n * sizeof(int));

    // 选择排序
    compCount = 0;
    moveCount = 0;
    selectionSort(tempArr, n, &compCount, &moveCount);
    printf("选择排序: 比较次数：%d，移动次数：%d\n", compCount, moveCount);

    // 复制数组到临时数组
    memcpy(tempArr, arr, n * sizeof(int));

    // 堆排序
    compCount = 0;
    moveCount = 0;
    heapSort(tempArr, n, &compCount, &moveCount);
    printf("堆排序: 比较次数：%d，移动次数：%d\n", compCount, moveCount);

    // 复制数组到临时数组
    memcpy(tempArr, arr, n * sizeof(int));

    // 归并排序
    compCount = 0;
    moveCount = 0;
    mergeSort(tempArr, 0, n - 1, &compCount, &moveCount);
    printf("归并排序: 比较次数：%d，移动次数：%d\n", compCount, moveCount);

    printf("\n");
  }

  return 0;
}