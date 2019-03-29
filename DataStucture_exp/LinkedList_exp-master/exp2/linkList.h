#pragma once
#include<iostream>
#define elementType int

using namespace std;

//定义单链表节点结构
typedef struct slNode{
    elementType data;           //数据域
    struct slNode *next;        //指针域,结构(节点)自身引用
}node, *linkList;

//-1. 打印单链表(调试用)
void printList(linkList L){
    cout << "正在打印顺序表..." << endl;

    node *p=L->next;
    while(p){
        cout << p->data << endl;
        p = p->next;
    }

    cout << "输入换行以继续." << endl;
    getchar();
}

//无暂停打印(作输出使用)
void prtNpauseList(linkList L){
    node *p=L->next;
    while(p){
        cout << p->data << endl;
        p = p->next;
    }
}

//初始化链表(使用C++的引用回传初始化后的链表)
void initialList(node *&L){
    L=new node;
    L->next=NULL;
}

//1. 尾插法创建单链表，打印创建结果
void creatListR(node *&L){
    node *u, *R;
    L=new node;
    L->next=NULL;
    R=L;
    elementType x;      //存放元素值
    cout <<"请输入元素数据(整数,9999退出):" << endl;
    cin >> x;
    while(x != 9999){
        u=new node;
        u->data=x;
        u->next=NULL;
        R->next=u;
        R=u;
        cin >> x;
    }
    cout << "链表建立成功!" << endl;

    cout << "输入换行以继续." << endl;
    getchar();
}

//2. 头插法创建单链表，打印创建结果
void creatListH(node *&L){
    node *u;
    L=new node;
    L->next=NULL;
    elementType x;      //存放元素值
    cout <<"请输入元素数据(整数,9999退出):" << endl;
    cin >> x;
    while(x != 9999){
        u=new node;
        u->data=x;
        u->next=L->next;
        L->next=u;
        cin >> x;
    }
    cout << "链表建立成功!" << endl;

    cout << "输入换行以继续." << endl;
    getchar();
}

//3. 销毁单链表
void destoryList(linkList *L){
    linkList q, p=*L;
    while(p){
        q=p->next;
        delete p;
        p=q;
    }
    *L=NULL;
    cout << "单链表销毁成功!" << endl;

    /**再次初始化防止代码崩溃**/
    cout << "是否初始化?(Y/N) -[注意]若不初始化程序进行某些操作时可能崩溃!" << endl;
    char x;
    cin >> x;
    if(x=='Y' || x=='y'){
        initialList(*L);
        cout << "初始化成功!" << endl;
    }

    cout << "输入换行以继续." << endl;
    getchar();
}

//4. 求链表长度
void listLength(node *L){
    int iLen=0;
    node *p=L->next;
    while(p){
        iLen++;
        p=p->next;
    }
    cout << "链表长度为:" << iLen << endl;

    cout << "输入换行以继续." << endl;
    getchar();
}

//5. 查找元素(位置查找)(求单链表中第i个元素（函数），若不存在，报错)
void getElement(node *L){
    cout << "请输入查找位置:" << endl;
    int iLoc;
    cin >> iLoc;
    int j=1;             //由1计数符合多数人认知
    node *p=L->next;
    while(j!=iLoc && p!=NULL){
        j++;
        p=p->next;
    }
    if(p){
        cout << "位置存在! 单链表中第" << iLoc << "个元素为" << p->data << endl;
    }
    else{
        cout << "错误!位置不存在!" << endl;
    }

    cout << "输入换行以继续." << endl;
    getchar();
}

//6. 插入节点(在第i个结点前插入值为x的结点)
void listInsert(node *L){

    cout << "请输入插入位置:" << endl;
    int iLoc;
    cin >> iLoc;

    cout << "请输入元素值:" << endl;
    int x;
    cin >> x;

    node *p=L;
    node *u;
    int k=1;                //由1计数符合多数人认知
    while(k!=iLoc && p){
        p=p->next;
        k++;
    }
    if(!p){
        cout << "错误!插入位置无效!" << endl;
    }
    else{
        //此时, k=i-1, p为e(i-1)结点的指针
        u=new node;
        u->data=x;
        u->next=p->next;
        p->next=u;

        cout << "插入成功!" << endl;
    }

    prtNpauseList(L);                //打印单链表L

    cout << "输入换行以继续." << endl;
    getchar();
}

//7. 查找元素(值查找)(链表中查找元素值为x的结点，成功返回结点指针，失败报错)
void listLocate(node *L){
    elementType x;
    cout << "请输入待查找元素值:" << endl;
    cin >> x;
    node *p=L->next;
    while(p && p->data!=x){
        //p指元素结点,又不是目标节点,继续搜索下一个节点
        p=p->next;
    }
    if(p){
        cout << "查找成功!单链表中存在元素" << x << "!" << endl;
    }
    else{
        cout << "错误!元素不存在!" << endl;
    }

    cout << "输入换行以继续." << endl;
    getchar();
}

//8. 删除单链表中第i个元素结点
void listDelete(node *L){
    cout << "请输入待删除元素的节点:" << endl;
    int iLoc;
    cin >> iLoc;

    node *u;
    node *p=L;
    int k=1;                //由1计数符合多数人认知
    while(k!=iLoc && p){
        p=p->next;
        k++;
    }
    if(!p || !(p->next)){
        cout << "错误!删除位置超过范围,删除失败!" << endl;
    }
    else{
        u=p->next;
        p->next=u->next;
        delete u;
        cout << "删除成功!" << endl;
    }

    prtNpauseList(L);                   //打印单链表L

    cout << "输入换行以继续." << endl;
    getchar();
}

