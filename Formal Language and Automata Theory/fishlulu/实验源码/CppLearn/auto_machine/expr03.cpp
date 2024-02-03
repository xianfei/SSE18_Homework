#include<iostream>
#include<cstring>
#include<string>
#include<stack>
#include<vector>
#include<set>
#include<queue>

#define MAX 128

#define ALPHABET_SIZE 2
using namespace std;

typedef set<int> IntSet;
typedef set<char> CharSet;

/*����˵��
 * 1.�������Ӳ���������
 * 2.������׺���ʽת��׺���ʽ
 * 3.��׺���ʽתnfa
 * 4.nfaתdfa
 * 5.dfa����Ϊ��Сdfa
 * 6.���*/


/********************���ʽתNFA********************/

struct NfaState				/*����NFA״̬*/
{
  int index;				/*NFA״̬��״̬��*/
  char input;				/*NFA״̬���ϵ�ֵ*/
  int chTrans;			/*NFA״̬��ת�Ƶ���״̬��*/
  IntSet epTrans;			/*��ǰ״̬ͨ����ת�Ƶ���״̬�ż���*/
};

struct NFA
{
  NfaState *head;			/*NFA��ͷָ��*/
  NfaState *tail;			/*NFA��βָ��*/
};

NfaState NfaStates[MAX];	/*NFA״̬����*/
int nfaStateNum = 0;		/*NFA״̬����*/

/*��״̬n1��״̬n2���һ���������ϵ�ֵΪch*/
void add(NfaState *n1, NfaState *n2, char ch)
{

  n1->input = ch;
  n1->chTrans = n2->index;
}

/*��״̬n1��״̬n2���һ���������ϵ�ֵΪ��*/
void add(NfaState *n1, NfaState *n2)
{

  n1->epTrans.insert(n2->index);
}

/*�½�һ��NFA������NFA״̬������ȡ������״̬��*/
NFA creatNFA(int sum)
{
  NFA n;
  n.head = &NfaStates[sum];
  n.tail = &NfaStates[sum + 1];
  return n;
}

/*���ַ���s��nλ��������ַ�ch*/
void insert(string &s, int n, char ch)
{

  s += '#';
  for(int i = s.size() - 1; i > n; i--)
  {
    s[i] = s[i - 1];
  }
  s[n] = ch;
}

int isInAlphabet(char ch)
{
  return (ch == '0' || ch == '1');
}
/*���ַ���s����Ԥ�����ڵ�һλ�ǲ���������*����)���ҵڶ�λ�ǲ�������(��֮��������ӷ���&��*/
void preprocess(string &s)
{
  int i = 0 , length = s.size();
  while(i < length)
  {
    if(isInAlphabet(s[i]) || (s[i] == '*') || (s[i] == ')'))
    {
      if(isInAlphabet(s[i+1]) || s[i + 1] == '(')
      {
        insert(s, i+1 , '&');
        length ++;
      }
    }
    i++;
  }
}

/*��׺ת��׺ʱ�õ������ȼ��Ƚϣ���Ϊÿ����������һ��Ȩ�أ�ͨ��Ȩ�ش�С�Ƚ����ȼ�*/
int priority(char ch)
{
  if(ch == '*')
  {
    return 3;
  }
  if(ch == '&')
  {
    return 2;
  }

  if(ch ==  '+')
  {
    return 1;
  }

  if(ch == '(')
  {
    return 0;
  }
}

