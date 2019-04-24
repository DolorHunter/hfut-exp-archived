; 3.求一个班50名学生成绩的平均值、最大值和最小值,并将结果显示出来。

DATA SEGMENT
            GRADE DB 10 dup(50,60,70,80,90);假设50个学生分数
            MSG1 DB 'AVG SCORE:$'
            MSG2 DB 'MAX SCORE:$'
            MSG3 DB 'MIN SCORE:$'
            SUM DW ?,'$',0DH,0AH        ;总成绩[TEST]
            AVG DB ?,'$',0DH,0AH        ;平均成绩
            MAX DB ?,'$',0DH,0AH        ;最大值
            MIN DB ?,'$',0DH,0AH        ;最小值
            CR DB 0DH,0AH,'$'           ;换行
DATA ENDS
STACK SEGMENT STACK
            DW 512 DUP(?)
STACK ENDS
CODE SEGMENT
ASSUME CS:CODE, DS:DATA
START:      MOV AX, DATA
            MOV DS, AX
            XOR AX, AX                  ;AX = 0000(不写好像也行)
            ;;;;;;;;;;;找平均数;;;;;;;;;;;
            MOV SI, 0
            MOV CX, 50
            XOR DX, DX                  ;DX = 0000
SUM_CAL:    MOV AL, GRADE[SI]
            ADD DL, AL
            ADC DH, 0                   ;DX暂存
            INC SI
            LOOP SUM_CAL
            MOV AL, DL
            MOV AH, DH                  ;移回AX
            MOV SUM, AX
            MOV CL, 50
            DIV CL                      ;AH=AX%CL ;AL=AX/CL
            MOV AVG, AL                 ;平均数存入AVG(ascii)
            ;;;;;;;;;平均数已求得;;;;;;;;;
            CBW                         ;AL->AX(除法准备)
            MOV BL, 10
            DIV BL                      ;AL=AX/10 ;AH=AX%10(D)
            ADD AL, 30H                 ;转化为数字-十位
            ADD AH, 30H                 ;转化为数字-个位
            MOV BL, AL
            MOV BH, AH                  ;暂存到BX
            MOV DX, OFFSET MSG1
            MOV AH, 09H
            INT 21H                     ;显示平均数信息
            MOV AL, BL
            CBW                         ;AL->AX
            MOV DX, AX
            MOV AH, 02H
            INT 21H                     ;显示最大分数-十位
            MOV AL, BH
            CBW                         ;AL->AX
            MOV DX, AX
            MOV AH, 02H
            INT 21H                     ;显示最大分数-个位            
            ;;;;;;;;;输出最大分数;;;;;;;;;

            MOV DX, OFFSET CR           ;换行
            MOV AH, 09H
            INT 21H
            ;;;;;;;;找最大分数;;;;;;;;;;;; 
            MOV SI, 0
            MOV CX, 49                  ;LOOP循环比较50次
FIND_MAX:   MOV AL, GRADE[SI]
AGAIN_MAX:  INC SI
            CMP AL, GRADE[SI]
            JB FIND_MAX                 ;遇到更大分数赋值给AL
            LOOP AGAIN_MAX
            MOV MAX, AL                 ;最大数存入MAX(ascii)
            ;;;;;;;;最大分数已找到;;;;;;;;
            CBW                         ;AL->AX(除法准备)
            MOV BL, 10
            DIV BL                      ;AL=AX/10 ;AH=AX%10(D)
            ADD AL, 30H                 ;转化为数字-十位
            ADD AH, 30H                 ;转化为数字-个位
            MOV BL, AL
            MOV BH, AH                  ;暂存到BX
            MOV AH, 09H
            MOV DX, OFFSET MSG2
            INT 21H                     ;显示最大分数信息
            MOV AL, BL
            CBW                         ;AL->AX
            MOV DX, AX
            MOV AH, 02H
            INT 21H                     ;显示最大分数-十位
            MOV AL, BH
            CBW                         ;AL->AX
            MOV DX, AX
            MOV AH, 02H
            INT 21H                     ;显示最大分数-个位
            ;;;;;;;;;输出最大分数;;;;;;;;;

            MOV DX, OFFSET CR           ;换行
            MOV AH, 09H
            INT 21H
            ;;;;;;;;找最小分数;;;;;;;;;;;; 
            MOV SI, 0
            MOV CX, 49
FIND_MIN:   MOV AL, GRADE[SI]
AGAIN_MIN:  INC SI
            CMP AL, GRADE[SI]
            JA FIND_MIN
            LOOP AGAIN_MIN
            MOV MIN, AL                 ;最小数存入MIN(ascii)
            ;;;;;;;;最小分数已找到;;;;;;;;
            CBW
            MOV BL, 10
            DIV BL
            ADD AL, 30H
            ADD AH, 30H
            MOV BL, AL
            MOV BH, AH
            MOV DX, OFFSET MSG3
            MOV AH, 09H
            INT 21H
            MOV AL, BL
            CBW
            MOV DX, AX
            MOV AH, 02H
            INT 21H
            MOV AL, BH
            CBW
            MOV DX, AX
            MOV AH, 02H
            INT 21H
            ;;;;;;;;;输出最小分数;;;;;;;;;
MOV AH, 4CH
INT 21H
CODE ENDS
END START