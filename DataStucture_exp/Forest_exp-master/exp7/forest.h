#pragma once
#include<iostream>
#define MAXLEN 100

using namespace std;

typedef char elementType;

	//森林双亲表示树的结点结构
typedef struct pNode
{
	elementType data;   //结点数据域
	int parent;         //父结点指针（下标）

}PTNode;
    //森林双亲表示树结构
typedef struct pTree
{
	PTNode node[MAXLEN];   //结点数组
	int n;                 //结点总数
}pTree;

    //森林孩子-兄弟链表表示
typedef struct csNode
{
	elementType data;
	struct csNode *firstChild, *nextSibling;
}csNode,*csTree;


//搜索双亲表示中，下标w的下一个兄弟结点，返回兄弟结点的下标
int next(pTree T, int w)
{
	int i;
	for(i=w+1;i<T.n;i++)
	{
		if(T.node[w].parent==T.node[i].parent)
			return i;
	}
	return -1;
}

//初始化树
void initialTree(pTree &T)
{
	T.n=0;   //结点数初始化为0
}

//1.1先序遍历
int firstChild(pTree &T, int v){    //搜索下标为v的结点的第一个孩子结点下标
	int w;
	if(v==-1)
		return -1;

	for(w=0; w<T.n; w++){
		if(T.node[w].parent==v)
			return w;
	}
	return -1;
}
int nextSibling(pTree &T, int v, int w){  //搜索v的下标位于w之后的下一个孩子结点下标
	int i;
	for(i=w+1; i<T.n; i++)
		if(T.node[i].parent==v)
			return i;
	return -1;
}
void preOrder(pTree &T,int v)
{
	int w;
	cout << T.node[v].data << "\t" ;

	w=firstChild(T,v);
	while(w!=-1)
	{

		preOrder(T,w);
		w=nextSibling(T,v,w);
	}
}

void preTraverse(pTree &T)
{
	int i;
	int visited[MAXLEN];
	for(i=0; i<T.n; i++)
	{
		visited[i]=0;
	}
	    //搜索根结点，可能是森林，有多个根结点
	for(i=0; i<T.n; i++)
	{
		if(T.node[i].parent==-1)
			preOrder(T,i);
	}
}

//1.2后序遍历
void postOrder(pTree &T, int v)
{
	int w;
	w=firstChild(T,v);
	while(w!=-1)
	{
		postOrder(T,w);
		w=nextSibling(T,v,w);
	}
	cout << T.node[v].data << "\t" ;   //访问根结点
}

void postTraverse(pTree &T){
	int i;
	int visited[MAXLEN];
	for(i=0; i<T.n; i++){
		visited[i]=0;
	}
	    //搜索根结点，可能是森林，有多个根结点
	for(i=0; i<T.n; i++){
		if(T.node[i].parent==-1)
			postOrder(T,i);
	}
}

//1.3层次遍历
int level(pTree &T, int n){
	int parent=n;
	int count=0;
	while(parent!=-1){
		parent=T.node[parent].parent;
		count++;
	}
	return count;
}
int height(pTree &T){
	int i=-1;
	int max=0;
	while(i!=T.n){
		if(max<level(T,i)){
            max=level(T,i);
		}
		i++;
	}
	return max;
}
void levelTraverse(pTree &T){
    int i,j,k=0;
	char len[MAXLEN];
	for(i=1; i<=height(T); i++){
        for(j=0; j<T.n; j++){
            if(i==level(T, j)){
                len[k]=T.node[j].data;
                k++;
            }
        }
    }
	for(i=0; i<k; i++){
		cout << len[i] << "\t";
	}
}

//2. 求森林高度
//int height(pTree &T)

//3. 求森林结点数目
//cout << "森林的结点度为" << T.n << endl;

//4. 求森林叶子数目
int leafNode(pTree &T){
	int parent[MAXLEN];
	int i,j=0;
	parent[0]=-1;
	for(i=0; i<T.n; i++){
		if(T.node[i].parent>parent[j])
			parent[++j]=T.node[i].parent;
	}
	return T.n-j;
}

//5. 森林的度
int degree(pTree &T){
	int parent[MAXLEN];
	int num[MAXLEN];
	int i=0,j=0,k=0,n=0;
	parent[0]=-1;
	for(i=0; i<T.n; i++){
		if(T.node[i].parent > parent[k])
			parent[k++] = T.node[i].parent;
	}
    for(i=0; i<k; i++){
        int h=0;
        for(j=0; j<T.n; j++){
            if(parent[i]==T.node[j].parent){
                num[i]=++h;
            }
        }
	}
	for(i=0; i<k; i++){
		if(n<num[i]){
			n=num[i];
		}
		return n;
	}
}

//6.先序输出结点值及其层次
void preOrderNode(pTree &T, int v){
	int w;
	cout << '(' << T.node[v].data << ',' << level(T,v) << ')' << "\t";
	w=firstChild(T,v);
	while(w!=-1){
		preOrderNode(T,w);
		w=nextSibling(T,v,w);
	}
}
void preTraverseNode(pTree &T){
	int i;
	int visited[MAXLEN];
	for(i=0;i<T.n;i++){
		visited[i]=0;
	}
	    //搜索根结点，可能是森林，有多个根结点
	for(i=0;i<T.n;i++){
		if(T.node[i].parent==-1)
			preOrderNode(T,i);
	}
}

//7.输出广义表表示的树
void outgList(csNode *T){
    if(T!=NULL){
        cout<<T->data;
        if(T->firstChild!=NULL){
            cout<<"(";
            outgList(T->firstChild);
        }
        if(T->nextSibling!=NULL){
			cout<<",";
			outgList(T->nextSibling);
		}
		else
			cout<<")";
    }
}

//递归创建一棵孩子兄弟链表表示的树
void create(csNode *&T, pTree &T1, int v)
{
	int w;
	T=new csNode;
	T->data=T1.node[v].data;
	T->firstChild=NULL;
	T->nextSibling=NULL;
	w=firstChild(T1,v);  //搜索v的第一个孩子结点
	if(w!=-1)
	{
		create(T->firstChild, T1, w);
	}

	w=next(T1, v);       //搜索v的下一个兄弟结点
	if(w!=-1)
	{
		create(T->nextSibling, T1, w);
	}
}

//从双亲表示的树（森林）创建孩子兄弟链表表示的树（森林）
void createCsTree(csNode *&T, pTree T1)
{
	int i;
	//搜索T1的第一个根结点
	for(i=0; i<T1.n; i++)
	{
		if(T1.node[i].parent==-1)   //找到第一个根结点
			break;
	}
	if(i<T1.n)
		create(T, T1, i);
}
