#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

const int n=5;
int cost_matrix[n][n]= {
        {INT_MAX,3,1,5,8},
        {3,INT_MAX,6,7,9},
        {1,6,INT_MAX,4,2},
        {5,7,4,INT_MAX,3},
        {8,9,2,3,INT_MAX}};
char symbol[]= {'1','2','3','4','5'};
int least_cost=INT_MAX;
int up_bound=1+2+3+7+3;
int low_bound=((1+3)+(3+6)+(1+2)+(3+4)+(2+3))/2;
std::vector<int> list;
int candidate_option[n][2]= {{1,3},{3,6},{1,2},{3,4},{2,3}};


int calc_lb(int start, int end, int candidate_option_[n][2]) { //计算下界
    int lowbound = 2*cost_matrix[start][end];
    if(cost_matrix[start][end] > candidate_option_[start][0]) lowbound += candidate_option_[start][0];
    if(cost_matrix[start][end] == candidate_option_[start][0]) lowbound += candidate_option_[start][1];
    if(cost_matrix[start][end] > candidate_option_[end][0]) lowbound += candidate_option_[end][0];
    if(cost_matrix[start][end] == candidate_option_[end][0]) lowbound += candidate_option_[end][1];
    //加上剩余没有选过的行的最小的两个元素
    for(int i=0;i<n;i++) if(i!=start&&i!=end) lowbound += candidate_option_[i][0] + candidate_option_[i][1];
    return lowbound/2;
}

void search(int root) {
    int lb=INT_MAX;
    list.push_back(root);
    for(int i=0;i<n;i++) { //遍历没有走过的地点
        if(std::find(list.begin(), list.end(), i) == list.end()) { // 取上界
            lb = ceil(calc_lb(root, i, candidate_option));
            if((lb<up_bound&&lb>=low_bound)||(list.size()==4&&lb==up_bound)) {
                if(list.size()==4) { // 当走过5个地点的时候结束递归
                    list.push_back(i);
                    least_cost=lb;
                    throw "exit";
                }
                int temp1=INT_MAX,temp2=INT_MAX;
                if(cost_matrix[root][i]>candidate_option[root][0]) {
                    temp1=candidate_option[root][1];
                    candidate_option[root][1]=cost_matrix[root][i];
                }
                if(cost_matrix[root][i]>candidate_option[i][0]) {
                    temp2=candidate_option[i][1];
                    candidate_option[i][1]=cost_matrix[root][i];
                }
                search(i);
                list.erase(std::find(list.begin(), list.end(), i)); // 回溯,删除i
                if(temp1!=INT_MAX) candidate_option[root][1]=temp1;
                if(temp2!=INT_MAX) candidate_option[i][1]=temp2;
            }
        }
    }
}
int main() {
    try {
        search(0);
    }catch (...) {
        std::cout << "方案为："<<std::endl;
        for (int i = 0; i < list.size(); i++) {
            std::cout << symbol[list.at(i)]<<"->";
        }
        std::cout << symbol[list.at(0)] <<std::endl;
        std::cout << "代价为：" << least_cost;
    }
}