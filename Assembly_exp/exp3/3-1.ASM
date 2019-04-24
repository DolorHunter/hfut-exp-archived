; 1. 编写一个子程序计算z=f(x,y)=x/y+x-y（x,y,z有符号数内存字数）。
;    要求通过堆栈传送输入参数，输出参数通过AX传递。(要求输入输出实现，
;    且有提示)。

DATA SEGMENT
            MSG1 DB 0DH,0AH,'INPUT NUMBER X:$'
            MSG2 DB 0DH,0AH,'INPUT NUMBER Y:$'
            MSG3 DB 0DH,0AH,'OUTPUT IS:$'
            X DW ?,0DH,0AH,'$'
            Y DW ?,0DH,0AH,'$'
            Z DW ?,0DH,0AH,'$'
            CR DB 0DH,0AH,'$'
            BUFFER DB 50
                   DB ?
                   DB 50 DUP(?)
DATA ENDS
STACK SEGMENT STACK
            DW 512 DUP(?)
STACK ENDS
CODE SEGMENT
ASSUME CS:CODE, DS:DATA, SS:STACK
START:      MOV AX, DATA
            MOV DS, AX

            MOV DX, OFFSET MSG1     ;显示提示输入信息X
            MOV AH, 9
            INT 21H
            
            MOV DX, OFFSET BUFFER   ;输入内容存入BUFFER
            MOV AH, 0AH             ;等待从键盘读字符
            INT 21H

            MOV SI, OFFSET BUFFER
            MOV CL, [SI+1]
            ADD SI, 2
            CALL TRANS              ;输入内容转为数字存入X(0X)
            MOV X, AX               ;保存X
            
            MOV DX, OFFSET MSG2     ;显示提示输入信息Y
            MOV AH, 09H
            INT 21H

            MOV DX, OFFSET BUFFER   ;输入内容存入BUFFER
            MOV AH, 0AH             ;等待从键盘读字符
            INT 21H

            MOV SI, OFFSET BUFFER
            MOV CL, [SI+1]
            ADD SI, 2
            CALL TRANS              ;输入内容转为数字存入Y(0X)
            MOV Y, AX               ;保存Y

            MOV DX, OFFSET MSG3     ;显示提示输出信息Z
            MOV AH, 09H
            INT 21H
            
            PUSH X 
            PUSH Y                  ;X, Y入栈

            CALL FX                 ;调用子函数FX

            MOV AX, Z
            MOV BX, 10
            PUSH BX                 ;10作为结束标志!!
PUSH_AGAIN: CWD                     ;AX->DX.AX
            IDIV BX                 ;DX=DX.AX%BX ;AX=DX.AX/BX
            PUSH DX
            CMP AX, 0      
            JNZ PUSH_AGAIN          ;商>0

POP_AGAIN:  POP DX
            CMP DX, 10              ;跟结束标志10比较
            JZ DONE
            ADD DX, 30H             ;ASCII->D
            MOV AH, 02H
            INT 21H
            JMP POP_AGAIN
DONE:
MOV AH, 4CH
INT 21H

                                    ;子函数
TRANS PROC                          ;字符转换数字
            PUSH BX
            PUSH SI
            XOR AX, AX
            MOV BL, 10
AGAIN:      IMUL BL
            SUB BYTE PTR[SI], 30H 
            ADD AL, BYTE PTR[SI]
            INC SI
            LOOP AGAIN
            POP SI
            POP BX
RET
TRANS ENDP

FX PROC                             ;计算公式
            PUSH BP                 ;保护现场
            MOV BP, SP
            PUSH BX
            PUSH DX
            MOV AX, [BP+6]          ;AX=X
            MOV BX, [BP+4]          ;BX=Y
            CWD                     ;AX->DX.AX
            IDIV BX                 ;AX=X/Y ;DX=X%Y
            ADD AX, [BP+6]          ;AX=X/Y+X
            SUB AX, [BP+4]          ;AX=X/Y+X-Y
            MOV Z, AX               ;Z=X/Y+X-Y
            POP DX
            POP BX
            POP BP                  ;恢复现场
RET 
FX ENDP

CODE ENDS
END START