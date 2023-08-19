DATA SEGMENT
    PRINT DB 'TPCA INTERRUPT',0DH,0AH,'$';中断服务程序中要显示在屏幕上的信息
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE,DS:DATA
START:
    MOV AX,DATA
    MOV DS,AX
;第一步：修改中断向量

    CLI;修改中断向量时要关中断

;设置主片MIRQ3中断向量
    MOV DX,SEG INT3;取新中断向量段地址
    MOV DS,DX
    MOV DX,OFFSET INT3;取新中断向量偏移地址
    MOV AL,0BH;AL为中断类型号
    MOV AH,25H;25H是功能编号，代表设置中断向量表项
    INT 21H

;设置从片SIRQ10中断向量
    MOV DX,SEG INT10;取新中断向量段地址
    MOV DS,DX
    MOV DX,OFFSET INT10;取新中断向量偏移地址
    MOV AL,72H;AL为中断类型号
    MOV AH,25H;25H是功能编号，代表设置中断向量表项
    INT 21H 

;第二步：发中断屏蔽/开放命令

;开放主片的IRQ3和IRQ2
    IN AL,21H;读IMR的方法：只要读奇地址端口，读进来的是中断屏蔽寄存器IMR的内容
    AND AL,11110011B;通过与运算开放IRQ3和IRQ2中断 11110011B
    OUT 21H,AL;奇数地址写OCW1，设置屏蔽字

;开放从片的IRQ2
    IN AL,0A1H;读从片基地址端口
    AND AL,11111011B;通过与运算开放IRQ2中断 11111011B
    OUT 0A1H,AL;奇地址写OWC1，设置屏蔽字


;第三步：编写中断服务程序

    MOV CX,10;设置计数初值

LOOP1:;循环等待中断
    STI;开中断
    CMP CX,0
    JNZ LOOP1

    MOV AH,4CH;结束
    INT 21H


INT3 PROC NEAR ;主片的中断服务程序

    ;先保护现场
    PUSH DX
    PUSH AX

    ;在屏幕上显示'TPCA INTERRUPT'
    MOV AX,DATA;注意此处要恢复数据段
    MOV DS,AX
    MOV DX,OFFSET PRINT
    MOV AH,09H;DOS的09号功能：在屏幕上输出一个字符串    DS:DX=字符串地址
    INT 21H

    DEC CX;计数器减1

    CMP CX,0;判断计数器是否减为0
    JNZ NEXT1

    ;如果计数器减到0，关闭中断IRQ3
    IN AL,21H;从奇地址读屏蔽字
    OR AL,00001000B;关闭中断IRQ3 00001000B
    OUT 21H,AL

    ;CPU开中断
    STI

    ;向主片发中断结束命令
NEXT1:   
    MOV AL,20H;OCW2=00100000B
    OUT 20H,AL
    
    ;恢复现场
    POP AX
    POP DX
    ;中断返回
    IRET

INT3 ENDP

INT10 PROC NEAR;从片的中断服务程序

    ;先保护现场
    PUSH DX
    PUSH AX

    ;在屏幕上显示'TPCA INTERRUPT'
    MOV AX,DATA;注意此处要恢复数据段
    MOV DS,AX
    MOV DX,OFFSET PRINT
    MOV AH,09H;DOS的09号功能：在屏幕上输出一个字符串    DS:DX=字符串地址
    INT 21H

    DEC CX;计数器减1

    CMP CX,0;判断计数器是否减为0
    JNZ NEXT2

    ;如果计数器减到0，关闭中断IRQ3
    IN AL,0A1H;从奇地址读屏蔽字
    OR AL,00000100B;关闭中断IRQ2 00000100B
    OUT 21H,AL

    ;CPU开中断
    STI

    ;向从片发中断结束命令
NEXT2:;注意这里要同时向主片和从片发中断结束命令
    MOV AL,20H 
    OUT 0A0H,AL;OCW2=00100000B
    OUT 20H,AL
    
    ;恢复现场
    POP AX
    POP DX
    ;中断返回
    IRET

INT10 ENDP

CODE ENDS
END START




