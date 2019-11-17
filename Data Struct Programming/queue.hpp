//
// Created by xianfei on 2019.
//

#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>

template <class T>
struct Queue{
    struct Node{
        Node *next= nullptr;
        T data;
    };
    Node* rear= nullptr;
    Node* front= nullptr;
    void enqueue(const T& data){
        Node* newNode = new Node;
        if(rear== nullptr){
            newNode->data=data;
            rear=front=newNode;
            return;
        }
        newNode->data=data;
        rear->next=newNode;
        rear=newNode;
    }
    T dequeue(){
        Node* willDequeue = front;
        if(willDequeue== nullptr)throw std::out_of_range("queue is empty");
        front = front->next;
        T willReturn=willDequeue->data;
        delete(willDequeue);
        return willReturn;
    }
};


#endif //QUEUE_H
