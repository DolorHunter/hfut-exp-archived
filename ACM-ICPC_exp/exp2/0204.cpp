/** encoding: gbk **/

/*

(4)  倒水问题：
给定2个没有刻度容器，对于任意给定的容积，求出如何只用两个瓶装出L升
的水，如果可以，输出步骤，如果不可以，请输出No Solution。

*/

# include<iostream>
# include<stack>

using namespace std;

int main(){
    stack<pair<int, int> > ans;
    int aConMax, bConMax, L;
    int aConCur=0, bConCur=0;
    cin>>aConMax>>bConMax>>L;

    if(aConMax == 0 || bConMax == 0)
        return 2;

    if((aConMax + bConMax) < L){
        cout << "No Solution!" << endl;
        return 1;
    }

    //120
    if(L == 0){
        ans.push(make_pair(aConCur, bConCur));
        pair<int ,int> prtV;
        while(!ans.empty()){
            prtV = ans.top();
            cout << '[' <<prtV.first << ", " << prtV.second << ']' << "\t";
            ans.pop();
        }
        return 0;
    }

    //57C
    if(L == aConMax + bConMax){
        aConCur = aConMax;
        ans.push(make_pair(aConCur, bConCur));
        bConCur = bConMax;
        ans.push(make_pair(aConCur, bConCur));
        pair<int ,int> prtV;
        while(!ans.empty()){
            prtV = ans.top();
            cout << '[' <<prtV.first << ", " << prtV.second << ']' << "\t";
            ans.pop();
        }
        return 0;
    }

    //578 579
    if((L != aConMax + bConMax) && L > bConMax){
        while(aConCur + bConCur != L){
            // 装至b将要溢出
            while(aConMax + bConCur < bConMax){
                aConCur = aConMax;
                ans.push(make_pair(aConCur, bConCur));
                bConCur += aConCur;
                aConCur = 0;
                ans.push(make_pair(aConCur, bConCur));
            }//05 03
            aConCur = aConMax;
            ans.push(make_pair(aConCur, bConCur));//55 53
            aConCur -= bConMax-bConCur;
            bConCur = bConMax;
            ans.push(make_pair(aConCur, bConCur));//37 17
            if(aConCur + bConCur != L){
                bConCur = 0;
                ans.push(make_pair(aConCur, bConCur));//30
                bConCur = aConCur;
                aConCur = 0;
                ans.push(make_pair(aConCur, bConCur));//03
            }
            else{
                pair<int ,int> prtV;
                while(!ans.empty()){
                    prtV = ans.top();
                    cout << '[' <<prtV.first << ", " << prtV.second << ']' << "\t";
                    ans.pop();
                }
                return 0;
            }
        }
    }

    // 133
    if(L == aConMax || L == bConMax){
        if(L==aConMax){
            aConCur = aConMax;
            ans.push(make_pair(aConCur, bConCur));
        }
        else{
            bConCur = bConMax;
            ans.push(make_pair(aConCur, bConCur));
        }
        pair<int ,int> prtV;
        while(!ans.empty()){
            prtV = ans.top();
            cout << '[' <<prtV.first << ", " << prtV.second << ']' << "\t";
            ans.pop();
        }
        return 0;
    }

    //354 351
    if((L != aConMax && L != bConMax) && L < bConMax){
        while(aConCur != L && bConCur !=L){
            // 装至b将要溢出
            while(aConMax + bConCur < bConMax){
                aConCur = aConMax;
                ans.push(make_pair(aConCur, bConCur));
                bConCur += aConCur;
                aConCur = 0;
                ans.push(make_pair(aConCur, bConCur));
            }//03 04(out) 03
            if(aConCur == L || bConCur == L){
                pair<int ,int> prtV;
                while(!ans.empty()){
                    prtV = ans.top();
                    cout << '[' <<prtV.first << ", " << prtV.second << ']' << "\t";
                    ans.pop();
                }
                return 0;
            }
            aConCur = aConMax;
            ans.push(make_pair(aConCur, bConCur));//33 33
            aConCur -= bConMax-bConCur;
            bConCur = bConMax;
            ans.push(make_pair(aConCur, bConCur));//15 15
            if(aConCur != L || bConCur != L){
                bConCur = 0;
                ans.push(make_pair(aConCur, bConCur));//10 10
                bConCur = aConCur;
                aConCur = 0;
                ans.push(make_pair(aConCur, bConCur));//01 01
                if(aConCur == L || bConCur == L){
                    pair<int ,int> prtV;
                    while(!ans.empty()){
                        prtV = ans.top();
                        cout << '[' <<prtV.first << ", " << prtV.second << ']' << "\t";
                        ans.pop();
                    }
                    return 0;
                }
            }
            else{
                pair<int ,int> prtV;
                while(!ans.empty()){
                    prtV = ans.top();
                    cout << '[' <<prtV.first << ", " << prtV.second << ']' << "\t";
                    ans.pop();
                }
                return 0;
            }
        }
    }

    return 0;
}
