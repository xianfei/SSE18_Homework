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
    AdjacencyMatrixGraph<int> amGraph(4, 4, false);
    amGraph.setVexes({0, 1, 2, 3});
    /// 创建边 格式：v1 v2 权值
    amGraph.setArcs({{0, 1, 1},
                     {0, 3, 1},
                     {1, 2, 1},
                     {2, 3, 1}});
    // 输出邻接矩阵
    std::cout << "邻接矩阵：\n" << amGraph;

    /// 使用邻接表存储   int vexNum, int arcNum, bool isDirected
    AdjacencyListGraph<int> alGraph(8, 9, true);
    alGraph.setVexes({1,2,3,4,5,6,7,8});
    /// 创建边 格式：v1 v2 权值
    alGraph.setArcs({{1, 2, 1},
                     {2, 4, 1},
                     {4, 8, 1},
                     {5, 8, 1},
                     {5, 2, 1},
                     {1, 3, 1},
                     {3, 6, 1},
                     {3, 7, 1},
                     {6, 7, 1}});
    /// 输出邻接表
    std::cout << "邻接表：\n" << alGraph;
    /// 深度优先搜索
    std::cout << "深度优先搜索: " << std::endl;
    for (const auto &item : alGraph.dfs()) std::cout << item <<" ";
    /// 宽度优先搜索
    std::cout << "宽度优先搜索: " << std::endl;
    for (const auto &item : alGraph.bfs()) std::cout << item <<" ";

    return 0;
}