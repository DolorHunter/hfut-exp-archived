#include<iostream>
#include<vector>
#include<cstring>
#include"file.h"

#define MAX 20
#define MAXLEN 10
#define MAXCODELEN 50

using namespace std;

char k[MAX][MAXLEN];  // Keywords
char s[MAX][MAXLEN];  // Delimiters (Arithmetic & Relational Operator)
char id[MAX][MAXLEN]; // Identifiers
char ci[MAX][MAXLEN]; // Constants
char instring[MAX][MAXLEN]; // Buffer for input words
char code[MAXCODELEN]; // Input code for testing

struct wordInfo{    // Structure of outtoken
    string word;      // Capture word
    string attribute; // Attribute of the word
    string type;      // Type of the word
    string position;  // Position of the word
};

vector<wordInfo> outtoken; // Buffer for output
wordInfo outputInfo; // Structure of outputInfo

void inputKeywordsToBuffer(){
    memset(instring, 0, sizeof(instring)); // Set 0
    readFileToArray("data/keywords.txt", instring);
    cout << "Input keywords to buffer successfully!!" << endl;
}

void creatKeywords(){
    inputKeywordsToBuffer();
    memset(k, 0, sizeof(k)); // Set 0
    for(int i=0; i<MAX; ++i){
        for(int j=0; j<MAXLEN; ++j){
            k[i][j] = instring[i][j]; // Transfer keywords to k[][]
        }
    }
    cout << "Keywords created successfully!!" << endl;
}

/// [test]
void printArrayKeywords(){
    for(int i=0; i<MAX; ++i){
        cout << k[i] << endl;
    }
    cout << "Keywords printed successfully!!" << endl;
}

void inputDelimitersToBuffer(){
    memset(instring, 0, sizeof(instring)); // Set 0
    readFileToArray("data/delimiters.txt", instring);
    cout << "Input delimiters to buffer successfully!!" << endl;
}

void creatDelimiters(){
    inputDelimitersToBuffer();
    memset(s, 0, sizeof(s)); // Set 0
    for(int i=0; i<MAX; ++i){
        for(int j=0; j<MAXLEN; ++j){
            s[i][j] = instring[i][j]; // Transfer keywords to k[][]
        }
    }
    cout << "Delimiters created successfully!!" << endl;
}

/// [test]
void printArrayDelimiters(){
    for(int i=0; i<MAX; ++i){
        cout << s[i] << endl;
    }
    cout << "Delimiters printed successfully!!" << endl;
}

void inputCode(){
    strcpy(code, "for i=0 then n++;\na<=3b%);"); ///for i=0 then n++;\na<=3b%);
    ///testInfo_1 _a for int ++ - ; / % ascii \n <= =>= aaa%\nthen
    cout << "Input the code successfully!!" << endl;
}

/// [test]
void printInputCode(){
    cout << code << endl;
    cout << "Tested code printed successfully!!" << endl;
}

