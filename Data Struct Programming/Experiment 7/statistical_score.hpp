//
// Created by xianfei on 2019/12/23.
//

#ifndef EXPERIMENT_7_STATISTICAL_SCORE_HPP
#define EXPERIMENT_7_STATISTICAL_SCORE_HPP

#include <utility>
#include <vector>
#include <ostream>
#include "sort_functions.hpp"

struct StuInfo {
    int id;
    std::string name;
    std::vector<int> grades;

    StuInfo(int a) {};

    StuInfo(int id, std::string name, std::vector<int> grades) : id(id), name(std::move(name)),
                                                                 grades(std::move(grades)) {}

    int getSum() {
        int sum = 0;
        for (const auto &item : grades) {
            sum += item;
        }
        return sum;
    };

    friend std::ostream &operator<<(std::ostream &os, StuInfo &info) {
        os << "学号: " << info.id << " 姓名: " << info.name << " 总分: " << info.getSum() << " 各科成绩: ";
        for (const auto &item : info.grades) {
            os << item << " ";
        }
        return os;
    }

    bool operator>(StuInfo &d2) {
        return this->getSum() < d2.getSum();
    }

    bool operator<(StuInfo &d2) {
        return this->getSum() > d2.getSum();
    }
};

#endif //EXPERIMENT_7_STATISTICAL_SCORE_HPP
