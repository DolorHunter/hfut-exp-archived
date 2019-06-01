/** encoding:gbk **/

/*

(4) 房间最短路问题：
给顶一个内含阻碍墙的房间，求解出一条从起点到终点的最最短路径。房间的边界
固定在x=0,x=10,y=0和y=10。起点和重点固定在(0,5)和(10,5)。房间里还有0到18个
墙，每个墙有两个门。输入给定的墙的个数，每个墙的x位置和两个门的y坐标区间，
输出最短路的长度。下图是个例子：

*/

# include <iostream>
# include <cstdlib>
# include <cmath>

# define MAXROW 10
# define MAXCOL 10

char room[MAXROW][MAXCOL];

using namespace std;

void printRoom(){
    cout << " 0 1 2 3 4 5 6 7 8 9 " << endl;
    cout << "0# # # # # # # # # # " << endl;
    for(int i=1; i<MAXROW-1; ++i){
        for(int j=0; j<MAXCOL; ++j){
            if(j == 0 || j == MAXCOL-1){
                if(j==0)
                    cout << i;
                cout << "# ";
                continue;
            }
            if(room[i][j]=='w')
                cout << "w ";
            else
                cout << "  ";
        }
        cout << endl;
    }
    cout << "9# # # # # # # # # # " << endl;
}

void genWall(int wall){
    // 过多墙壁生成的地图会导致离开失败
    int col, row1, row2;
    int minR, maxR, len;
    while(wall--){
        bool build = false;
        while(!build){
            col = rand()%(MAXCOL-2) + 1;
            row1 = rand()%(MAXROW-2) + 1;
            row2 = rand()%(MAXROW-2) + 1;
            minR = min(row1, row2);
            maxR = max(row1, row2);
            len = maxR - minR + 1;
            if((col == 1 || col == 8) && (minR<=5 && maxR>=5))  // 防止堵门
                continue;
            if((room[minR-1][col] != 'w' && room[maxR+1][col] != 'w') &&
               room[minR][col-1] != 'w' && room[maxR][col+1] != 'w'){
                while(len--){
                    room[minR+len][col]='w';
                    system("CLS");
                    printRoom();
                }
                build = true;
            }
        }
    }
}

float getLength(){
    float length = 0.0;
    int x = 0, y = 5;
    int tempX, tempY;
    float tempK, k;
    while(x!=MAXCOL-2){
        if(room[y][x+1] != 'w'){
            x++;
            length++;
        }
        else{
            tempX = x+1;
            tempY = y;
            int delta=1;
            while(room[tempY][tempX] == 'w'){
                tempY+=delta;
                if(room[tempY][tempX] != 'w')
                    break;
                tempY-=(2*delta);
                if(room[tempY][tempX] != 'w')
                    break;
                delta++;
            }
            k = (tempX-x)/(tempY-y);
            length += sqrt((tempY-y)*(tempY-y)+1);
            if(abs(tempK)>abs(k)){
                length += sqrt((tempY-y)*(tempY-y)+1);
                int tempLength = sqrt((tempX-0)*(tempX-0)+(tempY-5)*(tempY-5));
                tempK = tempX/(tempY-5);
                if(tempLength<length)
                    length = tempLength;
            }
            x = tempX;
            y = tempY;
        }
    }
    if(tempY<MAXCOL-1){
        float ke = (5-tempX)/(9-tempY);
        int inc = 0, incW = 0, delW = 1;
        for(int i=tempY; i<MAXCOL-1; ++i){
            inc++;
            if(room[i][tempX+int(inc*ke)]=='w'){
                incW=0;
                while(room[i][tempX+int(inc*ke)+incW] == 'w'){
                    incW+=delW;
                    if(room[i][tempX+int(inc*ke)+incW] != 'w')
                        break;
                    incW-=(2*delW);
                    if(room[i][tempX+int(inc*ke)+incW] != 'w')
                        break;
                    delW++;
                }
                length += sqrt((int(inc*ke)+incW)*(int(inc*ke)+incW)+1);
            }
        }
    }
    return length;
}


int main(){
    int wall;
    cin>>wall;
    genWall(wall);
    float len = getLength();
    cout << "最短距离为:" << len << endl;
    return 0;
}
