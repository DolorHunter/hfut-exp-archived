//修改版BiTree.h
//2019.01.03

#pragma once
#include<iostream>
#include<string.h>

typedef char elementType;

using namespace std;

//二叉链表存储结构描述
typedef struct lBNode{
    elementType data;                   //存放数据元素
    struct lBNode *lChild, *rChild;     //左右孩子指针
}BiNode, *BiTree;

//1.1打印先序遍历递归算法
void PrtPreOrderTraverse(BiNode *T){
    if(T!=NULL){
        cout << T->data << "\t";               //打印分支点
        PrtPreOrderTraverse(T->lChild);        //递归调用先序遍历左子树
        PrtPreOrderTraverse(T->rChild);        //递归调用先序遍历右子树
    }
}

//1.2打印中序遍历递归算法
void PrtInOrderTraverse(BiNode *T){
    if(T!=NULL){
        PrtInOrderTraverse(T->lChild);     //递归调用中序遍历左子树
        cout << T->data << "\t";           //打印分支点
        PrtInOrderTraverse(T->rChild);     //递归调用中序遍历右子树
    }
}

//1.3打印后序遍历递归算法
void PrtPostOrderTraverse(BiNode *T){
    if(T!=NULL){
        PrtPostOrderTraverse(T->lChild);   //递归调用后序遍历左子树
        PrtPostOrderTraverse(T->rChild);   //递归调用后序遍历右子树
        cout << T->data << "\t";           //打印打印分支点
    }
}

//1.打印出二叉树的三种遍历序
void PrtBinaryTree(BiNode *T){
    cout << "┌────────────────────────────────────────────────────────┐" << endl;
    cout << "│1.1 先序遍历递归算法                                    │" << endl;
    cout << "│1.2 中序遍历递归算法                                    │" << endl;
    cout << "│1.3 后序遍历递归算法                                    │" << endl;
    cout << "└────────────────────────────────────────────────────────┘" << endl;
    cout << "请输入打印规则:" ;
    int iRules;
    cin >> iRules;
    cin.get();

    switch(iRules){
        case 1:
            PrtPreOrderTraverse(T); break;
        case 2:
            PrtInOrderTraverse(T); break;
        case 3:
            PrtPostOrderTraverse(T); break;
        default:
            break;
    }
}

//2.设计算法按中序次序输出二叉树中各结点的值及其所对应的层次数
void PrtInTraverseLevel(BiNode *T){
	static int i=0;
	if(T!=NULL){
		i++;
		PrtInTraverseLevel(T->lChild);
		cout << T->data << "的层数为" << i << endl;
		PrtInTraverseLevel(T->rChild);
		i--;
	}
}

//3.求二叉树的高度
int BiTreeDepth(BiNode *T){
    int m,n;
    if(T==NULL){
        return 0;
    }
    else{
        m=BiTreeDepth(T->lChild);
        n=BiTreeDepth(T->rChild);
        return ((m>n)?m:n)+1;
    }
}
void PrtBiTreeDepth(BiNode *T){
    cout << "二叉树高度为" << BiTreeDepth(T) << endl;
}

//4.求二叉树的结点数
void GetNodeNumber(BiNode *T,int &iN){
    if(T!=NULL){
        GetNodeNumber(T->lChild, iN);
        iN++;
        GetNodeNumber(T->rChild, iN);
    }
}
void PrtGetNodeNumber(int &iN){
    cout << "二叉树结点数为" << iN << endl;
    iN=0;                                              //调用后归零
}

//5.求二叉树的叶子结点数
void InTraverseN0(BiNode *T, int &iN0){
    if(T!=NULL){
        InTraverseN0(T->lChild, iN0);                  //递归调用中序遍历左子树
        if(T->lChild==NULL && T->rChild==NULL){        //若分支点度数为0, iN0++
            iN0++;
        }
        InTraverseN0(T->rChild, iN0);                  //递归调用中序遍历右子树
    }
}
void PrtInTraverseN0(int &iN0){
    cout << "二叉树的叶子结点数为" << iN0 << endl;
    iN0=0;                                             //调用后归零
}

//6.求二叉树的度为2的结点数
void InTraverseN2(BiNode *T, int &iN2){
    if(T!=NULL){
        InTraverseN2(T->lChild, iN2);                  //递归调用中序遍历左子树
        if(T->lChild!=NULL && T->rChild!=NULL){ //若分支点度数为2, iN2++
            iN2++;
        }
        InTraverseN2(T->rChild, iN2);                  //递归调用中序遍历右子树
    }
}
void PrtInTraverseN2(int &iN2){
    cout << "二叉树的度为2的结点数为" << iN2 << endl;
    iN2=0;                                             //调用后归零
}

//7.键盘输入一个元素x，求其父节点、兄弟结点、子结点的值，不存在时给出相应提示信息。
//  对兄弟结点和孩子结点，存在时要明确指出是左兄弟、左孩子、右兄弟或右孩子

