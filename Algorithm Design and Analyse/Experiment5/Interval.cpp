#include <iostream>
#include <stack>
#include <sstream>

struct Request {
    int beginTime;
    int endTime;
    int value;
    friend bool operator<(const Request& r1, const Request& r2) {
        return r1.endTime < r2.endTime;
    }
};

const int requestNum=6;
int beginTime[] = {0,1,5,2,8,8};
int endTime[] = {4,6,7,9,10,11};
int values[] = {2,4,4,7,2,1};

Request reqs[requestNum + 1];
int p[requestNum + 1];
int optimal[requestNum + 1];
int record[requestNum + 1][2];

void init() {
    for (int i = 1; i <= requestNum; ++i) {
        reqs[i].beginTime = beginTime[i];
        reqs[i].endTime = endTime[i];
        reqs[i].value = values[i];
    }
}
// 预备，根据结束时间对所有请求排序，初始化数组p
void prepare() {
    std::sort(reqs + 1, reqs + requestNum + 1);
    memset(p, 0, sizeof(p));
    for (int i = 1; i <= requestNum; ++i) {
        for (int j = i-1; j > 0; --j) {
            if (reqs[j].endTime <= reqs[i].beginTime) {
                p[i] = j;
                break;
            }
        }
    }
    memset(record, 0, sizeof(record));
}
// 动态规划算法
void solve() {
    optimal[0] = 0;
    for (int i = 1; i <= requestNum; ++i) {
        if (optimal[p[i]] + reqs[i].value >= optimal[i-1]) {
            optimal[i] = optimal[p[i]] + reqs[i].value;
            record[i][0] = 1;
            record[i][1] = p[i];
        } else {
            optimal[i] = optimal[i-1];
            record[i][0] = 0;
            record[i][1] = i-1;
        }
    }
}

template <typename T>
std::string stack_to_str(std::stack<T> stack){ //输出栈 转换为字符串
    std::stringstream ss;
    ss<<'[';
    for(;!stack.empty();stack.pop()) {
        T element = stack.top();
        ss<< element;
        ss<<", ";
    }
    std::string s=ss.str().substr(0,ss.str().length()-2); //删除最后一个", "
    s+=']';
    return s;
}


std::stack<int> result;
// 输出结果
void output() {
    std::cout << "Max Value: " << optimal[requestNum]
    << "\nActivities Sequence:";
    for (int i = requestNum; i > 0; i = record[i][1]) {
        if (record[i][0] == 1) {
            result.push(i);
        }
    }
    std::cout << stack_to_str(result) << std::endl;
}



int main() {
    init();
    prepare();
    solve();
    output();
    return 0;
}
