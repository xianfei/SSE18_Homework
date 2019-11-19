//
// Created by xianfei on 2019.
//

#ifndef STACK_H
#define STACK_H

#include <stdexcept>
#include <cstdlib>

template <class T>
class Stack{
    const int DEFAULT_SIZE=10;
    T* _array=(T*)malloc(DEFAULT_SIZE * sizeof(T));
    int size=0;
    int capacity=DEFAULT_SIZE;
public:
    ~Stack(){
        free(_array);
    }
    T top(){
        if(size==0)throw std::out_of_range("stack is empty");
        return _array[size - 1];
    }
    void push(const T &num){
        if(size>=capacity-1){
            _array=(T*)realloc(_array, 2 * capacity * sizeof(T));
            if(!_array)throw std::overflow_error("stack overflow");
            capacity*=2;
        }
        _array[size++]=num;
    }
    T pop(){
        if(size==0)throw std::out_of_range("stack is empty");
        return _array[--size];
    }
    bool empty(){ return  size==0;}
};


#endif //STACK_H
