.MODEL SMALL

.CODE

MAIN PROC
    MOV AX,0
    MOV BX,1
    TOP:
    CMP BL,148
    JNG EXIT
    ADD AX,BX
    ADD BX,3
    LOOP TOP
    EXIT:
         
MAIN ENDP

END MAIN 