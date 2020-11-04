#include <iostream>
#include <string>
#include <vector>

const int obj_num = 4;
int limit = 10;  //重量上限
int w[obj_num] = {7, 3, 4, 5};      //每个物品的重量
int v[obj_num] = {42, 12, 40, 25};  //每个物品的价值
std::string objName[obj_num] = {"1","2","3","4"};  //每个物品的名称
int state[obj_num] = {0, 0, 0};
int max_state[obj_num] = {0, 0, 0};
int temp_weight = 0;
int total_value = 0;
int max_value = 0;

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

void output() {
    std::vector<std::string> hasObjs;
    for(int i=0;i<obj_num;i++)
        if(state[i])hasObjs.push_back(objName[i]);

    std::cout << hasObjs;
    std::cout << "\t" << temp_weight;
    for(int i=0;i<obj_num;i++)
        if(state[i]==1)
            total_value+=v[i];
    std::cout << "\t" << total_value;
    if(total_value>max_value) {
        max_value = total_value;
        for(int i=0;i<obj_num;i++)
            max_state[i]=state[i];
    }
    total_value = 0;
}

void digui_cut(int i) {
    //递归结束的条件
    //不可行的情况
    if (i > obj_num - 1) {
        output();
        std::cout << std::endl;
        return;
    }
    //先加入当前物品
    temp_weight += w[i];
    state[i] = 1;
    //如果加入该物品后没有超重则可以进入左子树继续搜索
    if (temp_weight <= limit) {
        digui_cut(i + 1);
    }
    //否则进入右子树，这是相当于剪枝操作
    state[i] = 0;
    temp_weight -= w[i];
    digui_cut(i + 1);
}

int main() {
    std::cout << "所有可能的情况为：\n状态\t总重量\t总价值" << std::endl;
    digui_cut(0);
    std::cout << "最大价值的组合为：";
    std::vector<std::string> maxObjs;
    for(int i=0;i<obj_num;i++)
        if(max_state[i]==1)
            maxObjs.push_back(objName[i]);
        std::cout << maxObjs;
    std::cout << "\n总重量为：" << max_value;
    return 0;
}

