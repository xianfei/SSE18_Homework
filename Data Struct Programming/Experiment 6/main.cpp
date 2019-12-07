#include <iostream>
#include "HashingTable.hpp"

int main() {
    HashingTable hashing(30);
    hashing.insert("lilei");
    hashing.insert("hanmeimeimeimei");
    hashing.insert("hanmeimeimei");
    hashing.insert("hanmeimei");
    hashing.insert("hanmei");
    hashing.insert("xianfei");
    std::cout << std::boolalpha << hashing.search("xianfei") << std::endl;
    std::cout << std::boolalpha << hashing.search("wangxianfei") << std::endl;
    std::cout << std::boolalpha << hashing.search("lilei") << std::endl;
    std::cout << std::boolalpha << hashing.search("lileilei") << std::endl;
    std::cout << std::boolalpha << hashing.search("hanmeimei") << std::endl;
    std::cout << std::boolalpha << hashing.search("hanmei") << std::endl;
    return 0;
}
