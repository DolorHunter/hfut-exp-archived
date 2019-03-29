#include<cstdlib>
#include<iostream>
#include"BiTree.h"
#include"file.h"
#include"basis.h"

using namespace std;

int main(int argc, char *argv[])
{
    BiTree T;
    char strLine[100][3];
    int nArrLen;
    char fileName[20];
    int nRow;
    int iN=0, iN0=0, iN2=0;

    bool sign=true;
    do{
            system("CLS");
            cout << "┌────────────────────────────────────────────────────────┐" << endl;
            cout << "│         Power by:计算机科学与技术17-1班 王子翔         │" << endl;
            cout << "│                       二叉树实验                       │" << endl;
            cout << "├───────────────────────────┬────────────────────────────┤" << endl;
            cout << "│ 1. 打印二叉树的三种遍历序.│ 6. 二叉树N2结点数.         │" << endl;
            cout << "│ 2. 中序输出各结点值与层数.│ 7. 输入元素查水表.         │" << endl;
            cout << "│ 3. 二叉树高度.            │ 8. 输入元素查层次.         │" << endl;
            cout << "│ 4. 二叉树结点数.          │ 9. 二叉树转化为二叉链表.   │" << endl;
            cout << "│ 5. 二叉树叶子结点数.      │ 10.交换左右孩子.           │" << endl;
            cout << "├───────────────────────────┴────────────────────────────┤" << endl;
            cout << "│0. 退出.                                                │" << endl;
            cout << "└────────────────────────────────────────────────────────┘" << endl;
            cout << "请输入序号:";

            int iChose;
            cin >> iChose;

            switch(iChose){
            case 0:
                sign=false; break;
            case 1:
                openFile(fileName);
                CreatBiTree(T, fileName, strLine, nArrLen, nRow);
                PrtBinaryTree(T);
                _pause();
                break;
            case 2:
                openFile(fileName);
                CreatBiTree(T, fileName, strLine, nArrLen, nRow);
                PrtInTraverseLevel(T);
                _pause();
                break;
            case 3:
                openFile(fileName);
                CreatBiTree(T, fileName, strLine, nArrLen, nRow);
                PrtBiTreeDepth(T);
                _pause();
                break;
            case 4:
                openFile(fileName);
                CreatBiTree(T, fileName, strLine, nArrLen, nRow);
                GetNodeNumber(T, iN);
                PrtGetNodeNumber(iN);
                _pause();
                break;
            case 5:
                openFile(fileName);
                CreatBiTree(T, fileName, strLine, nArrLen, nRow);
                InTraverseN0(T, iN0);
                PrtInTraverseN0(iN0);
                _pause();
                break;
            case 6:
                openFile(fileName);
                CreatBiTree(T, fileName, strLine, nArrLen, nRow);
                InTraverseN2(T, iN2);
                PrtInTraverseN2(iN2);
                _pause();
                break;
            case 7:
                openFile(fileName);
                CreatBiTree(T, fileName, strLine, nArrLen, nRow);
                InTraverseGetXAllInf(T);
                _pause();
                break;
            case 8:
                openFile(fileName);
                CreatBiTree(T, fileName, strLine, nArrLen, nRow);
                findXDepth(T);
                _pause();
                break;
            case 9:
                openFile(fileName);
                nRow=0;           //行号归零(自动归零已优化至CreatBiTree()中)
                ReadFileToArray(fileName, strLine, nArrLen);
                CreatBiTreeFromArray(T, strLine, nArrLen, nRow);
                PrtInOrderTraverse(T);
                _pause();
                break;
            case 10:
                openFile(fileName);
                CreatBiTree(T, fileName, strLine, nArrLen, nRow);
                ExchangeSon(T);
                PrtInOrderTraverse(T);
                _pause();
                break;

            default:
                break;
            }
    }while(sign);

    cout << "\n进程终止." << endl;

    DestoryBiTree(T);

    return 0;
}
