; 1. X��Y��Z��V��Ϊ�ֱ�������X��Y��Z��V�ֵ�Ԫ�д����16λ����������
;    �Ա�д������Գ���������¹��ܣ�
; �ټ������ʽֵ��V�C��X*Y+Z-720����/X��
; �ڽ���������ʽ��������������SUM1��Ԫ����������SUM2��Ԫ��

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
            IMUL Y          ;AX = (��λ)X*Y (AX=BX*AX)
                            ;DX = (��λ)X*Y
            MOV CX, AX      ;CX = AX
            MOV BX, DX      ;BX = DX
            MOV AX, Z
            CWD             ;��չZ��32λ
                            ;DX = (��λ)Z
                            ;AX = (��λ)Z 
            ADD CX, AX      ;CX = (��λ)X*Y+Z 
            ADC BX, DX      ;BX = (��λ)X*Y+Z 
            SUB CX, 720     ;CX = (��λ)X*Y+Z-720
            SBB BX, 0       ;BX = (��λ)X*Y+Z-720
            MOV AX, V 
            CWD             ;��չV��32λ
                            ;DX = (��λ)V
                            ;AX = (��λ)V 
            SUB AX, CX      ;AX = (��λ)V-(X*Y+Z-720)
            SBB DX, BX      ;DX = (��λ)V-(X*Y+Z-720)
            IDIV X
            MOV SUM1, AX
            MOV SUM2, DX
MOV AH, 4CH
INT 21H
CODE ENDS
END START