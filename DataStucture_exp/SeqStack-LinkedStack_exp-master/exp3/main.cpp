#include<iostream>
#include<cstdlib>
#include"linkedStack.h"
#include"seqStack.h"

using namespace std;

int main(int argc, char *argv[])
{
    do{
            system("CLS");
            cout << " # # # # Power by:计算机科学与技术17-1班 王子翔# # # # # #" << endl;
            cout << "************************顺序栈&链栈***********************" << endl;
            cout << "*1. 10进制数转换为16进制(顺序栈).                        *" << endl;
            cout << "*2. 判断其中的各括号是否是匹配(顺序栈).                  *" << endl;
            cout << "*3. 10进制数转换为16进制(链栈).                          *" << endl;
            cout << "*4. 判断其中的各括号是否是匹配(链栈).                    *" << endl;
            cout << "*- - - - - - - - - - - - - - - - - - - - - - - - - - - - *" << endl;
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
                radixChange10to16sStack(); break;
            case 2:
                bracketMatchsStack(); break;
            case 3:
                radixChange10to16lS(); break;
            case 4:
                bracketMatchlS(); break;
            default:
                break;
            }
    }while(getchar()!='0');

    return 0;
}
