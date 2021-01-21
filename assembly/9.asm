.MODEL SMALL

.DATA   

.CODE

MAIN PROC
    MOV AH,1
    INT 21H
    MOV CL,AL 
    
    SUB CL,48
    
    MOV AH,2
    MOV DL,0DH
    INT 21H
    MOV DL,0AH
    INT 21H
    
    MOV AH,1
    INT 21H
    MOV CH,AL
    
    ADD CL,CH   
    
    MOV AH,2
    MOV DL,0DH
    INT 21H
    MOV DL,0AH
    INT 21H
               
    MOV AH,1
    INT 21H
    MOV CH,AL
    
    SUB CH,48
    
    ADD CL,CH 
    
                
    MOV AH,2
    MOV DL,0DH
    INT 21H
    MOV DL,0AH
    INT 21H 
    
    MOV AH,1
    INT 21H
    MOV CH,AL
    
    SUB CH,48
    
    ADD CL,CH 
    
               
    MOV AH,2
    MOV DL,0DH
    INT 21H
    MOV DL,0AH
    INT 21H
    
    MOV DL,CL
    INT 21H
       
    MOV AH,4CH
    INT 21h
MAIN ENDP

END MAIN