/*��׺���ʽת��׺���ʽ*/
string infixToSuffix(string s)
{

  preprocess(s);			/*���ַ�������Ԥ����*/

  string str;				/*Ҫ����ĺ�׺�ַ���*/
  stack<char> oper;		/*�����ջ*/

  for(int i = 0; i < s.size(); i++)
  {

    if(isInAlphabet(s[i]))	/*����ǲ�����ֱ�����*/
    {
      str += s[i];
    }
    else							/*���������ʱ*/
    {
      if(s[i] == '(')			/*����������ѹ��ջ��*/
      {
        oper.push(s[i]);
      }
      else if(s[i] == ')')	/*����������ʱ*/
      {

        char ch = oper.top();
        while(ch != '(')		/*��ջ��Ԫ�س�ջ��ֱ��ջ��Ϊ������*/
        {
          str += ch;
          oper.pop();
          ch = oper.top();
        }

        oper.pop();				/*��������ų�ջ*/
      }
      else					/*��������������ʱ*/
      {

        if(!oper.empty())			/*���ջ��Ϊ��*/
        {

          char ch = oper.top();
          while(priority(ch) >= priority(s[i]))	/*����ջ�����ȼ����ڵ��ڵ�ǰ������������*/
          {

            str +=ch;
            oper.pop();

            if(oper.empty())	/*���ջΪ�������ѭ��*/
            {
              break;
            }
            else ch = oper.top();
          }
          oper.push(s[i]);		/*�ٽ���ǰ�������ջ*/
        }
        else				/*���ջΪ�գ�ֱ�ӽ��������ջ*/
        {
          oper.push(s[i]);
        }
      }
    }
  }

  /*������ջ��Ϊ�գ����ջ��������ַ���*/
  while(!oper.empty())
  {

    char ch = oper.top();
    oper.pop();

    str += ch;
  }


  return str;
}

/*��׺���ʽתnfa*/
NFA strToNfa(string s)
{

  stack<NFA> NfaStack;		/*����һ��NFAջ*/

  for(int i = 0; i < s.size(); i++)		/*��ȡ��׺���ʽ��ÿ�ζ�һ���ַ�*/
  {

    if(isInAlphabet(s[i]))		/*����������*/
    {

      NFA n = creatNFA(nfaStateNum);		/*�½�һ��NFA*/
      nfaStateNum += 2;					/*NFA״̬������2*/

      add(n.head, n.tail, s[i]);			/*NFA��ͷָ��β�����ϵ�ֵΪs[i]*/

      NfaStack.push(n);					/*����NFA��ջ*/
    }

    else if(s[i] == '*')		/*�����հ������*/
    {

      NFA n1 = creatNFA(nfaStateNum);		/*�½�һ��NFA*/
      nfaStateNum += 2;					/*NFA״̬������2*/

      NFA n2 = NfaStack.top();			/*��ջ�е���һ��NFA*/
      NfaStack.pop();

      add(n2.tail, n1.head);				/*n2��βͨ����ָ��n1��ͷ*/
      add(n2.tail, n1.tail);				/*n2��βͨ����ָ��n1��β*/
      add(n1.head, n2.head);				/*n1��ͷͨ����ָ��n2��ͷ*/
      add(n1.head, n1.tail);				/*n1��ͷͨ����ָ��n1��β*/

      NfaStack.push(n1);					/*��������ɵ�NFA��ջ*/
    }

    else if(s[i] ==  '+')		/*�����������*/
    {

      NFA n1, n2;							/*��ջ�е�������NFA��ջ��Ϊn2����ջ��Ϊn1*/
      n2 = NfaStack.top();
      NfaStack.pop();

      n1 = NfaStack.top();
      NfaStack.pop();

      NFA n = creatNFA(nfaStateNum);		/*�½�һ��NFA*/
      nfaStateNum +=2;					/*NFA״̬������2*/

      add(n.head, n1.head);				/*n��ͷͨ����ָ��n1��ͷ*/
      add(n.head, n2.head);				/*n��ͷͨ����ָ��n2��ͷ*/
      add(n1.tail, n.tail);				/*n1��βͨ����ָ��n��β*/
      add(n2.tail, n.tail);				/*n2��βͨ����ָ��n��β*/

      NfaStack.push(n);					/*��������ɵ�NFA��ջ*/
    }

    else if(s[i] == '&')		/*�������������*/
    {

      NFA n1, n2, n;				/*����һ���µ�NFA n*/

      n2 = NfaStack.top();				/*��ջ�е�������NFA��ջ��Ϊn2����ջ��Ϊn1*/
      NfaStack.pop();

      n1 = NfaStack.top();
      NfaStack.pop();

      add(n1.tail, n2.head);				/*n1��βͨ����ָ��n2��β*/

      n.head = n1.head;					/*n��ͷΪn1��ͷ*/
      n.tail = n2.tail;					/*n��βΪn2��β*/
      NfaStack.push(n);					/*��������ɵ�NFA��ջ*/
    }
  }
  return NfaStack.top();		/*����ջ��Ԫ�ؼ�Ϊ���ɺõ�NFA*/
}


