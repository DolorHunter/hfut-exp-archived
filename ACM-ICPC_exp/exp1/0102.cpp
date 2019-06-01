/** encoding: gbk **/

/*

(2) 练习泛型算法的使用。
定义一个vector，元素类型为int，插入10个随机数，使用sort按升序排序，输出
每个元素的值，再按降叙排序，输出每个元素的值。练习用find查找元素。用min和
max找出容器中的最小元素个最大元素，并输出。

*/

# include <algorithm>
# include <vector>
# include <iostream>

using namespace std;

void myVector(){
    vector<int> myV;

    cout << "生成10个随机数存入vector" << endl;

    // 生成10个随机数存入vector
    for (int i = 0; i < 10; ++i){
        myV.push_back(rand());
    }

    // 迭代器遍历vector并输出元素值
    vector<int>::iterator it;
    for (it = myV.begin(); it != myV.end(); ++it){
        cout << (*it) << ' ';
    }

    cout << "\n泛型算法sort将vector排序(升序)" << endl;

    // 泛型算法sort将vector排序(升序)
    sort(myV.begin(), myV.end());

    // 迭代器遍历vector并输出元素值
    for (it = myV.begin(); it != myV.end(); ++it){
        cout << (*it) << ' ';
    }

    cout << "\n泛型算法sort将vector排序(降序)" << endl;

    // 泛型算法sort将vector排序(降序)
    sort(myV.begin(), myV.end(), greater<int>());

    // 迭代器遍历vector并输出元素值
    for (it = myV.begin(); it != myV.end(); ++it){
        cout << (*it) << ' ';
    }

    cout << "\n泛型算法find查找某个随机数" << endl;

    // 泛型算法find查找某个随机数
    int x = rand();
    it = find(myV.begin(), myV.end(), x);

    if (*it == x){  // 找到输出
        cout << *it << endl;
    }
    else{   // 找不到将此数插入尾部
        myV.push_back(x);
    }

    // 迭代器遍历list并输出元素值
    for (it = myV.begin(); it != myV.end(); ++it){
        cout << *it << ' ';
    }

    cout << "\n找出容器中的最小元素个最大元素" << endl;

    //用min和max找出容器中的最小元素个最大元素，并输出。
    int max = *max_element(myV.begin(), myV.end());

    cout << "max=" << max << endl;

    int min = *min_element(myV.begin(), myV.end());

    cout << "min=" << min << endl;
}

int main(int argc, char *argv[]){
    cout << "--------vector--------" << endl;
    myVector();
    cout << "------vector end------" << endl;

    return 0;
}
