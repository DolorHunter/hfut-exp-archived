#pragma once
#include<iostream>
#include<cstdio>
#include<string.h>
#include"forest.h"

using namespace std;

//删除字符串、字符数组左边空格
void strLTrim(char* str)
{
	int i,j;
	int n=0;
	n=strlen(str)+1;
	for(i=0;i<n;i++)
	{
		if(str[i]!=' ')  //找到左起第一个非空格位置
			break;
	}
	    //以第一个非空格字符为手字符移动字符串
	for(j=0;j<n;j++)
	{
		str[j]=str[i];
		i++;
	}
}
//****************** 文件创建双亲表示的树（森林）********************//
//* 函数功能：从文本文件创建双亲表示的图                            *//
//* 入口参数  char fileName[]，数据文件名                           *//
//* 出口参数：pTree &T，即创建的树                                  *//
//* 返 回 值：bool，true创建成功；false创建失败                     *//
//* 函 数 名：CreateTreeFromFile(char fileName[], pTree &T)         *//
//* 备注：本函数使用的数据文件格式以边（父子对）为基本数据          *//
//*******************************************************************//
bool createTreeFromFile(char fileName[], pTree &T)
{
	FILE* pFile;     //定义顺序表的文件指针
	char str[1000];  //存放读出一行文本的字符串
	char strTemp[10]; //判断是否注释行

    int i=0,j=0;


	pFile=fopen(fileName,"r");
	if(!pFile)
	{
		printf("错误：文件%s打开失败。\n",fileName);
		return false;
	}

	while(fgets(str,1000,pFile)!=NULL)  //跳过空行和注释行
	{
		//删除字符串左边空格
		strLTrim(str);
		if (str[0]=='\n')  //空行，继续读取下一行
			continue;

		strncpy(strTemp,str,2);
		if(strstr(strTemp,"//")!=NULL)  //跳过注释行
			continue;
		else  //非注释行、非空行，跳出循环
			break;
	}

    //循环结束，str中应该已经是文件标识，判断文件格式
	if(strstr(str,"Tree or Forest")==NULL)
	{
		printf("错误：打开的文件格式错误！\n");
		fclose(pFile); //关闭文件
		return false;
	}


	//读取结点数据，到str。跳过空行
	while(fgets(str,1000,pFile)!=NULL)
	{
		//删除字符串左边空格
		strLTrim(str);
		if (str[0]=='\n')  //空行，继续读取下一行
			continue;

		strncpy(strTemp,str,2);
		if(strstr(strTemp,"//")!=NULL)  //注释行，跳过，继续读取下一行
			continue;
		else  //非空行，也非注释行，即图的顶点元素行
			break;
	}

	//结点数据存入树的结点数组
	char* token=strtok(str," ");
	int nNum=0;
	while(token!=NULL)
	{
		T.node[nNum].data=*token;
		T.node[nNum].parent=-1;       //父结点指针初始化为-1

		token = strtok( NULL, " ");

		nNum++;
	}

    //循环读取边（父子队）数据
	int nP;  //父结点数组下标
	int nC;  //子结点数组下标

	elementType Nf,Ns; //父子结点对的两个结点
	while(fgets(str,1000,pFile)!=NULL)
	{
		//删除字符串左边空格
		strLTrim(str);
		if (str[0]=='\n')  //空行，继续读取下一行
			continue;

		strncpy(strTemp,str,2);
		if(strstr(strTemp,"//")!=NULL)  //注释行，跳过，继续读取下一行
			continue;

		char* token=strtok(str," ");  //以空格为分隔符，分割一行数据，写入邻接矩阵

		if(token==NULL)  //分割为空串，失败退出
		{
			printf("错误：读取树的边数据失败！\n");
			fclose(pFile); //关闭文件
			return false;
		}
		Nf=*token;  //获取父结点

		token = strtok( NULL, " ");  //读取下一个子串，即子结点
		if(token==NULL)  //分割为空串，失败退出
		{
			printf("错误：读取树的边数据失败！\n");
			fclose(pFile); //关闭文件
			return false;
		}

		Ns=*token;  //获取边的第二个结点（子结点）
            //取得父结点下标
		for(nP=0;nP<nNum;nP++)
		{
			if(T.node[nP].data==Nf)  //从顶点列表找到第一个顶点的编号
				break;
		}
           //获取子结点的数组下标
		for(nC=0;nC<nNum;nC++)
		{
			if(T.node[nC].data==Ns)  //从顶点列表找到第二个顶点的编号
				break;
		}

		T.node[nC].parent=nP;        //nC的父结点的下标为nP
	}

    T.n=nNum;  //树的结点数，即顶点数组的实际大小

	fclose(pFile); //关闭文件
	return true;
}

//显示可以打开的.tre文件
void openFile(char fileName[20]){
    system("CLS");
    cout << "┌────────────────────────────────────────────────────────┐" << endl;
    cout << "│ 以下是可导入的树文件:                                  │" << endl;
    cout << "├────────────────────────────┬───────────────────────────┤" << endl;
	cout << "│1. F14.tre                  │4. F20.tre                 │" << endl;
	cout << "│2. F16.tre                  │5. tree10.tre              │" << endl;
	cout << "│3. F18.tre                  │6. tree11.tre              │" << endl;
	cout << "└────────────────────────────┴───────────────────────────┘" << endl;
    cout << "请选择你要导入的树的序号:" ;
    int choseFile;
    cin >> choseFile;
    cin.get();
    switch(choseFile){
        case 1:
            sprintf(fileName, "%s", "D:\\download\\tData\\F14.tre");
            break;
        case 2:
            sprintf(fileName, "%s", "D:\\download\\tData\\F16.tre");
            break;
        case 3:
            sprintf(fileName, "%s", "D:\\download\\tData\\F18.tre");
            break;
        case 4:
            sprintf(fileName, "%s", "D:\\download\\tData\\F20.tre");
            break;
        case 5:
            sprintf(fileName, "%s", "D:\\download\\tData\\tree10.tre");
            break;
        case 6:
            sprintf(fileName, "%s", "D:\\download\\tData\\tree11.tre");
            break;

        default:
            break;
    }
}
