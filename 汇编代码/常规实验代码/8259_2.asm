DATA SEGMENT
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE,DS:DATA
START:
    MOV AX,DATA
    MOV DS,AX

    ;�޸��ж�����
    CLI;�ȹ��ж�

    ;�����µ��ж�����
    PUSH DS;�����ֳ�
    MOV DX,SEG LIGHT;�ε�ַ
    MOV DS,DX
    MOV DX,OFFSET LIGHT;�ε�ַ
    MOV AL,0BH;ALΪ�ж����ͺ�
    MOV AH,25H;25H�ǹ��ܱ�ţ����������ж���������
    INT 21H
    POP DS

    ;���ж�����/��������
    IN AL,21H
    AND AL,11110111B;����OCW1������IRQ3�ж�
    OUT 21H,AL;д�ж�������OCW1

    MOV CX,5;��ʼ��������
    MOV BL,0;��ʼ��LED0С����

    STI;���ж�
WAIT1:
    ;��PC6����������
    MOV DX,283H
    MOV AL,10000000B;��ʼ����ʽ���PC6����Ϊ����ź�
    OUT DX,AL

    MOV DX,283H
    MOV AL,00001100B;ָ��PC6����͵�ƽ
    OUT DX,AL
    NOP
    NOP;�ÿ�ָ�������ӳ�
    MOV AL,00001101B;ָ��PC6����ߵ�ƽ
    OUT DX,AL
    NOP
    NOP
    CALL DELAY;��ʱ�ӳ���ʹ��LED����˸�ɼ�
    LOOP WAIT1;�ȴ��ж�

    IN AL,21H
    OR AL,00001000B;����OCW1���ر�IRQ3�ж�
    OUT 21H,AL


    MOV AH,4CH
    INT 21H

DELAY PROC;˫��ѭ������ʱ�ӳ���
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

    CLI;���ж�
    MOV AX,DATA
    MOV DS,AX

    MOV DX,283H
    MOV AL,10000000B;��ʼ����ʽ����,A�˿����
    OUT DX,AL

    XOR BL,00000001B;������㣬���һλȡ��������С����
    MOV AL,BL
    MOV DX,280H
    OUT DX,AL;�����С����

    MOV AL,20H ;дOCW2�����жϽ�������EOI
    OUT 20H,AL

    STI;���ж�
    POP CX
    POP AX
    POP DX
    IRET 
LIGHT ENDP

CODE ENDS
END START






