#pragma once

using namespace std;

//显示可以打开的.grp文件
void openFile(char fileName[20]){
    system("CLS");
	cout << "[注意]: 无向图UDG, 无向网UDN, 有向图DG, 有向网DN" << endl;
    cout << "┌────────────────────────────────────────────────────────┐" << endl;
    cout << "│以下是可导入的图文件:                                   │" << endl;
    cout << "├────────────────────────────┬───────────────────────────┤" << endl;
	cout << "│1. udg8.grp                 │6. udn6.grp                │" << endl;
	cout << "│2. udg115.grp               │7. dn8.grp                 │" << endl;
	cout << "│3. dg6.grp                  │8. dn10.grp                │" << endl;
	cout << "│4. f14.grp                  │9. Top6dg1.grp             │" << endl;
	cout << "│5. un8.grp                  │10.Top7dg1.grp             │" << endl;
	cout << "└────────────────────────────┴───────────────────────────┘" << endl;
    cout << "请选择你要导入的图的序号:" ;
    int choseFile;
    cin >> choseFile;
    cin.get();

    switch(choseFile){
        case 1:
            sprintf(fileName, "%s", "D:\\download\\grpData\\udg8.grp");
            break;
        case 2:
            sprintf(fileName, "%s", "D:\\download\\grpData\\udg115.grp");
            break;
        case 3:
            sprintf(fileName, "%s", "D:\\download\\grpData\\dg6.grp");
            break;
        case 4:
            sprintf(fileName, "%s", "D:\\download\\grpData\\f14.grp");
            break;
        case 5:
            sprintf(fileName, "%s", "D:\\download\\grpData\\un8.grp");
            break;
        case 6:
            sprintf(fileName, "%s", "D:\\download\\grpData\\udn6.grp");
            break;
        case 7:
            sprintf(fileName, "%s", "D:\\download\\grpData\\dn8.grp");
            break;
        case 8:
            sprintf(fileName, "%s", "D:\\download\\grpData\\dn10.grp");
            break;
        case 9:
            sprintf(fileName, "%s", "D:\\download\\grpData\\Top6dg1.grp");
            break;
        case 10:
            sprintf(fileName, "%s", "D:\\download\\grpData\\Top7dg1.grp");
            break;

        default:
            break;
    }
}
