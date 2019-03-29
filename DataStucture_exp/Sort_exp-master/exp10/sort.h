#pragma once
#define elementType int
#define MAXLEN 1024

using namespace std;

    //定义顺序表结构
typedef struct{
    int key;
}SqNode;
typedef struct{
    SqNode str[MAXLEN];
    int length;
}SqList;

//打印顺序表
void prtsqList(SqList *L){
    for(int i=1; i<=L->length; i++){
        cout << L->str[i].key << "\t" ;
    }
}

//1. 快速排序比较和交换元素的次数.
int Partition(SqList *L,int low,int high, int &iSwap, int &iCmp){
    L->str[0]=L->str[low];
    int pivotkey=L->str[low].key;
    //直到两指针相遇,程序结束
    while(low<high){
        //high指针左移,直至遇到比pivotkey值小的记录,指针停止移动
        while (low<high && L->str[high].key>=pivotkey){
            high--;
            iCmp++;
        }
        //直接将high指向的小于支点的记录移动到low指针的位置。
        L->str[low]=L->str[high];
        //low 指针右移,直至遇到比pivotkey值大的记录,指针停止移动
        while(low<high && L->str[low].key<=pivotkey){
            low++;
            iCmp++;
        }
        //直接将low指向的大于支点的记录移动到high指针的位置
        L->str[high]=L->str[low];
    }
    //将支点添加到准确的位置
    L->str[low]=L->str[0];
    iSwap++;
    return low;
}
void QSort(SqList *L,int low,int high, int &iSwap, int &iCmp){
    static int iCount=0;
    if(low<high){
        //找到支点的位置
        int pivotloc=Partition(L, low, high, iSwap, iCmp);
        //对支点左侧的子表进行排序
        QSort(L, low, pivotloc-1, iSwap, iCmp);
        cout << "第" << iCount << "次排序结果:" << endl;
        iCount++;
        prtsqList(L);
        //对支点右侧的子表进行排序
        QSort(L, pivotloc+1, high, iSwap, iCmp);
        cout << "第" << iCount << "次排序结果:" << endl;
        iCount++;
        prtsqList(L);
    }
}
void QuickSort(SqList *L, int &iSwap, int &iCmp){
    L->length=40;
    cout << "\n随机生成1000内数字参与排序." << endl;
    for(int i=1; i<=40; i++){
        L->str[i].key=rand()%1000;
    }
    QSort(L, 1,L->length, iSwap, iCmp);
}

//2. mod3排序.
void mod3(SqList *L, int i0, int i1, int i2){
    elementType str[MAXLEN];
    //把key拷贝至str[]
    for(int i=1; i<=L->length; i++){
        str[i]=L->str[i].key;
    }
    int iLoc=1;
    for(int i=1; i<=L->length; i++){
        if(str[i]%3==0){
            L->str[iLoc].key=str[i];
            iLoc++;
        }
        else if(str[i]%3==1){
            i0++;
            L->str[i0].key=str[i];
        }
        else{
            i1++;
            L->str[i1].key=str[i];
        }
    }
}
void mod3Sort(SqList *L){
    L->length=40;
    cout << "\n随机生成1000内数字参与排序." << endl;
    for(int i=1; i<=40; i++){
        L->str[i].key=rand()%1000;
    }
    int i0=0, i1=0, i2=0;
    for(int i=1; i<=40; i++){
        //mod存储余数
        int mod=L->str[i].key%3;
        //i0,i1,i2分别保存余数为0,1,2的数的个数
        switch(mod){
            case 0:
                i0++;
                break;
            case 1:
                i1++;
                break;
            case 2:
                i2++;
                break;
            default :
                break;
        }
    }
    mod3(L, i0, i1, i2);
}

