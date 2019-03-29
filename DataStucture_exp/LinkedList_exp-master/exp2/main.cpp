#include<iostream>
#include<cstdlib>
#include"linkList.h"

using namespace std;

int main(int argc, char *argv[])
{
    linkList L;
    initialList(L);
    do{
            system("CLS");
            cout << " # # # # Power by:计算机科学与技术17-1班 王子翔# # # # # #" << endl;
            cout << "***************************单链表*************************" << endl;
            cout << "*1. 尾插法创建单链表.        |8. 删除节点.               *" << endl;
            cout << "*2. 头插法创建单链表.        |9. 递增插入.               *" << endl;
            cout << "*3. 销毁单链表.              |10.分离奇偶.               *" << endl;
            cout << "*4. 求链表长度.              |11.递增取交.               *" << endl;
            cout << "*5. 查找元素(位置查找).      |12.去重.                   *" << endl;
            cout << "*6. 插入节点.                |13.合并递增表.             *" << endl;
            cout << "*7. 查找元素(值查找).        |                           *" << endl;
            cout << "*- - - - - - - - - - - - - - + - - - - - - - - - - - - - *" << endl;
            cout << "*0. 退出.                    |-1.打印单链表(调试用)      *" << endl;
            cout << "**********************************************************" << endl;
            cout << "请输入序号:" <<endl;

            int iChose;
            cin >> iChose;

            cout << "\n" << endl;

            switch(iChose){
                case -1:
                    printList(L); break;
                case 0:
                    cout << "退出程序." << endl;
                    return 0;
                case 1:
                    creatListR(L); break;
                case 2:
                    creatListH(L); break;
                case 3:
                    destoryList(&L); break;
                case 4:
                    listLength(L); break;
                case 5:
                    getElement(L); break;
                case 6:
                    listInsert(L); break;
                case 7:
                    listLocate(L); break;
                case 8:
                    listDelete(L); break;
                case 9:
                    setInsert(L); break;
                case 10:
                    seperateOEList(L); break;
                case 11:
                    intersecIncreList(); break;
                case 12:
                   deleteRepList(L); break;
                case 13:
                    mergeIncreList(); break;
                default:
                    break;
            }

    }while(getchar()!='0');     //双重保险 退出.

    return 0;
}
