/** encoding:WINDOWS-936 **/

/*

(3)  输入一个矩阵，计算所有的子矩阵中和的最大值。
例如，输入
0 -2 -7 0
9 2 -6 2
-4 1 -4 1
-1 8 0 -2
输出为：15
思考：当矩阵很大时，比如100*100的矩阵，你的程序还能够很快的得出结果吗，如果
不能，请思考如何用动态规划的思想解决。

*/

# include <iostream>
# include <cstring>

using namespace std;

int a[100][100], p[100][100];

int maxSonMat(int n){
    for(int i=0; i<=n; ++i){
        p[i][0] = 0;
        p[0][i] = 0;
    }
    for(int i=1; i<=n; ++i){
        for(int j=1; j<=n; ++j){
            // 计算子矩阵
            p[i][j] = p[i-1][j] + p[i][j-1] - p[i-1][j-1] + a[i][j];
        }
    }
    int MAX = 0;
    // 计算最大子矩阵和
    for(int i=1; i<=n; ++i){
        for(int j=1; j<=n; ++j){
            int sum=0;
            for(int k=1; k<=n; ++k){
                // 计算i~j行, k~m列的矩阵元素和
                int temp = p[j][k] - p[j][k-1] - p[i-1][k] + p[i-1][k-1];
                if(sum > 0)
                    sum += temp;
                else
                    sum = temp;
                // 求出最大矩阵和
                if(sum>MAX)
                    MAX = sum;
            }
        }
    }
    return MAX;
}

int main(){
    int n=4;
    int num;
    for(int i=1; i<=n; ++i){
        for(int j=1; j<=n; ++j){
            cin>>num;
            a[i][j] = num;
        }
    }
    cout << maxSonMat(n) << endl;
}