//3. 不同步长下希尔排序算法.
//希尔排序的实现函数,其中 dk 表示增值量
void ShellInsert(SqList * L, int dk){
    //从 dk+1 个记录起,每间隔 dk 个记录就调取一个进行直接插入排序算法
    for(int i=dk+1; i<=L->length; i++){
        //如果新调取的关键字的值,比子表中最后一个记录的关键字小,说明需要将该值调换位置
        if(L->str[i].key<L->str[i-dk].key){
            int j;
            //记录表中,使用位置下标为 0 的空间存储需要调换位置的记录的值
            L->str[0]=L->str[i];
            //做直接插入排序,如果下标为 0 的关键字比下标为 j 的关键字小,则向后一行下标为 j 的值,为新插入的记录腾出空间。
            for(j=i-dk; j>0 && (L->str[0].key<L->str[j].key); j-=dk){
                L->str[j+dk]=L->str[j];
            }
            //跳出循环后,将新的记录值插入到腾出的空间中,即完成了一次直接插入排序
            L->str[j+dk]=L->str[0];
        }
    }
}
void ShellSort(SqList * L){
    //用数组来存储增量值
    int dlta[]={5, 3, 1};
    int t=3;//数组长度
    L->length=40;
    //生成随机数
    cout << "\n随机生成1000内数字参与排序." << endl;
    for(int i=1; i<=40; i++){
        L->str[i].key=rand()%1000;
    }
    //调用不同的增量值,实现对多个子表分别进行直接插入排序
    for(int k=0; k<t; k++){
        ShellInsert(L, dlta[k]);
        cout << "\n增量为" << 5-2k << "时希尔算法结果:" << endl;
        prtsqList(L);
    }
}

//4. 动态演示快速排序.
//改进版void QuickSort(SqList *L, int &iSwap, int &iCmp)
//已经集成动态演示和计数功能, 此处直接调用即可

//5. 动态演示堆排序算法.
//筛选算法
void sift(SqList *L, int k, int m){
    //对数组中下标为1~n中的元素中的序号不大于m的以k为根的子序列调整
    //假设以2k和2k+1为根的左右子树均是堆
    SqNode x=L->str[k];   //临时保存当前根值,空出位置
    bool finish=false;//设置结束标识
    int i=k;
    int j=2*i;
    while(j<=m && !finish){
        if(j<m && L->str[j].key<L->str[j+1].key){
            j++;//让j指向左右孩子中的最大者
        }
        if(x.key>=L->str[j].key){
            finish=true;//原根为最大,置结束筛选标志
        }
        else{
            L->str[i]=L->str[j];//大的孩子结点上移
            i=j;//继续向下筛选,i指示新的空位
            j=2*i;
        }
    }
    L->str[i]=x;//降原根值填充到所搜索到的当前空位置中
}
//堆排序算法
void heapSort(SqList *L){
    L->length=40;
    //生成随机数
    cout << "\n随机生成1000内数字参与排序." << endl;
    for(int i=1; i<=40; i++){
        L->str[i].key=rand()%1000;
    }
    //对数组中下标为1~n的元素用堆排序算法实现排序
    for(int i=L->length/2; i>=1; i--){
        sift(L, i, L->length);//建立初始堆
    }
    int iCount=0;
    for(int i=L->length; i>=2; i--){
        SqNode temp=L->str[i];
        L->str[i]=L->str[1];
        L->str[1]=temp;
        sift(L, 1, i-1);
        iCount++;
        cout << "第" << iCount << "次堆排序结果:" << endl;
        prtsqList(L);
    }
}

//6. 二路归并法排序.
//SR中的记录分成两部分：下标从 i 至 m 有序,从 m+1 至 n 也有序,此函数的功能是合二为一至TR数组中,使整个记录表有序
void Merge(SqNode SR[], SqNode TR[], int i, int m, int n){
    int j, k;
    //将SR数组中的两部分记录按照从小到大的顺序添加至TR数组中
    for (j=m+1,k=i; i<=m && j<=n; k++){
        if (SR[i].key<SR[j].key){
            TR[k]=SR[i++];
        }else{
            TR[k]=SR[j++];
        }
    }
    //将剩余的比目前TR数组中都大的记录复制到TR数组的最后位置
    while(i<=m){
        TR[k++]=SR[i++];
    }
    while (j<=n){
        TR[k++]=SR[j++];
    }
}
void MSort(SqNode SR[], SqNode TR1[], int s, int t){
    SqNode TR2[MAXLEN];
    //递归的出口
    if (s==t){
        TR1[s]=SR[s];
    }else{
        int m=(s+t)/2;//每次递归将记录表中记录平分,直至每个记录各成一张表
        MSort(SR, TR2, s, m);//将分开的前半部分表中的记录进行排序
        MSort(SR, TR2, m+1, t);//将后半部分表中的记录进行归并排序
        Merge(TR2, TR1, s, m, t);//最后将前半部分和后半部分中的记录统一进行排序
    }
}
//二路归并排序主调用函数
void MergeSort(SqList *L){
    L->length=40;
    //生成随机数
    cout << "\n随机生成1000内数字参与排序." << endl;
    for(int i=1; i<=40; i++){
        L->str[i].key=rand()%1000;
    }
    MSort(L->str, L->str, 1, L->length);
}
