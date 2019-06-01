/** encoding: gbk **/

/*

(3)  骑士游历问题：
在国际棋盘上使一个骑士遍历所有的格子一遍且仅一遍，对于任意给定的顶点，
输出一条符合上述要求的路径。

*/

# include <iostream>
# include <cstring>
# include <stack>

// 定义最大棋盘
# define MAXROW 8
# define MAXCOL 8

using namespace std;

void printBoard();
void printRoute();

stack<pair<int, int> > route;
// 初始化棋盘
bool board[MAXROW][MAXCOL];
// 骑士走法(x±1, y±2), (x±2, y±1) 共8种情况
const int delX[8]={-2,-2,-1,-1, 1, 1, 2, 2};   // 设增量X
const int delY[8]={-1, 1,-2, 2,-2, 2,-1, 1};   // 设增量Y

int ct=0;

bool inBoard(int x, int y){
    if((0<=x && x<MAXROW) && (0<=y && y<MAXCOL))
        return true;
    return false;
}

bool newBlock(int x, int y){
    return !board[x][y];
}

bool doneTravel(){
	for(int i=0; i<MAXROW; ++i){
		for(int j=0; j<MAXCOL; ++j){
			if(!board[i][j])
				return false;
		}
	}
	return true;
}

void gotoPos(int x, int y){
	board[x][y] = true;
	route.push(make_pair(x, y));
	// 满路径打印路径并退出
	if(doneTravel() && route.size() == MAXROW*MAXCOL){
        ///ct++;   // count route
        ///cout << "--------" << ct << "--------" << endl;
        printRoute();
        exit(0);// 发现一条路线后exit()强制退出
        ///return ;// 发现所有路线后return退出
	}
	for(int i=0; i<8; ++i){
		int nextX = x + delX[i];
		int nextY = y + delY[i];
        // 若点在棋盘内, 且为新的点
		if(newBlock(nextX, nextY) && inBoard(nextX, nextY)){
			gotoPos(nextX, nextY);
			board[nextX][nextY] = false;
            route.pop();
		}
	}
}

void printRoute(){
	stack<pair<int, int> > prtS=route;
	int CR = 0;
	while(!prtS.empty()){
		pair<int, int> p = prtS.top();
		cout << "(" << p.first << ", " << p.second << ") ";
		prtS.pop();
		CR++;
		if(CR%MAXCOL==0)
            cout << endl;
	}
}

/// test
void printBoard(){
    for(int i=0; i<MAXROW; ++i){
        for(int j=0; j<MAXCOL; ++j){
            if(board[i][j] == 0)
                cout << 0 ;
            else
                cout << 1;
        }
        cout << endl;
    }
}


int main(int argc, char *argv[]){
	int x=-1, y=-1;
	while(!inBoard(x, y)){
        cout << "请输入初始横坐标:";
        cin >> x;
        cout << "请输入初始纵坐标:";
        cin >> y;
    }
    gotoPos(x, y);
	return 0;
}