//找到x元素所在层次(回传nodeDepth方便查找兄弟结点)(辅助函数)
bool InTraverseOneDataDepth(BiNode *T, char x, int &nodeDepth){
    if(T==NULL){
        return false;
    }
    else{
        if(InTraverseOneDataDepth(T->lChild, x, nodeDepth)){
            nodeDepth++;
            return true;
        }
        if(T->data==x){
            return true;
        }
        if(InTraverseOneDataDepth(T->rChild, x, nodeDepth)){
            nodeDepth++;
            return true;
        }
    }
}
//找到x父节点
void InOrderTraverseXFather(BiNode *T, char x, int &nodeDepth){
    if(T!=NULL){
        InOrderTraverseXFather(T->lChild, x, nodeDepth);
        if(T->lChild!=NULL && T->lChild->data==x){
            cout << "元素" << x << "的父节点为" << T->data << "在树中的层次为" << nodeDepth-1 << endl;
        }
        if(T->rChild!=NULL && T->rChild->data==x){
            cout << "元素" << x << "的父节点为" << T->data << "在树中的层次为" << nodeDepth-1 << endl;
        }
        InOrderTraverseXFather(T->rChild, x, nodeDepth);
    }
}
//找到x子结点
void InOrderTraverseXSon(BiNode *T, char x, int &nodeDepth){
    if(T!=NULL){
        InOrderTraverseXSon(T->lChild, x, nodeDepth);
        if(T->data==x){
            if(T->lChild!=NULL){
                cout << "元素" << x << "的左孩子为:" << T->lChild->data << ".在树中的层次为" << nodeDepth+1 << "." << endl;
            }
            else{
                cout << "元素" << x << "没有左孩子." << endl;
            }
            if(T->rChild!=NULL){
                cout << "元素" << x << "的右孩子为:" << T->rChild->data << ".在树中的层次为" << nodeDepth+1 << "." << endl;
            }
            else{
                cout << "元素" << x << "没有右孩子." << endl;
            }
        }
        InOrderTraverseXSon(T->rChild, x, nodeDepth);
    }
}
//找到x兄弟结点
void InOrderTraverseXBrother(BiNode *T, char x, int &nodeDepth){
    static int iDepth=0;
    if(T!=NULL){
        iDepth++;
        InOrderTraverseXBrother(T->lChild, x, nodeDepth);
        if(iDepth==nodeDepth && T->data!=x){
        cout << "元素" << x << "的兄弟结点为" << T->data << "在树中的层次为" << nodeDepth << "." << endl;
        }
        InOrderTraverseXBrother(T->rChild, x, nodeDepth);
        iDepth--;
    }
}
//7.查水表(主调用函数)
int InTraverseGetXAllInf(BiNode *T){
    cout << "请输入待查找元素的值:";
    char x;
    cin >> x;
    cin.get();

    int nodeDepth=1;                                   //用于保存x的层数信息

    if(T==NULL){
        return 0;
    }
    else{
        if(!InTraverseOneDataDepth(T, x, nodeDepth)){  //没有找到x结点
            cout << "中序遍历全树后仍未找到元素" << x << "!" << endl;
        }
        else{
            InOrderTraverseXFather(T, x, nodeDepth);              //找到x的父结点
            InOrderTraverseXSon(T, x, nodeDepth);                 //找到x的子结点
            InOrderTraverseXBrother(T, x, nodeDepth);             //找到x的兄弟结点
        }
    }
    cout << "查水表任务已完成!" << endl;
}


//8.键盘输入一个元素x，求其在树中的层次。不存在时给出相应提示信息
//找到x元素所在层次(不回传nodeDepth)
bool InTraverseXDepth(BiNode *T, char x, int nodeDepth){
    if(T==NULL){
        return false;
    }
    else{
        if(InTraverseXDepth(T->lChild, x, nodeDepth+1)){
            return true;
        }
        if(T->data==x){
            cout << "元素" << x << "在树中的层次为" << nodeDepth << endl;
            return true;
        }
        if(InTraverseXDepth(T->rChild, x, nodeDepth+1)){
            return true;
        }
    }
}
void findXDepth(BiNode *T){
    cout << "请输入待查找元素的值:";
    char x;
    cin >> x;
    cin.get();
    int nodeDepth=1;
    if(!InTraverseXDepth(T, x, nodeDepth)){
        cout << "中序遍历全树后仍未找到元素" << x << "!" << endl;
    }
}

//9.将按顺序方式存储在数组中的二叉树转换为二叉链表形式。（数组中要扩展为完全二叉树
//转换函数同file.h中的函数CreatBiTreeFromArray(), 为了避免重复定义此处省去此函数
//      bool CreatBiTreeFromArray(BiNode *&pBT, char (&strLine)[100][3], int &nLen, int &nRow)

//10.交换二叉树中每个结点的左右孩子指针的值。（即：左子树变为右子树，右子树变为左子树
void ExchangeSon(BiTree &T)
{
	if(!(T->lChild==NULL && T->rChild==NULL)){  //分支点有孩子
        BiTree temp=T->lChild;                  //引入临时变量temp存储lChild
		T->lChild=T->rChild;
		T->rChild=temp;
	}
	//如果交换后的这个结点左子树不为空，则继续向下寻找可以交换的结点；
	if(T->lChild!=NULL){
        ExchangeSon(T->lChild);
	}
	if(T->rChild!=NULL){
        ExchangeSon(T->rChild);
	}
}

//二叉树的销毁
void DestoryBiTree(BiNode *pBT){
    if(pBT!=NULL){
        DestoryBiTree(pBT->lChild);
        DestoryBiTree(pBT->rChild);
        delete pBT;
    }
}