/********************NFAתDFA********************/
struct Edge			/*����DFA��ת����*/
{
  char input;			/*���ϵ�ֵ*/
  int Trans;			/*����ָ���״̬��*/
};
struct DfaState		/*����DFA״̬*/
{
  bool isEnd;			/*�Ƿ�Ϊ��̬����Ϊtrue������Ϊfalse*/
  int index;			/*DFA״̬��״̬��*/
  IntSet closure;		/*NFA�Ħ�-move()�հ�*/
  int edgeNum;		        /*DFA״̬�ϵ��������*/
  Edge Edges[10];		/*DFA״̬�ϵ������*/
};
DfaState DfaStates[MAX];		/*DFA״̬����*/
int dfaStateNum = 0;			/*DFA״̬����*/
struct DFA			/*����DFA�ṹ*/
{
  int startState;				/*DFA�ĳ�̬*/
  set<int> endStates;			/*DFA����̬��*/
  set<char> terminator;		/*DFA���ս����*/
  int trans[MAX][ALPHABET_SIZE];		/*DFA��ת�ƾ���*/
};

/*��һ��״̬���Ħ�-cloure*/
IntSet epcloure(IntSet s)
{

  stack<int> epStack;		/*(�˴�ջ�Ͷ��о���)*/

  IntSet::iterator it;
  for(it = s.begin(); it != s.end(); it++)
  {
    epStack.push(*it);			/*����״̬���е�ÿһ��Ԫ�ض�ѹ��ջ��*/
  }

  while(!epStack.empty())			/*ֻҪջ��Ϊ��*/
  {

    int temp = epStack.top();		/*��ջ�е���һ��Ԫ��*/
    epStack.pop();

    IntSet::iterator iter;
    for(iter = NfaStates[temp].epTrans.begin(); iter != NfaStates[temp].epTrans.end(); iter++)
    {
      if(!s.count(*iter))				/*������ͨ������ת������״̬��*/
      {								/*�����ǰԪ��û���ڼ����г���*/
        s.insert(*iter);			/*��������뼯����*/
        epStack.push(*iter);		/*ͬʱѹ��ջ��*/
      }
    }
  }

  return s;		/*����s��Ϊ��-cloure*/
}

/*��һ��״̬��s�Ħ�-cloure(move(ch))*/
IntSet moveEpCloure(IntSet s, char ch)
{

  IntSet temp;

  IntSet::iterator it;
  for(it = s.begin(); it != s.end(); it++)		/*������ǰ����s�е�ÿ��Ԫ��*/
  {
    if(NfaStates[*it].input == ch)				/*�����Ӧת�����ϵ�ֵΪch*/
    {
      temp.insert(NfaStates[*it].chTrans);		/*��Ѹû�ͨ��chת������״̬���뵽����temp��*/
    }
  }

  temp = epcloure(temp);			/*�����temp�Ħűհ�*/
  return temp;
}

/*�ж�һ��״̬�Ƿ�Ϊ��̬*/
bool IsEnd(NFA n, IntSet s)
{

  IntSet::iterator it;
  for(it = s.begin(); it != s.end(); it++)	/*������״̬��������nfa״̬��*/
  {
    if(*it == n.tail->index)				/*�������nfa����̬�����״̬Ϊ��̬������true*/
    {
      return true;
    }
  }

  return false;		/*�����������������̬������false*/
}

