.MODEL SMALL

.CODE

MAIN PROC
    MOV AH,1
    INT 21H
    MOV BL,AL
    MOV AH,2
    CMP BL,'A'
    JE CR
    CMP BL,'B'
    JE LF
    MOV AH,4CH
    INT 21H
    CR:
    MOV DL,0DH
    INT 21H
    LF:
    MOV DL,0AH
    INT 21H
         
MAIN ENDP

END MAIN 