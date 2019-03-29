#pragma once
#include<iostream>
#define elementType int
#define MAXLEN 1024

using namespace std;

//顺序栈存储结构描述
typedef struct sStack{
    elementType data[MAXLEN];
    int top;
}seqStack;

//初始化栈
void initialStacksS(seqStack &S){
    S.top=-1;
}

//判断空栈
bool stackEmptysS(seqStack &S){
    if(S.top == -1){
        return true;
    }
    else{
        return false;
    }
}

//判断栈满
bool stackFullsS(seqStack &S){
    if(S.top == MAXLEN-1){
        return true;
    }
    else{
        return false;
    }
}

//入栈
void pushStacksS(seqStack &S, elementType x){
    if(stackFullsS(S)){
        cout << "栈满!无法入栈!" << endl;
    }
    else{
        S.top++;
        S.data[S.top]=x;
    }
}

//出栈
void popStacksS(seqStack &S, elementType &x){
    if(stackEmptysS(S)){
        cout << "栈空!无法出栈!" << endl;
    }
    else{
        x=S.data[S.top];
        S.top--;
    }
}
/*顺序栈基础函数结束*/

/**  主要函数  **/
//1.利用顺序栈实现将10进制数转换为16进制数
void radixChange10to16sStack(){
    cout << "请输入待转换数字(10进制):" ;
    elementType x;
    cin >> x;

    seqStack S;
    initialStacksS(S);

    if(x==0){
        cout << "该数转化后为(16进制):0" << endl;
    }
    else{
            while(x){
            elementType temp=x%16;
            pushStacksS(S, temp);
            x=x/16;
            }
            cout << "入栈成功!" << endl;

            cout << "该数转化后为(16进制):" ;
            while(!stackEmptysS(S)){
                elementType temp;
                popStacksS(S, temp);

                if(temp < 10){
                    cout << temp ;
                }
                else{        ///加入ABCDEF
                    switch(temp){
                        case 10:
                            cout << 'A' ; break;
                        case 11:
                            cout << 'B' ; break;
                        case 12:
                            cout << 'C' ; break;
                        case 13:
                            cout << 'D' ; break;
                        case 14:
                            cout << 'E' ; break;
                        case 15:
                            cout << 'F' ; break;
                    }
                }
            }
    }

    cout << "\n\n输入换行继续" << endl;
    getchar();
}

//2. 括号匹配(对一个合法的数学表达式来说，其中的各大小括号“{”，“}”，“[”，“]”，
//            “(”和“)”应是相互匹配的。设计算法对以字符串形式读入的表达式S，
//            判断其中的各括号是否是匹配的。)
void bracketMatchsStack(){
    cout << "请输入数学表达式:" ;
    char str[40];
    cin >> str;

    seqStack S;
    initialStacksS(S);

    bool sign=true;
    int c;
    for(int i=0; str[i]!=NULL && sign; i++){
        switch(str[i]){
        case '(':
        case '[':
        case '{':
            pushStacksS(S, str[i]);
            break;
        case ')':
            popStacksS(S, c);
            if(c!='('){
                sign=false;
            }
            break;
        case ']':
            popStacksS(S, c);
            if(c!='['){
                sign=false;
            }
            break;
        case '}':
            popStacksS(S, c);
            if(c!='{'){
                sign=false;
            }
            break;
        default:
            break;
        }
    }

    if(stackEmptysS(S) && sign){
        cout << "配对正确!" << endl;
    }
    else{
        cout << "配对错误!" << endl;
    }

    cout << "\n\n输入换行继续" << endl;
    getchar();
}
