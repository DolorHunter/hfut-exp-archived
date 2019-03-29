#pragma once
#define INF 65535
#include"grpAdjMatrix.h"
#include"seqQueue.h"
#include"seqStack.h"
#include"BiTree.h"
#include"forest.h"

typedef struct edgetype
{
	int vBegin;  //边的起始顶点编号，从1开始
	int vEnd;     //边的另一顶点编号，从1开始
	int eWeight;  //边的权值
}EdgeType;   //边数组的类型

typedef struct minEdgeType
{
	int v;//边中另一端的顶点编号
	cellType eWeight;//边的权值
}MinEdgeType;//边数组的元素类型

//1.打印图的两种遍历序

//DFS深度遍历算法
    //基于邻接矩阵的DFS的实现
void DFS(Graph &G, int verID){
    int w;
	visit(G, verID);
	w=firstAdj(G, verID);
	while(w!=0){
		if(!visited[w])            //w尚未访问
			DFS(G, w);             //递归深度遍历
		w=nextAdj(G, verID, w);    //递归返回后，再找verID的位于w后的下一个邻接点
	}
}
void AdjMatrixDFSTraverse(Graph &G){
    int vID=0;
    cout << "请输入首个访问点的序号:" ;
    cin >> vID;
    cin.get();
    //将用做标记的visit数组初始化为false
    for(vID=1; vID<=G.VerNum; vID++){
        visited[vID]=false;
    }
    DFS(G, vID);//从指定顶点遍历
    for(vID=1; vID<=G.VerNum; vID++){
        //如果该顶点的标记位为false，则调用深度优先搜索函数
        if(!visited[vID]){
            DFS(G, vID);
        }
    }
    cout << "\nDFS深度遍历已完成!" << endl;
}

//BFS广度遍历算法
    //基于邻接矩阵的BFS实现
void BFS(Graph &G, int verID){
	visit(G, verID);
	seqQueue Q;
	initialSeqQueue(Q);           //初始化循环顺序队列
	seqEnQueue(Q, verID);         //编号为verID的顶点入队
	char v, w;
	while(!seqQueueEmpty(Q)){     //队列不空循环处理顶点
		seqOutQueue(Q, v);        //v出队
		w=firstAdj(G, v);         //搜索v的第一个邻接点
		while(w!=0){
			if(!visited[w]){      //w尚未访问，访问w，并标记已访问
				visit(G, w);
				seqEnQueue(Q, w); //顶点w入队
			}
			w=nextAdj(G,v,w);     //搜索顶点v位于w后的下一个邻接点
		}
	}
}
void AdjMatrixBFSTraverse(Graph &G){
    int vID=0;
    cout << "请输入首个访问点的序号:" ;
    cin >> vID;
    cin.get();
	for(vID=1; vID<=G.VerNum; vID++)  //初始化
		visited[vID]=false;
	BFS(G, vID);  //从指定的顶点，遍历指定的第一个连通分量
	for(vID=1; vID<=G.VerNum; vID++){  //再依次遍历图中其它的连通分量
		if(!visited[vID])
			BFS(G, vID);
	}
	cout << "\nBFS广度遍历已完成!" << endl;
}

//2. 图的弧数目.
void ArcNum(Graph &G){
    cout << "图的弧数目为:" << G.ArcNum << "." << endl;
}

