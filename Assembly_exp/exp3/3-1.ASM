; 1. ��дһ���ӳ������z=f(x,y)=x/y+x-y��x,y,z�з������ڴ���������
;    Ҫ��ͨ����ջ��������������������ͨ��AX���ݡ�(Ҫ���������ʵ�֣�
;    ������ʾ)��

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

            MOV DX, OFFSET MSG1     ;��ʾ��ʾ������ϢX
            MOV AH, 9
            INT 21H
            
            MOV DX, OFFSET BUFFER   ;�������ݴ���BUFFER
            MOV AH, 0AH             ;�ȴ��Ӽ��̶��ַ�
            INT 21H

            MOV SI, OFFSET BUFFER
            MOV CL, [SI+1]
            ADD SI, 2
            CALL TRANS              ;��������תΪ���ִ���X(0X)
            MOV X, AX               ;����X
            
            MOV DX, OFFSET MSG2     ;��ʾ��ʾ������ϢY
            MOV AH, 09H
            INT 21H

            MOV DX, OFFSET BUFFER   ;�������ݴ���BUFFER
            MOV AH, 0AH             ;�ȴ��Ӽ��̶��ַ�
            INT 21H

            MOV SI, OFFSET BUFFER
            MOV CL, [SI+1]
            ADD SI, 2
            CALL TRANS              ;��������תΪ���ִ���Y(0X)
            MOV Y, AX               ;����Y

            MOV DX, OFFSET MSG3     ;��ʾ��ʾ�����ϢZ
            MOV AH, 09H
            INT 21H
            
            PUSH X 
            PUSH Y                  ;X, Y��ջ

            CALL FX                 ;�����Ӻ���FX

            MOV AX, Z
            MOV BX, 10
            PUSH BX                 ;10��Ϊ������־!!
PUSH_AGAIN: CWD                     ;AX->DX.AX
            IDIV BX                 ;DX=DX.AX%BX ;AX=DX.AX/BX
            PUSH DX
            CMP AX, 0      
            JNZ PUSH_AGAIN          ;��>0

POP_AGAIN:  POP DX
            CMP DX, 10              ;��������־10�Ƚ�
            JZ DONE
            ADD DX, 30H             ;ASCII->D
            MOV AH, 02H
            INT 21H
            JMP POP_AGAIN
DONE:
MOV AH, 4CH
INT 21H

                                    ;�Ӻ���
TRANS PROC                          ;�ַ�ת������
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

FX PROC                             ;���㹫ʽ
            PUSH BP                 ;�����ֳ�
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
            POP BP                  ;�ָ��ֳ�
RET 
FX ENDP

CODE ENDS
END START