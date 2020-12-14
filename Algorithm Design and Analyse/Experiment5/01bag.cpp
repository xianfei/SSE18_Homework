#include <iostream>
#include <vector>
#include <utility>

int main(){
    int limited_weight=10;
    int w[] = {0,2,2,6,5,4};  //每个物体的重量
    int v[] = {0,6,3,5,4,6};  //每个物体的价值
    int V[6][11]={0};
    for(int i=1;i<6;i++)
        for(int j=1;j<=limited_weight;j++) 
            if(j<w[i]) V[i][j]=V[i-1][j];
            else V[i][j]=std::max(V[i-1][j], V[i-1][j-w[i]]+v[i]);
    for(int i=0;i<6;i++) {
        for(int j=0;j<=limited_weight;j++) 
            std::cout << V[i][j] << "\t";
        std::cout << "\n";
    }
    std::cout<< "最大价值为" << V[5][limited_weight] << std::endl;
}