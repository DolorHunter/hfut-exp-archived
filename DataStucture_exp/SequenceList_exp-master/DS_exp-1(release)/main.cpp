#include<iostream>
#include"seqList.h"

using namespace std;

int main(int argc, char *argv[]){
    seqList L;
    initialList(&L);

    do{
            system("CLS");
            cout << " # # # # Power by:计算机科学与技术17-1班 王子翔# # # # # #" << endl;
            cout << "***************************顺序表*************************" << endl;
            cout << "*0. 初始化顺序表.           |5. 递增插入.                *" << endl;
            cout << "*1. 创建顺序表.             |6. 分解奇偶.                *" << endl;
            cout << "*2. 查找元素.               |7. 提取公共元素.            *" << endl;
            cout << "*3. 插入节点.               |8. 去重.                    *" << endl;
            cout << "*4. 删除节点.               |9. 退出.                    *" << endl;
            cout << "*- - - - - - - - - - - - - -+- - - - - - - - - - - - - - *" << endl;
            cout << "*-1.打印顺序表(调试用)      |-2.无暂停打印(调试用)       *" << endl;
            cout << "**********************************************************" << endl;
            cout << "请输入序号:" <<endl;
            int iChose;
            cin >> iChose;

            cout << "\n" << endl;

            switch(iChose){
                case 0:
                    initialList(&L); break;
                case 1:
                    buildList(&L); break;
                case 2:
                    searchList(&L); break;
                case 3:
                    insertList(&L); break;
                case 4:
                    deleteList(&L); break;
                case 5:
                    increinseList(&L); break;
                case 6:
                    seperateOEList(&L); break;
                case 7:
                    mixIncreList(); break;
                case 8:
                    delRepList(&L); break;
                case 9:
                    cout << "退出程序." << endl;
                    return 0;
                case -1:
                    printList(&L); break;
                case -2:
                    prtNpauseList(&L); break;
                default:
                    break;
            }

    }while(getchar()!='9');

    return 0;
}
