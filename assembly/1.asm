.MODEL SMALL

.DATA 
STR DB "Input a lowercase character:$"
STR2 DB "uppercase:$"

.CODE 

MAIN PROC   
    MOV AX,@DATA
    MOV DS,AX
    
    LEA DX,STR
    MOV AH,9
    INT 21h  
    
    MOV AH,1
    INT 21h 
    MOV BL,AL    
        
    MOV AH,2
    MOV DL,0DH
    INT 21H
    MOV DL,0AH
    INT 21h
         
    SUB BL,20h ;20h=32 difference between cap and small  
    
    MOV DL,BL
    INT 21h   
    
  
    

MAIN ENDP
END MAIN