//3. 深度优先遍历构造生成树.
void DFS_CreatTree(Graph &G, csNode *&T, int verID){
	csNode *p;
	csNode *u;
	int w;
	visited[verID] = true;
	w=firstAdj(G,verID);
	if(w!=0){
		while(visited[w] && w!=0)
			w=nextAdj(G, verID, w);
		if(w!=0){
			p=new csNode;
			p->data = G.Data[w];
			p->firstChild=NULL;
			p->nextSibling=NULL;
			T->firstChild=p;
		}
	}
	u=p;
	while(w!=0){
		if(!visited[w])        //w尚未访问
			DFS_CreatTree(G, u, w);          //递归深度遍历
		w=nextAdj(G,verID, w);    //递归返回后，再找verID的位于w后的下一个邻接点
		if(w!=0 && !visited[w]){
			p=new csNode;
			p->data=G.Data[w];
			p->firstChild=NULL;
			p->nextSibling=NULL;
			while(u->nextSibling!=NULL)
				u=u->nextSibling;
			u->nextSibling=p;
		}
		if(u!=NULL)
			u=u->nextSibling;
	}
}
void DFSTraverseCreatTree(Graph &G, csNode *&T){
    int vID;
    cout << "请输入首个访问点序号:" ;
    cin >> vID;
    cin.get();
	csNode *p;
	csNode *u;
	for(vID=1;vID<=G.VerNum;vID++)  //初始化
		visited[vID]=false;
	T=new csNode;
	T->data=G.Data[vID];
	T->firstChild=NULL;
	T->nextSibling=NULL;
	u=T;
	DFS_CreatTree(G, T, vID);  //从指定的顶点，遍历指定的第一个连通分量
	for(vID=1; vID<=G.VerNum; vID++){  //再依次遍历图中其它的连通分量
		if(!visited[vID]){
			p=new csNode;
			p->data=G.Data[vID];
			p->firstChild=NULL;
			p->nextSibling=NULL;
			while(u->nextSibling)
				u=u->nextSibling;
			u->nextSibling=p;
			DFS_CreatTree(G, p, vID);
		}
	}
	cout << "邻接矩阵创建构成森林遍历结果为(DFS):";
	prOrder(T);
	destroyTree(T);
}

//4. 广度优先遍历构造生成树.
void BFS_CreatTree(Graph &G, csNode *&T, int verID){
	csNode *u=T;
	csNode *p;
	int v, w;      //顶点编号
	v=verID;
	seqQueue Q;
	initialSeqQueue(Q);         //初始化循环顺序队列
	visited[verID]=true;
	seqEnQueue(Q, verID);       //编号为verID的顶点入队
	while(!seqQueueEmpty(Q)){     //队列不空循环处理顶点
		seqOutQueue(Q, v);       //v出队
		w=firstAdj(G,v);      //搜索v（verID）的第一个邻接点，返回到w
		if(w!=0){
			while(visited[w] && w!=0)
				w=nextAdj(G,v,w);
			if(w == 0)
				break;
			p=new csNode;
			p->data=G.Data[w];
			p->firstChild=NULL;
			p->nextSibling=NULL;
			u->firstChild=p;
		}
		u=p;
		while(w!=0){
			if(!visited[w]){   //w尚未访问，访问w，标记，入队
				visited[w]=true;
				seqEnQueue(Q,w);
			}
			w=nextAdj(G,v,w);  //搜索顶点v位于w之后的下一个邻接点
			if(w!=0 && !visited[w]){
				p=new csNode;
				p->data=G.Data[w];
				p->firstChild=NULL;
				p->nextSibling=NULL;
				while(u->nextSibling!=NULL)
					u=u->nextSibling;
				u->nextSibling=p;
			}
		}
	}
}
int BFSTraverseCreatTree(Graph &G, csNode *&T){
    int vID;
    cout << "请输入首个访问点序号:" ;
    cin >> vID;
    cin.get();
	csNode *p;
	csNode *u;
	for(vID=1;vID<=G.VerNum;vID++)  //访问标记数组初始化
		visited[vID]=false;
	T=new csNode;
	T->data=G.Data[vID];
	T->firstChild=NULL;
	T->nextSibling=NULL;
	u=T;
	BFS_CreatTree(G, T, vID);  //从指定的顶点，遍历指定的第一个连通分量
	for(vID=1; vID<=G.VerNum; vID++){  //再依次遍历图中其它的连通分量
		if(!visited[vID]){
			p=new csNode;
			p->data=G.Data[vID];
			p->firstChild=NULL;
			p->nextSibling=NULL;
			while(u->nextSibling!=NULL)
				u=u->nextSibling;
			u->nextSibling=p;
			BFS_CreatTree(G, p, vID);
		}
	}
	cout << "邻接矩阵创建构成森林遍历结果为(BFS):";
	prOrder(T);
	destroyTree(T);
}

