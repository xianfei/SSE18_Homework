//
// Created by 86130 on 2023/12/26.
//
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 20

typedef int KeyType;
typedef int InfoType; // 为了示例，将 InfoType 定义为 int 类型

// 记录类型
typedef struct
{
  KeyType key;        // 关键字项
  InfoType otherinfo; // 其它数据项，具体类型在主程中定义
} RedType;

// 顺序表类型
typedef struct
{
  RedType r[MAX_SIZE + 1]; // r[0] 闲置或用作哨兵单元
  int length;              // 顺序表长度
} SqList;

typedef SqList HeapType;

// 交换两个元素的值
void Swap(RedType *a, RedType *b)
{
  RedType temp = *a;
  *a = *b;
  *b = temp;
}

// 堆调整函数
void HeapAdjust(HeapType *H, int s, int m)
{
  RedType rc = H->r[s]; // 待调整的元素
  int j;

  //j = 2 * s 初始为左孩子节点
  for (j = 2 * s; j <= m; j *= 2)
  {
    // 选择左右孩子中较大的一个
    if (j < m && H->r[j].key < H->r[j + 1].key)
      j++;//j指向右孩子

    // 如果待调整元素的关键字大于等于其最大的孩子，则退出循环
    if (rc.key >= H->r[j].key)
      break;

    // 将较大的孩子上移
    H->r[s] = H->r[j];
    s = j;
  }

  // 将待调整元素放入最终位置
  H->r[s] = rc;
}

// 堆排序函数
void HeapSort(HeapType *H)
{
  int i;

  // 初始建堆，从最后一个非叶子节点开始
  for (i = H->length / 2; i > 0; i--)
    HeapAdjust(H, i, H->length);

  // 逐步将最大元素放到堆末尾，并重新调整堆
  for (i = H->length; i > 1; i--)
  {
    // 交换堆顶和堆末尾元素
    Swap(&(H->r[1]), &(H->r[i]));

    // 调整剩余部分为大顶堆
    HeapAdjust(H, 1, i - 1);
  }
}

int main()
{
  setbuf(stdout,NULL);
  // 示例数据
  HeapType H;
  H.length = 10;

  for (int i = 1; i <= H.length; i++)
  {
    H.r[i].key = rand() % 100; // 随机生成关键字
  }

  // 输出排序前的序列
  printf("排序前:\n");
  for (int i = 1; i <= H.length; i++)
  {
    printf("%d ", H.r[i].key);
  }
  printf("\n");

  // 堆排序
  HeapSort(&H);

  // 输出排序后的序列
  printf("排序后:\n");
  for (int i = 1; i <= H.length; i++)
  {
    printf("%d ", H.r[i].key);
  }
  printf("\n");

  return 0;
}