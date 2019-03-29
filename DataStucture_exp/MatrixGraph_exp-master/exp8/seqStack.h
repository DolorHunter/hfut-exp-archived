//修改版seqStack.h
//2019.01.03

#pragma once
#include<iostream>
#define MAXLEN 1024

typedef char elementType;

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
void popStacksS(seqStack &S, elementType x){
    if(stackEmptysS(S)){
        cout << "栈空!无法出栈!" << endl;
    }
    else{
        x=S.data[S.top];
        S.top--;
    }
}
