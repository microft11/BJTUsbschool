DATA SEGMENT
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE,DS:DATA
START:
    MOV AX,DATA
    MOV DS,AX

    ;修改中断向量
    CLI;先关中断

    ;设置新的中断向量
    PUSH DS;保护现场
    MOV DX,SEG LIGHT;段地址
    MOV DS,DX
    MOV DX,OFFSET LIGHT;段地址
    MOV AL,0BH;AL为中断类型号
    MOV AH,25H;25H是功能编号，代表设置中断向量表项
    INT 21H
    POP DS

    ;发中断屏蔽/开放命令
    IN AL,21H
    AND AL,11110111B;设置OCW1，开放IRQ3中断
    OUT 21H,AL;写中断屏蔽字OCW1

    MOV CX,5;初始化计数器
    MOV BL,0;初始化LED0小灯泡

    STI;开中断
WAIT1:
    ;让PC6产生上升沿
    MOV DX,283H
    MOV AL,10000000B;初始化方式命令，PC6设置为输出信号
    OUT DX,AL

    MOV DX,283H
    MOV AL,00001100B;指定PC6输出低电平
    OUT DX,AL
    NOP
    NOP;用空指令制造延迟
    MOV AL,00001101B;指定PC6输出高电平
    OUT DX,AL
    NOP
    NOP
    CALL DELAY;延时子程序，使得LED的闪烁可见
    LOOP WAIT1;等待中断

    IN AL,21H
    OR AL,00001000B;设置OCW1，关闭IRQ3中断
    OUT 21H,AL


    MOV AH,4CH
    INT 21H

DELAY PROC;双重循环的延时子程序
    PUSH CX
    MOV CX,01FFH
AGAIN:
    MOV DX,0FFFFH
DELAY1:
    DEC DX
    JNZ DELAY1
    LOOP AGAIN

    POP CX

RET
DELAY ENDP

LIGHT PROC NEAR
    PUSH DX
    PUSH AX
    PUSH CX

    CLI;关中断
    MOV AX,DATA
    MOV DS,AX

    MOV DX,283H
    MOV AL,10000000B;初始化方式命令,A端口输出
    OUT DX,AL

    XOR BL,00000001B;异或运算，最后一位取反，点亮小灯泡
    MOV AL,BL
    MOV DX,280H
    OUT DX,AL;输出到小灯泡

    MOV AL,20H ;写OCW2，送中断结束命令EOI
    OUT 20H,AL

    STI;开中断
    POP CX
    POP AX
    POP DX
    IRET 
LIGHT ENDP

CODE ENDS
END START






