.MODEL SMALL
.DATA
.CODE
MAIN PROC 

MOV AH,1
    INT 21H
    MOV CH,AL 
    
    MOV BH,CH ;BH=CH
    
    MOV AH,2
    MOV DL,0DH
    INT 21H
    MOV DL,0AH
    INT 21H
    
    MOV AH,1
    INT 21H
    MOV CL,AL 
    
    MOV AH,2
    MOV DL,0DH
    INT 21H
    MOV DL,0AH
    INT 21H
    
    SUB CL,48
    ADD CH,CL 
    
    MOV AH,2
    MOV DL,CH
    INT 21H  
    
    MOV DL,0DH
    INT 21H
    MOV DL,0AH
    INT 21H   
    

    SUB BH,CL
    MOV CL,BH
    
    MOV DL,CL
    INT 21H
    
    
    
        
MAIN ENDP
END MAIN