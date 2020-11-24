#include <iostream>
#include <algorithm>
#include <array>

template<std::size_t size>
int findKthMin(std::array<int,size> nums,int k) {
    k = size - k;
    int lo = 0, hi = size - 1;
    while (lo <= hi) {
        int i = lo;
        //这里把数组以A[lo]的大小分为两部分，
        //一部分是小于A[lo]的，一部分是大于A[lo]的
        // [lo,i]<A[lo]，[i+1,j)>=A[lo]
        for (int j = lo + 1; j <= hi; j++)
        if (nums[j] > nums[lo]) std::swap(nums[j], nums[++i]);
        std::swap(nums[lo],nums[i]);
        if (k == i) return nums[i];
        else if (k < i) hi = i - 1;
        else lo = i + 1;
    }
    return -1;
}

int main() {
    // 测试代码
    std::array a{54,62,12,49,81,27,33};
    int k =4;
    int result = findKthMin(a, k);
    std::cout << "第"<<k<<"小的数字是：" << result << std::endl;
    std::cout << "位置是：" << std::find(a.begin(),a.end(),result)-a.begin()+1 << std::endl;
    return 0;
}
