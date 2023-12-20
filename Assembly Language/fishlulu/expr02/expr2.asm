assume cs:codesg ds:data,es:table
data segment
db '1975','1976','1977','1978','1979','1980','1981','1982','1983','1984','1985','1986','1987','1988','1989','1990','1991','1992','1993','1994','1995'
;以上是表示 21 年的 21 个字符串
dd 16,22,382,1356,2390,8000,16000,24486,50065,97479,140317,197514,345980,590827,803530,1183000,1843000,2759000,3753000,4649000,5937000
;以上表示 21 年公司总收入的 21 个 dword 型数据
dw 3,7,10,13,28,38,130,220,476,778,1001,1442,2258,2793,4037,5635,8226,11542,14430,15257,17800
;以上是表示 21 年公司雇员人数的 21 个word 型数据
data ends

table segment
; t_YEAR db '0000'
; t_TOTAL_INCOME dd 0
; t_EMPS_NUM dw 0
table_data db 21 dup ('year summ ne ?? ')
table ends


codesg segment
    ; DATA_BYTE dd 1
    ; DATA_WORD dd 2
    ; DATA_DOUBLE dd 4
    ; ptr_YEAR dd 0
    ; ptr_INC dd 0
    ; ptr_EMPS dd 0
    ; ptr_table dd 0

    ; start:
    ; mov cx,21
    ; call table_fill
    ; int 21H

    start:
        ;将段的地址存放在相应的寄存器中
        mov ax,data
        mov ds,ax
        mov ax,table
        mov es,ax

        mov bx,0
        mov di,0
        mov cx,21
        fill_all_year:
        ;将之前存放的cx暂存在栈区中
            push cx
            mov cx,4
            fill_a_year:
                mov ax,[bx]
                mov ah,0
                mov es:[di],al
                inc bx
                inc di
                loop fill_a_year
                pop cx
                add di,0ch
                loop fill_all_year
        mov di,5;移动到income对应的列
        mov cx,21
        fill_all_income:
            push cx
            mov cx,2
            fill_a_income:
                mov ax,[bx]
                mov es:[di]
                add bx,2
                add di,2
                loop fill_a_income
                pop cx,
                add di,0ch
                loop fill_all_income
        mov di,0ah;移动到emps对应的列
        mov cx,21

        fill_all_emps:
            mov ax,[bx]
            mov es:[di],ax
            add bx,2
            add di,10h
        loop fill_all_emps

        mov bx,0
        mov cx,21
        calc_income_avg:
        mov ax,es:5[bx]
        mov dx,es:7[bx]
        div word ptr es:0ah[bx]
        mov es:0dh[bx],ax
        add bx,10h
        loop calc_income_avg
        MOV AX,4C00H        
        INT 21H
        CODE ENDS
END START




    
; table_fill:

;     ;表数据赋值
;     mov ax,YEAR[ptr_YEAR]
;     mov t_YEAR,ax
    
;     mov ax,TOTAL_INCOME[ptr_INC]
;     mov t_TOTAL_INCOME,ax
    
;     mov ax,EMPS_NUM[ptr_EMPS]
;     mov t_EMPS_NUM,ax

;     ;指针偏移
;     mov bx,DATA_BYTE
;     add ptr_YEAR,bx

;     mov bx,DATA_DOUBLE
;     add ptr_INC,bx

;     mov bx,DATA_WORD
;     add ptr_EMPS,bx

;     ;暂存的数据放在表中
;     mov ax,t_YEAR
;     mov table_data[ptr_table],ax
    
;     mov bx,DATA_BYTE
;     add ptr_table,bx

;     mov ax,t_TOTAL_INCOME
;     mov table_data[ptr_table],ax

;     mov bx,DATA_DOUBLE
;     add ptr_table,bx

;     mov ax,t_EMPS_NUM
;     mov table_data[ptr_table]
    
;     mov bx,DATA_WORD
;     add ptr_table,bx

;     loop table_fill
;     ret


