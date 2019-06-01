/** encoding:WINDOWS-936 **/

/*

(1)  求两个字符串的最长公共子序列。
X的一个子序列是相应于X下标序列{1, 2, …, m}的一个子序列，求解两个序列的所有
子序列中长度最大的，例如输入：pear, peach输出：pea。

*/

# include <iostream>
# include <cstring>
# include <stack>

using namespace std;


int matrix[100][100];
string str1;
string str2;
int len;
int x, y;
stack<char> ans;

int main(){
    str1 = "abbabcdef";
    str2 = "ababbcdef";

    len = 0;

    matrix[str1.length()][str2.length()];
    // 查找出值为1的最长对角线就能找到最长公共子串
    for(int i=0; i<str1.length(); ++i){
        for(int j=0; j<str2.length(); ++j){
            if(str1[i] == str2[j]){
                if(i>0 && j>0){
                    matrix[i][j] = matrix[i-1][j-1] + 1;
                }
                else{
                    matrix[i][j] = 1;
                }

                if(matrix[i][j] > len){
                    len = matrix[i][j];
                    x = i;
                    y = j;
                }
            }
            else{
                matrix[i][j] = 0;
            }
        }
    }

    for(int i=0; i<len; ++i){
        ans.push(str1[x--]);
    }

    cout << len << endl;

    while(!ans.empty()){
        cout << ans.top();
        ans.pop();
    }
    return 0;
}
