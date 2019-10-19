#include <iostream>
#include <stdexcept>

template <class T>
struct Stack{
    const int DEFAULT_SIZE=10;
    T* array=(T*)malloc(DEFAULT_SIZE*sizeof(T));
    int size=0;
    int capacity=DEFAULT_SIZE;
    T getTop(){
        if(size==0)throw std::out_of_range("stack is empty");
        return array[size-1];
    }
    void push(const T &num){
        if(size>=capacity-1){
            array=(T*)realloc(array,2*capacity*sizeof(T));
            if(!array)throw std::overflow_error("stack overflow");
            capacity*=2;
        }
        array[size++]=num;
    }
    T pop(){
        if(size==0)throw std::out_of_range("stack is empty");
        return array[--size];
    }
};

template <class T>
struct LkQueue{
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

int main() {
    LkQueue<int> q;
    for(int i=0;i<10;i++)q.enqueue(i);
    for(int i=0;i<10;i++)std::cout << q.dequeue() << std::endl;
    q.dequeue();
    return 0;
}