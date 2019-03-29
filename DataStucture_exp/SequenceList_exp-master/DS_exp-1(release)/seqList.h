#pragma once
#include<iostream>
#include<windows.h>
#define MAXLEN 1024
#define elementType int

using namespace std;

//定义顺序表结构体
typedef struct{
    elementType data[MAXLEN];   //定义存储表中元素的数组
    int listLen;                //定义表长度分量
}seqList;

//加载中...
void loading(){
    int i= 0;
    while(i<5){
        system("CLS");
        cout << "loading." << endl;
        Sleep(300);
        i++;
        system("CLS");
        cout << "loading.." << endl;
        Sleep(300);
        i++;
        system("CLS");
        cout << "loading..." << endl;
        Sleep(300);
        i++;
    }
}
//-1. 打印顺序表(调试用)
void printList(seqList *L){
    loading();
    cout << "正在打印顺序表..." << endl;
    for(int i=0; i<L->listLen; i++){
        cout << L->data[i] << endl;
    }

    cout << "输入换行以继续." << endl;
    getchar();
}

//-2. 无暂停打印(作输出使用)
void prtNpauseList(seqList *L){
    loading();
    for(int i=0; i<L->listLen; i++){
        cout << L->data[i] << endl;
    }
}

//0. 初始化顺序表
void initialList(seqList *L){
    loading();
    L->listLen = 0; //顺序表的长度为0
}

//1. 创建顺序表
void buildList(seqList *L){
    loading();
    int bit;
    cout << "请输入顺序表的大小:" << endl;
    cin >> bit;
    L->listLen = bit;

    for(int i=0; i<bit; i++){
        cout << "请输入第" << i << "个元素:" << endl;
        cin >> L->data[i];
    }
    cout << "顺序表已建立." << endl;

    cout << "输入换行以继续." << endl;
    getchar();
}

//2. 查找元素(求顺序表中第i个元素, 若不存在报错)
void searchList(seqList *L){
    loading();
    int iLoc;
    cout << "请输入要查找的位置:" << endl;
    cin >> iLoc;

    //定义查找失败标志defeat
    bool defeat;
    if(iLoc<0 || iLoc>L->listLen-1){
        cout << "位置错误!查找失败!" << endl;
    }
    else{
        for(int i=0; i<L->listLen; i++){
            if(iLoc == i){
                cout << "查找成功!该位置元素为" << L->data[i] << "." << endl;
                defeat = false;
                break;
            }
        }
        if(defeat){
            cout << "位置正确!查找失败!" << endl;
        }
    }

    cout << "输入换行以继续." << endl;
    getchar();
}

//3. 插入节点(在第i个结点前插入值为x的结点)
void insertList(seqList *L){
    loading();
    int iLoc;
    cout << "请输入插入节点的位置:" << endl;
    cin >> iLoc;

    elementType inp;
    cout << "请输入插入的值:" << endl;
    cin >> inp;

    if(L->listLen == MAXLEN){
        cout << "溢出, 不能插入!\n" << endl;
    }
    else if(iLoc<0 || iLoc>L->listLen){
        cout << "位置错误!\n" << endl;
    }
    else{
        for(int i=L->listLen; i>iLoc-1; i--){
            L->data[i+1] = L->data[i];
        }
        L->data[iLoc] = inp;
        L->listLen++;
    }

    cout << "****这是顺序表L(插入后)****" << endl;
    prtNpauseList(L);

    cout << "输入换行以继续." << endl;
    getchar();
}

//4. 删除节点(删除顺序表中第i个元素结点)
void deleteList(seqList *L){
    loading();
    int iLoc;
    cout << "请输入删除节点的位置:" << endl;
    cin >> iLoc;

    if(iLoc<0 || iLoc>L->listLen-1){
        cout << "位置错误!\n" << endl;
    }
    else{
        for(int i=iLoc; i<L->listLen; i++){
            L->data[i] = L->data[i+1];
        }
        L->listLen--;
    }

    cout << "****这是顺序表L(插入后)****" << endl;
    prtNpauseList(L);

    cout << "输入换行以继续." << endl;
    getchar();
}

