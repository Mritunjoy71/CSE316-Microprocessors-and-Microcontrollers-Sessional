.MODEL SMALL

.CODE

MAIN PROC
    MOV AX,2FH
    MOV BX,3FH
    MOV CX,4CH
    CMP AX,BX
    JL THEN1          
    END_IF:
    MOV AH,4CH
    INT 21H
    THEN1:
    CMP BX,CX
    JL THEN2
    MOV BX,0
    JMP END_IF
    THEN2:
    MOV AX,0
    JMP END_IF

         
MAIN ENDP

END MAIN 