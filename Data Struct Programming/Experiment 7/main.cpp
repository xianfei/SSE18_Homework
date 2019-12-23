#include "compare_sort.hpp"
#include "statistical_score.hpp"

void compare_sort() {
    // 创建随机数生成器
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> randNum(1, 10000);
    SList<IntObj> list;
    // 填充100个随机数
    std::cout << "在1-10000范围随机填充1000个数\n";
    for (int i = 0; i < 10000; ++i) list.R.emplace_back(randNum(e1));

    std::cout << "\n插入排序：\n";
    sort_output(list, InsertSort);
    std::cout << "\nShell排序：\n";
    sort_output(list, ShellSort);
    std::cout << "\n冒泡排序：\n";
    sort_output(list, BubbleSort);
    std::cout << "\n快速排序：\n";
    sort_output(list, QuickSort);
    std::cout << "\n选择排序：\n";
    sort_output(list, SelectionSort);
    std::cout << "\n堆排序：\n";
    sort_output(list, HeapSort);
    std::cout << "\n归并排序：\n";
    sort_output(list, MergeSort);
}

void statistical_score() {
    // 创建随机数生成器
    std::random_device r;
    std::default_random_engine e(r());
    std::uniform_int_distribution<int> randScore(1, 100), randNameIndex(0, 14);

    SList<StuInfo> stuInfo;
    std::cout << "添加100个同学的信息和成绩" << std::endl;
    // 随机拼凑一些常见的名字
    std::string name[2][15] = {{"赵", "钱", "孙", "李", "周", "吴", "郑", "王", "陈", "贾", "刘", "张", "孔", "严", "林"},
                               {"建", "国", "天", "雨", "明", "涵", "思", "丽", "田", "彤", "若", "梦", "欣", "佳", ""}};
    for (int i = 0; i < 100; i++) {
        std::vector<int> grades;
        for (int j = 0; j < 5; ++j) grades.emplace_back(randScore(e));
        auto s = std::to_string(i);
        stuInfo.R.emplace_back(2018211000 + i,
                               name[0][randNameIndex(e)] + name[1][randNameIndex(e)] + name[1][randNameIndex(e)],
                               grades);
    }
    for (int i = 0; i < stuInfo.length(); ++i) {
        std::cout << stuInfo[i] << std::endl;
    }

    // 可以更换成上一个函数中提到的任一排序方法
    QuickSort(stuInfo);
    std::cout << "\n排序后输出几个同学的信息和成绩" << std::endl;
    int rank=1,lastRank=0,lastRankScore=-1;
    for (int i = 0; i < stuInfo.length(); ++i) {
        if(lastRankScore!=stuInfo[i].getSum()){
            lastRank = rank;
            lastRankScore=stuInfo[i].getSum();
        }
        std::cout << "排名: "<< lastRank << ' ' <<stuInfo[i] << std::endl;
        ++rank;
    }
}

int main() {
//    compare_sort();
//    puts("\n\n\n\n\n");
    statistical_score();
}

