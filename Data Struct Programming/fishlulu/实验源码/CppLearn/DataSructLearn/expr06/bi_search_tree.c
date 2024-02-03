#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 30

typedef struct BiTNode {
  int data;
  struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

BiTree bi_search_tree_build(int *arr, int arr_len);
void bi_search_from_tree(BiTree pNode, int target);


int main() {
  // 从键盘读取一串数字,每个数字之间用空格隔开,输入'#'终止
  int num, index = 0;
  int nums[MAX_NODES];
  BiTree T = NULL;
  printf("请输入一串数字,输入'#'终止:\n");

  while (1) {
    if (index >= MAX_NODES) {
      printf("达到最大节点数限制，结束输入。\n");
      break;
    }

    if (scanf("%d", &num) == 1) {
      nums[index++] = num;
    } else {
      if (getchar() == '#') {
        printf("输入结束。\n");
        break;
      }
      printf("请输入有效数字。\n");
      // 清除输入缓冲区
      while (getchar() != '\n');
    }
  }

  if (index <= 0) {
    printf("未输入有效数字，无法建立二叉排序树。\n");
    return 0;
  }
  T = bi_search_tree_build(nums, index);
  //进行查找
  int target;
  // 从键盘读取一个数字
  printf("请输入要查找的数字: ");
  scanf("%d", &target);
  bi_search_from_tree(T, target);
  return 0;
}
void bi_search_from_tree(BiTree T, int target) {
  int len = 0;//查找长度
  if (T == NULL) {
    printf("二叉排序树为空，查找失败。\n");
    return;
  }
  BiTree r = T;// r为当前进行比较的根节点
  while (1) {
    len ++;
    if (target < r->data) {
      if (r->lchild == NULL) {
        printf("查找失败,查找长度为%d\n",++len);
        break;
      } else {
        r = r->lchild;
      }
    } else if (target > r->data) {
      if (r->rchild == NULL) {
        printf("查找失败,查找长度为%d\n",++len);
        break;
      } else {
              r = r->rchild;
      }
    } else {
    printf("查找成功,查找长度为%d\n",len);
    break;
    }
  }
}

BiTree bi_search_tree_build(int *arr, int arr_len) {
  // 创建根节点
  BiTree T = (BiTree)malloc(sizeof(BiTNode));
  T->data = arr[0];
  T->lchild = NULL;
  T->rchild = NULL;
  BiTree r = T; // r为当前进行比较的根节点

  // 从第二个节点开始遍历
  for (int i = 1; i < arr_len; ++i) {
    // 创建新节点
    BiTNode *p = (BiTNode *)malloc(sizeof(BiTNode));
    p->lchild = NULL;
    p->rchild = NULL;
    p->data = arr[i];
    while (1) {
      if (p->data < r->data) {
        if (r->lchild == NULL) {
          r->lchild = p;
          r = T; // 重置进行比较的根节点
          break;
        } else {
          r = r->lchild;
        }
      } else if (p->data > r->data) {
        if (r->rchild == NULL) {
          r->rchild = p;
          r = T; // 重置进行比较的根节点
          break;
        } else {
          r = r->rchild;
        }
      }
      // 如果相等,则不插入
      else {
        break;
      }
    }
  }
  printf("二叉排序树建立完成\n");
  return T;
}
