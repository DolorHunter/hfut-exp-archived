#pragma once
#define MAXLEN 1024
#define LH 1
#define EH 0
#define RH -1

typedef int elementType;
typedef int keytype;


using namespace std;

    //二分查找表的结点结构
typedef struct searchList_2{
    elementType key;                         //二分查找表的结点标志
    keytype x;                               //二分查找表的结点数据(本实验暂时不使用此部分)
}sLNode;
    //二分查找表结构
typedef struct searchList_1{
    sLNode str[MAXLEN];                      //二分查找表的数组
    int iLen;                                //二分查找表的长度
}sList;

    //二叉排序树的结点结构
typedef struct biSortTreeNode{
    elementType key;                         //二叉排序树的结点数据
    struct biSortTreeNode *lChild, *rChild;  //二叉排序树的结点左右孩子
}bstNode, *bstTree;

/*
    //定义平衡因子数
typedef enum AVL_FacNum{
    LH=1;
    EH=0;
    RH=-1;
}bh_t;
*/
    //定义平衡二叉树(AVL)
typedef struct AdelsonVelskyLandisTreeNode{
    elementType key;
    int bf;                                 //平衡值
    struct AdelsonVelskyLandisTreeNode *lChild, *rChild;
}*AVLTree, AVLNode;


//初始化二分查找表
void initialSearchList(sList &L){
    L.iLen=0;                                   //重置表长为0
    L.str[MAXLEN]={0};                          //重置表为0
}

//初始化二叉排序树
void initialBinarySortTree(bstNode *T){
    T=NULL;                                     //重置树为空
}

//递归算法打印二叉排序树
void prtBinarySortTree(bstNode *T){
    if(T!=NULL){
        prtBinarySortTree(T->lChild);
        cout << T->key << "\t" ;
        prtBinarySortTree(T->rChild);
    }
}
//递归算法打印AVL树
void prtAVLTree(AVLTree T){
    if(T!=NULL){
        prtAVLTree(T->lChild);
        cout << T->key << "\t" ;
        prtAVLTree(T->rChild);
    }
}

//销毁二叉排序树
void destoryBinarySortTree(bstNode *T){
    if(T!=NULL){
        destoryBinarySortTree(T->lChild);
        destoryBinarySortTree(T->rChild);
        delete T;
    }
}

//销毁AVL树
void destoryAVLTree(AVLTree T){
    if(T!=NULL){
        destoryAVLTree(T->lChild);
        destoryAVLTree(T->rChild);
        delete T;
    }
}

//1. 二分查找并打印过程中比较的元素.
int bin_search(sList &L, elementType x){
    int mid, low=0, high=L.iLen-1;   //初始化查找区域
    while(low<=high){
        mid=(low+high)/2;
        if(x==L.str[mid].key){
            cout << "\n找到元素:" << L.str[mid].key << endl;
            return mid;             //返回查找值的位置
        }
        else if(x<L.str[mid].key){
            cout << "\t比较元素:" << L.str[mid].key << endl;
            high=mid-1;
        }
        else{
            cout << "\t比较元素:" << L.str[mid].key << endl;
            low=mid+1;
        }
    }
    cout << "\n没有找到该元素!" << endl;
    return -1;                      //返回查找失败标志
}
void binSearch(sList &L){
    cout << "\n正在导入自定义数据表.." << endl;
    //导入自定义数据表L.str[].key={5, 10, 15, ...., 500};
    for(int i=1; i<100; i++){
        L.str[i].key=i*5;
        cout << i*5 << "\t" ;
        L.iLen++;
    }
    cout << "\n自定义数据表导入成功!" << endl;
    cout << "请输入要查找的元素:" ;
    elementType x;
    cin >> x;
    cin.get();
    bin_search(L, x);
}

//2. 二叉排序树中循环插入结点构建二叉排序树.
void bst_insert(bstNode *&T, bstNode *S){//将指针S所指结点插入到二叉排序树T中
    if(T==NULL)
        T=S;//插入到空树时,插入结点成为根节点
    else if(S->key < T->key)
        bst_insert(T->lChild, S);//插入到T->lChild
    else
        bst_insert(T->rChild, S);//插入到T->lChild
}
void bstCreat(bstNode *T){
    elementType x;
    cout << "请输入插入元素(输入9999退出):" ;
    cin >> x;
    cin.get();
    while(x!=9999){
        bstNode *S=new bstNode;
        S->key=x;
        S->lChild=NULL;
        S->rChild=NULL;
        bst_insert(T, S);
        cin >> x;
    }
}

//3. 二叉排序树中查找指定值的结点.
int bst_search(bstNode *T, elementType x){
    bstNode *P=T;
    while(P!=NULL){
        if(x==P->key){
            cout << "找到元素:" << P->key << endl;
            return P->key;
        }
        else if(x<P->key){
            P=P->lChild;
        }
        else{
            P=P->rChild;
        }
    }
    cout << "没有找到该元素!" << endl;
    return -1;
}
void bstSearch(bstNode *T){
    elementType x;
    cout << "请输入待查找元素:" ;
    cin >> x;
    bst_search(T, x);
}

