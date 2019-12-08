//
// Created by xianfei on 2019/12/8.
//

#ifndef EXPERIMENT_6_HASHINGTABLE_HPP
#define EXPERIMENT_6_HASHINGTABLE_HPP

#include <stdexcept>
static int ASLs=0;

class HashingTable {
    int _size = 0;
    int _p = 0;
    struct _Node {
        std::string data;
        _Node *nextPtr = nullptr;
    } *_dataPtr;

    int hashing(const std::string &str) {
        int sum = 0;
        for (const auto &item:str)sum += (int) item;
        return sum % _p;
    }

public:
    HashingTable(int size) : _size(size) {
        if(size<2)throw std::length_error("Hashing Table size must >= 2.");
        _dataPtr = new _Node[size];
        auto isPrime = [](int n) {
            bool _isPrime = true;
            for (int i = 2; i <= n / 2; ++i) {
                if (n % i == 0) {
                    _isPrime = false;
                    break;
                }
            }
            return _isPrime;
        };
        do
            if (isPrime(size)) {
                _p = size;
                break;
            }while (--size);
    }

    void insert(const std::string &data) {
        _Node *nodePtr = _dataPtr + hashing(data);
        while (nodePtr->nextPtr)nodePtr = nodePtr->nextPtr;
        nodePtr->nextPtr = new _Node();
        nodePtr->nextPtr->data = data;
    }

    bool search(const std::string &data) {
        int hashingCode = hashing(data);
        _Node *nodePtr = _dataPtr + hashingCode;
        int searchDeepth = 0;
        while (nodePtr) {
            if (nodePtr->data == data) {
                std::cout << "已查到" << data << "  HashingCode:" << hashingCode << "  查找长度" << searchDeepth << "   ";
                ASLs+=searchDeepth;
                return true;
            }
            searchDeepth++;
            nodePtr = nodePtr->nextPtr;
        }
        std::cout << "未查到" << data << "  HashingCode:" << hashingCode << "  查找长度" << searchDeepth << "   ";
        return false;
    }

};


#endif //EXPERIMENT_6_HASHINGTABLE_HPP
