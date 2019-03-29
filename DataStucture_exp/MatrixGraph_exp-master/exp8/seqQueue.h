//修改版seqQueue.h
//date:2019.01.01

#pragma once
#define MaxLen 100

typedef int QelementType;

using namespace std;

//顺序队列存储结构描述
typedef struct sQueue{
    QelementType data[MaxLen];       //存放队列元素
    int front;                      //队头指针
    int rear;                       //队尾指针
}seqQueue;

//打印seqQueue
void prtSeqQueue(seqQueue &sQ){
    int u=sQ.front+1;
    cout << "循环顺序队列打印结果如下:" << endl;
    while(u%MaxLen!=sQ.rear+1){
        cout << sQ.data[u%MaxLen] << "\t";
        u=u+1;
    }
    cout << endl;
}

//1.初始化队列
void initialSeqQueue(seqQueue &sQ){
    sQ.front=0;
    sQ.rear=0;
}

//2.判断队空
bool seqQueueEmpty(seqQueue &sQ){
    if(sQ.front==sQ.rear){
        return true;
    }
    else{
        return false;
    }
}

//3.判断队满
bool seqQueueFull(seqQueue &sQ){
    if(((sQ.rear+1)%MaxLen)==sQ.front){
        return true;
    }
    else{
        return false;
    }
}

//4.循环入队
void seqEnQueueLoop(seqQueue &sQ){
    cout << "请输入待入队元素(输入9999退出)" << endl;
    QelementType x;
    cin >> x;

    while(x!=9999){
        if(seqQueueFull(sQ)){
            cout << "队满!不能完成入队操作!" << endl;
        }
        else{
            sQ.rear=(sQ.rear+1)%MaxLen;       //后移rear
            sQ.data[sQ.rear]=x;               //填入数据x
            cin >> x;
        }
    }
}

//入队.
void seqEnQueue(seqQueue &sQ, QelementType x){
    if(seqQueueFull(sQ)){
        cout << "队满!不能完成入队操作!" << endl;
    }
    else{
        sQ.rear=(sQ.rear+1)%MaxLen;       //后移rear
        sQ.data[sQ.rear]=x;               //填入数据x
    }
}

//5.出队
void seqOutQueue(seqQueue &sQ, QelementType x){
    if(seqQueueEmpty(sQ)){
        cout << "队空!不能取队头元素!" << endl;
    }
    else{
        x=sQ.data[(sQ.front+1)%MaxLen];           //front指示的下一个单元才是队头元素
        sQ.front=(sQ.front+1)%MaxLen;             //front指针后移一个单位
    }
}

//6.取队头元素
void seqQueueFront(seqQueue &sQ, QelementType &x){
    if(seqQueueEmpty(sQ)){
        cout << "队空!不能取队头元素!" << endl;
    }
    else{
        x=sQ.data[(sQ.front+1)%MaxLen];           //front指示的下一个单元才是队头元素
        cout << x << endl;                        //打印x
    }
}

//7.求队列元素个数
void seqQueueLength(seqQueue &sQ){
    int iLen;
    iLen=(sQ.rear-sQ.front+MaxLen)%MaxLen;
    cout << "队列元素个数为" << iLen <<  "个." << endl;
}
