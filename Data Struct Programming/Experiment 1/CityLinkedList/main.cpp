#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
#include <cmath>

struct Coordinate{ // 存储坐标
    double x,y;
    Coordinate(double x=0, double y=0) : x(x), y(y) {}
    double getDistance(const Coordinate& c){ // 使用勾股定理计算距离
        return sqrt(pow(abs(x-c.x),2)+pow(abs(y-c.x),2));
    }

    friend std::ostream &operator<<(std::ostream &os, const Coordinate &coordinate) {
        os << "x: " << coordinate.x << " y: " << coordinate.y;
        return os;
    }
};

struct CityLinkList{
    std::string name;
    Coordinate c;
    CityLinkList* next = nullptr;
    void insert(const std::string &name, double x,double y){insert(name,Coordinate(x,y));}
    void insert(const std::string &name,Coordinate c){
        CityLinkList* newNode=new CityLinkList;
        newNode->next=next;
        next=newNode;
        newNode->name=name;
        newNode->c=c;
    }
    std::string getByDistance(Coordinate c,double distance){
        CityLinkList* nextptr=next;
        std::string names;
        while(nextptr!= nullptr){
            if(nextptr->c.getDistance(c)<=distance)names+=nextptr->name+" ";
            nextptr=nextptr->next;
        }
        return names;
    }
    Coordinate search(const std::string &name){
        CityLinkList* nextptr=next;
        while(nextptr->name!=name){
            nextptr=nextptr->next;
            if(nextptr== nullptr)throw std::out_of_range("Can't find "+name);
        }
        return nextptr->c;
    }
    void del(const std::string &name){
        CityLinkList *nextptr=next,*willDel;
        while(nextptr->next->name!=name){
            nextptr=nextptr->next;
            if(nextptr->next == nullptr)throw std::out_of_range("Can't find "+name);
        }
        willDel=nextptr->next;
        nextptr->next=nextptr->next->next;
        delete(willDel);
    }
};

int main() {
    CityLinkList cityLinkList;
    cityLinkList.insert("Beijing",100,100);
    cityLinkList.insert("Tianjin",102,102);
    cityLinkList.insert("Shanghai",109,109);
    cityLinkList.insert("Shijiazhuang",98,99);

    std::cout << "The coordinate of Tianjin is " << cityLinkList.search("Tianjin") << std::endl;
    std::cout << "The coordinate of Shanghai is " << cityLinkList.search("Shanghai") << std::endl;
    std::cout << "The cities which distance to (101,101) under than 5 are "
            <<cityLinkList.getByDistance(Coordinate(101,101),5) << std::endl;
    cityLinkList.del("Tianjin");
    std::cout << "After deleted Tianjin, ";
    std::cout << "the cities which distance to (101,101) under than 5 are "
            <<cityLinkList.getByDistance(Coordinate(101,101),5) << std::endl;
    try {
        std::cout << cityLinkList.search("Tianjin") << std::endl;
    }catch (std::exception &e){
        std::cout << e.what();
    }
    return 0;
}