/*nfaתdfa������*/
DFA nfaToDfa(NFA n, string str)		/*����Ϊnfa�ͺ�׺���ʽ*/
{
  int i;
  DFA d;
  set<IntSet> states;		/*����һ���洢�������ϵļ��ϣ������ж����һ��״̬��s�Ħ�-cloure(move(ch))���Ƿ������״̬*/

  memset(d.trans, -1, sizeof(d.trans));	/*��ʼ��dfa��ת�ƾ���*/

  for(i = 0; i < str.size(); i++)			/*������׺���ʽ*/
  {
    if(isInAlphabet(str[i]))		/*�����������������������뵽dfa���ս������*/
    {
      d.terminator.insert(str[i]);
    }
  }

  d.startState = 0;		/*dfa�ĳ�̬Ϊ0*/

  IntSet tempSet;
  tempSet.insert(n.head->index);		/*��nfa�ĳ�̬���뵽������*/

  DfaStates[0].closure = epcloure(tempSet);		/*��dfa�ĳ�̬(��nfa��̬��ʼ�������ַ��ܵ��������״̬)*/
  DfaStates[0].isEnd = IsEnd(n, DfaStates[0].closure);		/*�жϳ�̬�Ƿ�Ϊ��̬*/

  dfaStateNum++;			/*dfa������һ*/

  queue<int> q;
  q.push(d.startState);		//������Ȳ��ҿ��ַ��ܵ��������״̬,���ʹ�ö���

  while(!q.empty())		/*ֻҪ���в�Ϊ�գ���һֱѭ��*/
  {

    int num = q.front();				/*��������Ԫ��*/
    q.pop();

    CharSet::iterator it;
    for(it = d.terminator.begin(); it != d.terminator.end(); it++)		/*�����ս����*/
    {

      IntSet temp = moveEpCloure(DfaStates[num].closure, *it);		/*����ÿ���ս���Ħ�-cloure(move(ch))*/

      if(!states.count(temp) && !temp.empty())	/*����������״̬����Ϊ������֮ǰ�������״̬����ͬ�����½�һ��DFA״̬*/
      {

        states.insert(temp);				/*�����������״̬�����뵽״̬������*/

        DfaStates[dfaStateNum].closure = temp;

        DfaStates[num].Edges[DfaStates[num].edgeNum].input = *it;				/*��״̬�������뼴Ϊ��ǰ�ս��*/
        DfaStates[num].Edges[DfaStates[num].edgeNum].Trans = dfaStateNum;		/*��ת�Ƶ���״̬Ϊ���һ��DFA״̬*/
        DfaStates[num].edgeNum++;												/*��״̬������Ŀ��һ*/

        d.trans[num][*it - '0'] = dfaStateNum;		/*����ת�ƾ���*/

        DfaStates[dfaStateNum].isEnd = IsEnd(n, DfaStates[dfaStateNum].closure);	/*�ж��Ƿ�Ϊ��̬*/

        q.push(dfaStateNum);		/*���µ�״̬�ż��������*/

        dfaStateNum++;		/*DFA״̬������һ*/
      }
      //�ɲ�������else if�ж�tempΪ�ս����Ż�?
      else if(temp.empty())
      {
        //����������״̬��Ϊ�գ������κβ�����ʡȥ�˺�������ж�
        continue;
      }
      else			/*�������״̬����֮ǰ�����ĳ��״̬����ͬ*/
      {
        for(i = 0; i < dfaStateNum; i++)		/*����֮ǰ�������״̬����*/
        {
          if(temp == DfaStates[i].closure)		/*�ҵ���ü�����ͬ��DFA״̬*/
          {

            DfaStates[num].Edges[DfaStates[num].edgeNum].input = *it;		/*��״̬�������뼴Ϊ��ǰ�ս��*/
            DfaStates[num].Edges[DfaStates[num].edgeNum].Trans = i;			/*�û�ת�Ƶ���״̬��Ϊi*/
            DfaStates[num].edgeNum++;										/*��״̬������Ŀ��һ*/

            d.trans[num][*it - '0'] = i;		/*����ת�ƾ���*/

            break;
          }
        }
      }
    }
  }

  /*����dfa����̬��*/
  for(i = 0; i < dfaStateNum; i++)	/*����dfa������״̬*/
  {
    if(DfaStates[i].isEnd == true)		/*�����״̬����̬*/
    {
      d.endStates.insert(i);		/*�򽫸�״̬�ż��뵽dfa����̬����*/
    }
  }

  return d;
}
/******************DFA����С��******************/
IntSet s[MAX];					/*���ֳ����ļ�������*/
DfaState minDfaStates[MAX];		/*minDfa״̬����*/

