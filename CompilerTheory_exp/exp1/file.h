#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED

#pragma once
#include<iostream>
#include<cstdio>
#include<string.h>
        ///300行会清屏
#define MAXWORDS 20
#define MAXLEN 10

using namespace std;

//读入数据文件输入关键字
bool readFileToArray(char *fileName, char keyWords[MAXWORDS][MAXLEN]){
    FILE *fp;
    char str[65535];
    fp=fopen(fileName, "r");
    if(fp==NULL){
        cout << "数据文件打开失败!" << endl;
        return false;
    }
    //Read the identification and judge
    if(fgets(str, 1000, fp)!=NULL){
        if(fileName=="keywords.txt"){
            if(strcmp(str, "Keywords\n")!=0){
            cout << "打开的文件格式错误!" << endl;
            return false;
            fclose(fp);
            }
        }
        if(fileName=="delimiters.txt"){
            if(strcmp(str, "Delimiters\n")!=0){
            cout << "打开的文件格式错误!" << endl;
            return false;
            fclose(fp);
            }
        }
    }
    //Empty file protection
    else{
        cout << "打开的文件" << fileName << "为空!" << endl;
        return false;
        fclose(fp);
    }
    int Line=0;
    while(fscanf(fp, "%s\n", &keyWords[Line]) != EOF){
        Line++;
    }
    fclose(fp);
    return true;
}

#endif // FILE_H_INCLUDED
