 ; 2、使用地址表实现如下功能：根据输入的数字1－7，
;    分别显示相应的英文星期名，如果输入其他字符，则重新输入。

DATA SEGMENT
            MSG DB 'INPUT NUMBER(1 - 7):',0DH,0AH,'$'
            NUM DB ?
            S1 DB 'MONDAY$'
            S2 DB 'TUESDAY$',0DH,0AH,'$'
            S3 DB 'WEDNESDAY$',0DH,0AH,'$'
            S4 DB 'THURSDAY$',0DH,0AH,'$'
            S5 DB 'FRIDAY$',0DH,0AH,'$'
            S6 DB 'SATURDAY$',0DH,0AH,'$'
            S7 DB 'SUNDAY$',0DH,0AH,'$'
DATA ENDS
STACK SEGMENT STACK
            DW 512 DUP(?)
STACK ENDS
CODE SEGMENT
ASSUME CS:CODE, DS:DATA, SS:STACK
START:
            MOV AX, DATA
            MOV DS, AX
INPUT:      MOV DX, OFFSET MSG  ;显示提示输入信息
            MOV AH, 9
            INT 21H
            MOV AH, 0           ;等待从键盘读字符
            INT 16H
            MOV NUM, AL         ;输入
            CMP AL, '1'
            JB INPUT            ;比1小重新输入
            CMP AL, '7'
            JA INPUT            ;比7大重新输入
            CMP AL, '1'
            JE PRT1             ;AX=1 跳至PRT1
            CMP AL, '2'
            JE PRT2             ;AX=2 跳至PRT2
            CMP AL, '3'
            JE PRT3             ;AX=3 跳至PRT3
            CMP AL, '4'
            JE PRT4             ;AX=4 跳至PRT4
            CMP AL, '5'
            JE PRT5             ;AX=5 跳至PRT5
            CMP AL, '6'
            JE PRT6             ;AX=6 跳至PRT6
            CMP AL, '7'
            JE PRT7             ;AX=7 跳至PRT7
PRT1:       MOV DX, OFFSET S1
            JMP SHOW
PRT2:       MOV DX, OFFSET S2
            JMP SHOW
PRT3:       MOV DX, OFFSET S3
            JMP SHOW
PRT4:       MOV DX, OFFSET S4
            JMP SHOW
PRT5:       MOV DX, OFFSET S5
            JMP SHOW
PRT6:       MOV DX, OFFSET S6
            JMP SHOW
PRT7:       MOV DX, OFFSET S7
SHOW:       MOV AH, 09H
            INT 21H
MOV AH, 4CH
INT 21H
CODE ENDS
END START
