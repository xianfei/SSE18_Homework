#include <iostream>
#include "am_graph.hpp"
#include "al_graph.hpp"

int main() {


    /// 使用邻接表存储   int vexNum, int arcNum, bool isDirected
    AdjacencyListGraph<std::string> alGraph(8, 10, false);
    alGraph.setVexes({"v1","v2","v3","v4","v5","v6","v7","v8"});
    /// 创建边 格式：v1 v2 权值
    alGraph.setArcs({{"v1", "v2", 1},
                     {"v1", "v3", 1},
                     {"v2", "v4", 1},
                     {"v2", "v5", 1},
                     {"v3", "v6", 1},
                     {"v3", "v7", 1},
                     {"v4", "v8", 1},
                     {"v5", "v8", 1},
                     {"v6", "v8", 1},
                     {"v7", "v8", 1}});
    /// 输出邻接表
    std::cout << "邻接表：\n" << alGraph;
    /// 深度优先搜索
    std::cout << "深度优先搜索: " << std::endl;
    for (const auto &item : alGraph.dfs()) std::cout << item <<" ";
    std::cout << std::endl;
    /// 深度优先搜索
    std::cout << "深度优先搜索(不递归): " << std::endl;
    for (const auto &item : alGraph.dfs_noRes()) std::cout << item <<" ";
    std::cout << std::endl;
    /// 宽度优先搜索
    std::cout << "宽度优先搜索: " << std::endl;
    for (const auto &item : alGraph.bfs()) std::cout << item <<" ";
    std::cout << std::endl;


    return 0;
}
