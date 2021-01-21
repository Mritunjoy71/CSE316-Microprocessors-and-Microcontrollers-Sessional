.MODEL SMALL

.DATA   

.CODE

MAIN PROC
    MOV AH,1
    INT 21H
    MOV BH,AL 
    
    MOV AH,2
    MOV DL,0DH
    INT 21H
    MOV DL,0AH
    INT 21H
    
    MOV AH,1
    INT 21H
    MOV BL,AL  
    
    SUB BH,BL   
    
    MOV AH,2
    MOV DL,0DH
    INT 21H
    MOV DL,0AH
    INT 21H
               
    MOV AH,1
    INT 21H
    MOV BL,AL
    
    ADD BH,BL
               
    MOV AH,2
    MOV DL,0DH
    INT 21H
    MOV DL,0AH
    INT 21H
    
    MOV DL,BH
    INT 21H
       
    MOV AH,4CH
    INT 21h
MAIN ENDP

END MAIN
