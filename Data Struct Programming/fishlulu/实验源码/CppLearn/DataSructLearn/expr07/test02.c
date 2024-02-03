#include <stdio.h>
#include <stdlib.h>

// 学生结构体
struct Student {
  int id;
  char name[50];
  int scores[5]; // 假设有5门课程
  int totalScore;
  int rank;
};

// 快速排序实现
void quickSort(struct Student *student, int low, int high) {
  if (low < high) {
    int pivot = student[high].totalScore;
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
      if (student[j].totalScore > pivot) {
        i++;
        struct Student temp = student[i];
        student[i] = student[j];
        student[j] = temp;
      }
    }

    struct Student temp = student[i + 1];
    student[i + 1] = student[high];
    student[high] = temp;

    int partitionIndex = i + 1;
    quickSort(student, low, partitionIndex - 1);
    quickSort(student, partitionIndex + 1, high);
  }
}

// 计算总分
void calculateTotalScore(struct Student *student, int numStudents, int numCourses) {
  for (int i = 0; i < numStudents; i++) {
    student[i].totalScore = 0;
    for (int j = 0; j < numCourses; j++) {
      student[i].totalScore += student[i].scores[j];
    }
  }
}

// 打印名次表和学生详细信息
void printRankAndDetails(struct Student *student, int numStudents, int numCourses) {
  printf("| %-4s | %-8s | %-12s | %-4s | %-4s | %-6s | %-4s | %-8s | %-8s |\n",
         "名次", "学号", "姓名", "总分", "高数", "JavaSE", "计组", "形式语言", "数据结构");
  printf("|-------|----------|--------------|------|------|--------|------|----------|----------|\n");

  for (int i = 0; i < numStudents; i++) {
    printf("| %-4d | %-8d | %-12s | %-4d | %-4d | %-6d | %-4d | %-8d | %-8d |\n",
           student[i].rank, student[i].id, student[i].name, student[i].totalScore,
           student[i].scores[0], student[i].scores[1], student[i].scores[2],
           student[i].scores[3], student[i].scores[4]);
  }
}

int main() {
  int numStudents = 100; // 学生人数
  int numCourses = 5;    // 课程数量

  struct Student students[numStudents];

  // 模拟生成学生数据
  for (int i = 0; i < numStudents; i++) {
    students[i].id = 1001 + i;
    sprintf(students[i].name, "Student%d", i + 1);
    for (int j = 0; j < numCourses; j++) {
      students[i].scores[j] = rand() % 51 + 50; // 假设成绩在50~100之间
    }
  }

  // 计算总分
  calculateTotalScore(students, numStudents, numCourses);

  // 快速排序
  quickSort(students, 0, numStudents - 1);

  // 设置名次
  for (int i = 0; i < numStudents; i++) {
    if (i == 0 || students[i].totalScore < students[i - 1].totalScore) {
      students[i].rank = i + 1;
    } else {
      students[i].rank = students[i - 1].rank;
    }
  }

  // 打印结果
  printRankAndDetails(students, numStudents, numCourses);

  return 0;
}