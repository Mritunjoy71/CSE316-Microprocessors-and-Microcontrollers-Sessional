.MODEL SMALL

.CODE

MAIN PROC  
    MOV AX,8
    MOV BX,6
    MOV CX,5
    CMP AX,BX
    JL THEN_ONE
    CMP BX,CX
    JL THEN_ONE
    JMP THEN_TWO
    JMP END_IF
    THEN_ONE:
    MOV DX,0
    JMP END_IF
    THEN_TWO:
    MOV DX,1
    END_IF:
    
MAIN ENDP

END MAIN