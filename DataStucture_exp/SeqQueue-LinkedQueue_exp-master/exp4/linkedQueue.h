#pragma once
#define elementType int

using namespace std;

//链队列结点结构描述
typedef struct LNode{
    elementType data;           //存放数据元素
    struct LNode *next;         //下一个结点指针
}node;

//链队列结构描述
typedef struct{
    node *front;                //队头指针
    node *rear;                 //队尾指针
}linkQueue;

//打印linkedQueue
void prtLinkedQueue(linkQueue &lQ){
    node *u=lQ.front->next;
    cout << "链队列打印结果如下:" << endl;
    while(u!=NULL){
        cout << u->data << "\t";
        u=u->next;
    }
    cout << endl;
}

//9. 初始化队列.
void initialLinkedQueue(linkQueue &lQ){
    lQ.front=new node;           //产生头结点,指针为front
    lQ.rear=lQ.front;             //rear也指向头结点
    lQ.front->next=NULL;         //头结点的next置为NULL
}

//10.判断是否队空.
bool linkedQueueEmpty(linkQueue &lQ){
    return (lQ.front==lQ.rear);       //当Q.front==Q.rear时为1,否则为0.将其赋予return
}

//11.判断是否队满.
void linkedQueueFull(){
    cout << "[Warning]-链队列怎么可能会满呢?XD" << endl;
}

//12.循环入队.
void linkedEnQueue(linkQueue &lQ){
    cout << "请输入待入队元素(输入9999退出)" << endl;
    elementType x;
    cin >> x;

    while(x!=9999){
        node *P=new node;               //申请内存,产生新结点
        P->data=x;                      //x赋予新结点
        P->next=NULL;                   //x结点成为新的尾节点,next置NULL
        lQ.rear->next=P;                 //新结点链接到原表尾
        lQ.rear=P;                       //后移为之震,指向新队尾
        cin >> x;
    }

    _pause();                        //暂停
}

//入队.
void linkedEnQueueOnce(linkQueue &lQ, elementType &x){
    node *P=new node;               //申请内存,产生新结点
    P->data=x;                      //x赋予新结点
    P->next=NULL;                   //x结点成为新的尾节点,next置NULL
    lQ.rear->next=P;                 //新结点链接到原表尾
    lQ.rear=P;                       //后移为之震,指向新队尾
}

//13.出队.
void linkedOutQueue(linkQueue &lQ, elementType &x){
    node *u;
    if(linkedQueueEmpty(lQ)){
        cout << "空队列!无法出队!" << endl;
    }
    else{
        x=lQ.front->next->data;          //取队头元素到x
        cout << x << endl;
        u=lQ.front->next;                //u指向队头
        lQ.front->next=u->next;         //更新队头指针
        delete u;                       //删除原队头,释放内存
        if(lQ.front->next==NULL){        //如果删除结点后队空,则要修改rear指针
            lQ.rear=lQ.front;             //杜绝野指针
        }
    }

    _pause();                        //暂停
}

//14.取队头元素.
void linkedQueueFront(linkQueue &lQ, elementType &x){
    if(linkedQueueEmpty(lQ)){
        cout << "空队列!无法取头元素!" << endl;
    }
    else{
        x=lQ.front->next->data;
        cout << x << endl;
    }

    _pause();                        //暂停
}

//15.求队列元素个数.
void linkedQueueLength(linkQueue &lQ){
    int iLen=1;
    node *u=lQ.front->next;
    while(u!=lQ.rear){
        iLen++;
        u=u->next;
    }
    cout << "队列有" << iLen << "个元素." << endl;

    _pause();                        //暂停
}

//16.奇入偶出算法.
void linkedOddInEvenOut(linkQueue &lQ){
    initialLinkedQueue(lQ);
    cout << "请输入元素(输入0退出):";
    elementType x;
    cin >> x;
    while(x!=0){
        if(x%2==1){
            linkedEnQueueOnce(lQ, x);
            cout << "入队成功!" << endl;
            prtLinkedQueue(lQ);                 //打印LinkedQueue
            cout << "请输入元素(输入0退出):";
            cin >> x;
        }
        else{
            if(linkedQueueEmpty(lQ)){
                linkedOutQueue(lQ, x);
            }
            else{
                linkedOutQueue(lQ, x);
                cout << "出队成功!" << endl;
            }
            prtLinkedQueue(lQ);                 //打印LinkedQueue
            cout << "请输入元素(输入0退出):";
            cin >> x;
        }
    }

    _pause();                        //暂停
}