//5. Prim算法求最小生成树.
int HasEdge(Graph &G, int vBegin, int vEnd){
	if(G.gKind==UDN || G.gKind==DN){  //网情况
		if(G.AdjMatrix[vBegin][vEnd]!=INF)  //权值非无穷大即有边
			return 1;  //有边，返回1
		else
			return 0;  //无边，返回0
	}
	else{  //图情况
		if(G.AdjMatrix[vBegin][vEnd]==1)  //顶点编号与数组下标差1
			return 1;  //有边，返回1
		else
			return 0;  //无边，返回0
	}
}
void InitialTE(Graph &G, MinEdgeType TE[], int vID){
	int i;
	for(i=1;i<=G.VerNum;i++){
		if(HasEdge(G, vID, i) == 1){
			TE[i].v=vID;
			TE[i].eWeight=G.AdjMatrix[vID][i];
		}
		else
			TE[i].eWeight=INF;//不存在赋值为无穷大
	}
}
int GetMinEdge(Graph &G, MinEdgeType TE[]){
	cellType eMin=INF;  //保存最小的权值
	int i,j;
	for(i=1;i<=G.VerNum;i++){
		if(visited[i]== false && TE[i].eWeight<eMin){
			j=i;//保留最小结点下标
			eMin=TE[i].eWeight;
		}
	}
	return j;  //j即为V-U中，最小边关联顶点的编号
}
void UpdateTE(Graph &G, MinEdgeType TE[], int vID){
	//对新选出的编号为vID的顶点（新加入集合U中），调整候选边集合
	int i,j;
	for(i=1;i<=G.VerNum;i++){
		if(visited[i]== false){  //编号i顶点在V-U中，不在U中
			if(HasEdge(G,vID,i) && G.AdjMatrix[vID][i]<=TE[i].eWeight){
				TE[i].v=vID;
				TE[i].eWeight=G.AdjMatrix[vID][i];
			}
		}
	}
}
void Prim(Graph &G){
    int vID;
    cout << "请输入首个访问点序号:" ;
    cin >> vID;
    cin.get();
	MinEdgeType TE[MaxVerNum];
	int curID;
	int i;
	cellType wALL=0;//权值总和
	InitialTE(G, TE, vID);//获取各结点到 vID的权值
	visited[vID]=true;//代表已经访问
	for(i=1; i<G.VerNum; i++){
		curID=GetMinEdge(G, TE);
		visited[curID]=true;
		UpdateTE(G, TE, curID);
	}
	cout << "Prim最小生成树开始顶点为:" << G.Data[vID] << endl;
	cout << "选择的边和权值:" << endl;
	for(i=1; i<=G.VerNum; i++){
		if(i!=vID){
			cout << "(" << G.Data[TE[i].v] << "," << G.Data[i] << ")";
			wALL+=TE[i].eWeight;
		}
	}
	cout << "最小生成树总权值:"<< wALL << endl;
}

