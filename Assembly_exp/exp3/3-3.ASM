;3. 挂接1CH中断，正计时90秒后退出。要求屏幕显示0-89的秒数。
;   (30s倒计时模型->90s正计时)

    INTNO EQU 1CH
     

    DATA SEGMENT
      OLDISR DW ?,?
      TIMER DB 100       
      COUNTER_START DW 0        ;计数器起点
      COUNTER_END DW 90         ;计数器结束点
      ISDONE DB 0
    DATA ENDS
    
    CODE SEGMENT
      ASSUME CS:CODE,DS:DATA
START:
      MOV AX,DATA
      MOV DS,AX
      
      MOV AX,0
      MOV ES,AX
      
      ;PROTECT
   
      CLI                       ;禁止可屏蔽中断
      MOV AX, ES:[INTNO*4]      ;保存原终端向量
      MOV OLDISR[0],AX
      MOV AX,ES:[INTNO*4+2]
      MOV OLDISR[2], AX
      STI                       ;允许可屏蔽中断
    
      ;SET NEW ISR
    
      CLI
      MOV WORD PTR ES:[INTNO*4], OFFSET ISR
      MOV WORD PTR ES:[INTNO*4+2],SEG ISR
      STI


    ;WAIT HERE
WAITHERE:
    CMP ISDONE,1
    JNZ WAITHERE
  
  
EXIT:     
    ;RESTORE
   
      CLI
      MOV AX,OLDISR[0]
      MOV ES:[INTNO*4],AX       ;恢复原中断向量
      MOV AX,OLDISR[2]
      MOV ES:[INTNO*4+2],AX
      STI
        
      MOV AX,4C00H
      INT 21H
      
ISR PROC FAR
        PUSH DX
        PUSH AX
        
        MOV AX,DATA
        MOV DS,AX

        STI                     ;便于中断嵌套

       ;COUNT HERE
        INC TIMER
AGAIN:
        CMP TIMER, 1000/55      ;18(调用18次 大约1s)
        JB DONE
        MOV TIMER,0


        ;carriage
        MOV AH,2
        MOV DL,13
        INT 21H

        ;print time
        MOV AX,COUNTER_START

        MOV DL,10
        DIV DL
        MOV DH,AH
        MOV DL,AL
        MOV AH,2
        ADD DL,30H              ;D->ASCII
        INT 21H
        MOV DL,DH
        ADD DL,30H
        INT 21H
        
        INC COUNTER_START       ;计数器增加
        MOV AX, COUNTER_START
        CMP AX, COUNTER_END
        JB DONE
        MOV ISDONE,1
        
DONE:
        PUSHF
        CALL DWORD PTR OLDISR   ;调用原中断

        CLI
        POP AX
        POP DX
        IRET                    ;中断返回
ISR ENDP


CODE ENDS
      END START
