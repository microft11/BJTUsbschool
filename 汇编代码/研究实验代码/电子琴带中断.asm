STACK SEGMENT PARA 'STACK'
    DW 256 DUP(?)
STACK ENDS

data segment
    io8255a     equ 288h
    io8255ctl   equ 28bh
    io8253a     equ 280h
    io8253b     equ 283h
    table dw 524,588,660,698,784,880,988,1048;高音  
    ;table dw 262,294,330,347,392,440,494,524;低音
    msg db 'team-made electronic organ',0dh,0ah,'$'
    scale1 db 'd0',0dh,0ah,'$' ;do是个关键词故用d0
    scale2 db 'ra',0dh,0ah,'$'
    scale3 db 'mi',0dh,0ah,'$'
    scale4 db 'fa',0dh,0ah,'$'
    scale5 db 'sol',0dh,0ah,'$'
    scale6 db 'la',0dh,0ah,'$'
    scale7 db 'ti',0dh,0ah,'$'
    scale8 db 'd0!',0dh,0ah,'$' ;八个音阶
    OLD_OFF DW ?
    OLD_SEG DW ?
    key db ?
data ends

code segment
assume cs:code,ds:data,SS:STACK

; 填写中断向量
    MOV AX,350BH
    INT 21H
    MOV OLD_OFF,BX
    MOV BX,ES
    MOV OLD_SEG,BX
    CLI
    MOV DX,SEG audio
    MOV DS,DX
    MOV DX,OFFSET audio
    MOV AX,250BH
    INT 21H
    MOV AX,DATA
    MOV DS,AX
    STI

; 开始程序
start:
    mov ax,data
    mov ds,ax

    mov dx,offset msg
    mov ah,9
    int 21h 

sing:
    MOV DX,283H
    MOV AL,10011000B
    OUT DX,AL

    MOV DX,280H
    IN AL,DX

    mov dl, 0
    lp:              ;这一段确定开启的是那一个开关
        mov bl, al
        INC dl
        SHR BL, 1
        jc lp
    dec dl
    mov al, dl
    mov bl, al
    mov bh, 0       
    mov key, bl;    把音调特地保存在key中
    

    ;这一段对8254进行初始化
    mov ax,4240H         ;计数初值 = 1000000 / 频率, 保存到AX
    mov dx,0FH
    div word ptr[table+bx]
    mov bx,ax
    
    mov dx,io8253b          ;设置8254计时器0方式3
    mov al,00110110B
    out dx,al

    mov dx,io8253a         
    mov ax,bx
    out dx,al            ;写计数初值低字节 
    mov al,ah
    out dx,al            ;写计数初值高字节

    mov bl, key; 后边这段不用bl了，把key存到这里好往中断函数里传参

    ;这里控制8255输出口的开关，保证每一个音都是一样的长度
    mov dx,io8255a            
    mov al,03h
    out dx,al            ;置PA1PA0 = 11(开扬声器)
    call delay           ;延时
    ;理论上没错的话这里要进入中断了
    mov al,0h
    out dx,al            ;置PA1PA0 = 00(关扬声器)  

    jmp sing

finish:
    mov ax,4c00h
    int 21h
    
delay proc near          ;延时子程序
    push cx
    push ax
    mov ax,15
x1: mov cx,0ffffh
x2: dec cx
    jnz x2
    dec ax
    jnz x1
    pop ax
    pop cx
    ret
delay endp

audio proc FAR
    PUSH AX
    PUSH BX
    PUSH DX
    PUSH DI
    CLI
    call delay
    mov al, bl

    cmp al, 8
    jbe k8
    cmp al, 7
    jbe k7
    cmp al, 6
    jbe k6
    cmp al, 5
    jbe k5
    cmp al, 4
    jbe k4
    cmp al, 3
    jbe k3
    cmp al, 2
    jbe k2
    jmp k1

    k1:
        MOV DX,OFFSET scale1
        MOV AH,09H;DOS的09号功能：在屏幕上输出一个字符串    DS:DX=字符串地址
        INT 21H
        jmp next
    k2:
        MOV DX,OFFSET scale2
        MOV AH,09H
        INT 21H
        jmp next
    k3:
        MOV DX,OFFSET scale3
        MOV AH,09H;
        INT 21H
        jmp next
    k4:
        MOV DX,OFFSET scale4
        MOV AH,09H
        INT 21H
        jmp next
    k5:
        MOV DX,OFFSET scale5
        MOV AH,09H
        INT 21H
        jmp next
    k6:
        MOV DX,OFFSET scale6
        MOV AH,09H
        INT 21H
        jmp next
    k7:
        MOV DX,OFFSET scale7
        MOV AH,09H
        INT 21H
        jmp next
    k8:
        MOV DX,OFFSET scale8
        MOV AH,09H
        INT 21H
        jmp next
        


next:
    STI
    POP DI
    POP DX
    POP BX
    POP AX
IRET    
audio endp

code ends
end start
