#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <stdexcept>

std::stack<int>state;
std::stack<std::string>symbol;
std::stack<std::string>w;

std::string action[30][8]= {
    {"S4","","","","","S5","",""},             //0
    {"","","S6","S7","","","","ACC"},          //1
    {"","","R3","R3","S8","S9","","R3"},       //2
    {"","","R6","R6","R6","R6","","R6"},       //3
    {"S13","","","","","","S14",""},           //4
    {"","","R8","R8","R8","R8","","R8"},       //5
    {"S4","","","","","","S5",""},             //6
    {"S4","","","","","","S5",""},             //7
    {"S4","","","","","","S5",""},             //8
    {"S4","","","","","","S5",""},             //9
    {"","S19","S20","S21","","","",""},        //10
    {"","R3","R3","R3","S22","S23","",""},     //11
    {"","R6","R6","R6","R6","R6","",""},       //12
    {"S13","","","","","","S14",""},           //13
    {"","R8","R8","R8","R8","R8","",""},       //14
    {"","","R1","R1","S8","S9","","R1"},       //15
    {"","","R2","R2","S8","S9","","R2"},       //16
    {"","","R4","R4","R4","R4","","R4"},       //17
    {"","","R5","R5","R5","R5","","R5"},       //18
    {"","","R7","R7","R7","R7","","R7"},       //19
    {"S13","","","","","","S14",""},           //20
    {"S13","","","","","","S14",""},           //21
    {"S13","","","","","","S14",""},           //22
    {"S13","","","","","","S14",""},           //23
    {"","S28","S20","S21","","","",""},        //24
    {"","R1","R1","R1","S22","S23","",""},     //25
    {"","R4","R4","R4","R4","R4","",""},       //26
    {"","R5","R5","R5","R5","R5","",""},       //27
    {"","R7","R7","R7","R7","R7","",""},       //28
    {"","R2","R2","R2","S22","S23","",""}};    //29

int go_to[30][3]= {
    {1,2,3},       //0
    {-1,-1,-1},    //1
    {-1,-1,-1},    //2
    {-1,-1,-1},    //3
    {10,11,12},    //4
    {-1,-1,-1},    //5
    {-1,15,3},     //6
    {-1,16,3},     //7
    {-1,-1,17},    //8
    {-1,-1,18},    //9
    {-1,-1,-1},    //10
    {-1,-1,-1},    //11
    {-1,-1,-1},    //12
    {24,11,12},    //13
    {-1,-1,-1},    //14
    {-1,-1,-1},    //15
    {-1,-1,-1},    //16
    {-1,-1,-1},    //17
    {-1,-1,-1},    //18
    {-1,-1,-1},    //19
    {-1,25,12},    //20
    {-1,29,12},    //21
    {-1,-1,26},    //22
    {-1,-1,27},    //23
    {-1,-1,-1},    //24
    {-1,-1,-1},    //25
    {-1,-1,-1},    //26
    {-1,-1,-1},    //27
    {-1,-1,-1},    //28
    {-1,-1,-1}     //29
};

const char* expressions[9]={nullptr,"E->E+T","E->E-T","E->T","T->T*F","T->T/F","T->F","F->(E)","F->num"};

template <typename T>
std::string stack_to_str(std::stack<T> st){ //输出栈 转换为字符串
    std::stringstream ss;
    ss<<'[';
    std::stack<T> stack;
    while (!st.empty()) {
        stack.push(st.top());
        st.pop();
    }
    for(;!stack.empty();stack.pop()) {
        T element = stack.top();
        ss<< element;
        ss<<", ";
    }
    std::string s=ss.str().substr(0,ss.str().length()-2); //删除最后一个", "
    s+=']';
    return s;
}