//5. 递增插入(在一个递增有序的顺序表L中插入一个值为x的元素，并保持其递增有序特性)
void increinseList(seqList *L){
    loading();
    elementType inp;
    cout << "请输入递增插入的值:" << endl;
    cin >> inp;

    if(L->listLen == MAXLEN){
        cout << "溢出, 不能插入!\n" << endl;
    }
    else{
        int iLoc;
        for(int j=L->listLen; j>=0; j--){
            if(inp > L->data[j]){
                iLoc = j+1;
                break;
            }
            else{
                iLoc = 0;   //小于所有元素头插
            }
        }
        for(int j=L->listLen; j>=iLoc; j--){
            L->data[j+1] = L->data[j];
        }
        L->data[iLoc] = inp;
        L->listLen++;
    }

    cout << "****这是顺序表L(插入后)****" << endl;
    prtNpauseList(L);

    cout << "输入换行以继续." << endl;
    getchar();
}

//6. 分离奇偶(将顺序表Ｌ中的奇数项和偶数项结点分解开（元素值为奇数、偶数），分别放入新的顺序表中)
void seperateOEList(seqList *L){
    loading();
    seqList A;
    seqList B;
    initialList(&A);    //初始化顺序表A(存放奇数)
    initialList(&B);    //初始化顺序表B(存放偶数)
    int iA=0, iB=0;
    for(int i=0; i<L->listLen; i++){
        if((L->data[i] % 2) ==1){
            A.data[iA] = L->data[i];
            iA++;
            A.listLen++;
        }
        else{
            B.data[iB] = L->data[i];
            iB++;
            B.listLen++;
        }
    }

    cout << "****这是顺序表L(原始表)****" << endl;
    prtNpauseList(L);  //打印顺序表L

    cout << "****这是顺序表A(奇数表)****" << endl;
    prtNpauseList(&A);  //打印顺序表A

    cout << "****这是顺序表B(偶数表)****" << endl;
    prtNpauseList(&B);  //打印顺序表B

    cout << "输入换行以继续." << endl;
    getchar();
}

//7. 提取公共元素(求两个递增有序顺序表L1和L2中的公共元素，放入新的顺序表L3中)
void mixIncreList(){
    loading();
    seqList L1;
    seqList L2;
    seqList L3;
    initialList(&L1);
    initialList(&L2);
    initialList(&L3);

    cout << "****正在建立顺序表L1****" << endl;
    buildList(&L1);
    cout << "****顺序表L1建立完成!****\n" << endl;

    cout << "****正在建立顺序表L2****" << endl;
    buildList(&L2);
    cout << "****顺序表L2建立完成!****\n" << endl;

    int iA=0, iB=0, iC=0;
    int Lmax = L1.listLen>L2.listLen?L1.listLen:L2.listLen;

    for(int i=0; i<Lmax; i++){
        if(L1.data[iA] == L2.data[iB]){
            L3.data[iC] = L1.data[iA];
            L3.listLen++;

            iA++;
            iB++;
            iC++;
        }
        else if(L1.data[iA] > L2.data[iB]){
            iB++;
        }
        else{
            iA++;
        }
    }

    cout << "****这是顺序表L1(输入表)****" << endl;
    prtNpauseList(&L1);  //打印顺序表L

    cout << "****这是顺序表L2(输入表)****" << endl;
    prtNpauseList(&L2);  //打印顺序表A

    cout << "****这是顺序表L3(生成表)****" << endl;
    prtNpauseList(&L3);  //打印顺序表B

    cout << "输入换行以继续." << endl; ///这边多了一个回车是为什么???
}

//8. 去重(删除递增有序顺序表中的重复元素，并统计移动元素次数，要求时间性能最好)
void delRepList(seqList *L){
    loading();
    for(int i=L->listLen; i>=0; i--){
        if(L->data[i] == L->data[i-1]){
            int iLoc=i;
            for(int j=iLoc; j<L->listLen; j++){
                L->data[j-1] = L->data[j];
            }
            L->listLen--;
        }
    }

    cout << "****这是顺序表L(去重后)****" << endl;
    prtNpauseList(L);

    cout << "输入换行以继续." << endl;
    getchar();
}
