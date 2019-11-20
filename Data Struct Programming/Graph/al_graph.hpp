//
// Created by xianfei on 2019/11/18.
//

#ifndef GRAPH_AL_GRAPH_HPP
#define GRAPH_AL_GRAPH_HPP

#include <stdexcept>
#include <initializer_list>
#include <ostream>
#include <tuple>
#include <vector>
#include "queue.hpp"

template<typename VertexType>
class AdjacencyListGraph {
    struct ArcNode {
        int adjVex;/*邻接点域*/
        int weight;/*表示边上信息的域info*/
        ArcNode *next = nullptr;/*指向下一个邻接点的指针域*/
        ArcNode(int adjVex, int weight) : adjVex(adjVex), weight(weight) {}
    };

    bool _isDirected = false;
    int _vexNum = 0, _arcNum = 0;
    struct _vNode {
        VertexType v;
        ArcNode *next = nullptr;
    } *_vexList = nullptr;

private:  // dfs 的递归调用函数
    template<typename Function>
    void _dfs(int n, bool *visited, Function visit) {
        visited[n] = true;
        visit(_vexList[n].v);
        auto ptr = _vexList[n].next;
        if (ptr) {
            while (ptr->next != nullptr) {
                if (!visited[ptr->adjVex])_dfs(ptr->adjVex, visited, visit);
                ptr = ptr->next;
            }
            if (!visited[ptr->adjVex])_dfs(ptr->adjVex, visited, visit);
        }
    }

public:  // 返回vector的深度优先搜素算法
    std::vector<VertexType> dfs() {
        bool *visited = new bool[_vexNum];
        std::vector<VertexType> result;
        for (int i = 0; i < _vexNum; ++i)visited[i] = false;
        for (int i = 0; i < _vexNum; ++i)
            if (!visited[i])
                _dfs(i, visited, [&result](VertexType v) -> void { result.push_back(v); });
        delete[] visited;
        return result;
    }

    std::vector<VertexType> bfs() {
        bool *visited = new bool[_vexNum];
        std::vector<VertexType> result;
        for (int i = 0; i < _vexNum; ++i)visited[i] = false;
        Queue<int> queue;
        for (int i = 0; i < _vexNum; ++i) {
            if (!visited[i]) {
                queue.push(i);
                result.push_back(_vexList[i].v);
                visited[i] = true;
            } else continue;
            while (!queue.empty()) {
                auto ptr = _vexList[queue.pop()].next;
                if (ptr) {
                    while (ptr->next != nullptr) {
                        if (!visited[ptr->adjVex]) {
                            visited[ptr->adjVex] = true;
                            queue.push(ptr->adjVex);
                            result.push_back(_vexList[ptr->adjVex].v);
                        }
                        ptr = ptr->next;
                    }
                    if (!visited[ptr->adjVex]) {
                        visited[ptr->adjVex] = true;
                        queue.push(ptr->adjVex);
                        result.push_back(_vexList[ptr->adjVex].v);
                    }
                }
            }
        }

        delete[] visited;
        return result;
    }

public:

    AdjacencyListGraph(int vexNum, int arcNum, bool isDirected) : _vexNum(vexNum), _arcNum(arcNum),
                                                                  _isDirected(isDirected) {
        _vexList = new _vNode[vexNum];
    }

    virtual ~AdjacencyListGraph() {
        delete[] _vexList;
    }

    int locateVex(VertexType target) {
        for (int i = 0; i < _vexNum; i++) {
            if (_vexList[i].v == target)return i;
        }
        return -1;
    }

    void setVexes(std::initializer_list<VertexType> list) {
        int i = -1;
        for (const auto &item : list) {
            if (i + 1 == _vexNum)throw std::out_of_range("");
            _vexList[++i].v = item;
        }
    }

    void setArcs(std::initializer_list<std::tuple<VertexType, VertexType, int>> list) {
        for (const auto &[v1, v2, weight] : list) {
            int i = locateVex(v1), j = locateVex(v2);
            auto ptr = _vexList[i].next;
            if (ptr) {
                while (ptr->next != nullptr)ptr = ptr->next;
                ptr->next = new ArcNode(j, weight);
            } else _vexList[i].next = new ArcNode(j, weight);
            if (!_isDirected) {
                ptr = _vexList[j].next;
                if (ptr) {
                    while (ptr->next != nullptr)ptr = ptr->next;
                    ptr->next = new ArcNode(i, weight);
                } else _vexList[j].next = new ArcNode(i, weight);
            }
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const AdjacencyListGraph &graph) {
        for (int i = 0; i < graph._vexNum; i++) {
            os << graph._vexList[i].v << "\t->\t";
            auto ptr = graph._vexList[i].next;
            if (ptr) {
                while (ptr->next != nullptr) {
                    os << graph._vexList[ptr->adjVex].v << '\t' << ptr->weight << "\t->\t";
                    ptr = ptr->next;
                }
                os << graph._vexList[ptr->adjVex].v << '\t' << ptr->weight << "\t->\t^\t";
            } else os << "^\t";
            os << std::endl;
        }
        return os;
    }

};

#endif //GRAPH_AL_GRAPH_HPP
