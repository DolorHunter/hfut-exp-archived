#pragma once
#include<cstdlib>
#include"basis.h"

using namespace std;

int main(int argc, char *argv[])
{
    seqQueue sQ;
    initialSeqQueue(sQ);
    linkQueue lQ;
    initialLinkedQueue(lQ);

    elementType x;

    do{
            system("CLS");
            cout << " # # # # Power by:计算机科学与技术17-1班 王子翔# # # # # #" << endl;
            cout << "********************循环顺序队列&链队列*******************" << endl;
            cout << "*1. 初始化队列.             |9. 初始化队列.              *" << endl;
            cout << "*2. 判断是否队空.           |10.判断是否队空.            *" << endl;
            cout << "*3. 判断是否队满.           |11.判断是否队满.            *" << endl;
            cout << "*4. 入队.                   |12.入队.                    *" << endl;
            cout << "*5. 出队.                   |13.出队.                    *" << endl;
            cout << "*6. 取队头元素.             |14.取队头元素.              *" << endl;
            cout << "*7. 求队列元素个数.         |15.求队列元素个数.          *" << endl;
            cout << "*8. 奇入偶出算法.           |16.奇入偶出算法.            *" << endl;
            cout << "*- - - - - - - - - - - - - -+- - - - - - - - - - - - - - *" << endl;
            cout << "*0. 退出.                                                *" << endl;
            cout << "**********************************************************" << endl;
            cout << "请输入序号:";

            int iChose;
            cin >> iChose;

            cout << "\n" << endl;

            switch(iChose){
            case 0:
                return 0;
            case 1:
                initialSeqQueue(sQ); break;
            case 2:
                seqQueueEmpty(sQ); break;
            case 3:
                seqQueueFull(sQ); break;
            case 4:
                seqEnQueue(sQ); break;
            case 5:
                seqOutQueue(sQ, x); break;
            case 6:
                seqQueueFront(sQ, x); break;
            case 7:
                seqQueueLength(sQ); break;
            case 8:
                seqQueueOddInEvenOut(sQ); break;
            case 9:
                initialLinkedQueue(lQ); break;
            case 10:
                linkedQueueEmpty(lQ); break;
            case 11:
                linkedQueueFull(); break;
            case 12:
                linkedEnQueue(lQ); break;
            case 13:
                linkedOutQueue(lQ, x); break;
            case 14:
                linkedQueueFront(lQ, x); break;
            case 15:
                linkedQueueLength(lQ); break;
            case 16:
                linkedOddInEvenOut(lQ); break;

            default:
                break;
            }
    }while(getchar()!='0');

    return 0;
}