//6. Kruskal算法求最小生成树.
void GetEdges(Graph &G, EdgeType edges[]){
	int i,j;
	int k=1;
	for(i=1; i<=G.VerNum; i++){  //行循环
		for(j=1; j<=G.VerNum; j++){  //列循环
			if((G.AdjMatrix[i][j]>=1) && (G.AdjMatrix[i][j]<INF)){
				edges[k].vBegin=i;  //边的第一顶点
				edges[k].vEnd=j;    //边的第二顶点
				edges[k].eWeight=G.AdjMatrix[i][j];  //边的权值
				k++;
			}
		}
	}
}
EdgeType GetMinEdge(Graph &G, EdgeType edges[], int edgeUsed[], int &n){
    //n为返回的最小边在edges[]数组中的下标
	EdgeType minEdge;
	cellType wMin=INF;  //保存最小权值
	int i;
	int M;  //控制循环次数
	if(G.gKind==UDG || G.gKind==UDN)
		M=G.ArcNum*2;  //无向网，无向图，应为对称性，邻接居中有效数据是边数的2倍
	else
		M=G.ArcNum;    //有向图，有向网中，M即为图的边数
	for(i=0; i<M ;i++){
        //因为无向图邻接矩阵对称中，有效数据是边数的2倍，所以乘2
		if(edgeUsed[i]==0 && edges[i].eWeight<wMin){
			wMin=edges[i].eWeight;
			minEdge.eWeight=edges[i].eWeight;;
			minEdge.vBegin=edges[i].vBegin;
			minEdge.vEnd=edges[i].vEnd;
			n = i;//记录最小边序号
		}
	}
	return minEdge;  //返回取得的最小边
}
void Kruskal(Graph &G){
	int conVerID[MaxVerNum];  //顶点的连通分量编号数组
	EdgeType edges[MaxVerNum*MaxVerNum];  //存放图的所有边信息
	EdgeType treeEdges[MaxVerNum];        //存放生成树中的边信息，n-1条
	int edgeUsed[MaxVerNum*MaxVerNum];
	EdgeType minEdge;
	int i,j;
	int k=0;
	int conID;  //边的终止顶点的连通分量的编号
	int n;  //返回的最小边的序号
	GetEdges(G, edges);//获取所有边
	int M;  //循环次数
	if(G.gKind==UDG ||G.gKind==UDN)
		M=G.ArcNum*2;
	else
		M=G.ArcNum;
	for(i=0; i<M; i++)
		edgeUsed[i]=0;
	for(i=1; i<=G.VerNum; i++)
		conVerID[i]=i;
	for(i=1; i<G.VerNum; i++){  //取出n-1条边，构成生成树
		minEdge=GetMinEdge(G, edges, edgeUsed, n );
		while(conVerID[minEdge.vBegin] == conVerID[minEdge.vEnd]){
			edgeUsed[n]=1;  //标记不可用
			minEdge=GetMinEdge( G, edges, edgeUsed, n );
		}
		treeEdges[i]=minEdge;//将挑选出的最小边放到数组中
		conID=conVerID[minEdge.vEnd];
		for(j=1; j<=G.VerNum; j++){  //合并连通号
			if(conVerID[j]==conID)
				conVerID[j]=conVerID[minEdge.vBegin];
		}
		edgeUsed[n]=1; //标记已经使用过
	}
	cellType wAll=0;  //总权值
	cout << endl;  //输出结果
	cout << "选择的边和权值:" << endl;
	for(i=1;i<G.VerNum;i++){  //n-1条边
		cout << "("<<G.Data[treeEdges[i].vBegin]<<","<<G.Data[treeEdges[i].vEnd]<<")";
		wAll+=treeEdges[i].eWeight;
	}
	cout << "最小生成树总权值:"<<wAll << endl;
	cout << endl;
}

