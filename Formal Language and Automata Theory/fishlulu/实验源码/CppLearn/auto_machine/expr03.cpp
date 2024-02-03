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

/*步骤说明
 * 1.正则连接操作符补充
 * 2.正则中缀表达式转后缀表达式
 * 3.后缀表达式转nfa
 * 4.nfa转dfa
 * 5.dfa化简为最小dfa
 * 6.输出*/


/********************表达式转NFA********************/

struct NfaState				/*定义NFA状态*/
{
  int index;				/*NFA状态的状态号*/
  char input;				/*NFA状态弧上的值*/
  int chTrans;			/*NFA状态弧转移到的状态号*/
  IntSet epTrans;			/*当前状态通过ε转移到的状态号集合*/
};

struct NFA
{
  NfaState *head;			/*NFA的头指针*/
  NfaState *tail;			/*NFA的尾指针*/
};

NfaState NfaStates[MAX];	/*NFA状态数组*/
int nfaStateNum = 0;		/*NFA状态总数*/

/*从状态n1到状态n2添加一条弧，弧上的值为ch*/
void add(NfaState *n1, NfaState *n2, char ch)
{

  n1->input = ch;
  n1->chTrans = n2->index;
}

/*从状态n1到状态n2添加一条弧，弧上的值为ε*/
void add(NfaState *n1, NfaState *n2)
{

  n1->epTrans.insert(n2->index);
}

/*新建一个NFA（即从NFA状态数组中取出两个状态）*/
NFA creatNFA(int sum)
{
  NFA n;
  n.head = &NfaStates[sum];
  n.tail = &NfaStates[sum + 1];
  return n;
}

/*在字符串s第n位后面插入字符ch*/
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
/*对字符串s进行预处理，在第一位是操作数、‘*’或‘)’且第二位是操作数或‘(’之间加入连接符‘&’*/
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

/*中缀转后缀时用到的优先级比较，即为每个操作符赋一个权重，通过权重大小比较优先级*/
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

/*中缀表达式转后缀表达式*/
string infixToSuffix(string s)
{

  preprocess(s);			/*对字符串进行预处理*/

  string str;				/*要输出的后缀字符串*/
  stack<char> oper;		/*运算符栈*/

  for(int i = 0; i < s.size(); i++)
  {

    if(isInAlphabet(s[i]))	/*如果是操作数直接输出*/
    {
      str += s[i];
    }
    else							/*遇到运算符时*/
    {
      if(s[i] == '(')			/*遇到左括号压入栈中*/
      {
        oper.push(s[i]);
      }
      else if(s[i] == ')')	/*遇到右括号时*/
      {

        char ch = oper.top();
        while(ch != '(')		/*将栈中元素出栈，直到栈顶为左括号*/
        {
          str += ch;
          oper.pop();
          ch = oper.top();
        }

        oper.pop();				/*最后将左括号出栈*/
      }
      else					/*遇到其他操作符时*/
      {

        if(!oper.empty())			/*如果栈不为空*/
        {

          char ch = oper.top();
          while(priority(ch) >= priority(s[i]))	/*弹出栈中优先级大于等于当前运算符的运算符*/
          {

            str +=ch;
            oper.pop();

            if(oper.empty())	/*如果栈为空则结束循环*/
            {
              break;
            }
            else ch = oper.top();
          }
          oper.push(s[i]);		/*再将当前运算符入栈*/
        }
        else				/*如果栈为空，直接将运算符入栈*/
        {
          oper.push(s[i]);
        }
      }
    }
  }

  /*最后如果栈不为空，则出栈并输出到字符串*/
  while(!oper.empty())
  {

    char ch = oper.top();
    oper.pop();

    str += ch;
  }


  return str;
}

