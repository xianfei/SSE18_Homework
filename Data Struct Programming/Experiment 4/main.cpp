#include <iostream>
#include <stdexcept>
#include "stack.hpp"

template<typename Type>
struct BiTree {
    Type data;
    BiTree *lchild = nullptr, *rchild = nullptr;
};

// 将数组转化为指针
template<typename Type,typename T>
void createBiTree(BiTree<Type> *&biTreePtr, T ptr_) {
    const Type* ptr=ptr_;
    createBiTree(biTreePtr,ptr);
}

template<typename Type>
void createBiTree(BiTree<Type> *&biTreePtr, const Type *&arrayPtr) {
    if (!*arrayPtr)return;
    if (*arrayPtr == '#') {
        arrayPtr++;
        return;
    } else {
        if (!biTreePtr)biTreePtr = new BiTree<Type>;
        biTreePtr->data = *arrayPtr;
        arrayPtr++;
    }
    createBiTree(biTreePtr->lchild, arrayPtr);
    createBiTree(biTreePtr->rchild, arrayPtr);
}

// 前序遍历（参数：二叉树的指针，遍历执行函数指针）
template<typename Type, typename FunPtr>
void preOrderTraverse(BiTree<Type> *biTreePtr, FunPtr fun) {
    if (biTreePtr == nullptr) return;
    fun(biTreePtr->data);
    preOrderTraverse(biTreePtr->lchild, fun);
    preOrderTraverse(biTreePtr->rchild, fun);
}

// 非递归前序遍历（参数：二叉树的指针，遍历执行函数指针）
template<typename Type, typename FunPtr>
void preOrderTraverse_noRecursion(BiTree<Type> *biTreePtr, FunPtr fun) {
    if (biTreePtr == nullptr) return;
    Stack<BiTree<Type> *> stack;
    stack.push(biTreePtr);
    while (!stack.isEmpty()) {
        biTreePtr = stack.pop();
        while (biTreePtr) {
            fun(biTreePtr->data);
            if (biTreePtr->rchild)stack.push(biTreePtr->rchild);
            biTreePtr = biTreePtr->lchild;
        }
    }
}

// 中序遍历（参数：二叉树的指针，遍历执行函数指针）
template<typename Type, typename FunPtr>
void inOrderTraverse(BiTree<Type> *biTreePtr, FunPtr fun) { // 中序遍历
    if (biTreePtr == nullptr) return;
    inOrderTraverse(biTreePtr->lchild, fun);
    fun(biTreePtr->data);
    inOrderTraverse(biTreePtr->rchild, fun);
}

// 非递归中序遍历（参数：二叉树的指针，遍历执行函数指针）
// 思路：一路寻找左子树 找不着了就找左子树的双亲的右子树继续
template<typename Type, typename FunPtr>
void inOrderTraverse_noRecursion(BiTree<Type> *biTreePtr, FunPtr fun) { // 中序遍历
    if (biTreePtr == nullptr) return;
    Stack<BiTree<Type> *> stack;
    while(biTreePtr||!stack.isEmpty()){
        if(biTreePtr){
            stack.push(biTreePtr);
            biTreePtr=biTreePtr->lchild;
        }else{
            biTreePtr=stack.pop();
            fun(biTreePtr->data);
            biTreePtr=biTreePtr->rchild;
        }
    }
}

// 后序遍历（参数：二叉树的指针，遍历执行函数指针）
template<typename Type, typename FunPtr>
void postOrderTraverse(BiTree<Type> *biTreePtr, FunPtr fun) { // 后序遍历
    if (biTreePtr == nullptr) return;
    postOrderTraverse(biTreePtr->lchild, fun);
    postOrderTraverse(biTreePtr->rchild, fun);
    fun(biTreePtr->data);
}

// 非递归后序遍历（参数：二叉树的指针，遍历执行函数指针）
// 思路：把DLR前序遍历的LR交换，变为DRL。使用stack逆序输出变为LRD即后序。
template<typename Type, typename FunPtr>
void postOrderTraverse_noRecursion(BiTree<Type> *biTreePtr, FunPtr fun) {
    if (biTreePtr == nullptr) return;
    Stack<BiTree<Type> *> stack;
    Stack<Type> result;
    stack.push(biTreePtr);
    while (!stack.isEmpty()) {
        biTreePtr = stack.pop();
        while (biTreePtr) {
            result.push(biTreePtr->data);
            if (biTreePtr->lchild)stack.push(biTreePtr->lchild);
            biTreePtr = biTreePtr->rchild;
        }
    }
    while(!result.isEmpty())fun(result.pop());
}

// RDL中序遍历（参数：二叉树的指针，遍历执行函数指针）
template<typename Type>
void printTreeByRDL(BiTree<Type> *biTreePtr, int depth= 0) { // 中序遍历
    if (biTreePtr == nullptr) return;
    ++depth;
    printTreeByRDL(biTreePtr->rchild, depth);
    for(int i=0;i<depth;i++)printf("\t");
    std::cout << (biTreePtr->data);
    putchar('\n');
    printTreeByRDL(biTreePtr->lchild, depth);
}

int main() {
    // 测试遍历
    BiTree<char> *tree= nullptr;
    createBiTree(tree, "ABC##DE#G##F###");
    printf("Pre order traverse output: \n");
    preOrderTraverse(tree, putchar);
    printf("\nPre order traverse output (no recursion): \n");
    preOrderTraverse_noRecursion(tree, putchar);
    printf("\nIn order traverse output: \n");
    inOrderTraverse(tree, putchar);
    printf("\nIn order traverse output (no recursion): \n");
    inOrderTraverse_noRecursion(tree, putchar);
    printf("\nPost order traverse output: \n");
    postOrderTraverse(tree, putchar);
    printf("\nPost order traverse output (no recursion): \n");
    postOrderTraverse_noRecursion(tree, putchar);

    // 测试RDL打印
    BiTree<char> *treeForPrint= nullptr;
    createBiTree(treeForPrint,"AB#D##CE#F###");
    printf("\nPrint tree by RDL:\n");
    printTreeByRDL(treeForPrint);

    // 测试RDL打印
    BiTree<char> *treeForPrint_empty= nullptr;
    createBiTree(treeForPrint_empty,"");
    printf("\nPrint empty tree by RDL:\n");
    printTreeByRDL(treeForPrint_empty);
    return 0;
}