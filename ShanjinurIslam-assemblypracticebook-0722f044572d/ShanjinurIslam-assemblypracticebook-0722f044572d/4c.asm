.MODEL SMALL

.CODE

MAIN PROC
    MOV BX,1
    MOV AH,1
    TOP:
    CMP BX,5
    JG END_L
    INT 21H
    INC BX
    LOOP TOP
    END_L:
    MOV AH,2
    MOV DL,0DH
    INT 21H
    MOV BX,1
    
    BOT:
    CMP BX,5
    JG END_LOOP
    MOV DL,'X'
    INT 21H
    INC BX
    LOOP BOT
    END_LOOP:
    
         
MAIN ENDP

END MAIN 