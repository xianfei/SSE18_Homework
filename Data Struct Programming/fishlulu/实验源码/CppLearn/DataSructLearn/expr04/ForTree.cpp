//
// Created by 86130 on 2023/11/6.
//

//建立一颗二叉树,接受键盘输入,先序插入

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
  char data;
  struct node *lchild;
  struct node *rchild;
} node;

node* createNode() {
  node *pNode = (node *)malloc(sizeof(node));
  pNode->lchild = NULL;
  pNode->rchild = NULL;
  return pNode;
}
node* recurseBuild(char* str,int* index,int len)
{
  if(str[*index] == ' ' || str[*index] == '\0') {
    return NULL;
  }
  node* pNode = createNode();
  pNode->data = str[*index];
  (*index)++;
  if(*index == len) {
    return pNode;
  }
  pNode->lchild = recurseBuild(str,index,len);
  (*index)++;
  if(*index == len) {
    return pNode;
  }
  pNode->rchild = recurseBuild(str, index,len);
  return pNode;
}
// 从键盘持续读取字符,先序方式插入二叉树,读取到#或者null为止
node* buildTreeWithString(char* str) {

  if(*str == ' ' || *str == '\0') {
    return NULL;
  }
  int *index = (int *)malloc(sizeof(int));
  (*index)=0;
  int len = strlen(str);
  node* root = createNode();
  root->data = str[*index];
  (*index)++;
  root->lchild = recurseBuild(str,index,len);
  (*index)++;
  root->rchild = recurseBuild(str,index,len);
  return root;
}
//前序遍历二叉树
void preOrder(node* root) {
  if(root == NULL) {
    return;
  }
  printf("%c",root->data);
  preOrder(root->lchild);
  preOrder(root->rchild);
}
//中序遍历二叉树
void inOrder(node* root) {
  if(root == NULL) {
    return;
  }
  inOrder(root->lchild);
  printf("%c",root->data);
  inOrder(root->rchild);
}
//后序遍历二叉树
void postOrder(node* root) {
  if(root == NULL) {
    return;
  }
  postOrder(root->lchild);
  postOrder(root->rchild);
  printf("%c",root->data);
}

void printTreeWithDepth(node* root,int* depth)
{
        if(root == NULL) {
//          printf("\n");
          return;
        }
        (*depth)++;
        printTreeWithDepth(root->rchild,depth);
        for (int i = 0; i < (*depth); ++i) {
          printf(" ");
        }
        printf("%c\n",root->data);
        printTreeWithDepth(root->lchild,depth);
        (*depth)--;
}
//按凹入表打印二叉树
void printTree(node* root)
{
  int* depth = (int*)malloc(sizeof(int));
  (*depth) = 0;

  if(root == NULL) {
    printf("Tree is Empty");
    return;
  }
  printTreeWithDepth(root->rchild,depth);
  printf("%c\n",root->data);
  printTreeWithDepth(root->lchild,depth);


}
int main(){
//        char str[100];
//        scanf("%s",str);
        char* str_test = "AB D  CE F   ";
        node* root = buildTreeWithString(str_test);

//        //前序中序后序遍历
//        printf("PreOrder:");
//        preOrder(root);
//        printf("\n");
//        printf("InOrder:");
//        inOrder(root);
//        printf("\n");
//        printf("postOrder:");
//        postOrder(root);
        //凹入表打印二叉树
        printTree(root);
        return 0;
}
