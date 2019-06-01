/** encoding: gbk **/

/*

(2) 八皇后问题：
在一个国际象棋棋盘上放八个皇后，使得任何两个皇后之间不相互攻击，求出所有
的布棋方法。上机运行并检验结果。
思考：将此题推广到N皇后的情况，检验在N比较大的情况下，比方说N=16的时
候，你的程序能否快速的求出结果，如果不能，思考有什么方法能够优化算法。

*/

# include <iostream>
# include <cstring>
# include <stack>

# define QUEENS 8
# define MAXROW 8
# define MAXCOL 8

using namespace std;

bool radiateBoard[MAXROW][MAXCOL];
char queenBoard[MAXROW][MAXCOL];
stack<pair<int, int> > newPos;
pair<int, int> pos;
int q;
int ct;

bool allRadiate(){
    for(int i=0; i<MAXROW; ++i){
        for(int j=0; j<MAXCOL; ++j){
            if(!radiateBoard[i][j])
                return false;
        }
    }
    return true;
}

void printBoard(){
    ct++;
    cout << "-------" << ct << "-------" << endl;
    for(int i=0; i<MAXROW; ++i){
        for(int j=0; j<MAXCOL; ++j){
            if(queenBoard[i][j] == 'Q')
                cout << "Q ";
            else
                cout << "x ";
        }
        cout << endl;
    }
}

/// test
void printRadiate(){
    for(int i=0; i<MAXROW; ++i){
        for(int j=0; j<MAXCOL; ++j){
            if(radiateBoard[i][j])
                cout << 1 << " ";
            else
                cout << 0 << " ";
        }
        cout << endl;
    }
}

void addQueen(int x, int y){
    queenBoard[x][y] = 'Q';
    radiateBoard[x][y] = true;
    q++;
    if(q == QUEENS){
        printBoard();
        ///exit(1);    /// testing
        return ;    // Finished return
    }
    // Mark new radiate area(except queens)
    newPos.push(make_pair(-1, -1)); // Mark button of stack(newPos)
    for(int i=0; i<MAXROW; ++i){
        for(int j=0; j<MAXCOL; ++j){
            bool radiate = !((i-x) && (j-y));
            if(!radiate)
                radiate = !((x-i-y+j) && (x-i+y-j));
            if(!radiateBoard[i][j] && radiate){
                radiateBoard[i][j] = true;
                newPos.push(make_pair(i, j));
            }
        }
    }
    if(allRadiate() && q<QUEENS){
        return ;    // Unfinished return
    }
    // Add new queen
    for(int i=0; i<MAXROW; ++i){
        for(int j=0; j<MAXCOL; ++j){
            if(!radiateBoard[i][j]){
                addQueen(i, j);
                if(q==QUEENS)
                    return ;    // Finished return
                queenBoard[i][j] = '0';
                radiateBoard[i][j] = false;
                q--;
                // Unmarked new radiate area(except queens)
                pos = newPos.top();
                while(pos.first!=-1 && pos.second!=-1){
                    radiateBoard[pos.first][pos.second] = false;
                    newPos.pop();
                    pos = newPos.top();
                }
                newPos.pop();   // Unmarked the button of stack(newPos)
            }
        }
    }
}


int main(){
    for(int i=0; i<MAXROW; ++i){
        for(int j=0; j<MAXCOL; ++j){
            while(!newPos.empty()){
                newPos.pop();
            }
            q = 0;
            memset(radiateBoard, false, sizeof(radiateBoard));
            memset(queenBoard, 0, sizeof(queenBoard));
            addQueen(i, j);
        }
    }
    return 0;
}