/*后缀表达式转nfa*/
NFA strToNfa(string s)
{

  stack<NFA> NfaStack;		/*定义一个NFA栈*/

  for(int i = 0; i < s.size(); i++)		/*读取后缀表达式，每次读一个字符*/
  {

    if(isInAlphabet(s[i]))		/*遇到操作数*/
    {

      NFA n = creatNFA(nfaStateNum);		/*新建一个NFA*/
      nfaStateNum += 2;					/*NFA状态总数加2*/

      add(n.head, n.tail, s[i]);			/*NFA的头指向尾，弧上的值为s[i]*/

      NfaStack.push(n);					/*将该NFA入栈*/
    }

    else if(s[i] == '*')		/*遇到闭包运算符*/
    {

      NFA n1 = creatNFA(nfaStateNum);		/*新建一个NFA*/
      nfaStateNum += 2;					/*NFA状态总数加2*/

      NFA n2 = NfaStack.top();			/*从栈中弹出一个NFA*/
      NfaStack.pop();

      add(n2.tail, n1.head);				/*n2的尾通过ε指向n1的头*/
      add(n2.tail, n1.tail);				/*n2的尾通过ε指向n1的尾*/
      add(n1.head, n2.head);				/*n1的头通过ε指向n2的头*/
      add(n1.head, n1.tail);				/*n1的头通过ε指向n1的尾*/

      NfaStack.push(n1);					/*最后将新生成的NFA入栈*/
    }

    else if(s[i] ==  '+')		/*遇到或运算符*/
    {

      NFA n1, n2;							/*从栈中弹出两个NFA，栈顶为n2，次栈顶为n1*/
      n2 = NfaStack.top();
      NfaStack.pop();

      n1 = NfaStack.top();
      NfaStack.pop();

      NFA n = creatNFA(nfaStateNum);		/*新建一个NFA*/
      nfaStateNum +=2;					/*NFA状态总数加2*/

      add(n.head, n1.head);				/*n的头通过ε指向n1的头*/
      add(n.head, n2.head);				/*n的头通过ε指向n2的头*/
      add(n1.tail, n.tail);				/*n1的尾通过ε指向n的尾*/
      add(n2.tail, n.tail);				/*n2的尾通过ε指向n的尾*/

      NfaStack.push(n);					/*最后将新生成的NFA入栈*/
    }

    else if(s[i] == '&')		/*遇到连接运算符*/
    {

      NFA n1, n2, n;				/*定义一个新的NFA n*/

      n2 = NfaStack.top();				/*从栈中弹出两个NFA，栈顶为n2，次栈顶为n1*/
      NfaStack.pop();

      n1 = NfaStack.top();
      NfaStack.pop();

      add(n1.tail, n2.head);				/*n1的尾通过ε指向n2的尾*/

      n.head = n1.head;					/*n的头为n1的头*/
      n.tail = n2.tail;					/*n的尾为n2的尾*/
      NfaStack.push(n);					/*最后将新生成的NFA入栈*/
    }
  }
  return NfaStack.top();		/*最后的栈顶元素即为生成好的NFA*/
}


/********************NFA转DFA********************/
struct Edge			/*定义DFA的转换弧*/
{
  char input;			/*弧上的值*/
  int Trans;			/*弧所指向的状态号*/
};
struct DfaState		/*定义DFA状态*/
{
  bool isEnd;			/*是否为终态，是为true，不是为false*/
  int index;			/*DFA状态的状态号*/
  IntSet closure;		/*NFA的ε-move()闭包*/
  int edgeNum;		        /*DFA状态上的射出弧数*/
  Edge Edges[10];		/*DFA状态上的射出弧*/
};
DfaState DfaStates[MAX];		/*DFA状态数组*/
int dfaStateNum = 0;			/*DFA状态总数*/
struct DFA			/*定义DFA结构*/
{
  int startState;				/*DFA的初态*/
  set<int> endStates;			/*DFA的终态集*/
  set<char> terminator;		/*DFA的终结符集*/
  int trans[MAX][ALPHABET_SIZE];		/*DFA的转移矩阵*/
};

/*求一个状态集的ε-cloure*/
IntSet epcloure(IntSet s)
{

  stack<int> epStack;		/*(此处栈和队列均可)*/

  IntSet::iterator it;
  for(it = s.begin(); it != s.end(); it++)
  {
    epStack.push(*it);			/*将该状态集中的每一个元素都压入栈中*/
  }

  while(!epStack.empty())			/*只要栈不为空*/
  {

    int temp = epStack.top();		/*从栈中弹出一个元素*/
    epStack.pop();

    IntSet::iterator iter;
    for(iter = NfaStates[temp].epTrans.begin(); iter != NfaStates[temp].epTrans.end(); iter++)
    {
      if(!s.count(*iter))				/*遍历它通过ε能转换到的状态集*/
      {								/*如果当前元素没有在集合中出现*/
        s.insert(*iter);			/*则把它加入集合中*/
        epStack.push(*iter);		/*同时压入栈中*/
      }
    }
  }

  return s;		/*最后的s即为ε-cloure*/
}

