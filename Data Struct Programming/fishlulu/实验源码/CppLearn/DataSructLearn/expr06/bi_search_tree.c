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
  // �Ӽ��̶�ȡһ������,ÿ������֮���ÿո����,����'#'��ֹ
  int num, index = 0;
  int nums[MAX_NODES];
  BiTree T = NULL;
  printf("������һ������,����'#'��ֹ:\n");

  while (1) {
    if (index >= MAX_NODES) {
      printf("�ﵽ���ڵ������ƣ��������롣\n");
      break;
    }

    if (scanf("%d", &num) == 1) {
      nums[index++] = num;
    } else {
      if (getchar() == '#') {
        printf("���������\n");
        break;
      }
      printf("��������Ч���֡�\n");
      // ������뻺����
      while (getchar() != '\n');
    }
  }

  if (index <= 0) {
    printf("δ������Ч���֣��޷�����������������\n");
    return 0;
  }
  T = bi_search_tree_build(nums, index);
  //���в���
  int target;
  // �Ӽ��̶�ȡһ������
  printf("������Ҫ���ҵ�����: ");
  scanf("%d", &target);
  bi_search_from_tree(T, target);
  return 0;
}
void bi_search_from_tree(BiTree T, int target) {
  int len = 0;//���ҳ���
  if (T == NULL) {
    printf("����������Ϊ�գ�����ʧ�ܡ�\n");
    return;
  }
  BiTree r = T;// rΪ��ǰ���бȽϵĸ��ڵ�
  while (1) {
    len ++;
    if (target < r->data) {
      if (r->lchild == NULL) {
        printf("����ʧ��,���ҳ���Ϊ%d\n",++len);
        break;
      } else {
        r = r->lchild;
      }
    } else if (target > r->data) {
      if (r->rchild == NULL) {
        printf("����ʧ��,���ҳ���Ϊ%d\n",++len);
        break;
      } else {
              r = r->rchild;
      }
    } else {
    printf("���ҳɹ�,���ҳ���Ϊ%d\n",len);
    break;
    }
  }
}

BiTree bi_search_tree_build(int *arr, int arr_len) {
  // �������ڵ�
  BiTree T = (BiTree)malloc(sizeof(BiTNode));
  T->data = arr[0];
  T->lchild = NULL;
  T->rchild = NULL;
  BiTree r = T; // rΪ��ǰ���бȽϵĸ��ڵ�

  // �ӵڶ����ڵ㿪ʼ����
  for (int i = 1; i < arr_len; ++i) {
    // �����½ڵ�
    BiTNode *p = (BiTNode *)malloc(sizeof(BiTNode));
    p->lchild = NULL;
    p->rchild = NULL;
    p->data = arr[i];
    while (1) {
      if (p->data < r->data) {
        if (r->lchild == NULL) {
          r->lchild = p;
          r = T; // ���ý��бȽϵĸ��ڵ�
          break;
        } else {
          r = r->lchild;
        }
      } else if (p->data > r->data) {
        if (r->rchild == NULL) {
          r->rchild = p;
          r = T; // ���ý��бȽϵĸ��ڵ�
          break;
        } else {
          r = r->rchild;
        }
      }
      // ������,�򲻲���
      else {
        break;
      }
    }
  }
  printf("�����������������\n");
  return T;
}