void reduce(std::string action_string) {
    switch (std::atoi(action_string.c_str()+1)) {
        case 1: //用产生式E->E+T
            //pop出3个元素
            for(int i=0;i<3;i++){
                state.pop();
                symbol.pop();
            }
            //将当前元素push进去
            symbol.push("E");
            if(go_to[state.top()][0]==-1) throw std::runtime_error("illegal goto");
            state.push(go_to[state.top()][0]);
            break;
        case 2: //用产生式E->E-T
            //pop出3个元素
            for(int i=0;i<3;i++){
                state.pop();
                symbol.pop();
            }
            //将当前元素push进去
            symbol.push("E");
            if(go_to[state.top()][0]==-1) throw std::runtime_error("illegal goto");
            state.push(go_to[state.top()][0]);
            break;
        case 3://用产生式E->T
            //pop出1个元素
            state.pop();
            symbol.pop();
            //将当前元素push进去
            symbol.push("E");
            if(go_to[state.top()][0]==-1) throw std::runtime_error("illegal goto");
            state.push(go_to[state.top()][0]);
            break;
        case 4:  //用产生式T->T*F
            //pop出3个元素
            for(int i=0;i<3;i++){
                state.pop();
                symbol.pop();
            }
            //将当前元素push进去
            symbol.push("T");
            if(go_to[state.top()][1]==-1) throw std::runtime_error("illegal goto");
            state.push(go_to[state.top()][1]);
            break;
        case 5: //用产生式T->T/F
            //pop出3个元素
            for(int i=0;i<3;i++){
                state.pop();
                symbol.pop();
            }
            //将当前元素push进去
            symbol.push("T");
            if(go_to[state.top()][1]==-1) throw std::runtime_error("illegal goto");
            state.push(go_to[state.top()][1]);
            break;
        case 6: //用产生式T->F
            //pop出1个元素
            state.pop();
            symbol.pop();
            //将当前元素push进去
            symbol.push("T");
            if(go_to[state.top()][1]==-1) throw std::runtime_error("illegal goto");
            state.push(go_to[state.top()][1]);
            break;
        case 7: //用产生式F->(E)
            //pop出3个元素
            for(int i=0;i<3;i++){
                state.pop();
                symbol.pop();
            }
            //将当前元素push进去
            symbol.push("F");
            if(go_to[state.top()][2]==-1) throw std::runtime_error("illegal goto");
            state.push(go_to[state.top()][2]);
            break;
        case 8: //用产生式F->num
            //pop出1个元素
            state.pop();
            symbol.pop();
            //将当前元素push进去
            symbol.push("F");
            if(go_to[state.top()][2]==-1) throw std::runtime_error("illegal goto");
            state.push(go_to[state.top()][2]);
            break;
    }
}

void output(int step,std::string action_string){
    // 输出步骤序号
    std::cout << step << "\t";
    // 输出状态栈
    std::printf("%-30s",stack_to_str(state).c_str());
    // 输出符号栈
    std::printf("%-26s\t",stack_to_str(symbol).c_str());
    // 输出输入符号流
    std::string expressionString;
    for (auto dump = w; !dump.empty(); dump.pop())
    expressionString+= dump.top() ;
    std::printf("%25s",(expressionString).c_str());
    // 输出分析动作
    switch (action_string[0]) {
        case 'R':
            std::cout << "\treduce by " << expressions[std::atoi(action_string.c_str()+1)] << std::endl;
            break;
        case 'S':
            std::cout << "\tshift " << action_string.c_str()+1 << std::endl;
            break;
        case 'A':
            std::cout << "\t接受成功"<< std::endl;
            break;
        default:
            throw std::logic_error("impossible");
    }
}

