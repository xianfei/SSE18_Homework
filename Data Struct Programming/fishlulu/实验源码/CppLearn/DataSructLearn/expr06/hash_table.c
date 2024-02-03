//使用哈希表链地址法解决冲突
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_LEN 20
#define MAX_NAME_NUM 30
//选择一个素数作为哈希表的长度
#define HASH_SIZE 53

typedef struct HashNode
{
  char name[MAX_NAME_LEN];
  struct HashNode *next;
} HashNode, *pHashNode;
typedef struct HashTable
{
  struct HashNode* slots[HASH_SIZE];//指向第一个节点
  short lens[HASH_SIZE];//记录链表长度
} HashTable,*pHashTable;

int hash(char* name) {
  int sum = 0;
  while (*name != '\0') {
    if (*name >= 'A' && *name <= 'Z') {
      sum += *name;
    }
    name++;
  }
  return sum % HASH_SIZE;
}
pHashTable hashTableBuild(char** nameList,int nameNum)
{
    //构造哈希表
    pHashTable pTable = (pHashTable)malloc(sizeof(HashTable));
    //初始化哈希表
    for (int i = 0; i < HASH_SIZE; i++)
    {
      pTable->slots[i] = NULL;
      pTable->lens[i] = 0;
    }
    //遍历名字列表,将名字插入哈希表
    for (int i = 0; i < nameNum; i++)
    {
      //计算哈希值
      int hashValue = hash(nameList[i]);
      //创建新节点
      pHashNode pNewNode = (pHashNode)malloc(sizeof(HashNode));
      strcpy(pNewNode->name, nameList[i]);
      pNewNode->next = NULL;
      //将新节点插入哈希表
      if (pTable->slots[hashValue] == NULL)
      {
        pTable->slots[hashValue] = pNewNode;
        pTable->lens[hashValue] = 1;
      }
      else
      {
        pHashNode pCurNode = pTable->slots[hashValue];
        while (pCurNode->next != NULL)
        {
          pCurNode = pCurNode->next;
        }
          pCurNode->next = pNewNode;
          pTable->lens[hashValue]++;
        }
    }
    return pTable;

}
int main()
{

    char* nameList[MAX_NAME_NUM] = {
        "ZhangXiaoHong", "LiMing", "WangLei", "ChenWei", "ZhaoYun", "LiuXiao", "SunXiaoyu",
        "HuangQiang", "XuJing", "YangYang", "HeYan", "DengHui", "LinFang", "CaiLing", "LuJun",
        "GaoXin", "FengMei", "YuJie", "XieCheng", "HuJia", "JiangWen", "TangFei", "ShiQingZheng",
        "XiaoLan", "SongHua", "YuanLi", "HanXue", "MoYun", "RenWei","OuYangXiaoLan"
    };
    int nameNum = 30;
    pHashTable pTable = hashTableBuild(nameList, nameNum);

    //遍历哈希表
    for (int i = 0; i < HASH_SIZE; i++)
    {
      printf("第%d个槽位有%d个元素\n", i, pTable->lens[i]);
      pHashNode pCurNode = pTable->slots[i];
      while (pCurNode != NULL)
      {
            printf("%s ", pCurNode->name);
            pCurNode = pCurNode->next;
      }
      printf("\n");
    }
}