//7. Dijkstra算法求最短路径.
void PrintDijkstra(Graph &G, int path[], int dist[], int vID ){
    //数组sPath[]保存vID到目标顶点i的最短路径顶点
	int sPath[MaxVerNum];
	int vPre;    //前驱结点编号
	int top=-1;  //保存最短路径上的顶点个数，以控制输出最短路径
	int i, j;
	for(i=1; i<=G.VerNum; i++){
		cout << G.Data[vID] << "到" << G.Data[i] << "最短路径";
		if(dist[i]==INF)
			cout << "无可达路径." << endl;
		else{
			cout << "最短距离:" <<dist[i] << endl;
			cout << "路径:";
		}
		top++;
		sPath[top]=i;     //sPath[]保存目标顶点编号i
		vPre=path[i];
		while(vPre!=-1){
			top++;
			sPath[top]=vPre;
			vPre=path[vPre];
		}
		if(dist[i]!=INF){
            //sPath[top]为指定的起始顶点vID
			for(j=top; j>=0; j-- ){
				cout << G.Data[sPath[j]];
				if(j != 0)
					cout << "->";
			}
		}
		top=-1;
		cout << endl;
	}
}
void Dijkstra(Graph &G){
    int vID;
    cout << "请输入首个访问点序号:" ;
    cin >> vID;
    cin.get();
	int path[MaxVerNum];
	int dist[MaxVerNum];
    int solved[MaxVerNum];//代表是否解出最短路径
	int i, j, v;
	cellType minDist;//保存最短距离
	for(i=1;i<=G.VerNum;i++){
		solved[i]=0;//初始化标记都未找到
     	dist[i]=G.AdjMatrix[vID][i];//保存起始结点到各结点距离
		if(dist[i]!=INF)
			path[i]=vID;  //第i顶点的前驱为vID
		else
			path[i]=-1;   //当前顶点i无前驱
 	}
 	solved[vID]=1;//起始结点已解
	dist[vID]=0; //起始节点到自己距离为0
	path[vID]=-1;
	for(i=1; i<G.VerNum; i++){
		minDist=INF;
		for(j=1;j<=G.VerNum;j++){
			if(solved[j]==0 && dist[j]<minDist){
				v=j;//保留已解结点的下标
				minDist=dist[j];
			}
		}
		if(minDist == INF){//未找到
			cout<<"该图不是连通图！"<<endl;
			return;
		}
		solved[v]=1;
		for(j=1; j<=G.VerNum; j++){
		     if(solved[j]==0 && (minDist+G.AdjMatrix[v][j])<dist[j]){
                dist[j]=minDist+G.AdjMatrix[v][j];
		        path[j]=v;   //更新顶点j的直接前驱为顶点v
		    }
		}
	}
	PrintDijkstra(G, path, dist, vID);
}

//8. Floyd算法求最短路径.
void PrintFloyd(Graph &G, int dist[MaxVerNum][MaxVerNum], int path[MaxVerNum][MaxVerNum]){
	int sPath[MaxVerNum];
	int prior;
	int top=-1;
	for(int i=1; i<=G.VerNum; i++){
		for(int j=1; j<=G.VerNum; j++){
			cout << G.Data[i] << "到" << G.Data[j];
			if(dist[i][j]==INF)
				cout << "无路径." << endl;
			else{
				cout << "最短距离:" << dist[i][j] << endl;
				cout << "路径为:";
				top++;
				sPath[top]=j;      //sPath[0]为当前顶点i
				prior=path[i][j];  //i顶点的前驱顶点
				while(prior!=i){
					top++;
					sPath[top]=prior;
					prior=path[i][prior];
				}
				top++;
				sPath[top]=i;  //加进起始顶点i
				if(dist[i][j]!=INF){
					for(int m=top;m>=0;m--){
                        //sPath[top]为指定的起始顶点
						cout << G.Data[sPath[m]] << "  ";
						if(m != 0)
							cout<<"->";
					}
				}
				top=-1;
				cout << endl << endl;
			}
		}
	}
}
void Floyd(Graph &G){
	int i, j, m;
	int dist[MaxVerNum][MaxVerNum];
	int path[MaxVerNum][MaxVerNum];
	for(i=1; i<=G.VerNum; i++){  //初始化距离矩阵和路径矩阵
		for(j=1;j<=G.VerNum;j++){
            //距离矩阵初始化为邻接矩阵
			dist[i][j]=G.AdjMatrix[i][j];
        	if(i!=j && G.AdjMatrix[i][j]<INF)
				path[i][j]=i;
		    else
				path[i][j]=-1;
		}
	}
	for(m=1; m<=G.VerNum; m++){//跳点m
	      for(i=1; i<=G.VerNum; i++){
		  		for(j=1; j<=G.VerNum;j++){
                    //m作为跳点，i、j之间距离变小，接收m作为中转点
		    		if(i!=j && dist[i][m]+dist[m][j]<dist[i][j]){
                        //更新最短距离
						dist[i][j]=dist[i][m]+dist[m][j];
						path[i][j]=path[m][j];
		        	}
		    	}
		 }
	}
	PrintFloyd(G, dist, path);
}

