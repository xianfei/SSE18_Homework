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

int main() {
    Stack<int> s;
    int num;
    std::cin>>num;
    do{
        s.push(num%8);
        num/=8;
    }while(num);
    for(int i=0,n=s.size;i<n;i++)std::cout << s.pop();
    return 0;
}