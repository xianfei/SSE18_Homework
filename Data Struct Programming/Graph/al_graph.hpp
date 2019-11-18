//
// Created by xianfei on 2019/11/18.
//

#ifndef GRAPH_AL_GRAPH_HPP
#define GRAPH_AL_GRAPH_HPP

#include <stdexcept>
#include <initializer_list>
#include <ostream>
#include <tuple>


template <typename VertexType>
class AL_Graph{
public:
    struct ArcNode{
        int adjVex;/*邻接点域*/
        int weight;/*表示边上信息的域info*/
        ArcNode * next= nullptr;/*指向下一个邻接点的指针域*/
        ArcNode(int adjVex, int weight) : adjVex(adjVex), weight(weight) {}
    };
    bool _isDirected = false;
    int _vexNum=0,_arcNum=0;
    struct _vNode{VertexType v;ArcNode * next= nullptr;} *vexList = nullptr;
    AL_Graph(int vexNum, int arcNum, bool isDirected) : _vexNum(vexNum), _arcNum(arcNum), _isDirected(isDirected) {
        vexList = new _vNode[vexNum];
    }

    virtual ~AL_Graph() {
        delete [] vexList;
    }

    int locateVex(VertexType target){
        for (int i=0;i<_vexNum;i++) {
            if(vexList[i].v==target)return vexList[i].v;
        }
        return -1;
    }

    void setVexes(std::initializer_list<VertexType> list){
        int i=-1;
        for (const auto &item : list) {
            if(i+1==_vexNum)throw std::out_of_range("");
            vexList[++i].v=item;
        }
    }

    void setArcs(std::initializer_list<std::tuple<int,int,int>> list){
        for (const auto &[v1,v2,weight] : list) {
            int i=locateVex(v1),j=locateVex(v2);
            auto ptr=vexList[i].next;
            if(ptr){
                while(ptr->next!= nullptr)ptr=ptr->next;
                ptr->next=new ArcNode(j,weight);
            }
            else vexList[i].next=new ArcNode(j,weight);
            if(!_isDirected){
                auto ptr=vexList[j].next;
                if(ptr){
                    while(ptr->next!= nullptr)ptr=ptr->next;
                    ptr->next=new ArcNode(i,weight);
                }
                else vexList[j].next=new ArcNode(i,weight);
            }
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const AL_Graph &graph) {
        for(int i=0;i<graph._vexNum;i++){
            os << graph.vexList[i].v << "\t->\t";
            auto ptr=graph.vexList[i].next;
            if(ptr){
                while(ptr->next!= nullptr){
                    os << ptr->adjVex <<'\t' << ptr->weight <<"\t->\t";
                    ptr=ptr->next;
                }
                os << ptr->adjVex <<'\t' << ptr->weight <<"\t^\t";
            }
            os << std::endl;
        }
        return os;
    }

};

#endif //GRAPH_AL_GRAPH_HPP
