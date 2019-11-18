#include <iostream>
#include "am_graph.hpp"
#include "al_graph.hpp"


int main() {

    ///     0
    ///    /|
    ///   1-+-2
    ///     |/
    ///     3

    /// 使用邻接矩阵存储   int vexNum, int arcNum, bool isDirected
    AM_Graph<int> amGraph(4, 4, false);
    amGraph.setVexes({0, 1, 2, 3});
    /// 创建边 格式：v1 v2 权值
    amGraph.setArcs({{0, 1, 1},
                     {0, 3, 1},
                     {1, 2, 1},
                     {2, 3, 1}});
    // 输出邻接矩阵
    std::cout << "邻接矩阵：\n" << amGraph;

    /// 使用邻接表存储   int vexNum, int arcNum, bool isDirected
    AL_Graph<int> alGraph(4, 4, false);
    alGraph.setVexes({0, 1, 2, 3});
    /// 创建边 格式：v1 v2 权值
    alGraph.setArcs({{0, 1, 1},
                     {0, 3, 1},
                     {1, 2, 1},
                     {2, 3, 1}});
    // 输出邻接表
    std::cout << "邻接表：\n" << alGraph;

    return 0;
}