int minDfaStateNum = 0;			/*minDfa��״̬������ͬʱҲ�ǻ��ֳ��ļ�����*/

struct stateSet			/*����״̬��*/
{

  int index;			/*��״̬������ת������״̬�����*/
  IntSet s;			/*��״̬���е�dfa״̬��*/
};

/*��ǰ��������Ϊcount������״̬n������״̬�����i*/
int findSetNum(int count, int n)
{

  for(int i = 0; i < count; i++)
  {
    if(s[i].count(n))
    {
      return i;
    }
  }
}

/*��С��DFA*/
DFA minDFA(DFA d)
{

  int i, j;
  DFA minDfa;
  minDfa.terminator = d.terminator;		/*��dfa���ս��������minDfa*/

  memset(minDfa.trans, -1, sizeof(minDfa.trans));		/*��ʼ��minDfaת�ƾ���*/

  /*����һ�λ��֣�������̬�����̬�ֿ�*/
  bool endFlag = true;					/*�ж�dfa������״̬�Ƿ�ȫΪ��̬�ı�־*/
  for(i = 0; i < dfaStateNum; i++)	/*����dfa״̬����*/
  {
    if(DfaStates[i].isEnd == false)			/*�����dfa״̬������̬*/
    {

      endFlag = false;						/*��־ӦΪfalse*/
      minDfaStateNum = 2;						/*��һ�λ���Ӧ������������*/

      s[1].insert(DfaStates[i].index);		/*�Ѹ�״̬��״̬�ż���s[1]������*/
    }
    else									/*�����dfa״̬����̬*/
    {
      s[0].insert(DfaStates[i].index);		/*�Ѹ�״̬��״̬�ż���s[0]������*/
    }
  }

  if(endFlag)					/*�����־Ϊ�棬������dfa״̬������̬*/
  {
    minDfaStateNum = 1;			/*��һ�λ��ֽ���Ӧֻ��һ������*/
  }

  bool cutFlag = true;		/*��һ���Ƿ�����µĻ��ֵı�־*/
  while(cutFlag)				/*ֻҪ��һ�β����µĻ��־ͼ���ѭ��*/
  {

    int cutCount = 0;			/*��Ҫ�����µĻ��ֵ�����*/
    for(i = 0; i < minDfaStateNum; i++)			/*����ÿ�����ּ���*/
    {

      CharSet::iterator it;
      for(it = d.terminator.begin(); it != d.terminator.end(); it++)		/*����dfa���ս����*/
      {
        int setNum = 0;				/*��ǰ�������е�״̬������*/
        stateSet temp[20];			/*����״̬������������*/

        IntSet::iterator iter;
        for(iter = s[i].begin(); iter != s[i].end(); iter++)		/*���������е�ÿ��״̬��*/
        {
          if(s[i].size() == 1) break;		/*���������ֻ��һ��״̬������Ҫ����*/

          bool epFlag = true;			/*�жϸü������Ƿ����û�и��ս����Ӧ��ת������״̬*/
          for(j = 0; j < DfaStates[*iter].edgeNum; j++)		/*������״̬�����б�,���ҵ���Ӧ�ս���ı�*/
          {

            if(DfaStates[*iter].Edges[j].input == *it)		/*����ñߵ�����Ϊ���ս��*/
            {

              epFlag = false;			/*���־Ϊfalse*/

              /*�����״̬ת������״̬���ı��*/
              int transNum = findSetNum(minDfaStateNum, DfaStates[*iter].Edges[j].Trans);

              int curSetNum = 0;			/*������������Ѱ���Ƿ���ڵ��������ŵ�״̬��*/
              while((temp[curSetNum].index != transNum) && (curSetNum < setNum))
              {
                curSetNum++;
              }

              if(curSetNum == setNum)		/*�������в����ڵ��������ŵ�״̬��*/
              {

                /*�ڻ��������½�һ��״̬��*/
                temp[setNum].index = transNum;		/*��״̬������ת������״̬�����ΪtransNum*/
                temp[setNum].s.insert(*iter);		/*�ѵ�ǰ״̬��ӵ���״̬����*/

                setNum++;		/*�������е�״̬��������һ*/
              }
              else			/*�������д��ڵ��������ŵ�״̬��*/
              {
                temp[curSetNum].s.insert(*iter);	/*�ѵ�ǰ״̬���뵽��״̬����*/
              }
            }
          }

          if(epFlag)		/*�����״̬����������ս����Ӧ��ת����*/
          {
            /*Ѱ�һ��������Ƿ����ת�������Ϊ-1��״̬��
            ����涨���������ת�����������������״̬�����Ϊ-1*/
            int curSetNum = 0;
            while((temp[curSetNum].index != -1) && (curSetNum < setNum))
            {
              curSetNum++;
            }

            if(curSetNum == setNum)			/*���������������״̬��*/
            {

              /*�ڻ��������½�һ��״̬��*/
              temp[setNum].index = -1;			/*��״̬��ת�Ƶ���״̬�����Ϊ-1*/
              temp[setNum].s.insert(*iter);		/*�ѵ�ǰ״̬���뵽��״̬����*/

              setNum++;		/*�������е�״̬��������һ*/
            }
            else			/*�������д��ڵ��������ŵ�״̬��*/
            {
              temp[curSetNum].s.insert(*iter);	/*�ѵ�ǰ״̬���뵽��״̬����*/
            }
          }
        }

        if(setNum > 1)	/*����������е�״̬����������1����ʾͬһ��״̬���е�Ԫ����ת������ͬ��״̬��������Ҫ����*/
        {

          cutCount++;		/*���ִ�����һ*/

          /*Ϊÿ�黮�ִ����µ�dfa״̬*/
          for(j = 1; j < setNum; j++)		/*�����������������1��ʼ�ǽ���0�黮������ԭ������*/
          {

            IntSet::iterator t;

            for(t = temp[j].s.begin(); t != temp[j].s.end(); t++)
            {
              s[i].erase(*t);			/*��ԭ����״̬����ɾ����״̬*/
              s[minDfaStateNum].insert(*t);		/*���µ�״̬���м����״̬*/
            }

            minDfaStateNum++;		/*��С��DFA״̬������һ*/
          }
        }
      }
    }

    if(cutCount == 0)		/*�����Ҫ���ֵĴ���Ϊ0����ʾ���β���Ҫ���л���*/
    {
      cutFlag = false;
    }
  }

  /*����ÿ�����ֺõ�״̬��*/
  for(i = 0; i < minDfaStateNum; i++)
  {

    IntSet::iterator y;
    for(y = s[i].begin(); y != s[i].end(); y++)		/*���������е�ÿ��Ԫ��*/
    {

      if(*y == d.startState)			/*�����ǰ״̬Ϊdfa�ĳ�̬�������С��DFA״̬ҲΪ��̬*/
      {
        minDfa.startState = i;
      }

      if(d.endStates.count(*y))		/*�����ǰ״̬����̬�������С��DFA״̬ҲΪ��̬*/
      {

        minDfaStates[i].isEnd = true;
        minDfa.endStates.insert(i);		/*������С��DFA״̬������̬����*/
      }

      for(j = 0; j < DfaStates[*y].edgeNum; j++)		/*������DFA״̬��ÿ������Ϊ��С��DFA������*/
      {

        /*�������ֺõ�״̬���ϣ��ҳ��û�ת�Ƶ���״̬���������ĸ�����*/
        for(int t = 0; t < minDfaStateNum; t++)
        {
          if(s[t].count(DfaStates[*y].Edges[j].Trans))
          {

            bool haveEdge = false;		/*�жϸû��Ƿ��Ѿ������ı�־*/
            for(int l = 0; l < minDfaStates[i].edgeNum; l++)	/*�����Ѵ����Ļ�*/
            {					/*����û��Ѿ�����*/
              if((minDfaStates[i].Edges[l].input == DfaStates[*y].Edges[j].input) && (minDfaStates[i].Edges[l].Trans == t))
              {
                haveEdge = true;		/*��־Ϊ��*/
              }
            }

            if(!haveEdge)		/*����û������ڣ��򴴽�һ���µĻ�*/
            {

              minDfaStates[i].Edges[minDfaStates[i].edgeNum].input = DfaStates[*y].Edges[j].input;	/*����ֵ��DFA����ͬ*/
              minDfaStates[i].Edges[minDfaStates[i].edgeNum].Trans = t;	/*�û�ת�Ƶ���״̬Ϊ���״̬���ı��*/

              //������0-1
              minDfa.trans[i][DfaStates[*y].Edges[j].input - '0'] = t;	/*����ת�ƾ���*/

              minDfaStates[i].edgeNum++;		/*��״̬�Ļ�����Ŀ��һ*/
            }

            break;
          }
        }
      }
    }
  }

  return minDfa;
}