/*求一个状态集s的ε-cloure(move(ch))*/
IntSet moveEpCloure(IntSet s, char ch)
{

  IntSet temp;

  IntSet::iterator it;
  for(it = s.begin(); it != s.end(); it++)		/*遍历当前集合s中的每个元素*/
  {
    if(NfaStates[*it].input == ch)				/*如果对应转换弧上的值为ch*/
    {
      temp.insert(NfaStates[*it].chTrans);		/*则把该弧通过ch转换到的状态加入到集合temp中*/
    }
  }

  temp = epcloure(temp);			/*最后求temp的ε闭包*/
  return temp;
}

/*判断一个状态是否为终态*/
bool IsEnd(NFA n, IntSet s)
{

  IntSet::iterator it;
  for(it = s.begin(); it != s.end(); it++)	/*遍历该状态所包含的nfa状态集*/
  {
    if(*it == n.tail->index)				/*如果包含nfa的终态，则该状态为终态，返回true*/
    {
      return true;
    }
  }

  return false;		/*如果不包含，则不是终态，返回false*/
}

/*nfa转dfa主函数*/
DFA nfaToDfa(NFA n, string str)		/*参数为nfa和后缀表达式*/
{
  int i;
  DFA d;
  set<IntSet> states;		/*定义一个存储整数集合的集合，用于判断求出一个状态集s的ε-cloure(move(ch))后是否出现新状态*/

  memset(d.trans, -1, sizeof(d.trans));	/*初始化dfa的转移矩阵*/

  for(i = 0; i < str.size(); i++)			/*遍历后缀表达式*/
  {
    if(isInAlphabet(str[i]))		/*如果遇到操作数，则把它加入到dfa的终结符集中*/
    {
      d.terminator.insert(str[i]);
    }
  }

  d.startState = 0;		/*dfa的初态为0*/

  IntSet tempSet;
  tempSet.insert(n.head->index);		/*将nfa的初态加入到集合中*/

  DfaStates[0].closure = epcloure(tempSet);		/*求dfa的初态(从nfa初态开始经过空字符能到达的所有状态)*/
  DfaStates[0].isEnd = IsEnd(n, DfaStates[0].closure);		/*判断初态是否为终态*/

  dfaStateNum++;			/*dfa数量加一*/

  queue<int> q;
  q.push(d.startState);		//广度优先查找空字符能到达的所有状态,因此使用队列

  while(!q.empty())		/*只要队列不为空，就一直循环*/
  {

    int num = q.front();				/*弹出队首元素*/
    q.pop();

    CharSet::iterator it;
    for(it = d.terminator.begin(); it != d.terminator.end(); it++)		/*遍历终结符集*/
    {

      IntSet temp = moveEpCloure(DfaStates[num].closure, *it);		/*计算每个终结符的ε-cloure(move(ch))*/

      if(!states.count(temp) && !temp.empty())	/*如果求出来的状态集不为空且与之前求出来的状态集不同，则新建一个DFA状态*/
      {

        states.insert(temp);				/*将新求出来的状态集加入到状态集合中*/

        DfaStates[dfaStateNum].closure = temp;

        DfaStates[num].Edges[DfaStates[num].edgeNum].input = *it;				/*该状态弧的输入即为当前终结符*/
        DfaStates[num].Edges[DfaStates[num].edgeNum].Trans = dfaStateNum;		/*弧转移到的状态为最后一个DFA状态*/
        DfaStates[num].edgeNum++;												/*该状态弧的数目加一*/

        d.trans[num][*it - '0'] = dfaStateNum;		/*更新转移矩阵*/

        DfaStates[dfaStateNum].isEnd = IsEnd(n, DfaStates[dfaStateNum].closure);	/*判断是否为终态*/

        q.push(dfaStateNum);		/*将新的状态号加入队列中*/

        dfaStateNum++;		/*DFA状态总数加一*/
      }
      //可不可以用else if判断temp为空进行优化?
      else if(temp.empty())
      {
        //如果求出来的状态集为空，则不做任何操作，省去了后面遍历判断
        continue;
      }
      else			/*求出来的状态集在之前求出的某个状态集相同*/
      {
        for(i = 0; i < dfaStateNum; i++)		/*遍历之前求出来的状态集合*/
        {
          if(temp == DfaStates[i].closure)		/*找到与该集合相同的DFA状态*/
          {

            DfaStates[num].Edges[DfaStates[num].edgeNum].input = *it;		/*该状态弧的输入即为当前终结符*/
            DfaStates[num].Edges[DfaStates[num].edgeNum].Trans = i;			/*该弧转移到的状态即为i*/
            DfaStates[num].edgeNum++;										/*该状态弧的数目加一*/

            d.trans[num][*it - '0'] = i;		/*更新转移矩阵*/

            break;
          }
        }
      }
    }
  }

  /*计算dfa的终态集*/
  for(i = 0; i < dfaStateNum; i++)	/*遍历dfa的所有状态*/
  {
    if(DfaStates[i].isEnd == true)		/*如果该状态是终态*/
    {
      d.endStates.insert(i);		/*则将该状态号加入到dfa的终态集中*/
    }
  }

  return d;
}
/******************DFA的最小化******************/
IntSet s[MAX];					/*划分出来的集合数组*/
DfaState minDfaStates[MAX];		/*minDfa状态数组*/

