; 1. X、Y、Z、V均为字变量，在X、Y、Z、V字单元中存放是16位带符号数。
;    试编写汇编语言程序完成以下功能：
; ①计算表达式值（V–（X*Y+Z-720））/X；
; ②将上述表达式运算结果整数放在SUM1单元，余数放在SUM2单元。

DATA SEGMENT
            SUM1 DW 0
            SUM2 DW 0
            X DW 233
            Y DW 108
            Z DW 25
            V DW -40
DATA ENDS
STACK SEGMENT STACK
            DW 512 DUP(?)
STACK ENDS
CODE SEGMENT
ASSUME CS:CODE, DS:DATA
START:
            MOV AX, DATA
            MOV DS, AX
            MOV AX, X
            IMUL Y          ;AX = (低位)X*Y (AX=BX*AX)
                            ;DX = (高位)X*Y
            MOV CX, AX      ;CX = AX
            MOV BX, DX      ;BX = DX
            MOV AX, Z
            CWD             ;拓展Z成32位
                            ;DX = (高位)Z
                            ;AX = (低位)Z 
            ADD CX, AX      ;CX = (低位)X*Y+Z 
            ADC BX, DX      ;BX = (高位)X*Y+Z 
            SUB CX, 720     ;CX = (低位)X*Y+Z-720
            SBB BX, 0       ;BX = (高位)X*Y+Z-720
            MOV AX, V 
            CWD             ;拓展V成32位
                            ;DX = (高位)V
                            ;AX = (低位)V 
            SUB AX, CX      ;AX = (低位)V-(X*Y+Z-720)
            SBB DX, BX      ;DX = (高位)V-(X*Y+Z-720)
            IDIV X
            MOV SUM1, AX
            MOV SUM2, DX
MOV AH, 4CH
INT 21H
CODE ENDS
END START
