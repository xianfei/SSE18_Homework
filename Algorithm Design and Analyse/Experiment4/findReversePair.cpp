#include <iostream>
#include <vector>
#include <utility>

int temp[100]; //临时数组用于合并步骤，不在递归函数中开启数组，防止递归过程内存中同时存在大量数组

std::vector<std::pair<int,int>> pairs;

int merge(int arr[], int l, int m, int r) {
    int count = 0, i, j;
    for(i = l; i <= r; i++)
        temp[i] = arr[i];
    int k = l;
    for(i = l, j = m + 1; i <= m && j <= r;k++) {
        if(temp[i] > temp[j]) {
            
            count += m - i + 1;//每次发现左序列元素比右序列元素大，逆序对数量增加，m-i+1即为该元素到左序列尾的元素数量
            //其余代码为归并排序的步骤
            for (int ii=0; ii<m - i + 1; ii++) {
                pairs.push_back(std::pair<int,int>{temp[i+ii],temp[j]});
            }
            arr[k] = temp[j];
            j++;
        }
        else {
            arr[k] = temp[i];
            i++;
        }
    }
    if(i > m) {
        while(j <= r) {
            arr[k] = temp[j];
            j++;
            k++;
        }
    }
    else {
        while(i <= m) {
            arr[k] = temp[i];
            i++;
            k++;
        }
    }
    return count;
}


int findReversePair(int arr[], int l, int r) {
    if(l == r)
        return 0;
    int m = (l + r) / 2;
    int ln = findReversePair(arr, l, m);//左序列逆序对数量
    int rn = findReversePair(arr,  m + 1, r);//右序列逆序对数量
    int mn = merge(arr, l, m, r);//左序列与右序列元素构成的逆序对数量
    return ln + rn + mn;
}
 


int main(void) {
    int test[]={9,8,2,3,6,1,7};
    int i = sizeof(test)/sizeof(test[0]);
    findReversePair(test, 0, i - 1);
    std::cout << "共有"<< pairs.size() << "对\n分别是：";
    for(auto [a,b]:pairs) std::cout<< '<' << a << ',' << b << '>' << ' ';
    std::cout << std::endl;
    return 0;
}
 
