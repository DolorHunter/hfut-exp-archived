#include<cstdlib>
#include<iostream>
#include"basis.h"
#include"file.h"
#include"forest.h"

using namespace std;

int main()
{
    char fileName[20];
    pTree T;
    csTree p;
	p=new csNode;

	bool sign = true;
	do {
		system("CLS");
		cout << "┌────────────────────────────────────────────────────────┐" << endl;
        cout << "│         Power by:计算机科学与技术17-1班 王子翔         │" << endl;
        cout << "│                     树与森林实验                       │" << endl;
        cout << "├───────────────────────────┬────────────────────────────┤" << endl;
        cout << "│ 1. 打印森林的三种遍历序.  │ 5. 森林的度.               │" << endl;
        cout << "│ 2. 森林的高度.            │ 6. 先序输出结点的值及层次. │" << endl;
        cout << "│ 3. 森林结点总数.          │ 7. 输出广义表表示的树.     │" << endl;
        cout << "│ 4. 森林叶子总数.          │                            │" << endl;
        cout << "├───────────────────────────┴────────────────────────────┤" << endl;
        cout << "│0. 退出.                                                │" << endl;
        cout << "└────────────────────────────────────────────────────────┘" << endl;
        cout << "请输入序号:";

		int iChose;
		cin >> iChose;

		switch (iChose) {
		case 0:
			sign = false;
			break;
		case 1:
            openFile(fileName);
            initialTree(T);
            createTreeFromFile(fileName, T);
            cout << "\n先序遍历为:";
			preTraverse(T);
			cout << "\n后序遍历为:";
			postTraverse(T);
			cout << "\n层次遍历为:";
			levelTraverse(T);
            _pause();
			break;
		case 2:
            openFile(fileName);
            initialTree(T);
            createTreeFromFile(fileName, T);
            cout << "森林的高度为" << height(T) << "." << endl;
			_pause();
			break;
		case 3:
            openFile(fileName);
            initialTree(T);
            createTreeFromFile(fileName, T);
            cout << "森林的结点数为" << T.n << "." << endl;
			_pause();
			break;
		case 4:
            openFile(fileName);
            initialTree(T);
            createTreeFromFile(fileName, T);
            cout << "森林的叶子数为" << leafNode(T) << "." << endl;
			_pause();
			break;
		case 5:
		    openFile(fileName);
		    initialTree(T);
            createTreeFromFile(fileName, T);
            cout << "森林的度为" << degree(T) << "." << endl;
			_pause();
			break;
		case 6:
		    openFile(fileName);
		    initialTree(T);
            createTreeFromFile(fileName, T);
            preTraverseNode(T);
			_pause();
			break;
		case 7:
		    openFile(fileName);
		    initialTree(T);
            createTreeFromFile(fileName, T);
            createCsTree(p,T);
            outgList(p);
			_pause();
			break;

		default:
			break;
		}
	}while(sign);

	cout << "\n进程终止." << endl;

	return 0;
}
