//
// Created by xianfei on 2019.
//

#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>

template <class T>
class Queue{
    struct Node{
        Node *next= nullptr;
        T data;
    };
    Node* _rear= nullptr;
    Node* _front= nullptr;
public:
    virtual ~Queue(){
        while(_front != nullptr)pop();
    }
    void push(const T& data){
        Node* newNode = new Node;
        if(_rear == nullptr){
            newNode->data=data;
            _rear= _front=newNode;
            return;
        }
        newNode->data=data;
        _rear->next=newNode;
        _rear=newNode;
    }
    T front(){
        if(_front == nullptr)throw std::out_of_range("queue is empty");
        return _front->data;
    }
    T pop(){
        Node* willDequeue = _front;
        if(willDequeue== nullptr)throw std::out_of_range("queue is empty");
        _front = _front->next;
        T willReturn=willDequeue->data;
        if(willDequeue == _rear)_rear=nullptr;
        delete(willDequeue);
        return willReturn;
    }
};


#endif //QUEUE_H
