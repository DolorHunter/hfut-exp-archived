; 2. 编写一个宏，求三个数的最大数，原型为：MAX3 x,y,z,min，
;    最大值要求输出。

_MAX MACRO X,Y,Z,MAX
            MOV AX, X 
            CMP AX, Y 
            JL  EXCHANGE1
BACK:       CMP AX, Z 
            JL EXCHANGE2
            JMP FIN
EXCHANGE1:  MOV AX, Y
            JMP BACK
EXCHANGE2:  MOV AX, Z
FIN:        MOV MAX, AX
ENDM

DATA SEGMENT
            MSG DB 'MAX=$'
            X DW 5
            Y DW 10
            Z DW 23
            MAX DW ?,'$'
            CR DB 0DH,0AH,'$'
DATA ENDS
STACK SEGMENT STACK
            DW 512 DUP(?)
STACK ENDS
CODE SEGMENT
ASSUME CS:CODE, DS:DATA, SS:STACK
START:      MOV AX, DATA
            MOV DS, AX

            _MAX X,Y,Z,MAX

            MOV DX, OFFSET MSG
            MOV AH, 09H
            INT 21H

            MOV AX, MAX
            MOV BX, 10
            PUSH BX         ;10作为结束标志!!
PUSH_AGAIN: CWD             ;AX->DX.AX
            IDIV BX         ;DX=DX.AX%BX ;AX=DX.AX/BX
            PUSH DX
            CMP AX, 0      
            JNZ PUSH_AGAIN  ;商>0

POP_AGAIN:  POP DX
            CMP DX, 10      ;跟结束标志10比较
            JZ DONE
            ADD DX, 30H     ;ASCII->D
            MOV AH, 02H
            INT 21H
            JMP POP_AGAIN
DONE:
MOV AH, 4CH
INT 21H
CODE ENDS
END START