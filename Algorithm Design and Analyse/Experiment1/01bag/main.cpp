#include <iostream>
#include <vector>

const int limited = 10;

//用于输出vector数组
template<typename T>
std::ostream &operator<<(std::ostream &os, std::vector<T> vec) {
    os << "[";
    if (!vec.empty()) {
        std::copy(vec.begin(), vec.end() - 1, std::ostream_iterator<T>(os, ","));
        os << vec.back();
    }
    os << "]";
    return os;
}

static std::vector<std::vector<int>> getSub(std::vector<int> objs) {
    std::vector<std::vector<int>> result;
    int max = 1 << objs.size();  //共有16种可能

    for (int i = 0; i < max; i++) { //16个子集进行循环求解
        std::vector<int> subList;   //存放子集序列
        int k = i;
        int index = 0;
        while (k > 0) {  //k=0时，子集为空集
            if ((k & 1) > 0) subList.push_back(objs[index]);  //当k=14时，不执行
            k >>= 1;   //判断从右往左数的下一位是否加入子集当中
            index++;
        }
        result.push_back(subList);
    }
    return result;
}

int main() {
    int w1[] = {7, 3, 4, 5};      //每个物体的重量
    int v1[] = {42, 12, 40, 25};  //每个物体的价值
    std::vector index{1, 2, 3, 4};   //物体的标号
    int max_value = 0;          //最大的价值
    int max_index = 0;           //价值最大的方案的index
    std::vector<std::vector<int>> list = getSub(index); //所有可能性的集合

    std::cout << "重量\t价值\t是否可行\t\t方案\n";
    //遍历所有子集，求每个子集的总重量和总价值，并选出价值最大的方案
    for (int i = 0; i < list.size(); i++) {
        int total_value = 0;
        int total_weight = 0;
        std::vector<int> subList = list[i];
        for (int j : subList) {
            total_weight += w1[j - 1];
            total_value += v1[j - 1];
        }
        if (total_weight > limited)      //如果总重量超标
            std::cout << total_weight << "\t" << total_value << "\t不可行\t\t" << subList << std::endl;
        else { //如果总重量未超标
            std::cout << total_weight << "\t" << total_value << "\t可行\t\t\t" << subList << std::endl;
            //找出总价值最大方案
            if (total_value > max_value) {
                max_value = total_value;
                max_index = i;
            }
        }
    }
    std::cout << "\n最佳方案为：";
    for (int &i : list.at(max_index)) {
        std::cout << "物品" << i << "\t";
    }
    std::cout << "\n总价值为：" << max_value << std::endl;
    return 0;
}

