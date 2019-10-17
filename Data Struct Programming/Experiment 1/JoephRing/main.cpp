#include <iostream>

struct CircleLinkedList {
    static struct node {
        node *next = nullptr;
        int num;
        int password;
    };
    node *head = nullptr;

    void add(int pw, int num_) {
        auto newNode = new node;
        if (head == nullptr) {
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

    int pop(int m) {
        auto iter = head;
        while (iter->next != iter) {

            for (int i = 0; i < m - 2; i++)iter = iter->next;
            auto choosed = iter->next;
            int result = choosed->num;
            m = choosed->password;
            iter->next = choosed->next;
            delete (choosed);
            printf("%d,", result);
        }
    }
};

int main() {
    CircleLinkedList joephRing;
    int nums[] = {3, 1, 7, 2, 4, 8, 4};
    for (int i = 0; i < 7; i++)joephRing.add(nums[i], i + 1);
    joephRing.pop(20);
    return 0;
}