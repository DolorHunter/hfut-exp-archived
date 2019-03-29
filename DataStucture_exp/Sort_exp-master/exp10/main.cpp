#include<cstdlib>
#include<iostream>
#include"basis.h"
#include"sort.h"

using namespace std;

int main(int argc, char argv[]){
    SqList L;
    int iSwap=0, iCmp=0;
	bool sign = true;
	do {
		system("CLS");
		cout << "┌────────────────────────────────────────────────────────┐" << endl;
        cout << "│         Power by计算机科学与技术17-1班 王子翔          │" << endl;
        cout << "│                       排序实验                         │" << endl;
        cout << "├────────────────────────────────────────────────────────┤" << endl;
        cout << "│ 1. 快速排序比较和交换元素的次数.                       │" << endl;
        cout << "│ 2. mod3排序.                                           │" << endl;
        cout << "│ 3. 不同步长下希尔排序算法.                             │" << endl;
        cout << "│ 4. 动态演示快速排序.                                   │" << endl;
        cout << "│ 5. 动态演示堆排序算法.                                 │" << endl;
        cout << "│ 6. 二路归并法排序.                                     │" << endl;
        cout << "├────────────────────────────────────────────────────────┤" << endl;
        cout << "│0. 退出.                                                │" << endl;
        cout << "└────────────────────────────────────────────────────────┘" << endl;
        cout << "请输入序号:";

		int iChose;
		cin >> iChose;
		cin.get();
		switch (iChose){
		case 0:
			sign=false;
			break;
		case 1:
		    iCmp=0, iSwap=0;//重置计数参数
		    QuickSort(&L, iSwap, iCmp);
		    cout << "\n快速排序最终结果:" << endl;
            prtsqList(&L);
            cout << "\n比较元素的次数:" << iCmp << endl;
            cout << "交换元素的次数:" << iSwap << endl;
            _pause();
            sign=true;
			break;
		case 2:
            mod3Sort(&L);
            cout << "\nmod3排序最终结果:" << endl;
            prtsqList(&L);
			_pause();
			sign=true;
			break;
		case 3:
		    //整合打印的希尔排序
		    ShellSort(&L);
		    _pause();
			sign=true;
			break;
		case 4:
		    QuickSort(&L, iSwap, iCmp);
		    cout << "\n快速排序最终结果:" << endl;
            prtsqList(&L);
			_pause();
			sign=true;
			break;
		case 5:
		    heapSort(&L);
		    cout << "\n堆排序最终结果:" << endl;
            prtsqList(&L);
			_pause();
			sign=true;
			break;
        case 6:
            MergeSort(&L);
            cout << "二路归并排序后:" ;
            prtsqList(&L);
			_pause();
			sign=true;
			break;

		default:
		    sign=true;
			break;
		}
	}while(sign);

	cout << "\n进程终止!" << endl;

	return 0;
}