//9. 递增插入(在一个递增有序的单链表L中插入一个值为x的元素，并保持其递增有序特性)
void setInsert(node *&L){
    node *u;
    node *P=L;

    elementType x;
    cout << "请输入要插入的元素:" << endl;
    cin >> x;

    //搜索插入位置P(P->data<=x,则需返回上一个位置插入,自己造成麻烦)
    while(P->next!=NULL && P->next->data<=x){
        P=P->next;
    }

    //P指向表尾,或P->next的元素比x大,P->next即为插入位置
    if(P->next==NULL || P->next->data>x){
        u=new node;
        u->data=x;
        u->next=P->next;
        P->next=u;
    }

    prtNpauseList(L);               //打印单链表L

    cout << "输入换行以继续." << endl;
    getchar();
}

//10. 分离奇偶(将单链表Ｌ中的奇数项和偶数项结点分解开（元素值为奇数、偶数）)
void seperateOEList(node *L){
    linkList L1;
    linkList L2;
    initialList(L1);
    initialList(L2);
    node *u,*R;     //L1指针
    node *v,*S;     //L2指针
    R=L1;
    S=L2;

    node *p=L->next;
    while(p){
        if(p->data%2 ==1){
            u=new node;
            u->data=p->data;
            u->next=NULL;
            R->next=u;
            R=u;
        }
        else{
            v=new node;
            v->data=p->data;
            v->next=NULL;
            S->next=v;
            S=v;
        }
        p=p->next;
    }

    cout << "****这是原始表L****" << endl;
    prtNpauseList(L);                   //打印单链表L

    cout << "****这是奇数表L1****" << endl;
    prtNpauseList(L1);                   //打印单链表L1

    cout << "****这是偶数表L2****" << endl;
    prtNpauseList(L2);                   //打印单链表L2

    cout << "输入换行以继续." << endl;
    getchar();
}

//11. 递增取交(求两个递增有序单链表L1和L2中的公共元素，放入新的单链表L3中)
void intersecIncreList(){
    linkList L1;
    linkList L2;
    linkList L3;
    initialList(L1);
    initialList(L2);
    initialList(L3);

    cout << "尾插法建立递增单链表L1" << endl;
    creatListR(L1);

    cout << "尾插法建立递增单链表L2" << endl;
    creatListR(L2);

    node *u,*p;     //L1, L2指针
    node *v,*S;     //L3指针
    u=L1->next;
    p=L2->next;
    S=L3;

    while(u && p){
        if(u->data == p->data){
            v=new node;
            v->data=u->data;
            v->next=NULL;
            S->next=v;
            S=v;
            u=u->next;
            p=p->next;
        }
        else if(u->data > p->data){
            p=p->next;
        }
        else{
            u=u->next;
        }
    }

    cout << "****这是L1表****" << endl;
    prtNpauseList(L1);                   //打印单链表L1

    cout << "****这是L2表****" << endl;
    prtNpauseList(L2);                   //打印单链表L2

    cout << "****这是交集表L3****" << endl;
    prtNpauseList(L3);                   //打印单链表L3

    cout << "输入换行以继续." << endl;
    //getchar();
}

//12. 去重(删除递增有序单链表中的重复元素，要求时间性能最好)
void deleteRepList(node *L){
    node *u=L;          //前指针
    node *R=u->next;    //后指针
    node *p;            //删除指针(中指针)
    while(R->next){
        if(u->next->data == R->next->data){
            p=u->next;
            u->next=R->next;
            R=R->next;
            delete p;

        }
        else{
            u=u->next;
            R=R->next;
        }
    }

    cout << "完成去重操作!" << endl;
    prtNpauseList(L);

    cout << "输入换行以继续." << endl;
    getchar();
}

//13.合并递增表(不申请新结点，利用原表结点对2表进行合并成为一个集合，
//              合并后用L1的头结点作为头结点，删除L2的头结点，要求时间性能最好。)
void mergeIncreList(){
    linkList L1;
    linkList L2;
    initialList(L1);
    initialList(L2);

    cout << "尾插法建立递增单链表L1" << endl;
    creatListR(L1);

    cout << "尾插法建立递增单链表L2" << endl;
    creatListR(L2);

    node *u=L1;
    node *R=L2;
    node *p;                         //连接L2指针
    while(u->next && R->next){
        if(u->next->data == R->next->data){
            u->next;
            R->next;
        }
        else if(u->next->data > R->next->data){
            p=R->next->next;
            R->next->next=u->next;
            u->next=R->next;
            R->next=p;
            u->next;
            R->next;
        }
        else{
            u=u->next;
        }
    }
    if(R->next){                    //末位L2非空接至L1尾
        u->next=R->next;
    }

    cout << "" << endl;
    cout << "**正在删除L2头结点**" << endl;
    R=L2;
    delete R;
    cout << "**L2头结点删除成功!**" << endl;

    cout << "" << endl;
    cout << "****这是合并后的L1****" << endl;
    prtNpauseList(L1);                  //打印单链表L1


    cout << "输入换行以继续." << endl;
    getchar();
}
