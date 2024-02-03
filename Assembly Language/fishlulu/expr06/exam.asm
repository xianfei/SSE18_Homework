; 试设计一个程序，能够使用键盘中字母键模拟钢琴按键发音。其中，按照字母在键盘中的排列方
; 式，字母键z/x/c/v/b/n/m 分别发出低1—低7 共 7 个低音音符，字母键a/s/d/f/g/h/j 分别发
; 出中1—中7 共7 个中音音符，字母键q/w/e/r/t/y/u 分别发出高1—高7 共7 个高音音符。按ESC
; 键退出程序。当按键按下时持续发音，当按键弹起时停止发音。

; 按键（顺序为键盘布局） mark    break
; q~u                  10h~16h 90h~96h
; a~j                  1eh~24h 9eh~a4h
; z~m                  2ch~32h ach~b2h
; Esc                  01h     81h

; 如要8255 控制8254
; 的2 号定时器驱动扬声器发声，则需要的汇编命令如下：
; OR AL， 00000011B
; OUT 61H，AL
; 关闭扬声器的汇编命令如下：
; AND AL， 11111100B
; OUT 61H，AL
; 同时，定时器8254 的2 号定时器使用1.19MHz 的基准频率，故若要8254 驱动扬声器发出指
; 定频率的声音，则需要向2 号定时器的计数常数寄存器（即I/O 端口42H）存放基准频率除以指定
; 频率的商（即122870H/指定频率），该商需分两次送往I/O 端口42H，先送商的低字节，再送商
; 的高字节。同时，在使用定时器8254 的2 号定时器之前，需要初始化，即往8254 的2 号定时器
; 的控制寄存器（即I/O 端口43H）写控制字0B6H：
; MOV AL， 0B6H
; OUT 43H，AL
; 音符 频率（Hz）
; 低1 130.81
; 中1 261.63
; 高1 523.52
; 低2
; 146.83
; 中2
; 293.66
; 高2
; 587.33
; 低3
; 164.81
; 中3
; 329.63
; 高3
; 659.26
; 低4
; 174.61
; 中4
; 349.23
; 高4
; 698.46
; 低5
; 196.00
; 中5
; 392.00
; 高5
; 783.99
; 低6
; 220.00
; 中6
; 440.00
; 高6
; 880.00
; 低7
; 246.94
; 中7
; 493.88
; 高7
; 987.77

title keyboard piano simulator

data segment
    ;定义音符指定频率
    note_low dw 130,146,164,174,196,220,246
    
    note_med dw 261,293,329,349,392,440,493
    
    note_high dw 523,587,659,698,783,880,987
    
    base_freq dw 0012H,2870H
data ends

stack1 segment
    db 100 dup(0)
stack1 ends

code segment
    assume cs:code, ds:data,ss:stack1
start:
    mov ax, data
    mov ds, ax
    mov ax, stack1
    mov ss, ax
    ;初始化定时器8254
    mov al, 0b6h
    out 43h, al

scan_loop:

    call get_key
    ;判断是否为Esc键
    cmp al, 01h

    je code_end;如果是则跳转到结束程序
    ;如果按键不在指定按键按下范围内则重新扫描
    cmp al, 10h
    jl scan_loop;如果小于10h则一定不是有效输入z跳转到scan_loop重新扫描
    cmp al, 16h
    jg not_high_note;如果大于16h则不是高音跳转到not_high_note
    jmp is_high_note;如果在10h~16h之间则是高音跳转到is_high_note
not_high_note:
    cmp al, 1eh
    jl scan_loop;如果小于1eh则一定不是有效输入跳转到scan_loop重新扫描
    cmp al, 24h
    jg not_med_note;如果大于24h则不是中音跳转到not_med_note
    jmp is_med_note;如果在1eh~24h之间则是中音跳转到is_med_note
not_med_note:
    cmp al, 2ch
    jl scan_loop;如果小于2ch则一定不是有效输入跳转到scan_loop重新扫描
    cmp al, 32h
    jg scan_loop  ; 如果大于32h也不是有效输入，跳转到scan_loop重新扫描
    jmp is_low_note;如果在2ch~32h之间则是低音跳转到is_low_note

is_high_note:
    ; 计算音符索引
    sub al, 10h  ; 从扫描码中减去10h，以得到音符的索引
    mov cl, al   ; 保存音符索引
    lea si, note_high; 将音符表的首地址送入si
    ;计算基准频率/指定频率的商,并分两次送入到I/O端口42H(8254的2号定时器的计数常数寄存器)
    call send_note;计算基准频率/指定频率的商,并分两次送入到I/O端口42H(8254的2号定时器的计数常数寄存器)
    jmp wait_keyup;跳转到wait_keyup等待按键弹起
is_med_note:
    ; 计算音符索引
    sub al, 1eh
    mov cl, al   
    lea si, note_med
    call send_note
    jmp wait_keyup;跳转到wait_keyup等待按键弹起
is_low_note:
    ; 计算音符索引
    sub al, 2ch
    mov cl, al   
    lea si, note_low
    call send_note
    jmp wait_keyup;跳转到wait_keyup等待按键弹起

wait_keyup:
    ;将原来按键扫描码保存到dx中
    mov dl, al
    add dl,80H;将原来按键扫描码加上80h得到按键弹起扫描码
    ; 等待按键弹起
    call get_key
    cmp al,01h
    jz code_end;如果是Esc键则跳转到code_end结束程序
    cmp al, dl
    jnz wait_keyup;如果不是对应按键的弹起扫描码则继续监听

    ;如果按键弹起则终止发声
    and al,11111100B
    out 61H,al  
    jmp scan_loop;跳转到scan_loop重新扫描
code_end:
    call debug
    ;关闭扬声器
    AND AL, 11111100B
    OUT 61H, AL
    ;结束程序
    mov ax, 4c00h
    int 21h

debug proc
    ;输入字符e到控制台 
    mov ah, 2  
    mov dl, 'e'  
    int 21h
    ret      
debug endp
send_note proc
    ; 输入参数：
    ;   - si 寄存器指向音符表（note_low, note_med, note_high),最终指向音符表中的某个音符频率
    ;   - cl 寄存器中包含音符索引
    ;   - ax 寄存器中包含基准频率
    ;将原来寄存器中的值保存到栈中
    push ax
    push bx
    push cx
    push dx
    ;定位到指定音符的频率
    mov ch,0
    shl cl,1;cl*2
    add si,cx;si=si+cl*2
    mov cx,ds:[si];
    ; 计算基准频率/指定频率的商
    mov dx,base_freq
    mov ax,base_freq+2
    div cx
    ; 将商的低字节和高字节分别写入I/O端口42H
    out 42h, al ; 低字节
    mov al, ah  ; 将高字节送入al
    out 42h, al ; 高字节
    ; 开启扬声器
    OR AL, 00000011B
    OUT 61H, AL
    ;函数返回
    pop dx
    pop cx
    pop bx
    pop ax
    ret
send_note endp
get_key proc

    ;获取按键扫描码
    IN AL, 60H
    mov dl, al;将输入的字符备份到dl等待后续wait_keyup使用
    ret

get_key endp
code ends
end start
