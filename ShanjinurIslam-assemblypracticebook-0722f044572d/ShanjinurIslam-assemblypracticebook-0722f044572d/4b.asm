.MODEL SMALL

.DATA
    STR1 DB 0DH,0AH,'$'
    VAR1 DB ?
.CODE

MAIN PROC
    MOV CX,@DATA
    MOV DS,CX
    
    MOV AH,1
    INT 21H
    MOV VAR1,AL
    
    MOV BX,1
    TOP:
    CMP BX,80
    JG EXIT
    
    MOV AH,2
    MOV DL,VAR1
    INT 21H
    
    LEA DX,STR1
    MOV AH,9
    INT 21H
    
    INC BX
    
    LOOP TOP
    EXIT:
         
MAIN ENDP

END MAIN 