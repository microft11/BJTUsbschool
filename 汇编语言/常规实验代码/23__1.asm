data segment
data ends
code segment
assume cs:code,ds:data
start: mov ax,data
mov ds,ax		;开始程序，没啥实际意义
mov dx,283H	;命令口
mov al,00110100B	;0计数器，读写两个字节，使用方式2，时间常数使用二进制计数
out dx,al		;写入控制命令字寄存器
mov ax,0100H	;设置计数初值，因为是两个字节，所以分两次输入，中间需要将AH赋值给到AL
mov dx,280H	;0号计数器数据口
out dx,al		;先送低字节到0号计数器
mov al,ah		;取高字节送AL
out dx,al		;再送高字节到0号计数器
mov dx,283h	;命令口
mov al,76H	;01110110，即使用1号计数器，同样读写两个字节，使用方式3，二进制计数
out dx,al		;写入新的控制命令字寄存器
mov ax,0010H	;设置计数初值
mov dx,281h	
out dx,al		
mov al,ah		
out dx,al		
code ends		
end start