//4. 二叉排序树中删除特定值的结点.
void bst_deleteNode(bstNode *T, elementType x){
	bstNode *p=T;       //遍历结点指针
	bstNode *q;         //双亲结点指针
	elementType temp;
	while(p!=NULL && p->key!=x){
		q=p;
		if(x<p->key)
			p=p->lChild ;
		else
			p=p->rChild ;
	}
	if(p==NULL)
		cout << "元素" << x << "不存在!" << endl;
	else {
		//情况1:结点p的双亲结点为q, 且p为叶子结点, 则直接将其删除
		if(p->lChild==NULL && p->rChild==NULL){
			if(p==q->lChild)//p是q左孩子
				q->lChild=NULL;
			if(p==q->rChild)//p是q右孩子
				q->rChild=NULL;
			delete p;
		}
		//情况2:结点p的双亲结点为q, 且p只有左子树或只有右子树,
		//则可将p的左子树或右子树直接改为其双亲结点q的左子树或右子树.
		else if(p->rChild==NULL && p->lChild!=NULL){//p只有左子树
			if(p==q->lChild)//p是q左孩子
				q->lChild=p->lChild;
			else if(p==q->rChild)//p是q右孩子
				q->rChild=p->lChild;
			delete p;
		}
		else if(p->lChild==NULL && p->rChild!=NULL){//p只有右子树
			if( p==q->lChild )//p是q左孩子
				q->lChild=p->rChild;
			if( p==q->rChild )//p是q右孩子
				q->rChild=p->rChild;
			delete p;
		}
		//情况3:结点p的双亲结点为q, 且p既有左子树又有右子树.
		//本代码使用直接前驱（也可以直接后继）
		else if(p->lChild!=NULL && p->rChild!=NULL ){
				bstNode *s, *sParent;
				sParent=p;
				s=sParent->lChild ;
				while(s->rChild!=NULL){//找到p的直接前驱
					sParent=s;
					s=s->rChild ;
				}
				temp=s->key ;
				bst_deleteNode(T, temp);
				p->key=temp;
		}
	}
}
void bstDeleteNode(bstNode *T){
    elementType x;
    cout << "请输入待删除元素:" ;
    cin >> x;
    bst_deleteNode(T, x);
}

//5. 构造一棵平衡的二叉排序树存放数组.
//单向右旋转
void R_Rotate(AVLTree *T){
	AVLTree p;
	p=(*T)->lChild;
	(*T)->lChild=p->rChild;
	p->rChild=(*T);
	(*T)=p;
}
//单向左旋转
void L_Rotate(AVLTree *T){
	AVLTree p;
	p=(*T)->rChild;
	(*T)->rChild=p->lChild;
	p->lChild=(*T);
	(*T)=p;
}
//先左旋后右旋平衡旋转
void LeftBalance(AVLTree *T)
{
	AVLTree lc=(*T)->lChild;
	AVLTree rd=lc->rChild;
	//判断进行向哪边旋转
	switch (lc->bf){
		case LH:
			(*T)->bf=lc->bf=EH;
			R_Rotate(T);
			break;
		case RH:
			switch (rd->bf){
			case LH:
				(*T)->bf = RH;
				lc->bf=EH;
				break;
			case EH:
				(*T)->bf=lc->bf=EH;
				break;
			case RH:
				(*T)->bf=EH;
				lc->bf=LH;
				break;
			}
		rd->bf=EH;
		L_Rotate(&((*T)->lChild));
		R_Rotate(T);
		break;
	}
}
//先右旋后左旋平衡旋转
void RightBalance(AVLTree *T){
	AVLTree rc=(*T)->rChild;
	AVLTree ld=rc->lChild;
	switch (rc->bf){
		case RH:
			(*T)->bf=rc->bf=EH;
			L_Rotate(T);
			break;
		case LH:
			switch (ld->bf){
				case RH:
					(*T)->bf=LH;
					rc->bf=EH;
					break;
				case EH:
					(*T)->bf=rc->bf=EH;
					break;
				case LH:
					(*T)->bf=EH;
					rc->bf=RH;
					break;
			}
		ld->bf=EH;
		R_Rotate(&((*T)->rChild));
		L_Rotate(T);
		break;
	}
}
//平衡二叉树AVL插入元素
bool InsertAVL(AVLTree *T, elementType x, bool *taller){
	if (*T==NULL){
		(*T)=new AVLNode;
		(*T)->key=x;
		(*T)->lChild=(*T)->rChild=NULL;
		(*T)->bf=EH;
		*taller=true;
		return true;
	}
	else{
		if(x==(*T)->key){
			*taller=false;
			return false;
		}
		else if(x<(*T)->key){
			if(!InsertAVL(&((*T)->lChild), x, taller)){
				//先判断要插入的这个结点是否在树中
				return false;
			}
			if(*taller){
				switch ((*T)->bf){
					case LH:
						LeftBalance(T);
						*taller=false;
						break;
					case EH:
						(*T)->bf=LH;
						*taller=true;
						break;
					case RH:
						(*T)->bf=EH;
						*taller=false;
						break;
				}
			}
		}
		else{
			if(!InsertAVL(&((*T)->rChild), x, taller)){
				return false;
			}
			if(*taller){
				switch ((*T)->bf){
					case RH:
						RightBalance(T);
						*taller=false;
						break;
					case EH:
						(*T)->bf=RH;
						*taller=true;
						break;
					case LH:
						*taller=false;
						(*T)->bf=EH;
						break;
				}
			}
		}
	}
}
void creatAVLFromArray(AVLTree *T){
	bool taller;
    elementType str[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26};
    cout << "开始导入数据!" << endl;
	for (int i=0; i < 26; i++) {
		InsertAVL(T, str[i], &taller);
	}
    cout << "AVL树建立成功!" << endl;
}
