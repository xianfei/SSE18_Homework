//
// Created by xianfei on 2019/12/8.
//

#ifndef EXPERIMENT_6_BSTREE_HPP
#define EXPERIMENT_6_BSTREE_HPP

template<typename T>
class BSTree {
    struct _Node {
        T data;
        _Node *lPtr = nullptr;
        _Node *rPtr = nullptr;
    } *_nodes = nullptr;

    void _rdl(_Node *node) {
        if (node->lPtr)_rdl(node->lPtr);
        std::cout << node->data << ' ';
        if (node->rPtr)_rdl(node->rPtr);
    }

public:
    void insert(T data) {
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
            }
        }
        nextNode->data = data;
    }


    void rdl() {
        _rdl(_nodes);
    }

};


#endif //EXPERIMENT_6_BSTREE_HPP
