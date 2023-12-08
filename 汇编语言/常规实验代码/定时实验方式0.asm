code segment
start:
    mov dx,283h;
    mov al,00010000b; 
    out dx,al; 
    
    mov dx,280h; 
    mov ax,03h;
    out dx,al;  
 
code ends
end start