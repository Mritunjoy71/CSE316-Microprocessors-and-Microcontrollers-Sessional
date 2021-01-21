.MODEL SMALL

.DATA
    S1 DB "Enter 1st Number: $"
    S2 DB "Enter 2nd Number: $"
    S3 DB "You have entered: $"
    S4 DB "After swapping: $"   

.CODE

MAIN PROC
    MOV AX,@DATA
    MOV DS,AX
    
    LEA DX,S1
    MOV AH,9
    INT 21H
    
    MOV AH,1
    INT 21h
    MOV CH,AL
    
    MOV AH,2
    MOV DL,0DH
    INT 21H
    MOV DL,0AH
    INT 21H
    
    LEA DX,S2
    MOV AH,9
    INT 21H
    
    MOV AH,1
    INT 21h
    MOV CL,AL
    
    MOV AH,2
    MOV DL,0DH
    INT 21H          ;NEW LINE
    MOV DL,0AH
    INT 21H
    
    LEA DX,S3
    MOV AH,9
    INT 21h
    
    MOV AH,2
    MOV DL,CH
    INT 21H 
    
    MOV DL,' '      ;SPACE
    INT 21H 
    
    MOV DL,CL
    INT 21H
    
    MOV DL,0DH
    INT 21H
    MOV DL,0AH
    INT 21H
    
    LEA DX,S4
    MOV AH,9
    INT 21H
    
    ADD CH,CL      ;CH=CH+CL
    SUB CL,CH  
    NEG CL        ;CL=CL-CH      ;CH=CH+CL
    SUB CH,CL        
    
    MOV AH,2
    MOV DL,CH
    INT 21H
    MOV DL,' '
    INT 21H
    MOV DL,CL
    INT 21H
    
               
    MOV AH,4CH
    INT 21h
MAIN ENDP

END MAIN