void analyse(std::string input_string) {
    std::stack<std::string> s;
    for(int i=0;i<input_string.length();i++) {
        if(input_string[i]!='n') s.push(std::string{input_string[i]});
        else {
            char temp[4]={0};
            temp[0]=input_string[i];
            temp[1]=input_string[i+1];
            temp[2]=input_string[i+2];
            s.push(temp);
            i=i+2;
        }
    }
    std::cout <<"步骤\t\t\t\t状态栈\t\t\t\t\t\t符号栈\t\t\t\t\t\t\t输入符号流\t\t\t分析动作\n";
    while (!s.empty()){
        w.push(s.top());
        s.pop();
    }
    state.push(0);
    symbol.push("$");
    int step=0;
    while (!w.empty()) {
        //栈顶状态
        step++;
        int temp_state=state.top();
        std::string action_string;
        std::string temp_s=w.top();
        if(w.top()==std::string("(")) {
            //遇到“(”时的动作
            action_string=action[temp_state][0];
            if(action_string==std::string("")) throw std::runtime_error("illegal action");
            //移进
            if(action_string[0]=='S') {
                output(step, action_string);
                state.push(std::atoi(action_string.c_str()+1));
                symbol.push(w.top());
                w.pop();
            }
            //规约
            else if(action_string[0]=='R') {
                output(step, action_string);
                reduce(action_string);
            }
        }
        else if(w.top()==std::string(")")) {
            //遇到“)”时的动作
            action_string=action[temp_state][1];
            if(action_string==std::string("")) throw std::runtime_error("illegal action");
            //移进
            if(action_string[0]=='S') {
                output(step, action_string);
                state.push(std::atoi(action_string.c_str()+1));
                symbol.push(w.top());
                w.pop();
            }
            //规约
            else if(action_string[0]=='R') {
                output(step, action_string);
                reduce(action_string);
            }
        }
        else if(w.top()==std::string("+")) {
            //遇到“+”时的动作
            action_string=action[temp_state][2];
            if(action_string==std::string("")) throw std::runtime_error("illegal action");
            //移进
            if(action_string[0]=='S') {
                output(step, action_string);
                state.push(std::atoi(action_string.c_str()+1));
                symbol.push(w.top());
                w.pop();
            }
            //规约
            else if(action_string[0]=='R') {
                output(step, action_string);
                reduce(action_string);
            }
        }
        else if(w.top()==std::string("-")) {
            //遇到“-”时的动作
            action_string=action[temp_state][3];
            if(action_string==std::string("")) throw std::runtime_error("illegal action");
            //移进
            if(action_string[0]=='S') {
                output(step, action_string);
                state.push(std::atoi(action_string.c_str()+1));
                symbol.push(w.top());
                w.pop();
            }
            //规约
            else if(action_string[0]=='R') {
                output(step, action_string);
                reduce(action_string);
            }
        }
        else if(w.top()==std::string("*")) {
            //遇到“*”时的动作
            action_string=action[temp_state][4];
            if(action_string==std::string("")) throw std::runtime_error("illegal action");
            //移进
            if(action_string[0]=='S') {
                output(step, action_string);
                state.push(std::atoi(action_string.c_str()+1));
                symbol.push(w.top());
                w.pop();
            }
            //规约
            else if(action_string[0]=='R') {
                output(step, action_string);
                reduce(action_string);
            }
        }
        else if(w.top()==std::string("/")) {
            //遇到“/”时的动作
            action_string=action[temp_state][5];
            if(action_string==std::string("")) throw std::runtime_error("illegal action");
            //移进
            if(action_string[0]=='S') {
                output(step, action_string);
                state.push(std::atoi(action_string.c_str()+1));
                symbol.push(w.top());
                w.pop();
            }
            //规约
            else if(action_string[0]=='R') {
                output(step, action_string);
                reduce(action_string);
            }
        }
        else if(w.top()==std::string("num")) {
            //遇到“num”时的动作
            action_string=action[temp_state][6];
            if(action_string==std::string(""))throw std::runtime_error("illegal action");
            //移进
            if(action_string[0]=='S') {
                output(step, action_string);
                state.push(std::atoi(action_string.c_str()+1));
                symbol.push(w.top());
                w.pop();
            }
            //规约
            else if(action_string[0]=='R') {
                output(step, action_string);
                reduce(action_string);
            }
        }
        else if(w.top()==std::string("$")) {
            //遇到“$”时的动作
            action_string=action[temp_state][7];
            if(action_string==std::string("")) throw std::runtime_error("illegal action");
            //接受符号串
            if(action_string==std::string("ACC")) {
                output(step, action_string);
                state.pop();
                symbol.pop();
                w.pop();
            }
            //移进
            if(action_string[0]=='S') {
                output(step, action_string);
                state.push(std::atoi(action_string.c_str()+1));
                symbol.push(w.top());
                w.pop();
            }
            //规约
            else if(action_string[0]=='R') {
                output(step, action_string);
                reduce(action_string);
            }
        }else throw std::runtime_error(std::string("illegal character ")+w.top());
    }
}

int main(){
    std::string string = "(num*num+(num/num)$";
    std::cout << "输入为：" << string << "\n分析结果：\n";
//    try{
        analyse(string);
//    }catch(std::exception &e){
//        std::cerr << "分析错误 " << e.what() << std::endl ;
//        return -1;
//    }
    return 0;
}

