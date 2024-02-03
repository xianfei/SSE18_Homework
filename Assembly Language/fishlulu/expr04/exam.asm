title add_long_numbers

data segment 
    var1 db 92h, 95h, 12h, 71h, 08h, 27h, 92h, 0c3h ;变量var1保存长度为8个字节的有符号数1
    var2 db 8eh, 3dh, 0c2h, 0abh,7ah, 35h, 0a5h, 09h;变量var2保存长度为8个字节的有符号数2 
    len equ $-var2 ;len计算每个加数所占字节数，len不占用内存 
    sum db len dup(0) ;用于保存运算结果 
data ends 
stack1 segment stack 
;子程序设计必须定义堆栈段 
    dw 40 dup(0) 
stack1 ends

code segment
    assume cs:code,ds:data,ss:stack1
start:
    mov ax,data
    mov ds,ax
    mov ax,stack1
    mov ss,ax
    
    lea si,var1;将两个数的地址压入堆栈
    push si
    lea si,var2
    push si
    push len;将长度压入堆栈
    lea di,sum;将结果的地址压栈
    push di
    call add_long_num;结果存放在sum上,地址存放在di中
    
    ;结束程序
    mov ah,4ch
    int 21h

add_long_num proc near;传入两个有符号长整数进行加法运算
    ;将寄存器保存到栈
    push ax;一次计算一个字节,计算结果保存在这个字节中,ah存放被加数字节,al存放加数字节,cf存放进位,sum结果暂存到ah中
    push bx;存放被加数的地址
    push si;存放加数的地址
    push cx;存放字节长度
    push di;指向结果的地址
    mov bp,sp;保存栈顶地址
    mov di,[bp+12];获取四个参数,sum地址
    mov cx,[bp+14];len
    mov si,[bp+16];var2地址
    mov bx,[bp+18];var1地址
    clc ;清除进位标志
add_lop:

    ;如果有进位,下一位加数加1(此时会报cf=1)
    mov ah,[bx]
    mov al,[si]
    add ah,al ;将两个字节相加,结果保存到ah中
    jc add_carry ;加法运算产生了进位,则将进位加到结果下一位中
add_carry_back:
    adc [di],ah ;将结果保存到sum中,如果有进位,则将进位加到结果的下一位,理论上这步不会产生进位
    jcxz add_end ;如果cx=0,说明已经处理完所有字节,则跳转到add_end,结束加法运算 
    inc si ;指向加数的下一个字节
    inc bx ;指向被加数的下一个字节
    inc di ;指向结果的下一个字节
    loop add_lop ;循环处理下一个字节
    jmp add_end ;循环结束跳转到add_end,结束加法运算

add_carry:
    jcxz add_carry_back;如果cx=0,且发生了进位,则说明溢出,此时要根据情况来判断是否保留进位,暂时不处理
    adc byte ptr [di+1],0 ;如果有进位,则将进位加到结果的下一位
    jmp add_carry_back

add_end:
    ;可能会返回溢出标志,但是不处理
    ;还原主函数寄存器环境
    pop di
    pop cx
    pop si
    pop bx
    pop ax
    ret 8 ;返回时清除栈中的8个字节
add_long_num endp

code ends
end start




