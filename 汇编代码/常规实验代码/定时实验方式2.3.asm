code segment
start:
    mov dx,283h
    mov al,10110100b
    out dx,al
    
    mov dx,282h
    mov ax,3e8h
    out dx,al
    mov al,ah
    out dx,al 
code ends
end start
