bits 64 ;64bitモードのプログラムであることを指定

section .text
global _start

_start:
    mov rax, 1 ; Linuxシステムコールのsys_writeを指定
    mov rdi, 1 ; stdoutを指定
    mov rsi, msg ; msgのアドレスを格納
    mov rdx, length ; lengthを格納
    syscall     ;　上記でシステムコール実行

    mov rax, 60 ; sys_exitを指定
    mov rdi, 0  ; return 0;
    syscall     ; システムコール実行して終了

section .data
    msg db 'Hello, World!! for NASM.', 0x0A   ;文字列データ配列 "0x0a"は改行
    length equ $ - msg ;文字列の長さ
