/** encoding: gbk **/

/*

(1) 练习vector和list的使用。
定义一个空的vector，元素类型为int，生成10个随机数插入到vector中，用迭代
器遍历vector并输出其中的元素值。在vector头部插入一个随机数，用迭代器遍历vector
并输出其中的元素值。用泛型算法find查找某个随机数，如果找到便输出，否则将此数
插入vector尾部。用泛型算法sort将vector排序，用迭代器遍历vector并输出其中的元
素值。删除vector尾部的元素，用迭代器遍历vector并输出其中的元素值。将vector清
空。
定义一个list，并重复上述实验，并注意观察结果。

*/

# include <algorithm>
# include <vector>
# include <list>
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
        cout << *it << ' ';
    }

    cout << "\n头部插入随机数" << endl;

    // 头部插入随机数
    myV.insert(myV.begin(), rand());

    // 迭代器遍历vector并输出元素值
    for (it = myV.begin(); it != myV.end(); ++it){
        cout << *it << ' ';
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

    // 迭代器遍历vector并输出元素值
    for (it = myV.begin(); it != myV.end(); ++it){
        cout << *it << ' ';
    }

    cout << "\n泛型算法sort将vector排序" << endl;

    // 泛型算法sort将vector排序
    sort(myV.begin(), myV.end());

    // 迭代器遍历vector并输出元素值
    for (it = myV.begin(); it != myV.end(); ++it){
        cout << *it << ' ';
    }

    cout << "\n删除vector尾部元素" << endl;

    // 删除vector尾部元素
    myV.pop_back();

    // 迭代器遍历vector并输出元素值
    for (it = myV.begin(); it != myV.end(); ++it){
        cout << *it << ' ';
    }

    cout << "\n将vector清空" << endl;

    // 将vector清空
    myV.erase(myV.begin(), myV.end());

    // 迭代器遍历vector并输出元素值
    for (it = myV.begin(); it != myV.end(); ++it){
        cout << *it << ' ';
    }
}

void myList(){
    list<int> myL;

    cout << "生成10个随机数存入list" << endl;

    // 生成10个随机数存入list
    for (int i = 0; i < 10; ++i){
        myL.push_back(rand());
    }

    // 迭代器遍历list并输出元素值
    list<int>::iterator it;
    for (it = myL.begin(); it != myL.end(); ++it){
        cout << *it << ' ';
    }

    cout << "\n头部插入随机数" << endl;

    // 头部插入随机数
    myL.push_front(rand());

    // 迭代器遍历list并输出元素值
    for (it = myL.begin(); it != myL.end(); ++it){
        cout << *it << ' ';
    }

    cout << "\n泛型算法find查找某个随机数" << endl;

    // 泛型算法find查找某个随机数
    int x = rand();
    it = find(myL.begin(), myL.end(), x);

    if (*it == x){  // 找到输出
        cout << *it << endl;
    }
    else{   // 找不到将此数插入尾部
        myL.push_back(x);
    }

    // 迭代器遍历list并输出元素值
    for (it = myL.begin(); it != myL.end(); ++it){
        cout << *it << ' ';
    }

    cout << "\n泛型算法sort将list排序" << endl;

    // 泛型算法sort将list排序
    myL.sort();

    // 迭代器遍历list并输出元素值
    for (it = myL.begin(); it != myL.end(); ++it){
        cout << *it << ' ';
    }

    cout << "\n删除list尾部元素" << endl;

    // 删除list尾部元素
    myL.pop_back();

    // 迭代器遍历list并输出元素值
    for (it = myL.begin(); it != myL.end(); ++it){
        cout << *it << ' ';
    }

    cout << "\n将list清空" << endl;

    // 将list清空
    myL.erase(myL.begin(), myL.end());

    // 迭代器遍历list并输出元素值
    for (it = myL.begin(); it != myL.end(); ++it){
        cout << *it << ' ';
    }
}

int main(int argc, char *argv[]){
    cout << "--------vector--------" << endl;
    myVector();
    cout << "------vector end------" << endl;
    cout << "---------list---------" << endl;
    myList();
    cout << "-------list end-------" << endl;

    return 0;
}
