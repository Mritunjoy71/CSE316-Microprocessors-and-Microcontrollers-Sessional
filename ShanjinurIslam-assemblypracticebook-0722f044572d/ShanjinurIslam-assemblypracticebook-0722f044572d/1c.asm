.MODEL SMALL

.CODE

MAIN PROC
    MOV DL,'0'
    CMP DL,'A'
    JNGE END_IF
    CMP DL,'Z'
    JNLE END_IF
    MOV AH,2
    INT 21H
    END_IF:
    MOV AH,4CH
    INT 21H
MAIN ENDP

END MAIN