//ʹ�ù�ϣ������ַ�������ͻ
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_LEN 20
#define MAX_NAME_NUM 30
//ѡ��һ��������Ϊ��ϣ��ĳ���
#define HASH_SIZE 53

typedef struct HashNode
{
  char name[MAX_NAME_LEN];
  struct HashNode *next;
} HashNode, *pHashNode;
typedef struct HashTable
{
  struct HashNode* slots[HASH_SIZE];//ָ���һ���ڵ�
  short lens[HASH_SIZE];//��¼������
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
    //�����ϣ��
    pHashTable pTable = (pHashTable)malloc(sizeof(HashTable));
    //��ʼ����ϣ��
    for (int i = 0; i < HASH_SIZE; i++)
    {
      pTable->slots[i] = NULL;
      pTable->lens[i] = 0;
    }
    //���������б�,�����ֲ����ϣ��
    for (int i = 0; i < nameNum; i++)
    {
      //�����ϣֵ
      int hashValue = hash(nameList[i]);
      //�����½ڵ�
      pHashNode pNewNode = (pHashNode)malloc(sizeof(HashNode));
      strcpy(pNewNode->name, nameList[i]);
      pNewNode->next = NULL;
      //���½ڵ�����ϣ��
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

    //������ϣ��
    for (int i = 0; i < HASH_SIZE; i++)
    {
      printf("��%d����λ��%d��Ԫ��\n", i, pTable->lens[i]);
      pHashNode pCurNode = pTable->slots[i];
      while (pCurNode != NULL)
      {
            printf("%s ", pCurNode->name);
            pCurNode = pCurNode->next;
      }
      printf("\n");
    }
}


