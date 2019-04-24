; 4、从键盘读入一个字符串，以Enter结束，字符串不超过50个字符，
;并打印该字符串；查找中间是否有‘masm’子串。如果有，输出‘Yes’；
;否则，输出‘No’)。
; - 查找中间是否有‘masm’子串
; + 查找中间是否有‘WZX’子串

DATA SEGMENT
            BUFFER DB 50        	;定义缓冲区长度
                   DB ?         	;输入完成自动获取字符个数
                   DB 50 DUP(?)
			CR DB 0DH,0AH,'$'
            STRING DB 'WZX$'
            INPUT DB 'PLEASE INPUT A STRING(YES=WZX):$'
            OUTPUT1 DB 0DH,0AH,'YES$'
            OUTPUT2 DB 0DH,0AH,'NO$'
DATA ENDS
STACK SEGMENT STACK
              DW 512 DUP(?)
CODE SEGMENT
ASSUME CS:CODE, DS:DATA, SS:STACK
START:      MOV AX, DATA
            MOV DS, AX
            MOV ES, AX              ;[!!IMPORTANT!!]

            MOV DX, OFFSET INPUT	;打印提示输入信息
            MOV AH, 09H
            INT 21H

            MOV DX, OFFSET BUFFER	;读入字符串至BUFFER
            MOV AH, 0AH
            INT 21H

            MOV SI, OFFSET BUFFER
            MOV AL, [SI+1]          ;最多比较次数(BUFFER长度)
            ADD SI, 2     	        ;指向BUFFER+2(BUFFER内容)
            LEA DI, STRING	        ;指向STRING(STRING内容)
            MOV DX, SI     		    ;DX = &BUFFER+2
            MOV BX, DI				;BX = &STRING
			

            XOR CX, CX              ;CX = 0000
FIND_AGAIN: MOV CL, 3               ;字符串长度
			REPZ CMPSB         		;CX!=0 & ZF=1 CMPSB
									;字符串未结束且串相等继续比较
            JZ FOUND                ;串结束依然相等跳转到FOUND
            
            INC DX          		;下一个字节
            MOV SI, DX          	;BUFFER下一个字节
            MOV DI, BX          	;STRING地址归零
            DEC AL              	;剩余比较次数-1
            CMP AL, 3               ;比比较串长度短则跳出
            JNB FIND_AGAIN
			
			MOV DX, OFFSET OUTPUT2	;输出NO
            JMP SHOW            	;跳过FOUND

FOUND:		MOV DX, OFFSET OUTPUT1	;输出YES

SHOW:       MOV AH, 09H
            INT 21H
MOV AH, 4CH                     	;返回DOS系统
INT 21H
CODE ENDS
END START