#include<cstdlib>
#include<iostream>
#include"basis.h"
#include"search.h"

using namespace std;

int main(int argc, char argv[]){
    sList L;
    bstNode bsT;
    AVLTree avlT;
	bool sign = true;
	do {
		system("CLS");
		cout << "┌────────────────────────────────────────────────────────┐" << endl;
        cout << "│         Power by计算机科学与技术17-1班 王子翔          │" << endl;
        cout << "│                       查找实验                         │" << endl;
        cout << "├────────────────────────────────────────────────────────┤" << endl;
        cout << "│ 1. 二分查找并打印过程中比较的元素.                     │" << endl;
        cout << "│ 2. 二叉排序树中循环插入结点构建二叉排序树.             │" << endl;
        cout << "│ 3. 二叉排序树中查找指定值的结点.                       │" << endl;
        cout << "│ 4. 二叉排序树中删除特定值的结点.                       │" << endl;
        cout << "│ 5. 构造一棵平衡的二叉排序树存放数组.                   │" << endl;
        cout << "├────────────────────────────────────────────────────────┤" << endl;
        cout << "│0. 退出.                                                │" << endl;
        cout << "└────────────────────────────────────────────────────────┘" << endl;
        cout << "请输入序号:";

		int iChose;
		cin >> iChose;
		switch (iChose){
		case 0:
			sign=false;
			break;
		case 1:
		    initialSearchList(L);
            binSearch(L);
            _pause();
            sign=true;
			break;
		case 2:
            bstCreat(&bsT);
            cout << "打印二叉排序树:";
            prtBinarySortTree(&bsT);
			_pause();
			sign=true;
			break;
		case 3:
            bstSearch(&bsT);
			_pause();
			sign=true;
			break;
		case 4:
            bstDeleteNode(&bsT);
            cout << "打印删除后的二叉排序树:";
            prtBinarySortTree(&bsT);
			_pause();
			sign=true;
			break;
		case 5:
		    creatAVLFromArray(&avlT);
		    cout << "打印AVL树:";
            prtAVLTree(avlT);
			_pause();
			sign=true;
			break;

		default:
		    sign=true;
			break;
		}
	}while(sign);

	cout << "\n进程终止!" << endl;

	destoryBinarySortTree(&bsT);
	destoryAVLTree(avlT);

	return 0;
}
