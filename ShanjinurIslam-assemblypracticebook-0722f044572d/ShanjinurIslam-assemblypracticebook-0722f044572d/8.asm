.MODEL SMALL

.CODE

MAIN PROC
    MOV AH,1
    INT 21H
    MOV CL,AL
    INT 21H
    MOV CH,AL
    
    CMP CL,CH
    JG ELSE
    MOV AH,2
    MOV DL,CL
    INT 21H
    MOV DL,' '
    INT 21H
    MOV DL,CH
    INT 21H
    JMP END_IF  
    ELSE:
    MOV AH,2
    MOV DL,CH
    INT 21H
    MOV DL,' '
    INT 21H
    MOV DL,CL
    INT 21H
    JMP END_IF
    
    END_IF:
    MOV AH,4CH
    INT 21H
         
MAIN ENDP

END MAIN 