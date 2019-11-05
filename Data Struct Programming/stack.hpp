//
// Created by xianfei on 2019.
//

#ifndef STACK_H
#define STACK_H

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
    bool isEmpty(){ return  size==0;}
};


#endif //STACK_H
