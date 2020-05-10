//
// Created by xianfei on 2019/12/8.
//

#ifndef EXPERIMENT_6_BSTREE_HPP
#define EXPERIMENT_6_BSTREE_HPP

#include <vector>
#include <stdexcept>
#include <iostream>
using namespace std;

template<typename T>
class BSTree {
    struct _Node {
        T data;
        _Node *lPtr = nullptr;
        _Node *rPtr = nullptr;
    } *_nodes = nullptr;

    template<class Function>
    void _ldr(_Node *node, const Function &fun) {
        if (node->lPtr)_ldr(node->lPtr, fun);
        fun(node->data);
        if (node->rPtr)_ldr(node->rPtr, fun);
    }

    template<class Function>
    void _rdl(_Node *node, const Function &fun, int i = 0) {
        ++i;
        if (node->rPtr)_rdl(node->rPtr, fun, i);
        fun(node->data, i);
        if (node->lPtr)_rdl(node->lPtr, fun, i);
    }

public:
    void insert(const T &data) {
        if (_nodes == nullptr) {
            _nodes = new _Node;
            _nodes->data = data;
            return;
        }
        _Node *nextNode = _nodes;
        while (true) {
            if (data < nextNode->data) {
                if (nextNode->lPtr == nullptr) {
                    nextNode->lPtr = new _Node;
                    nextNode = nextNode->lPtr;
                    break;
                } else nextNode = nextNode->lPtr;
            } else if (data > nextNode->data) {
                if (nextNode->rPtr == nullptr) {
                    nextNode->rPtr = new _Node;
                    nextNode = nextNode->rPtr;
                    break;
                } else nextNode = nextNode->rPtr;
            } else return; // data exist, ignore it.
        }
        nextNode->data = data;
    }

    bool search(const T &data) {
        if (_nodes == nullptr) {
            throw std::out_of_range("");
        }
        _Node *nextNode = _nodes;
        int searchDeepth = 1;
        while (true) {
            if (data < nextNode->data) {
                if (nextNode->lPtr == nullptr) {
                    std::cout << "未查到" << data << "  查找深度" << searchDeepth << "   ";
                    return false;
                } else nextNode = nextNode->lPtr;
            } else if (data > nextNode->data) {
                if (nextNode->rPtr == nullptr) {
                    std::cout << "未查到" << data << "  查找深度" << searchDeepth << "   ";
                    return false;
                } else nextNode = nextNode->rPtr;
            } else {
                std::cout << "已查到" << data << "  查找深度" << searchDeepth << "   ";
                return true;
            }
            searchDeepth++;
        }
    }

    void del(const T &data) {
        if (_nodes == nullptr) {
            throw std::out_of_range("Can't found ");
        }
        _Node **prioNode = nullptr;
        _Node *nextNode = _nodes;

        while (true) {
            if (data < nextNode->data) {
                if (nextNode->lPtr == nullptr) {
                    throw std::out_of_range("Can't found ");
                } else {
                    prioNode = &nextNode->lPtr;
                    nextNode = nextNode->lPtr;
                }
            } else if (data > nextNode->data) {
                if (nextNode->rPtr == nullptr) {
                    throw std::out_of_range("Can't found ");
                } else {
                    prioNode = &nextNode->rPtr;
                    nextNode = nextNode->rPtr;
                }
            } else {
                break;
            }
        }

        if(nextNode->lPtr == nullptr && nextNode->rPtr == nullptr&&prioNode== nullptr){
            // 只有根节点删除根节点
            _nodes= nullptr;
        } else if (nextNode->lPtr == nullptr && nextNode->rPtr == nullptr) {
            // 删除叶子节点
            *prioNode = nullptr;
        } else if (nextNode->rPtr == nullptr) {
            // 删除只有左子树节点
            *prioNode = (**prioNode).lPtr;
        } else if (nextNode->lPtr == nullptr) {
            // 删除只有右子树节点
            *prioNode = (**prioNode).rPtr;
        } else {
            // 删除左右都有子树的节点
            // 寻找左子树的最大节点 (ldr序列末尾)
            std::vector<T> result;
            _ldr(nextNode->lPtr, [&result](const T &data) { result.push_back(data); });
            this->del(result.back());
            nextNode->data = result.back();
        }
    }

    std::vector<T> ldr() {
        std::vector<T> result;
        if(_nodes)_ldr(_nodes, [&result](const T &data) { result.push_back(data); });
        return result;
    }

    void print() {
        if(_nodes)_rdl(_nodes, [](const T &data, int deepth) {
            for (int i = 0; i < deepth; i++)printf("\t");
            std::cout << (data);
            putchar('\n');
        });
    }

};


#endif //EXPERIMENT_6_BSTREE_HPP
