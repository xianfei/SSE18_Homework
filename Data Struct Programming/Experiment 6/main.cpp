#include <iostream>
#include "HashingTable.hpp"
#include "BSTree.hpp"

void testBST() {
    BSTree<int> bst;
    for (auto &item:{23, 13, 67, 45, 12, 34, 6})bst.insert(item);
    bst.rdl();
}

void testHashing() {
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
}

int main() {
    testBST();
    std::cout << '\n' << std::endl;
    testHashing();
    return 0;
}
