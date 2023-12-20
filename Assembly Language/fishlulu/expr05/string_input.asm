title 根据数字分割输入的字符串并输出
data segment
    ;0AH输入,09H输出
    maxlen db 15;0AH子功能入口参数，指定最大字符数 
    inputlen db 0;0AH子功能出口参数，返回实际输入的字符数 
    str1 db 15 dup(0);0AH子功能的字符串缓存区 
    str2 db 15 dup(0);09H子功能的字符串缓存区 
data ends 

stack1 segment 
    dw 40h dup(0) 
stack1 ends

code segment
    assume cs:code,ds:data,ss:stack1
    start:
        mov ax,data
        mov ds,ax
        mov ax,stack1
        mov ss,ax
        
        ;从键盘读取输入的字符串
        mov ah,0AH
        lea dx,maxlen ;DX指向0AH子功能的入口参数,第一个字节maxlen表示存放的字符串最大
        int 21H
        
        ;输出换行
        mov ah,02H
        mov dl,0DH
        int 21H
        mov dl,0AH
        int 21H

        ;解析str1中的字符串,并按照规则输出
        call process_strin
        ;结束运行
        mov ah,4CH
        int 21H
;定义process_strin过程
process_strin proc near
    push ax
    push cx
    push si
    push di
    
    mov si,0;初始化str1索引
    mov di,0;初始化str2索引
    mov al,byte ptr [inputlen] ;CX=实际输入的字符数
    mov ah,0
    mov cx,ax

read_strin:
        mov al,byte ptr [si+str1] ;AL存储str1中的字符
        ;如果读到的字符是数字(ascii 30H~39H)
        cmp al, '0'      ; 比较是否大于等于 '0'
        jl not_a_digit   ; 如果小于 '0'，说明不是数字
        cmp al, '9'      ; 比较是否小于等于 '9'
        jg not_a_digit   ; 如果大于 '9'，说明不是数字
        ;如果读到的是数字
        ;跳过数字字符的读取,输出当前字符串并换行
        call str_out
        mov di,0
        inc si
        loop read_strin
        jcxz end_read



    not_a_digit:
        mov byte ptr [di+str2],al ;将字符存入str2
        inc si
        inc di
        loop read_strin
        call str_out
    end_read:
        ;结束读取
        pop di
        pop si
        pop cx
        pop ax
        ret
process_strin endp


str_out proc near
    push ax
    push bx
    push dx
    ;在str2存储的字符串结尾加上'$'
    mov al,'$'
    mov byte ptr [di+str2],al
    ;输出字符串
    mov ah,09H
    lea dx,str2
    int 21H
    ;结尾输出换行符
    mov ah,02H
    mov dl,0DH
    int 21H
    mov dl,0AH
    int 21H

    pop dx
    pop bx
    pop ax
    ret
str_out endp

code ends
end start



