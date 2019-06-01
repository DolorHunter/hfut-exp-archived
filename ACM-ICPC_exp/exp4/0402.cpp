/** encoding:WINDOWS-936 **/

/*

(2)  给定两个字符串a和b，现将串a通过变换变为串b，可用的操作为，删除串a中的一
个字符；在串a的某个位置插入一个元素；将串a中的某个字母换为另一个字母。对于
任意的串a和串b，输出最少多少次能够将串变为串b。
思考：输出变换的步骤。

*/

# include <iostream>
# include <stack>

using namespace std;

//stack<char> ans;
int ans;
string str1;
string str2;
int mat[100][100];

int min3(int a, int b, int c){
    int min2 = min(a, b);
    return min(min2, c);
}

///test
void print(){
    for(int i=0; i<str1.length(); ++i){
        for(int j=0; j<str2.length(); ++j){
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}

int main(){
    str1 = "abcff2";
    str2 = "bce543d";

    mat[str1.length()][str2.length()];
    // 给定第一行
    for(int i=0; i<str2.length(); ++i){
        mat[0][i] = i;
    }
    // 给定第一列
    for(int i=0; i<str1.length(); ++i){
        mat[i][0] = i;
    }
    // 递推公式计算mat[i][j]
    for(int i=1; i<str1.length(); ++i){
        for(int j=1; j<str2.length(); ++j){
            mat[i][j] = min3(mat[i-1][j]+1, mat[i][j-1]+1, mat[i-1][j-1]+(str1[i]==str2[j]?0:1));
        }
    }

    print();
    // 最后一行，最后一列为最小编辑距离
    ans = mat[str1.length()-1][str2.length()-1];
    cout << ans << endl;

    return 0;
}