int minDfaStateNum = 0;			/*minDfa的状态总数，同时也是划分出的集合数*/

struct stateSet			/*划分状态集*/
{

  int index;			/*该状态集所能转换到的状态集标号*/
  IntSet s;			/*该状态集中的dfa状态号*/
};

/*当前划分总数为count，返回状态n所属的状态集标号i*/
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

/*最小化DFA*/
DFA minDFA(DFA d)
{

  int i, j;
  DFA minDfa;
  minDfa.terminator = d.terminator;		/*把dfa的终结符集赋给minDfa*/

  memset(minDfa.trans, -1, sizeof(minDfa.trans));		/*初始化minDfa转移矩阵*/

  /*做第一次划分，即将终态与非终态分开*/
  bool endFlag = true;					/*判断dfa的所有状态是否全为终态的标志*/
  for(i = 0; i < dfaStateNum; i++)	/*遍历dfa状态数组*/
  {
    if(DfaStates[i].isEnd == false)			/*如果该dfa状态不是终态*/
    {

      endFlag = false;						/*标志应为false*/
      minDfaStateNum = 2;						/*第一次划分应该有两个集合*/

      s[1].insert(DfaStates[i].index);		/*把该状态的状态号加入s[1]集合中*/
    }
    else									/*如果该dfa状态是终态*/
    {
      s[0].insert(DfaStates[i].index);		/*把该状态的状态号加入s[0]集合中*/
    }
  }

  if(endFlag)					/*如果标志为真，则所有dfa状态都是终态*/
  {
    minDfaStateNum = 1;			/*第一次划分结束应只有一个集合*/
  }

  bool cutFlag = true;		/*上一次是否产生新的划分的标志*/
  while(cutFlag)				/*只要上一次产生新的划分就继续循环*/
  {

    int cutCount = 0;			/*需要产生新的划分的数量*/
    for(i = 0; i < minDfaStateNum; i++)			/*遍历每个划分集合*/
    {

      CharSet::iterator it;
      for(it = d.terminator.begin(); it != d.terminator.end(); it++)		/*遍历dfa的终结符集*/
      {
        int setNum = 0;				/*当前缓冲区中的状态集个数*/
        stateSet temp[20];			/*划分状态集“缓冲区”*/

        IntSet::iterator iter;
        for(iter = s[i].begin(); iter != s[i].end(); iter++)		/*遍历集合中的每个状态号*/
        {
          if(s[i].size() == 1) break;		/*如果集合中只有一个状态，则不需要划分*/

          bool epFlag = true;			/*判断该集合中是否存在没有该终结符对应的转换弧的状态*/
          for(j = 0; j < DfaStates[*iter].edgeNum; j++)		/*遍历该状态的所有边,来找到对应终结符的边*/
          {

            if(DfaStates[*iter].Edges[j].input == *it)		/*如果该边的输入为该终结符*/
            {

              epFlag = false;			/*则标志为false*/

              /*计算该状态转换到的状态集的标号*/
              int transNum = findSetNum(minDfaStateNum, DfaStates[*iter].Edges[j].Trans);

              int curSetNum = 0;			/*遍历缓冲区，寻找是否存在到达这个标号的状态集*/
              while((temp[curSetNum].index != transNum) && (curSetNum < setNum))
              {
                curSetNum++;
              }

              if(curSetNum == setNum)		/*缓冲区中不存在到达这个标号的状态集*/
              {

                /*在缓冲区中新建一个状态集*/
                temp[setNum].index = transNum;		/*该状态集所能转换到的状态集标号为transNum*/
                temp[setNum].s.insert(*iter);		/*把当前状态添加到该状态集中*/

                setNum++;		/*缓冲区中的状态集个数加一*/
              }
              else			/*缓冲区中存在到达这个标号的状态集*/
              {
                temp[curSetNum].s.insert(*iter);	/*把当前状态加入到该状态集中*/
              }
            }
          }

          if(epFlag)		/*如果该状态不存在与该终结符对应的转换弧*/
          {
            /*寻找缓冲区中是否存在转换到标号为-1的状态集
            这里规定如果不存在转换弧，则它所到达的状态集标号为-1*/
            int curSetNum = 0;
            while((temp[curSetNum].index != -1) && (curSetNum < setNum))
            {
              curSetNum++;
            }

            if(curSetNum == setNum)			/*如果不存在这样的状态集*/
            {

              /*在缓冲区中新建一个状态集*/
              temp[setNum].index = -1;			/*该状态集转移到的状态集标号为-1*/
              temp[setNum].s.insert(*iter);		/*把当前状态加入到该状态集中*/

              setNum++;		/*缓冲区中的状态集个数加一*/
            }
            else			/*缓冲区中存在到达这个标号的状态集*/
            {
              temp[curSetNum].s.insert(*iter);	/*把当前状态加入到该状态集中*/
            }
          }
        }

        if(setNum > 1)	/*如果缓冲区中的状态集个数大于1，表示同一个状态集中的元素能转换到不同的状态集，则需要划分*/
        {

          cutCount++;		/*划分次数加一*/

          /*为每组划分创建新的dfa状态*/
          for(j = 1; j < setNum; j++)		/*遍历缓冲区，这里从1开始是将第0组划分留在原集合中*/
          {

            IntSet::iterator t;

            for(t = temp[j].s.begin(); t != temp[j].s.end(); t++)
            {
              s[i].erase(*t);			/*在原来的状态集中删除该状态*/
              s[minDfaStateNum].insert(*t);		/*在新的状态集中加入该状态*/
            }

            minDfaStateNum++;		/*最小化DFA状态总数加一*/
          }
        }
      }
    }

    if(cutCount == 0)		/*如果需要划分的次数为0，表示本次不需要进行划分*/
    {
      cutFlag = false;
    }
  }

  /*遍历每个划分好的状态集*/
  for(i = 0; i < minDfaStateNum; i++)
  {

    IntSet::iterator y;
    for(y = s[i].begin(); y != s[i].end(); y++)		/*遍历集合中的每个元素*/
    {

      if(*y == d.startState)			/*如果当前状态为dfa的初态，则该最小化DFA状态也为初态*/
      {
        minDfa.startState = i;
      }

      if(d.endStates.count(*y))		/*如果当前状态是终态，则该最小化DFA状态也为终态*/
      {

        minDfaStates[i].isEnd = true;
        minDfa.endStates.insert(i);		/*将该最小化DFA状态加入终态集中*/
      }

      for(j = 0; j < DfaStates[*y].edgeNum; j++)		/*遍历该DFA状态的每条弧，为最小化DFA创建弧*/
      {

        /*遍历划分好的状态集合，找出该弧转移到的状态现在属于哪个集合*/
        for(int t = 0; t < minDfaStateNum; t++)
        {
          if(s[t].count(DfaStates[*y].Edges[j].Trans))
          {

            bool haveEdge = false;		/*判断该弧是否已经创建的标志*/
            for(int l = 0; l < minDfaStates[i].edgeNum; l++)	/*遍历已创建的弧*/
            {					/*如果该弧已经存在*/
              if((minDfaStates[i].Edges[l].input == DfaStates[*y].Edges[j].input) && (minDfaStates[i].Edges[l].Trans == t))
              {
                haveEdge = true;		/*标志为真*/
              }
            }

            if(!haveEdge)		/*如果该弧不存在，则创建一条新的弧*/
            {

              minDfaStates[i].Edges[minDfaStates[i].edgeNum].input = DfaStates[*y].Edges[j].input;	/*弧的值与DFA的相同*/
              minDfaStates[i].Edges[minDfaStates[i].edgeNum].Trans = t;	/*该弧转移到的状态为这个状态集的标号*/

              //适用于0-1
              minDfa.trans[i][DfaStates[*y].Edges[j].input - '0'] = t;	/*更新转移矩阵*/

              minDfaStates[i].edgeNum++;		/*该状态的弧的数目加一*/
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
  //************输出转移矩阵************
  //第一行输入6个空格,输出0, ,1
  cout<<"      "<<"0"<<" "<<"1"<<endl;
  int index = 0;//初始化index为0，用于输出最终状态号,初态为0
  int startFlag = false;//是否已经输出了初态
  //用于存储最终状态号,索引对应为原来的状态号,值初始化为-1
  int index_table[minDfaStateNum];
  for(i = 0; i < minDfaStateNum; i++)
  {
    index_table[i] = -1;
  }
  //最终状态矩阵
  int final_minDfaTrans[minDfaStateNum+1][ALPHABET_SIZE];//+1是因为还有陷阱态
  //最终结束状态
  IntSet final_end_states;
  //初始化转移矩阵
  for(i = 0; i < minDfaStateNum+1; i++)
  {
    for(j = 0; j < ALPHABET_SIZE; j++)
    {
      final_minDfaTrans[i][j] = -1;
    }
  }
  queue<int> q;//广度优先查找空字符能到达的所有状态,因此使用队列
  q.push(d.startState);//将初态加入队列

  while(!q.empty())
  {
    int state_num = q.front();//该状态号为原来的状态号
    q.pop();
    if(!startFlag)
    {
        //如果还没有输出初态
        startFlag = true;
        index_table[state_num] = index;//将该状态号存入index_table中
        cout<<"(s)";
    }
    else if(d.endStates.count(state_num)){
        cout<<"(e)";
        //更新最终结束状态集合
        final_end_states.insert(index_table[state_num]);
    }
    cout<<'q'<<index_table[state_num]<<' ';

    for(j = 0; j < ALPHABET_SIZE; j++)
    {
        if(d.trans[state_num][j] != -1)
        {
          int tran_state = d.trans[state_num][j];
          //如果该状态没有分配最终状态号
          if(index_table[tran_state] == -1)
          {
              q.push(tran_state);
              index_table[tran_state] = ++index;
          }
          //输出
          cout<<'q'<<index_table[tran_state]<<' ';
          final_minDfaTrans[index_table[state_num]][j] = index_table[tran_state];//更新转移矩阵
        }
        else
        {
          cout<<"N"<<' ';
        }
    }
    cout<<endl;//换行
  }
  //输出右线性文法
  cout<<endl;
  IntSet end_terminators;//用于存储能转换到终态的终结符
  //统计没有转移状态的状态集合

  //遍历minDfaTrans数组
  for (int i = 0; i < minDfaStateNum+1; ++i) {
    for (int j = 0; j < ALPHABET_SIZE; ++j) {
        if(final_minDfaTrans[i][j] != -1)
        {
          int tran_state = final_minDfaTrans[i][j];
          //如果该转移状态没有自己的转移状态,则带这个转移状态输出
          if(final_minDfaTrans[tran_state][0] != -1 || final_minDfaTrans[tran_state][1] != -1)
          {
              cout << "q" << i << "->";
              cout << (char)(j + '0');
              cout << 'q' << final_minDfaTrans[i][j] << endl;
          }
          if(final_end_states.count(
                  final_minDfaTrans[i][j]))//如果可以转移到终态
          {
              end_terminators.insert(j);
          }
        }
    }
    //遍历end_terminators
    for(int it : end_terminators)
    {
        cout << "q" << i << "->";
        cout << (char)(it + '0') << endl;
    }
    //清空end_terminators
    end_terminators.clear();
  }
}
//判断是否属于该正则语法的函数
int isRegular(DFA minDfa,string str)
{
  int startState = minDfa.startState;//起始状态,初始化为初态
  //遍历str,判断是否能到达终态
  for (int i = 0; i < str.size(); ++i) {
    char c = str[i];
    if(!minDfa.terminator.count(c))
    {
        return false;//如果存在不属于终结符的字符,则不属于该正则语法
    }
    int j = (int)(c-'0');
    if(minDfa.trans[startState][j] != -1)
    {
        startState = minDfa.trans[startState][j];//更新起始状态
    }
    else
    {
        return false;//如果没有转移状态,则不属于该正则语法
    }

  }
  //如果到达终态,则属于该正则语法
  if(minDfa.endStates.count(startState))
  {
    return true;//如果到达终态,则属于该正则语法
  }
}

int main()
{
  string re;
  string str;
  //键盘输入正则表达式
  cin>>re;
  cin>>str;
  /***初始化所有的数组***/
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


























