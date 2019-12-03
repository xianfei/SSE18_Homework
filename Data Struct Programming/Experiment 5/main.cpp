#include <iostream>
#include "al_graph.hpp"

void test1() {
    /// 使用邻接表存储   int vexNum, int arcNum, bool isDirected
    AdjacencyListGraph<std::string> alGraph(8, 10, false);
    alGraph.setVexes({"v1", "v2", "v3", "v4", "v5", "v6", "v7", "v8"});
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
    for (const auto &item : alGraph.dfs("v1")) std::cout << item << " ";
    std::cout << std::endl;
    /// 深度优先搜索
    std::cout << "深度优先搜索(不递归): " << std::endl;
    for (const auto &item : alGraph.dfs_noRes("v1")) std::cout << item << " ";
    std::cout << std::endl;
    /// 宽度优先搜索
    std::cout << "宽度优先搜索: " << std::endl;
    for (const auto &item : alGraph.bfs("v1")) std::cout << item << " ";
    std::cout << std::endl;
}

void test2() {
    /// 使用邻接表存储   int vexNum, int arcNum, bool isDirected
    AdjacencyListGraph<std::string> alGraph(8, 10, false);
    alGraph.setVexes({"v1", "v2", "v3", "v4", "v5", "v6", "v7", "v8"});
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
    for (const auto &item : alGraph.dfs("v8")) std::cout << item << " ";
    std::cout << std::endl;
    /// 深度优先搜索
    std::cout << "深度优先搜索(不递归): " << std::endl;
    for (const auto &item : alGraph.dfs_noRes("v8")) std::cout << item << " ";
    std::cout << std::endl;
    /// 宽度优先搜索
    std::cout << "宽度优先搜索: " << std::endl;
    for (const auto &item : alGraph.bfs("v8")) std::cout << item << " ";
    std::cout << std::endl;
}

void test3() {
    /// 使用邻接表存储   int vexNum, int arcNum, bool isDirected
    AdjacencyListGraph<int> alGraph(8, 9, true);
    alGraph.setVexes({1, 2, 3, 4, 5, 6, 7, 8});
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
    for (const auto &item : alGraph.dfs()) std::cout << item << " ";
    std::cout << std::endl;
    /// 深度优先搜索
    std::cout << "深度优先搜索(不递归): " << std::endl;
    for (const auto &item : alGraph.dfs_noRes()) std::cout << item << " ";
    std::cout << std::endl;
    /// 宽度优先搜索
    std::cout << "宽度优先搜索: " << std::endl;
    for (const auto &item : alGraph.bfs()) std::cout << item << " ";
    std::cout << std::endl;
}

void test4() {
    /// 使用邻接表存储   int vexNum, int arcNum, bool isDirected
    AdjacencyListGraph<int> alGraph(1, 0, false);
    alGraph.setVexes({1});
    /// 输出邻接表
    std::cout << "邻接表：\n" << alGraph;
    /// 深度优先搜索
    std::cout << "深度优先搜索: " << std::endl;
    for (const auto &item : alGraph.dfs()) std::cout << item << " ";
    std::cout << std::endl;
    /// 深度优先搜索
    std::cout << "深度优先搜索(不递归): " << std::endl;
    for (const auto &item : alGraph.dfs_noRes()) std::cout << item << " ";
    std::cout << std::endl;
    /// 宽度优先搜索
    std::cout << "宽度优先搜索: " << std::endl;
    for (const auto &item : alGraph.bfs()) std::cout << item << " ";
    std::cout << std::endl;
}

int main() {
    
    std::cout << "测试1" << std::endl;
    test1();

    std::cout << "测试2" << std::endl;
    test2();

    std::cout << "测试3" << std::endl;
    test3();

    std::cout << "测试4" << std::endl;
    test4();

    return 0;
}