//9. 拓扑序列.
void GetInDegrees(Graph &G, int inds[]){
	for(int j=1; j<=G.VerNum; j++){
		for(int i=1; i<=G.VerNum; i++){
			if(G.AdjMatrix[i][j]>=1 && G.AdjMatrix[i][j]<INF)
				inds[j]++;
		}
	}
}
bool TopologicalSort(Graph &G, int topoList[]){
	seqStack S;
	initialStacksS(S);
	int v, w;//结点变量
	int ind[MaxVerNum];
	for(int i=1; i<=G.VerNum; i++)
		ind[i]=0;  //入度数组初始化
	for(int i=1; i<G.VerNum; i++)
		topoList[i]=-1;
	GetInDegrees(G, ind);
	for(int i=1; i<=G.VerNum; i++){
		  if(ind[i]==0)
		  	pushStacksS(S, i);
	}
	int iCount=0;
	while(!stackEmptysS(S)){
		popStacksS(S, v);    //从栈顶弹出一个入度为0的顶点编号到v
		cout << G.Data[v];
		w = firstAdj(G,v);
		iCount++;
		topoList[iCount]=v;
     	while(w!=0){
        	ind[w]--;
            if(ind[w]==0)   //顶点w的入度已经为0，入栈
				pushStacksS(S,w);
            w=nextAdj(G,v,w);
      	}
	}
	if(iCount == G.VerNum){
        //n为图的顶点数
		cout << endl << "可以产生拓扑排序!" << endl;
		return true;
	}
	else{
		cout << endl << "不可以产生拓扑排序！" << endl;
		return false;
	}
}

//10.AOE网关键路径.
void PrintKeyPath(Graph &G ,int topoList[] , int vlt[],int vet[]){
	int w, v;                              //判定关键路径并输出
	cout << "关键路径为:";
	v=topoList[1];
	cout << G.Data[v];    //输出源点
	while(v!=0){
		w=firstAdj(G, v);          //搜索v的第一个邻接点
		if(w!=0)
			cout<<"->";
		while(w!=0){
			if(vet[w]==vlt[w]){
                //输出关键活动关联的顶点
				cout<<G.Data[w];
				break;
			}
			else
			  w=nextAdj(G,v,w);  //搜索下一个邻接点
		}
		v=w;
	}
}
void _KeyPath(Graph &G, int topoList []){
	int i,j;
	int vet[MaxVerNum];//最早发生时间
	int vlt[MaxVerNum];//最晚开始时间
	int vPre;  //保存顶点的前驱顶点编号
	int vSuc;  //保存顶点的后继顶点编号
	for(i=1; i<=G.VerNum; i++)
        vet[i]=0;
	for(i=1; i<=G.VerNum; i++){
		vPre=topoList[i];
		for(j=1; j<=G.VerNum; j++){
		    if(G.AdjMatrix[vPre][j]>=1 && G.AdjMatrix[vPre][j]<INF)
		         if(vet[j]<vet[vPre]+G.AdjMatrix[vPre][j])
				 	vet[j]=vet[vPre]+G.AdjMatrix[vPre][j];
		}
	}
	for(i=1;i<=G.VerNum;i++)
        vlt[i]=vet[G.VerNum];
	for(i=G.VerNum; i>=1; i--){
		vSuc=topoList[i];
		for(j=G.VerNum;j>=1;j--){
            //j与vSuc相邻
		    if(G.AdjMatrix[j][vSuc]>=1 && G.AdjMatrix[j][vSuc]<INF)
				if(vlt[j] > vlt[vSuc]-G.AdjMatrix[j][vSuc])
					vlt[j]=vlt[vSuc]-G.AdjMatrix[j][vSuc];
		}
	}
	PrintKeyPath(G, topoList, vlt, vet);
}
void KeyPath(Graph &G, int topoList[]){
    if(TopologicalSort(G, topoList)){
		cout << "邻接矩阵实现:" << endl;
        _KeyPath(G, topoList);
	}
    else
        cout << "不存在关键路径!" <<endl;
}
