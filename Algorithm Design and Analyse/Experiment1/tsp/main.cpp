#include <iostream>
#include <vector>
#include <limits>

// 将INT_MAX视为无穷
std::vector<std::vector<int>> cost_matrix = {
        {INT_MAX, 3,  6,      7},
        {12, INT_MAX, 2,      8},
        {8,       6, INT_MAX, 2},
        {3,       7,  6, INT_MAX}};
int least_cost = INT_MAX;
char points[] = {'a', 'b', 'c', 'd'};
int best_index[] = {0, 0, 0, 0, 0};

void printArr(std::vector<int> arr) {
    // 打印数组
    int cost = 0;
    // 打印每次可选的路径
    for (int i : arr) std::cout << points[i] << "->";
    std::cout << points[arr[0]];
    int j = 0;
    for (; j < 3; j++) cost += cost_matrix[arr[j]][arr[j + 1]];
    cost += cost_matrix[arr[j]][arr[0]];
    // 记录更小的代价对应的路径
    if (cost < least_cost) {
        least_cost = cost;
        best_index[0] = arr[0];
        best_index[1] = arr[1];
        best_index[2] = arr[2];
        best_index[3] = arr[3];
        best_index[4] = arr[0];
    }
    // 输出每条路径代价
    std::cout << "\t" << cost << std::endl;
}

// 对数组arr进行全排列
void arrArr(std::vector<int> arr, int p) {
    // 递归结束条件
    if (p == arr.size() - 1) {
        //  每次递归结束  将整个数组打印出来
        printArr(arr);
    }
    // for循环将数组中所有的元素和第一个元素进行交换  然后进行全排列
    for (int i = p; i <= arr.size() - 1; i++) {
        std::swap(arr[i], arr[p]);
        // 把剩下的元素都做全排列
        arrArr(arr, p + 1);
        // 然后再交换回去  数组还原  保证下一次不会有重复交换
        std::swap(arr[i], arr[p]);
    }
}

int main() {
    std::vector<int> index = {0, 1, 2, 3};
    std::cout << "所有路径及成本：" << std::endl;
    arrArr(index, 1);
    std::cout << "\n最佳路径及成本：" << std::endl;
    for (int i = 0;i<4;i++) std::cout << points[best_index[i]] << "->";
    std::cout << points[best_index[0]] << "\t" << least_cost << std::endl;
}