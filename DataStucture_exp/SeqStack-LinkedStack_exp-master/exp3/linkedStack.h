#pragma once
#include<iostream>
#define elementType int
#define MAXLEN 1024

using namespace std;

//链栈存储结构描述
typedef struct lsNode{
    elementType data;
    struct lsNode *next;
}sNode, *linkedStack;

//初始化栈
void initialStacklS(sNode *& top){
    top =NULL;
}

//入栈
void pushStacklS(sNode *&top, elementType x){
    sNode *s;
    s=new sNode;
    s->data=x;
    s->next=top;
    top=s;
}

//出栈
void popStacklS(sNode *&top, elementType &x){
    sNode *u;
    if(top==NULL){
        cout << "栈空!无法出栈!" << endl;
    }
    else{
        x=top->data;
        u=top;
        top=top->next;
        delete u;
    }
}
/*链栈基础函数结束*/

/**  主要函数  **/
//3. 利用链栈实现将10进制数转换为16进制数。
void radixChange10to16lS(){
    cout << "请输入待转换数字(10进制):" ;
    elementType x;
    cin >> x;

    sNode *R;
    initialStacklS(R);

    if(x==0){
        cout << "该数转化后为(16进制):0" << endl;
    }
    else{
            while(x){
            elementType temp=x%16;
            pushStacklS(R, temp);
            x=x/16;
            }
            cout << "入栈成功!" << endl;

            cout << "该数转化后为(16进制):" ;
            while(R){
                elementType temp;
                popStacklS(R, temp);

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

//4. 括号匹配(对一个合法的数学表达式来说，其中的各大小括号“{”，“}”，“[”，“]”，
//            “(”和“)”应是相互匹配的。设计算法对以字符串形式读入的表达式S，
//            判断其中的各括号是否是匹配的。)
void bracketMatchlS(){
    cout << "请输入数学表达式:" ;
    char str[40]={0};
    cin >> str;

    sNode *R;
    initialStacklS(R);

    bool sign=true;
    int c;
    for(int i=0; str[i]!=NULL && sign; i++){
        switch(str[i]){
        case '(':
        case '[':
        case '{':
            pushStacklS(R, str[i]);
            break;
        case ')':
            popStacklS(R, c);
            if(c!='('){
                sign=false;
            }
            break;
        case ']':
            popStacklS(R, c);
            if(c!='['){
                sign=false;
            }
            break;
        case '}':
            popStacklS(R, c);
            if(c!='{'){
                sign=false;
            }
            break;
        default:
            break;
        }
    }

    if(R==NULL && sign){
        cout << "配对正确!" << endl;
    }
    else{
        cout << "配对错误!" << endl;
    }

    cout << "\n\n输入换行继续" << endl;
    getchar();
}
