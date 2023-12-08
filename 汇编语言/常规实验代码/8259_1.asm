DATA SEGMENT
    PRINT DB 'TPCA INTERRUPT',0DH,0AH,'$';�жϷ��������Ҫ��ʾ����Ļ�ϵ���Ϣ
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE,DS:DATA
START:
    MOV AX,DATA
    MOV DS,AX
;��һ�����޸��ж�����

    CLI;�޸��ж�����ʱҪ���ж�

;������ƬMIRQ3�ж�����
    MOV DX,SEG INT3;ȡ���ж������ε�ַ
    MOV DS,DX
    MOV DX,OFFSET INT3;ȡ���ж�����ƫ�Ƶ�ַ
    MOV AL,0BH;ALΪ�ж����ͺ�
    MOV AH,25H;25H�ǹ��ܱ�ţ����������ж���������
    INT 21H

;���ô�ƬSIRQ10�ж�����
    MOV DX,SEG INT10;ȡ���ж������ε�ַ
    MOV DS,DX
    MOV DX,OFFSET INT10;ȡ���ж�����ƫ�Ƶ�ַ
    MOV AL,72H;ALΪ�ж����ͺ�
    MOV AH,25H;25H�ǹ��ܱ�ţ����������ж���������
    INT 21H 

;�ڶ��������ж�����/��������

;������Ƭ��IRQ3��IRQ2
    IN AL,21H;��IMR�ķ�����ֻҪ�����ַ�˿ڣ������������ж����μĴ���IMR������
    AND AL,11110011B;ͨ�������㿪��IRQ3��IRQ2�ж� 11110011B
    OUT 21H,AL;������ַдOCW1������������

;���Ŵ�Ƭ��IRQ2
    IN AL,0A1H;����Ƭ����ַ�˿�
    AND AL,11111011B;ͨ�������㿪��IRQ2�ж� 11111011B
    OUT 0A1H,AL;���ַдOWC1������������


;����������д�жϷ������

    MOV CX,10;���ü�����ֵ

LOOP1:;ѭ���ȴ��ж�
    STI;���ж�
    CMP CX,0
    JNZ LOOP1

    MOV AH,4CH;����
    INT 21H


INT3 PROC NEAR ;��Ƭ���жϷ������

    ;�ȱ����ֳ�
    PUSH DX
    PUSH AX

    ;����Ļ����ʾ'TPCA INTERRUPT'
    MOV AX,DATA;ע��˴�Ҫ�ָ����ݶ�
    MOV DS,AX
    MOV DX,OFFSET PRINT
    MOV AH,09H;DOS��09�Ź��ܣ�����Ļ�����һ���ַ���    DS:DX=�ַ�����ַ
    INT 21H

    DEC CX;��������1

    CMP CX,0;�жϼ������Ƿ��Ϊ0
    JNZ NEXT1

    ;�������������0���ر��ж�IRQ3
    IN AL,21H;�����ַ��������
    OR AL,00001000B;�ر��ж�IRQ3 00001000B
    OUT 21H,AL

    ;CPU���ж�
    STI

    ;����Ƭ���жϽ�������
NEXT1:   
    MOV AL,20H;OCW2=00100000B
    OUT 20H,AL
    
    ;�ָ��ֳ�
    POP AX
    POP DX
    ;�жϷ���
    IRET

INT3 ENDP

INT10 PROC NEAR;��Ƭ���жϷ������

    ;�ȱ����ֳ�
    PUSH DX
    PUSH AX

    ;����Ļ����ʾ'TPCA INTERRUPT'
    MOV AX,DATA;ע��˴�Ҫ�ָ����ݶ�
    MOV DS,AX
    MOV DX,OFFSET PRINT
    MOV AH,09H;DOS��09�Ź��ܣ�����Ļ�����һ���ַ���    DS:DX=�ַ�����ַ
    INT 21H

    DEC CX;��������1

    CMP CX,0;�жϼ������Ƿ��Ϊ0
    JNZ NEXT2

    ;�������������0���ر��ж�IRQ3
    IN AL,0A1H;�����ַ��������
    OR AL,00000100B;�ر��ж�IRQ2 00000100B
    OUT 21H,AL

    ;CPU���ж�
    STI

    ;���Ƭ���жϽ�������
NEXT2:;ע������Ҫͬʱ����Ƭ�ʹ�Ƭ���жϽ�������
    MOV AL,20H 
    OUT 0A0H,AL;OCW2=00100000B
    OUT 20H,AL
    
    ;�ָ��ֳ�
    POP AX
    POP DX
    ;�жϷ���
    IRET

INT10 ENDP

CODE ENDS
END START




