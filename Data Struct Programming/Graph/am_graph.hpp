//
// Created by xianfei on 2019/11/18.
//

#ifndef GRAPH_AM_GRAPH_HPP
#define GRAPH_AM_GRAPH_HPP

#include <stdexcept>
#include <cstring>
#include <ostream>
#include <tuple>
#include <initializer_list>

template <typename VertexType>
class AM_Graph{
public:
    int _vexNum=0,_arcNum=0;
    bool _isDirected = false;
    int **arcMatrix = nullptr;
    VertexType *vexList = nullptr;

    AM_Graph(int vexNum, int arcNum, bool isDirected) : _vexNum(vexNum), _arcNum(arcNum), _isDirected(isDirected) {
        arcMatrix = new int*[vexNum];
        for (int i=0;i<vexNum;i++) {
            arcMatrix[i]=new int[vexNum];
            memset(arcMatrix[i],0, sizeof(int)*vexNum);
        }
        vexList = new VertexType[vexNum];
        memset(vexList,0, sizeof(int)*vexNum);
    }

    virtual ~AM_Graph() {
        for (int i=0;i<_vexNum;i++) delete [] arcMatrix[i];
        delete [] arcMatrix;
        delete [] vexList;
    }

    int locateVex(VertexType target){
        for (int i=0;i<_vexNum;i++) {
            if(vexList[i]==target)return vexList[i];
        }
        return -1;
    }

    void setVexes(std::initializer_list<VertexType> list){
        int i=-1;
        for (const auto &item : list) {
            if(i+1==_vexNum)throw std::out_of_range("");
            vexList[++i]=item;
        }
    }

    void setArcs(std::initializer_list<std::tuple<int,int,int>> list){
        for (const auto &[v1,v2,weight] : list) {
            int i=locateVex(v1),j=locateVex(v2);
            arcMatrix[i][j] = weight;
            if(!_isDirected)arcMatrix[j][i] = weight;
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const AM_Graph &graph) {
        for(int i=0;i<graph._vexNum;i++){
            for(int j=0;j<graph._vexNum;j++){
                os << graph.arcMatrix[i][j] << ' ';
            }
            os << std::endl;
        }
        return os;
    }
};

#endif //GRAPH_AM_GRAPH_HPP
