#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 30

// 结构体表示邻接表中的一个节点
struct Node {
  int data;
  struct Node* next;
};

// 结构体表示每个节点的邻接表
struct AdjList {
  struct Node* head;
};

// 结构体表示图
struct Graph {
  int numNodes;
  struct AdjList* array;
};

// 函数创建一个新节点
struct Node* createNode(int data) {
  struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
  newNode->data = data;
  newNode->next = NULL;
  return newNode;
}

// 函数创建一个带有给定节点数量的图
struct Graph* createGraph(int numNodes) {
  struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
  graph->numNodes = numNodes;

  // 为邻接表数组分配内存
  graph->array = (struct AdjList*)malloc(numNodes * sizeof(struct AdjList));

  // 将每个邻接表初始化为空
  for (int i = 0; i < numNodes; ++i)
    graph->array[i].head = NULL;

  return graph;
}

// 函数向无向图中添加一条边
void addEdge(struct Graph* graph, int src, int dest) {
  // 从src到dest添加一条边
  struct Node* newNode = createNode(dest);
  newNode->next = graph->array[src].head;
  graph->array[src].head = newNode;

  // 由于图是无向的，也要从dest到src添加一条边
  newNode = createNode(src);
  newNode->next = graph->array[dest].head;
  graph->array[dest].head = newNode;
}

// 深度优先搜索的递归实现
void DFSUtil(struct Graph* graph, int node, int visited[]) {
  visited[node] = 1;
  printf("%d ", node);

  struct Node* temp = graph->array[node].head;
  while (temp != NULL) {
    if (!visited[temp->data])
      DFSUtil(graph, temp->data, visited);
    temp = temp->next;
  }
}

// 执行深度优先搜索
void DFS(struct Graph* graph, int startNode) {
  int visited[MAX_NODES] = {0}; // 初始化访问数组
  printf("深度优先遍历: ");
  DFSUtil(graph, startNode, visited);
  printf("\n");
}

// 广度优先搜索的递归实现
void BFSUtil(struct Graph* graph, int queue[], int front, int rear, int visited[]) {
  if (front >= rear)
    return;

  int currentNode = queue[front++];
  printf("%d ", currentNode);

  struct Node* temp = graph->array[currentNode].head;
  while (temp != NULL) {
    if (!visited[temp->data]) {
      visited[temp->data] = 1;
      queue[rear++] = temp->data;
    }
    temp = temp->next;
  }

  BFSUtil(graph, queue, front, rear, visited);
}

// 执行广度优先搜索
void BFS(struct Graph* graph, int startNode) {
  int visited[MAX_NODES] = {0}; // 初始化访问数组
  int queue[MAX_NODES];
  int front = 0, rear = 0;

  visited[startNode] = 1;
  printf("广度优先遍历: ");
  //  printf("%d ", startNode);
  queue[rear++] = startNode;

  BFSUtil(graph, queue, front, rear, visited);

  printf("\n");
}

int main() {
  setbuf(stdout, 0);
  int numNodes, numEdges, startNode;
  printf("输入节点数量: ");
  scanf("%d", &numNodes);

  struct Graph* graph = createGraph(numNodes);

  printf("输入边的数量: ");
  scanf("%d", &numEdges);

  printf("输入边（作为节点对）:\n");
  for (int i = 0; i < numEdges; ++i) {
    int src, dest;
    scanf("%d %d", &src, &dest);
    addEdge(graph, src, dest);
  }

  printf("输入遍历的起始节点: ");
  scanf("%d", &startNode);

  DFS(graph, startNode);
  BFS(graph, startNode);

  return 0;
}