void printMinDFA(DFA d)
{
  int i, j;
  //************���ת�ƾ���************
  //��һ������6���ո�,���0, ,1
  cout<<"      "<<"0"<<" "<<"1"<<endl;
  int index = 0;//��ʼ��indexΪ0�������������״̬��,��̬Ϊ0
  int startFlag = false;//�Ƿ��Ѿ�����˳�̬
  //���ڴ洢����״̬��,������ӦΪԭ����״̬��,ֵ��ʼ��Ϊ-1
  int index_table[minDfaStateNum];
  for(i = 0; i < minDfaStateNum; i++)
  {
    index_table[i] = -1;
  }
  //����״̬����
  int final_minDfaTrans[minDfaStateNum+1][ALPHABET_SIZE];//+1����Ϊ��������̬
  //���ս���״̬
  IntSet final_end_states;
  //��ʼ��ת�ƾ���
  for(i = 0; i < minDfaStateNum+1; i++)
  {
    for(j = 0; j < ALPHABET_SIZE; j++)
    {
      final_minDfaTrans[i][j] = -1;
    }
  }
  queue<int> q;//������Ȳ��ҿ��ַ��ܵ��������״̬,���ʹ�ö���
  q.push(d.startState);//����̬�������

  while(!q.empty())
  {
    int state_num = q.front();//��״̬��Ϊԭ����״̬��
    q.pop();
    if(!startFlag)
    {
        //�����û�������̬
        startFlag = true;
        index_table[state_num] = index;//����״̬�Ŵ���index_table��
        cout<<"(s)";
    }
    else if(d.endStates.count(state_num)){
        cout<<"(e)";
        //�������ս���״̬����
        final_end_states.insert(index_table[state_num]);
    }
    cout<<'q'<<index_table[state_num]<<' ';

    for(j = 0; j < ALPHABET_SIZE; j++)
    {
        if(d.trans[state_num][j] != -1)
        {
          int tran_state = d.trans[state_num][j];
          //�����״̬û�з�������״̬��
          if(index_table[tran_state] == -1)
          {
              q.push(tran_state);
              index_table[tran_state] = ++index;
          }
          //���
          cout<<'q'<<index_table[tran_state]<<' ';
          final_minDfaTrans[index_table[state_num]][j] = index_table[tran_state];//����ת�ƾ���
        }
        else
        {
          cout<<"N"<<' ';
        }
    }
    cout<<endl;//����
  }
  //����������ķ�
  cout<<endl;
  IntSet end_terminators;//���ڴ洢��ת������̬���ս��
  //ͳ��û��ת��״̬��״̬����

  //����minDfaTrans����
  for (int i = 0; i < minDfaStateNum+1; ++i) {
    for (int j = 0; j < ALPHABET_SIZE; ++j) {
        if(final_minDfaTrans[i][j] != -1)
        {
          int tran_state = final_minDfaTrans[i][j];
          //�����ת��״̬û���Լ���ת��״̬,������ת��״̬���
          if(final_minDfaTrans[tran_state][0] != -1 || final_minDfaTrans[tran_state][1] != -1)
          {
              cout << "q" << i << "->";
              cout << (char)(j + '0');
              cout << 'q' << final_minDfaTrans[i][j] << endl;
          }
          if(final_end_states.count(
                  final_minDfaTrans[i][j]))//�������ת�Ƶ���̬
          {
              end_terminators.insert(j);
          }
        }
    }
    //����end_terminators
    for(int it : end_terminators)
    {
        cout << "q" << i << "->";
        cout << (char)(it + '0') << endl;
    }
    //���end_terminators
    end_terminators.clear();
  }
}
//�ж��Ƿ����ڸ������﷨�ĺ���
int isRegular(DFA minDfa,string str)
{
  int startState = minDfa.startState;//��ʼ״̬,��ʼ��Ϊ��̬
  //����str,�ж��Ƿ��ܵ�����̬
  for (int i = 0; i < str.size(); ++i) {
    char c = str[i];
    if(!minDfa.terminator.count(c))
    {
        return false;//������ڲ������ս�����ַ�,�����ڸ������﷨
    }
    int j = (int)(c-'0');
    if(minDfa.trans[startState][j] != -1)
    {
        startState = minDfa.trans[startState][j];//������ʼ״̬
    }
    else
    {
        return false;//���û��ת��״̬,�����ڸ������﷨
    }

  }
  //���������̬,�����ڸ������﷨
  if(minDfa.endStates.count(startState))
  {
    return true;//���������̬,�����ڸ������﷨
  }
}

int main()
{
  string re;
  string str;
  //��������������ʽ
  cin>>re;
  cin>>str;
  /***��ʼ�����е�����***/
  int i, j;
  for(i = 0; i < MAX; i++)
  {
    NfaStates[i].index = i;
    NfaStates[i].input = '#';
    NfaStates[i].chTrans = -1;
  }

  for(i = 0; i < MAX; i++)
  {

    DfaStates[i].index = i;
    DfaStates[i].isEnd = false;

    for(j = 0; j < 10; j++)
    {

      DfaStates[i].Edges[j].input = '#';
      DfaStates[i].Edges[j].Trans = -1;
    }
  }

  for(i = 0; i < MAX; i++)
  {

    minDfaStates[i].index = i;
    minDfaStates[i].isEnd = false;

    for(int j = 0; j < 10; j++)
    {
      minDfaStates[i].Edges[j].input = '#';
      minDfaStates[i].Edges[j].Trans = -1;
    }
  }


  NFA n = strToNfa(infixToSuffix(re));
  DFA d = nfaToDfa(n, str);
  DFA minDfa = minDFA(d);
//  printMinDFA(minDfa);
  isRegular(minDfa,str)?printf("true\n"):printf("false\n");
  return 0;
}


























