#include <iostream>

struct CircleLinkedList {
    struct node { // 节点类
        node *next = nullptr;
        int num;
        int password;
    };
    node *head = nullptr;
    void add(int pw, int num_) {
        auto newNode = new node;
        if (head == nullptr) { // 如果还没有节点
            head = newNode;
            newNode->next = head;
        }
        auto iter = head;
        while (iter->next != head)iter = iter->next;
        iter->next = newNode;
        newNode->next = head;
        newNode->num = num_;
        newNode->password = pw;
    }
    void pop(int m) {
        auto iter = head;
        m--; // 第一次数应该少数一个，因为iter本来应该指头结点的前一个，可是iter现在指向头结点
        while (iter->next != iter) { // 链表中只有一个元素时终止
            for (int i = 0; i < m - 1; i++)iter = iter->next;
            auto choosed = iter->next;
            int result = choosed->num;
            m = choosed->password;
            iter->next = choosed->next;
            delete (choosed);
            printf("%d,", result);
        }
        printf("%d",iter->num);
        delete(iter);
        head = nullptr;
    }
};

int main() {
    CircleLinkedList joephRing;
    int nums[] = {3, 1, 7, 2, 4, 8, 4};
    for (int i = 0; i < 7; i++)joephRing.add(nums[i], i + 1);
    int m;
    scanf("%d",&m);
    joephRing.pop(m);
    return 0;
}