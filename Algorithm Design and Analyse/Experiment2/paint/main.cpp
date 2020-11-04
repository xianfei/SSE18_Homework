#include <iostream>
#include <vector>

const int vertex_num = 5;  //顶点数
int colors = 3;  //颜色数
int vertexs[vertex_num + 1] = {0, 0, 0, 0, 0, 0};  //顶点涂色状态
std::vector<std::vector<int>> edges;  //边集合
int sum = 0;

bool canPaint(int v, int c) {
    for (int k = 0; k < vertex_num; k++) { //如果与它相连并且与它将要涂的颜色一样
        if (edges[v][k] == 1 && vertexs[k] == c) {
            return false;
        }
    }
    return true;
}

void search(int num) {
    if (num > vertex_num) {
        sum++;
        for (int i = 1; i <= vertex_num; i++)
            std::cout << vertexs[i];
        std::cout << std::endl;
    } else
        for (int i = 1; i <= colors; i++) { //每一个有1-m种情况可以涂
            if (canPaint(num, i)) { //第x个涂第i种颜色
                vertexs[num] = i;
                search(num + 1);
                vertexs[num] = 0;//回溯
            }
        }
}

int main() {
    edges.resize(vertex_num + 1);
    for (auto &e : edges)e.resize(vertex_num + 1);
    // 初始化图为测试用例（邻接矩阵）
    edges[1][2] = edges[2][1] = 1;
    edges[1][3] = edges[3][1] = 1;
    edges[2][3] = edges[3][2] = 1;
    edges[2][4] = edges[4][2] = 1;
    edges[2][5] = edges[5][2] = 1;
    edges[3][5] = edges[5][3] = 1;
    edges[4][5] = edges[5][4] = 1;
    search(1);
    std::cout << "总方案数为：" << sum << std::endl;
    return 0;
}
