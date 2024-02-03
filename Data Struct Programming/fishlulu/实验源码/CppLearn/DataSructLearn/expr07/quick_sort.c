#include <stdio.h>
#include <stdlib.h>

#define Maxsize 100

typedef int elemtype;

typedef struct {
  int key; // 表示排序关键字
} RedType;

typedef struct {
  RedType r[Maxsize + 1]; // 存放待排序全体记录
  int length; // 排序记录个数
} SqList;

int Partition(RedType R[], int low, int high) {
  // 划分过程
  R[0] = R[low];
  int pivotkey = R[low].key; // 枢轴

  while (low < high) {
    while (low < high && R[high].key >= pivotkey)
      --high; // 从右向左扫描
    R[low] = R[high];

    while (low < high && R[low].key <= pivotkey)
      ++low; // 从左向右扫描
    R[high] = R[low];
  }

  R[low] = R[0];
  return low;
}

void QSort(RedType R[], int s, int t) {
  // 快速排序 R[s..t]
  if (s < t) { // 长度大于1
    // 第一次划分
    int pivotloc = Partition(R, s, t);
    // 低序列排序，pivotloc 是枢轴位置
    QSort(R, s, pivotloc - 1);
    // 高序列快速排序
    QSort(R, pivotloc + 1, t);
  }
} // QSort

void QuickSort(SqList *L) {
  // Sorting sequence table
  QSort(L->r, 1, L->length);
} // QuickSort

int main() {
  setbuf(stdout,NULL);
  // 1-10随机数字组成SqList
  SqList L;
  L.length = 10;
  for (int i = 1; i <= L.length; i++) {
    L.r[i].key = rand() % 10 + 1;
  }
  // 输出SqList
  printf("排序前:\n");
  for (int i = 1; i <= L.length; i++) {
    printf("%d ", L.r[i].key);
  }
  printf("\n");
  // 快速排序
  QuickSort(&L);
  // 输出SqList
  printf("排序后:\n");
  for (int i = 1; i <= L.length; i++) {
    printf("%d ", L.r[i].key);
  }

  return 0;
}