void analysisCode(){
    bool error = true; // Keywords, Delimiters (true)or Error (false)
    int line=1, row=1; // Count line & row info
    // Current position of the input code
    for(int i=0; code[i]!='\0'; ++i){
        if(code[i] == '\n'){
            ++line; // Count the line info
            row = 1; // Reset row info IF "enter"
            continue; // Skip the Enter
        }
        if(code[i] == ' '){
            continue; // Skip to Space
        }
        else{ // Not a Space
            // Keywords, Delimiters or Error
            error = true; // Reset error sign
            // j: Current number of the keyword
            for(int j=0; j<MAX; ++j){ // Current keywords or not
                if(code[i] != k[j][0]){ // Not this keyword
                    continue; // To the next keyword
                }
                else{ // Potential keywords
                    int t=0; // t: delta for comparing the keyword
                    while(k[j][t] != '\n'){
                        if(code[i+t] == k[j][t]){
                            ++t;
                        }
                        else{ // Not this keyword
                            break; // Find the next keyword
                        }
                    }
                    if(k[j][t] != '\0'){ // Not a keyword
                    ///             ^ '\n' will cause unknown error making it continue all the time.
                        continue; // Find the next keyword
                    }
                    else{ // Find the keyword
                        char curKeywordCh[MAXLEN];
                        memset(curKeywordCh, 0, sizeof(curKeywordCh)); // Set 0
                        strncpy(curKeywordCh, code+i, t); // Save keyword to curKeywordCh
                        string curKeywordStr = (string)curKeywordCh; // Transfer to string
                        outputInfo.word = curKeywordStr; // Word information
                        outputInfo.attribute = "(1, " + curKeywordStr + ")"; // Attribute information
                        outputInfo.type = "关键字"; // Type information
                        outputInfo.position = "\t(" + to_string(line) + ", " + to_string(row) + ")"; // Position information
                        outtoken.push_back(outputInfo); // Save keyword information to vector
                        i+=t; // Skip the rest of the keyword(directly goto the next word)
                        ++row; // Next row
                        error=false; // No error
                        break;
                    }
                }
            }
            for(int j=0; j<MAX; ++j){ // Is delimiters or not
                if(j<6){ // Delimiter t=2
                    if(code[i] != s[j][0]){ // Not a delimiter
                        ; // IF it is other sign(t=3~6)
                    }
                    else{ // Is delimiter
                        char curKeywordCh[MAXLEN];
                        memset(curKeywordCh, 0, sizeof(curKeywordCh)); // Set 0
                        strncpy(curKeywordCh, code+i, 1); // Save keyword to curKeywordCh
                        string curKeywordStr = (string)curKeywordCh; // Transfer to string
                        outputInfo.word = curKeywordStr; // Word information
                        outputInfo.attribute = "(2, " + curKeywordStr + ")"; // Attribute information
                        outputInfo.type = "\t分界符"; // Type information
                        outputInfo.position = "\t(" + to_string(line) + ", " + to_string(row) + ")"; // Position information
                        outtoken.push_back(outputInfo); // Save keyword information to vector
                        ++row; // Next row
                        error=false; // No error
                        break;
                    }
                }
                else if(j<10){ // Arithmetic t=3
                    if(code[i] != s[j][0]){ // Not a arithmetic
                        ; // IF it is other sign(t=4~6)
                    }
                    else{ // Is arithmetic
                        if(code[i+1] == '+' || code[i+1] == '-' || code[i+1] == '*' || code[i+1] == '/'){ // Has arithmetic after arithmetic
                            char curKeywordCh[MAXLEN];
                            memset(curKeywordCh, 0, sizeof(curKeywordCh)); // Set 0
                            strncpy(curKeywordCh, code+i, 2); // Save keyword to curKeywordCh
                            string curKeywordStr = (string)curKeywordCh; // Transfer to string
                            outputInfo.word = curKeywordStr; // Word information
                            outputInfo.attribute = "ERROR"; // Attribute information
                            outputInfo.type = "\tERROR"; // Type information
                            outputInfo.position = "\t(" + to_string(line) + ", " + to_string(row) + ")"; // Position information
                            outtoken.push_back(outputInfo); // Error Information
                            i+=(2-1); // Skip the rest of arithmetic
                            ++row; // Next row
                            error=false; // No error
                            break;
                        }
                        else{
                            char curKeywordCh[MAXLEN];
                            memset(curKeywordCh, 0, sizeof(curKeywordCh)); // Set 0
                            strncpy(curKeywordCh, code+i, 1); // Save keyword to curKeywordCh
                            string curKeywordStr = (string)curKeywordCh; // Transfer to string
                            outputInfo.word = curKeywordStr; // Word information
                            outputInfo.attribute = "(3, " + curKeywordStr + ")"; // Attribute information
                            outputInfo.type = "\t算数运算符"; // Type information
                            outputInfo.position = "(" + to_string(line) + ", " + to_string(row) + ")"; // Position information
                            outtoken.push_back(outputInfo); // Save keyword information to vector
                            ++row; // Next row
                            error=false; // No error
                            break;
                        }
                    }
                }
                else if(j<16){ // Relational operator t=4
                    if(code[i] != s[j][0]){ // Not a relational operator
                        ; // IF it is other sign(t=5~6)
                    }
                    else{ // Is relational operator
                        if(code[i+1] == s[j][1]){ // Is binocular operator
                            char curKeywordCh[MAXLEN];
                            memset(curKeywordCh, 0, sizeof(curKeywordCh)); // Set 0
                            strncpy(curKeywordCh, code+i, 2); // Save keyword to curKeywordCh
                            string curKeywordStr = (string)curKeywordCh; // Transfer to string
                            outputInfo.word = curKeywordStr; // Word information
                            outputInfo.attribute = "(4, " + curKeywordStr + ")"; // Attribute information
                            outputInfo.type = "\t关系运算符"; // Type information
                            outputInfo.position = "(" + to_string(line) + ", " + to_string(row) + ")"; // Position information
                            outtoken.push_back(outputInfo); // Save keyword information to vector
                            ++row; // Next row
                            i+=1; // Skip the rest
                            error=false; // No error
                            break;
                        }
                        else{ // Is unary operator
                            char curKeywordCh[MAXLEN];
                            memset(curKeywordCh, 0, sizeof(curKeywordCh)); // Set 0
                            strncpy(curKeywordCh, code+i, 1); // Save keyword to curKeywordCh
                            string curKeywordStr = (string)curKeywordCh; // Transfer to string
                            outputInfo.word = curKeywordStr; // Word information
                            outputInfo.attribute = "(4, " + curKeywordStr + ")"; // Attribute information
                            outputInfo.type = "\t关系运算符"; // Type information
                            outputInfo.position = "(" + to_string(line) + ", " + to_string(row) + ")"; // Position information
                            outtoken.push_back(outputInfo); // Save keyword information to vector
                            ++row; // Next row
                            error=false; // No error
                            break;
                        }
                    }
                }
                else if(code[i] >= '0' && code[i] <= '9'){ // Unsigned number t=5
                    bool letterAfterNumber = false; // No letter after number
                    if(code[i+1] >= 'A' && code[i+1] <= 'Z' || code[i+1] >= 'a' && code[i+1] <= 'z'){
                        letterAfterNumber = true; // Has letter after number
                    }
                    if(letterAfterNumber){ // Has letter after
                        char curKeywordCh[MAXLEN];
                        memset(curKeywordCh, 0, sizeof(curKeywordCh)); // Set 0
                        strncpy(curKeywordCh, code+i, 2); // Save keyword to curKeywordCh
                        string curKeywordStr = (string)curKeywordCh; // Transfer to string
                        outputInfo.word = curKeywordStr; // Word information
                        outputInfo.attribute = "ERROR"; // Attribute information
                        outputInfo.type = "\tERROR"; // Type information
                        outputInfo.position = "\t(" + to_string(line) + ", " + to_string(row) + ")"; // Position information
                        outtoken.push_back(outputInfo); // Error Information
                        ++row; // Next row
                        i+=1; // Skip the rest of arithmetic
                        error=false; // No error
                        break;
                    }
                    else{ // No letter after
                        int t=1;
                        while(code[i+t] >= '0' && code[i+t] <= '9'){ // Number after
                            ++t; // To the next number
                        }
                        char curKeywordCh[MAXLEN];
                        memset(curKeywordCh, 0, sizeof(curKeywordCh)); // Set 0
                        strncpy(curKeywordCh, code+i, t); // Save keyword to curKeywordCh
                        string curKeywordStr = (string)curKeywordCh; // Transfer to string
                        outputInfo.word = curKeywordStr; // Word information
                        outputInfo.attribute = "(5, " + curKeywordStr + ")"; // Attribute information
                        outputInfo.type = "\t无符号数"; // Type information
                        outputInfo.position = "(" + to_string(line) + ", " + to_string(row) + ")"; // Position information
                        outtoken.push_back(outputInfo); // Save keyword information to vector
                        ++row; // Next row
                        i+=(t-1); // Skip the number string
                        error=false; // No error
                        break;
                    }
                }
                bool isIdentifier = false; // Identifier t=6
                if(code[i] == '_' || code[i] >= 'A' && code[i] <= 'Z' || code[i] >= 'a' && code[i] <= 'z'){
                    isIdentifier = true; // Has letter identifier or '_'
                }
                if(isIdentifier){ // Identifier t=6
                    int t=1;
                    while(code[i+1] == '_' || code[i+t] >='A' && code[i+t] <='Z' || code[i+t] >='a' && code[i+t] <='z'
                          || code[i+t] >= '0' && code[i+t] <= '9'){
                        ++t; // To the next letter
                    }
                    char curKeywordCh[MAXLEN];
                    memset(curKeywordCh, 0, sizeof(curKeywordCh)); // Set 0
                    strncpy(curKeywordCh, code+i, t); // Save keyword to curKeywordCh
                    string curKeywordStr = (string)curKeywordCh; // Transfer to string
                    outputInfo.word = curKeywordStr; // Word information
                    outputInfo.attribute = "(6, " + curKeywordStr + ")"; // Attribute information
                    outputInfo.type = "\t标识符"; // Type information
                    outputInfo.position = "\t(" + to_string(line) + ", " + to_string(row) + ")"; // Position information
                    outtoken.push_back(outputInfo); // Save keyword information to vector
                    row++; // Next row
                    i+=(t-1); // Skip the identifier string
                    error=false; // No error
                    break;
                }
            }
            if(error){ // Not situations above
                char curKeywordCh[MAXLEN];
                memset(curKeywordCh, 0, sizeof(curKeywordCh)); // Set 0
                strncpy(curKeywordCh, code+i, 1); // Save keyword to curKeywordCh
                string curKeywordStr = (string)curKeywordCh; // Transfer to string
                outputInfo.word = curKeywordStr; // Word information
                outputInfo.attribute = "ERROR"; // Attribute information
                outputInfo.type = "\tERROR"; // Type information
                outputInfo.position = "\t(" + to_string(line) + ", " + to_string(row) + ")"; // Position information
                outtoken.push_back(outputInfo); // Error Information
                ++row; // Next row
            }
        }
    }
    cout << "Analysis the code successfully!!" << endl;
}

void printOutputInfo(){
    cout << "单词\t二元序列\t类型\t\t位置(行, 列)" << endl;
    vector<wordInfo>::iterator it; // Create iterator
    for(it=outtoken.begin(); it!=outtoken.end(); ++it){
        cout << it->word << "\t" << it->attribute << "\t" << it->type << "\t" << it->position << endl;
    }
    cout << "Print output information successfully!!" << endl;
}

int main(){
    creatKeywords(); // Created Keywords
    ///printArrayKeywords(); ///[test]
    creatDelimiters(); // Created Delimiters
    ///printArrayDelimiters(); ///[test]
    inputCode(); // Input code for testing
    ///printInputCode(); ///[test]
    analysisCode(); // Analysis the code
    printOutputInfo(); // Print the result
    cout << "File <main.cpp> running successfully!!" << endl;
    return 0;
}
