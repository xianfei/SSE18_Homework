title count_zero_bits

assume cs:code,ds:data
data segment
arry1 dw 223,4037,5635,8226,11542,14430,45257,811;223=1101 1111 B
len equ $-arry1
res1 db len/2 dup(0)
data ends

code segment
assume cs:code,ds:data
start:
mov ax,data
mov ds,ax
mov cx,len

lea si,arry1;将数组地址送到si
lea di,res1;将结果数组地址送到di
count_loop:
mov bx,[si];将数组元素送到bx
mov ah,0;ah用于存放元素中0的位数
count_bits:
shr bx,1;数组元素右移一位
jnc is_zero;cf数值和右移的时候移除的数字一致,为0则说明最右边的数字为0
jmp next_bit;继续处理下一位
is_zero:
inc ah;增加0的计数
next_bit:
test bx,bx;判断bx是否为0
jnz count_bits;如果不为0，继续处理下一位
mov [di],ah ;将0的计数送到结果数组
add si,2;指向下一个字,一个字大小为2字节
inc di;结果数组指针向下移动
loop count_loop;循环处理下一个数组元素

; 打印 res1 数组中的内容
mov cx, len/2          ; res1 数组的长度
mov di, offset res1         ; 将 DX 设置为 res1 数组的偏移地址
mov ah, 02h        ; DOS功能号：输出字符
print_loop:
mov al,[di]       ; 从 res1 数组中加载一个字节
add al, '0'        ; 将字节转换为字符
mov dl, al
int 21h

inc di             ; 指向下一个 res1 元素
loop print_loop    ; 继续打印下一个字符
;退出程序
mov ah,4ch
int 21h
code ends
end start