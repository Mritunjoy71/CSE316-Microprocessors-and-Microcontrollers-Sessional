.MODEL SMALL

.CODE

MAIN PROC  
    MOV AX,5
    MOV BX,6
    MOV CX,4
    CMP AX,BX
    JL THEN_ONE
    JMP END_IF
    THEN_ONE:
    CMP BX,CX
    JL THEN_TWO
    MOV BX,0
    JMP END_IF
    THEN_TWO:
    MOV AX,0
    JMP END_IF
    END_IF:
MAIN ENDP

END MAIN