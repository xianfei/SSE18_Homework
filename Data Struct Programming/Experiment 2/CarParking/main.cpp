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
    bool isEmpty(){ return  size==0;}
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

struct Car{
    int id,time;
    Car(int id, int time) : id(id), time(time) {}
    Car() = default;
};

struct Parking{
    Stack<Car> parkingLot;
    Stack<Car> temp;
    LkQueue<Car> road;
    int n=2,roadN=0,moneyPerTime=0;
    Parking(int n_,int moneyPerTime_):n(n_),moneyPerTime(moneyPerTime_){}
    bool operate(const char *str){
        char opt;
        int id_,time_;
        sscanf(str,"('%c',%d,%d)",&opt,&id_,&time_);
        switch (opt){
            case 'A':
                if(parkingLot.size<2){ // in stack
                    parkingLot.push(Car(id_,time_));
                    printf("Parking at parking lot at position %d.\n",parkingLot.size);
                    return true;
                }else{ // in queue
                    road.enqueue(Car(id_,time_));
                    roadN++;
                    printf("Parking at road side at position %d.\n",roadN);
                    return true;
                }
            case 'D':
                while(!parkingLot.isEmpty()){
                    Car tempCar=parkingLot.pop();
                    if(tempCar.id!=id_){
                        temp.push(tempCar);
                    }else{
                        printf("Leaving time:%d,need pay %d.\n",time_-tempCar.time,(time_-tempCar.time)*moneyPerTime);
                    }
                }
                while(!temp.isEmpty())parkingLot.push(temp.pop());
                while(parkingLot.size<2&&road.front!= nullptr){
                    Car tempCar=road.dequeue();
                    // 在马路边上停着不计费 所以更改时间为入栈时间
                    tempCar.time=time_;
                    parkingLot.push(tempCar);
                    roadN--;
                }
                return true;
            case 'E':
                puts("Program exit.");
                return false;
        }
    }
};

int main() {
    Parking p(2,5); // 第一个2为停车场的大小 第二个5为单位时间的费用
    char str[20]={0};
    do{
        scanf("%s",str);
    }while(p.operate(str)); //operate 函数的返回值为是否应该继续循环，bool类型
    return 0;
}