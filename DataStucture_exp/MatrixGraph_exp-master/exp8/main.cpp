#include<cstdlib>
#include<iostream>
#include"basis.h"
#include"file.h"
#include"createGrpAdjMatrix.h"
#include"graph.h"

using namespace std;

int main(int argc, char *argv[])
{
    char fileName[20];
    Graph G;
    csNode *T;
    int topoList[MaxVerNum+1];
	bool _continue = true;
	do {
		system("CLS");
		cout << "┌────────────────────────────────────────────────────────┐" << endl;
        cout << "│         Power by:计算机科学与技术17-1班 王子翔         │" << endl;
        cout << "│                        图实验                          │" << endl;
        cout << "├───────────────────────────┬────────────────────────────┤" << endl;
        cout << "│ 1. 打印图的两种遍历序.    │ 6. Kruskal算法求最小生成树.│" << endl;
        cout << "│ 2. 图的弧数目.            │ 7. Dijkstra算法求最短路径. │" << endl;
        cout << "│ 3. 深度优先遍历构造生成树.│ 8. Floyd算法求最短路径.    │" << endl;
        cout << "│ 4. 广度优先遍历构造生成树.│ 9. 拓扑序列.               │" << endl;
        cout << "│ 5. Prim算法求最小生成树.  │ 10.AOE网关键路径.          │" << endl;
        cout << "├───────────────────────────┴────────────────────────────┤" << endl;
        cout << "│0. 退出.                                                │" << endl;
        cout << "└────────────────────────────────────────────────────────┘" << endl;
        cout << "请输入序号:";

		int iChose;
		cin >> iChose;
		cin.get();

		switch (iChose) {
		case 0:
			_continue = false;
			break;
		case 1:
		    openFile(fileName);
		    CreateGrpFromFile(fileName, G);
            AdjMatrixDFSTraverse(G);
            AdjMatrixBFSTraverse(G);
            _pause();
            _continue=true;
			break;
		case 2:
		    openFile(fileName);
		    CreateGrpFromFile(fileName, G);
		    ArcNum(G);
			_pause();
            _continue=true;
			break;
		case 3:
		    openFile(fileName);
		    CreateGrpFromFile(fileName, G);
            DFSTraverseCreatTree(G, T);
			_pause();
            _continue=true;
			break;
		case 4:
		    openFile(fileName);
		    CreateGrpFromFile(fileName, G);
		    BFSTraverseCreatTree(G, T);
			_pause();
            _continue=true;
			break;
		case 5:
		    openFile(fileName);
		    CreateGrpFromFile(fileName, G);
		    Prim(G);
			_pause();
            _continue=true;
			break;
		case 6:
		    openFile(fileName);
		    CreateGrpFromFile(fileName, G);
		    Kruskal(G);
			_pause();
            _continue=true;
			break;
		case 7:
		    openFile(fileName);
		    CreateGrpFromFile(fileName, G);
            Dijkstra(G);
		    _pause();
            _continue=true;
			break;
        case 8:
            openFile(fileName);
		    CreateGrpFromFile(fileName, G);
		    Floyd(G);
		    _pause();
            _continue=true;
			break;
        case 9:
            openFile(fileName);
		    CreateGrpFromFile(fileName, G);
            TopologicalSort(G, topoList);
		    _pause();
            _continue=true;
			break;
        case 10:
            openFile(fileName);
		    CreateGrpFromFile(fileName, G);
		    KeyPath(G, topoList);
		    _pause();
            _continue=true;
			break;

        case 11://打印图(测试)
            openFile(fileName);
		    CreateGrpFromFile(fileName, G);
            printGraph(G);
            _pause();
            _continue=true;
            break;

		default:
			break;
		}
	}while(_continue);

	cout << "\n进程终止." << endl;

	return 0;
}
