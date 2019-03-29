#pragma once
#include<iostream>
#include<cstdio>

using namespace std;

//读入数据文件输入数组
//////////////////////////////////////////////////////////////////////////////////////
//函数:ReadFileToArray(char fileName[], char strLine[100][3], int &nArrLen)         //
//参数说明:                                                                         //
//fileName[]存放文件名                                                              //
//strLine[][3]存放结点的二维数组, 数组的3列对应数组文件的三列                       //
//nArrLen返回二叉树结点的个数                                                       //
//////////////////////////////////////////////////////////////////////////////////////
bool ReadFileToArray(char *fileName, char strLine[100][3], int &nArrLen){
    FILE *fp;
    char str[1000];
    fp=fopen(fileName, "r");
    if(fp==NULL){
        cout << "二叉树数据文件打开失败!" << endl;
        return false;
    }
    //读入第一行判断二叉树标识BinaryTree是否正确
    if(fgets(str, 1000, fp)!=NULL){
        if(strcmp(str, "BinaryTree\n")!=0){
            cout << "打开的文件格式错误!" << endl;
            return false;
            fclose(fp);
        }
    }
    //空文件保护
    else{
        cout << "打开的文件为空!" << endl;
        return false;
        fclose(fp);
    }
    nArrLen=0;
    while(fscanf(fp, "%c %c %c\n", &strLine[nArrLen][0], &strLine[nArrLen][1], &strLine[nArrLen][2]) != EOF){
        nArrLen++;
    }
    fclose(fp);
    return true;
}

//从数组按先序次序创建二叉树
//////////////////////////////////////////////////////////////////////////////////////
//函数:CreatBiTreeFromArray(BiNode *&pBT, char strLine[100][3], int nLen, int &nRow)//
//参数说明:                                                                         //
//strLine[100][3]为保存结点数据的二维数组                                           //
//nArrLen为结点个数                                                                    //
//nRow为数组当前行号                                                                //
//////////////////////////////////////////////////////////////////////////////////////
bool CreatBiTreeFromArray(BiNode *&pBT, char strLine[100][3], int nArrLen, int &nRow){
    if(nRow>=nArrLen || nArrLen==0){
        return false;                           //数组已经处理完毕或没有数据,退出
    }
    //根据数组数据递归创建二叉树
    pBT=new BiNode;                             //建立根节点
    pBT->data=strLine[nRow][0];
    pBT->lChild=NULL;
    pBT->rChild=NULL;
    int nRowNext=nRow;  //保留本次递归的行号
    if(strLine[nRowNext][1]=='1'){
        //当前结点有左子树,读下一行数据,递归调用创建左子树
        nRow++;
        CreatBiTreeFromArray(pBT->lChild, strLine, nArrLen, nRow);
    }
    if(strLine[nRowNext][2]=='1'){
        //当前节点有右子树,读下一行数据,递归调用创建右子树
        nRow++;
        CreatBiTreeFromArray(pBT->rChild, strLine, nArrLen, nRow);
    }
    return true;
}

//封装ReadFileToArray() &CreatBiTreeFromArray()函数
void CreatBiTree(BiNode *&T, char (&fileName)[20], char (&strLine)[100][3], int &nArrLen, int &nRow){
    bool import=false;
    nRow=0;
    if(ReadFileToArray(fileName, strLine, nArrLen)){
        if(CreatBiTreeFromArray(T, strLine, nArrLen, nRow)){
            cout << "二叉树导入成功!" << endl;
            import=true;
        }
    }
    if(!import){
        cout << "二叉树导入失败!执行exit(1)." << endl;
        exit(1);
    }
}

//显示可以打开的.btr文件
void openFile(char fileName[20]){
    system("CLS");
    cout << "┌────────────────────────────────────────────────────────┐" << endl;
    cout << "│以下是可导入的树文件:                                   │" << endl;
    cout << "├────────────────────────────┬───────────────────────────┤" << endl;
	cout << "│1. bt4.btr                  │7. bt15.btr                │" << endl;
	cout << "│2. bt8.btr                  │8. bt21.btr                │" << endl;
	cout << "│3. bt9.btr                  │9. bt261.btr               │" << endl;
	cout << "│4. bt10.btr                 │10.bt262.btr               │" << endl;
	cout << "│5. bt12.btr                 │11.fu1l4.btr               │" << endl;
	cout << "│6. bt14.btr                 │12.fu1l5.btr               │" << endl;
	cout << "└────────────────────────────┴───────────────────────────┘" << endl;
    cout << "请选择你要导入的树的序号:" ;
    int choseFile;
    cin >> choseFile;
    cin.get();
    switch(choseFile){
        case 1:
            sprintf(fileName, "%s", "D:\\download\\BTdata\\bt4.btr");
            break;
        case 2:
            sprintf(fileName, "%s", "D:\\download\\BTdata\\bt8.btr");
            break;
        case 3:
            sprintf(fileName, "%s", "D:\\download\\BTdata\\bt9.btr");
            break;
        case 4:
            sprintf(fileName, "%s", "D:\\download\\BTdata\\bt10.btr");
            break;
        case 5:
            sprintf(fileName, "%s", "D:\\download\\BTdata\\bt12.btr");
            break;
        case 6:
            sprintf(fileName, "%s", "D:\\download\\BTdata\\bt14.btr");
            break;
        case 7:
            sprintf(fileName, "%s", "D:\\download\\BTdata\\bt15.btr");
            break;
        case 8:
            sprintf(fileName, "%s", "D:\\download\\BTdata\\bt21.btr");
            break;
        case 9:
            sprintf(fileName, "%s", "D:\\download\\BTdata\\bt261.btr");
            break;
        case 10:
            sprintf(fileName, "%s", "D:\\download\\BTdata\\bt262.btr");
            break;
        case 11:
            sprintf(fileName, "%s", "D:\\download\\BTdata\\full4.btr");
            break;
        case 12:
            sprintf(fileName, "%s", "D:\\download\\BTdata\\full5.btr");
            break;
        default:
            break;
    }
}
