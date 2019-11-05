#include <iostream>
#include <stdexcept>
#include "stack.hpp"

template<typename Type>
struct BiTree {
    Type data;
    BiTree *lchild = nullptr, *rchild = nullptr;
};

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
template<typename Type, typename ParaType, typename RetType>
void preOrderTraverse(BiTree<Type> *biTreePtr, RetType(*fun)(ParaType)) {
    if (biTreePtr == nullptr) return;
    fun(biTreePtr->data);
    preOrderTraverse(biTreePtr->lchild, fun);
    preOrderTraverse(biTreePtr->rchild, fun);
}

// 非递归前序遍历（参数：二叉树的指针，遍历执行函数指针）
template<typename Type, typename ParaType, typename RetType>
void preOrderTraverse_noRecursion(BiTree<Type> *biTreePtr, RetType(*fun)(ParaType)) {
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

template<typename Type, typename ParaType, typename RetType>
void inOrderTraverse(BiTree<Type> *biTreePtr, RetType(*fun)(ParaType)) { // 中序遍历
    if (biTreePtr == nullptr) return;
    inOrderTraverse(biTreePtr->lchild, fun);
    fun(biTreePtr->data);
    inOrderTraverse(biTreePtr->rchild, fun);
}

template<typename Type, typename ParaType, typename RetType>
void postOrderTraverse(BiTree<Type> *biTreePtr, RetType(*fun)(ParaType)) { // 后序遍历
    if (biTreePtr == nullptr) return;
    postOrderTraverse(biTreePtr->lchild, fun);
    postOrderTraverse(biTreePtr->rchild, fun);
    fun(biTreePtr->data);
}

int main() {
    auto tree = new BiTree<char>;
    // char str[20] = "ABC##DE#G##F###";
    const char *s = "ABC##DE#G##F###";
    createBiTree(tree, s);
    printf("Pre Order Traverse: ");
    preOrderTraverse(tree, putchar);
    printf("\nPre Order Traverse (no recursion): ");
    preOrderTraverse_noRecursion(tree, putchar);
    printf("In Order Traverse: ");
    inOrderTraverse(tree, putchar);
    printf("Post Order Traverse: ");
    postOrderTraverse(tree, putchar);
    // std::cout << "Hello, World!" << std::endl;
    return 0;
}