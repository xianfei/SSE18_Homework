#include <iostream>
#include "HashingTable.hpp"
#include "BSTree.hpp"

void testBST() {
    BSTree<int> bst;
    int testData[] = {23, 13, 67, 45, 12, 34, 6, 78, 18, 21};
    for (auto &item:testData)bst.insert(item);

    for (auto &item:bst.ldr())std::cout << item << ' ';
    std::cout << std::endl;

    std::cout << std::boolalpha << bst.search(23) << std::endl;
    std::cout << std::boolalpha << bst.search(34) << std::endl;
    std::cout << std::boolalpha << bst.search(68) << std::endl;

    std::cout << "凹入表形式横向打印:" << std::endl;
    bst.print();
    std::cout << "删除45 （仅存在左子树情况）：" << std::endl;
    bst.del(45);
    bst.print();
    std::cout << "删除18 （仅存在左子树情况）：" << std::endl;
    bst.del(18);
    bst.print();
    std::cout << "删除23 （存在左右子树情况）：" << std::endl;
    bst.del(23);
    bst.print();
    std::cout << "删除6 （叶子节点情况）：" << std::endl;
    bst.del(6);
    bst.print();

}

void testHashing() {
    // 测试数据为30个人名汉语拼音
    std::string testData[]={"wangxianfei","chenyitao","sutianyu","shihanpeng","xiedonglin",
                            "chenchuanzhi","pengsihao","hanrui","hourunning","xiekai",
                            "fangmoyi","jiahaochen","zhangaiqi","yaoliunian","lijiahe",
                            "luxintong","zhouying","zhanglongwei","hanyu","zixinyuan",
                            "xutianhang","heyujie","wangxiaochen","linanxin","zhangshuning",
                            "yanhaolong","zhangmingxin","majiaji","liutianyi","mayuchen"};
    HashingTable hashing(64);
    for (const auto &item : testData)hashing.insert(item);

    std::cout << std::boolalpha << hashing.search("xianfei") << std::endl;
    std::cout << std::boolalpha << hashing.search("wangxianfei") << std::endl;
    std::cout << std::boolalpha << hashing.search("dingchongwen") << std::endl;
    std::cout << std::boolalpha << hashing.search("luyanchang") << std::endl;
    std::cout << std::boolalpha << hashing.search("xiedonglin") << std::endl;
    std::cout << std::boolalpha << hashing.search("chenyitao") << std::endl;

    std::cout << "\n计算平均成功查找长度：" << std::endl;
    ASLs=0; // 用于计算平均成功查找长度
    for (const auto &item : testData) {
        std::cout << std::boolalpha << hashing.search(item) << std::endl;
    }
    std::cout << "平均成功查找长度："<<ASLs/30.0 << std::endl;

}

int main() {
    testBST();
    std::cout << '\n' << std::endl;
    testHashing();
    return 0;
}
