#include <iostream>
#include <string>
#include <vector>

const int obj_num = 4;
int limit = 10;  //重量上限
int w[obj_num] = {7, 3, 4, 5};      //每个物品的重量
int v[obj_num] = {42, 12, 40, 25};  //每个物品的价值
int v_w[obj_num] = {0};
std::string objName[obj_num] = {"1", "2", "3", "4"};  //每个物品的名称
int state[obj_num] = {0, 0, 0};
int max_value = 0;
int up_bound = 0;

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

struct Node {
    int w,v;
    Node(int w, int v) : w(w), v(v) {}
};

int upbound(Node n, int k) {//界限函数
    int ub = 0;
    for (int i = k; i < obj_num; i++) {
        if ((limit - n.w) * v_w[i] > ub)
            ub = (limit - n.w) * v_w[i] + n.v;
    }
    return ub;
}

void search(Node node, int i) {
    if (i == obj_num) return;  //递归结束条件
    int ub1, ub2, w_ = w[i], v_ = v[i];
    //加入物体i
    Node node1(node.w + w_, node.v + v_);
    ub1 = upbound(node1, i + 1);
    //不加入物体i
    Node node2(node.w, node.v);
    ub2 = upbound(node2, i + 1);
    //当两种情况都未将背包装满时
    if (node1.w <= limit && node2.w <= limit) {
        if (ub1 >= ub2 && ub1 < up_bound) {
            state[i] = 1;
            max_value = node1.v;
            search(node1, i + 1);
        } else if (ub1 < ub2 && ub2 < up_bound) {
            max_value = node2.v;
            search(node2, i + 1);
        }
    }
    //如果加入此物品将背包装满
    else if (node1.w > limit && node2.w <= limit) {
        max_value = node2.v;
        search(node2, i + 1);
    }
}

int main() {
    for (int i = 0; i < obj_num; i++) {
        v_w[i] = v[i] / w[i];  //计算v/w的值
        up_bound += v[i]; //上界为所有价值之和
    }
    search(Node(0, 0), 0); //计算最小边界，最大边界
    std::cout << "最大价值的组合为：";
    std::vector<std::string> maxObjs;
    for (int i = 0; i < obj_num; i++)
        if (state[i] == 1)
            maxObjs.push_back(objName[i]);
    std::cout << maxObjs;
    std::cout << "\n总重量为：" << max_value;
    return 0;
}

